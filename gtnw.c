#include "gtnw.h"
#include "location.h"
#include "map.h"
#include "util.h"
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
static bool surrender=false;
static int winner=0; /* on surrender */
static unsigned int max(long long a, long long b)
{
  return a>b?a:b;
}
static void fire_missile(struct location_t* city)
{
  int random=rand()%100;
  int x=city->x, y=city->y;
  if(random>=90) /* crit */
    {
      map[y][x]='!';
      city->population=0;
    }
  else if(random>=60) /* major */
    {
      map[y][x]='X';
      city->population=max((double)city->population*(double).4-400, 0);
    }
  else if(random>=30) /* minor */
    {
      map[y][x]='*';
      city->population=max((double)city->population*(double).6-200, 0);
    }
  else if(random>=10) /* marginal */
    {
      map[y][x]='x';
      city->population=max((double)city->population*(double).8-100, 0);
    }
  else
    {
      map[y][x]='O';
    }
}
static void calc_pops(long long* us_pop, long long* ussr_pop)
{ 
  *us_pop=0;
  *ussr_pop=0;
  /* calculate populations */
  for(int i=0;i<sizeof(world)/sizeof(struct location_t);++i)
    {
      if(world[i].owner==USSR)
	*ussr_pop+=world[i].population;
      else
	*us_pop+=world[i].population;
    }
}
static void print_map_with_pops(void)
{
  for(int i=0;i<sizeof(map)/sizeof(char*);++i)
    {
      print_string(map[i]);
      print_string("\n");
    }
  long long us_pop=0, ussr_pop=0;
  calc_pops(&us_pop, &ussr_pop);
  /* now sort into US and USSR cities */
  struct location_t us_cities[sizeof(world)/sizeof(struct location_t)+1], ussr_cities[sizeof(world)/sizeof(struct location_t)+1];
  int us_back=0, ussr_back=0;
  for(int i=0;i<sizeof(world)/sizeof(struct location_t);++i)
    {
      if(world[i].owner==USSR)
	{
	  ussr_cities[ussr_back]=world[i];
	  ++ussr_back;
	}
      else
	{
	  us_cities[us_back]=world[i];
	  ++us_back;
	}
    }
  if(us_back<ussr_back)
    {
      while(us_back!=ussr_back)
	{
	  us_cities[us_back].print=false;
	  ++us_back;
	}
    }
  else if(us_back>ussr_back)
    {
      while(us_back!=ussr_back)
	{
	  ussr_cities[ussr_back].print=false;
	  ++ussr_back;
	}
    }
  us_cities[us_back].print=true;
  us_cities[us_back].print_name="Total";
  us_cities[us_back].population=us_pop;
  ussr_cities[ussr_back].print=true;
  ussr_cities[ussr_back].print_name="Total";
  ussr_cities[ussr_back].population=ussr_pop;
  ++us_back;
  ++ussr_back;
  print_string("\n\n");
  char buf[512];
  for(int i=0;i<us_back;++i)
    {
      if(us_cities[i].print && ussr_cities[i].print)
	{
          char buf_2[32];
          snprintf(buf_2, 31, "%u", us_cities[i].population);
	  snprintf(buf, 512, "%s: %u %*s: %u", us_cities[i].print_name, us_cities[i].population, 64-strlen(us_cities[i].print_name)-strlen(buf_2), ussr_cities[i].print_name, ussr_cities[i].population);
	}
      else if(us_cities[i].print && !ussr_cities[i].print)
	snprintf(buf, 512, "%s: %u", us_cities[i].print_name, us_cities[i].population);
      else
	{
	  memset(buf, ' ', 255);
	  buf[255]=0;
	  snprintf(buf+64, 512-64, "%s: %u", ussr_cities[i].print_name, ussr_cities[i].population);
	}
      print_string(buf);
      print_string("\n");
    }
}
static void do_first_strike(int side)
{
  attr_on(WA_UNDERLINE, 0);
  print_string("AWAITING FIRST STRIKE COMMAND");
  attr_off(WA_UNDERLINE, 0);
  print_string("\n\n\nPLEASE LIST PRIMARY TARGETS BY\nCITY AND/OR COUNTY NAME:\n\n");
  char target_names[32][129];
  bool good=true;
  int num_targets=0;
  struct location_t *targets[32];
  int num_targets_found=0;
  int max_targets=side==USA?4:6;
  for(int i=0;num_targets_found<max_targets && good;++i)
    {
      getnstr(target_names[i], 128);
      if(strcmp(target_names[i],"")==0)
        {
          good=false;
        }
      else
	{
	  ++num_targets;
	  allLower(target_names[i]);
	  remove_punct(target_names[i]);
	  bool found=false;
	  for(int j=0;j<sizeof(world)/sizeof(struct location_t);++j)
	    {
	      if(strcmp(world[j].name, target_names[i])==0)
		{
		  found=true;
		  if(world[j].owner!=side)
		    {
		      targets[num_targets_found]=&world[j];
		      ++num_targets_found;
		    }
		  else
		    {
		      print_string("\n\nATTEMPTING TO FIRE AT OWN CITY.\nPLEASE CONFIRM (YES OR NO):  ");
		      char response[17];
		      getnstr(response, 16);
		      allLower(response);
		      remove_punct(response);
		      if(strcmp(response, "yes")==0 || strcmp(response, "y")==0)
			{
                          print_string("\n\nATTEMPTING TO FIRE AT OWN CITY.\nARE YOU SURE (YES OR NO):  ");
                          response[0]=0;
                          getnstr(response, 16);
                          allLower(response);
                          remove_punct(response);
                          if(strcmp(response, "yes")==0 || strcmp(response, "y")==0)
                            { 
                              print_string("\nTARGET CONFIRMED.\n\n");
                              targets[num_targets_found]=&world[j];
                              ++num_targets_found;
                            }
			}
		    }
		}
	    }
	  if(!found)
	    {
	      print_string("TARGET NOT FOUND: ");
	      print_string(target_names[i]);
	      print_string("\n");
	    }
	}
    }
  for(int i=0;i<num_targets_found;++i)
    {
      fire_missile(targets[i]);
    }
  clear();
  print_map_with_pops();
}
static void do_missile_launch(int side)
{
  clear();
  attr_on(WA_UNDERLINE, 0);
  print_string("AWAITING STRIKE COMMAND");
  attr_off(WA_UNDERLINE, 0);
  print_string("\n\n\nPLEASE LIST PRIMARY TARGETS BY\nCITY AND/OR COUNTY NAME:\n\n");
  char target_names[32][129];
  bool good=true;
  int num_targets=0;
  struct location_t *targets[32];
  int num_targets_found=0;
  int max_targets=side==USA?4:6;
  for(int i=0;num_targets_found<max_targets && good;++i)
    {
      getnstr(target_names[i], 128);
      if(strcmp(target_names[i],"")==0)
        {
          good=false;
        }
      else
	{
	  ++num_targets;
	  allLower(target_names[i]);
	  remove_punct(target_names[i]);
	  bool found=false;
	  for(int j=0;j<sizeof(world)/sizeof(struct location_t);++j)
	    {
	      if(strcmp(world[j].name, target_names[i])==0)
		{
		  found=true;
		  if(world[j].owner!=side)
		    {
		      targets[num_targets_found]=&world[j];
		      ++num_targets_found;
		    }
		  else
		    {
		      print_string("\n\nATTEMPTING TO FIRE AT OWN CITY.\nPLEASE CONFIRM (YES OR NO):  ");
		      char response[17];
		      getnstr(response, 16);
		      allLower(response);
		      remove_punct(response);
		      if(strcmp(response, "yes")==0 || strcmp(response, "y")==0)
			{
                          print_string("\n\nATTEMPTING TO FIRE AT OWN CITY.\nARE YOU SURE (YES OR NO):  ");
                          response[0]=0;
                          getnstr(response, 16);
                          allLower(response);
                          remove_punct(response);
                          if(strcmp(response, "yes")==0 || strcmp(response, "y")==0)
                            { 
                              print_string("\nTARGET CONFIRMED.\n\n");
                              targets[num_targets_found]=&world[j];
                              ++num_targets_found;
                            }
			}
		    }
		}
	    }
	  if(!found)
	    {
	      print_string("TARGET NOT FOUND: ");
	      print_string(target_names[i]);
	      print_string("\n");
	    }
	}
    }
  for(int i=0;i<num_targets_found;++i)
    {
      fire_missile(targets[i]);
    }
  clear();
  print_map_with_pops();
}
enum ai_strategy_t { AGGRESSIVE, PASSIVE, PEACEFUL };
static void init_ai(int side)
{
  
}
static void do_ai_move(int side)
{
  
}
static void do_peace_talks(int side)
{
}
static void do_human_move(int side)
{
  bool good=false;
  print_string("\nWHAT ACTION DO YOU WISH TO TAKE?\n\n  1. MISSILE LAUNCH\n  2. PEACE TALKS\n  3. SURRENDER\n  4. NOTHING\n\n");
  int move=0;
  while(!good)
    {
      print_string("PLEASE CHOOSE ONE:  ");
      scanw("%u", &move);
      if(move>0 && move<5)
        good=true;
    }
  switch(move)
    {
    case 1:
      do_missile_launch(side);
      break;
    case 2:
      do_peace_talks(side);
      break;
    case 3:
      surrender=true;
      winner=side==1?2:1;
      break;
    case 4:
      break;
    }
}

void global_thermonuclear_war(void)
{
  srand(time(0));
  surrender=false;
  clear();
  for(int i=0;i<sizeof(map)/sizeof(const char*);++i)
    {
      print_string(map[i]);
      print_string("\n");
    }
  print_string("\nWHICH SIDE DO YOU WANT?\n\n  1.  UNITED STATES\n  2.  SOVIET UNION\n\n");
  bool good=false;
  unsigned int side=0;
  while(!good)
    {
      print_string("PLEASE CHOOSE ONE:  ");
      scanw("%u", &side);
      if(side==1 || side==2)
        good=true;
    }
  clear();
  do_first_strike(side);
  long long us_pop=0, ussr_pop;
  calc_pops(&us_pop, &ussr_pop);
  init_ai(side);
  while(us_pop!=0 && ussr_pop!=0 && !surrender)
    {
      do_human_move(side);
      calc_pops(&us_pop, &ussr_pop);
      if(us_pop!=0 && ussr_pop!=0 && !surrender)
        {
          do_ai_move(side);
          calc_pops(&us_pop, &ussr_pop);
        }
    }
  print_string("\n\n");
  if(!surrender)
    {
      if(us_pop==0 && ussr_pop==0)
        {
          print_string("WINNER: NONE\n\n");
        }
      else if(us_pop==0)
        {
          print_string("WINNER: SOVIET UNION\n\n");
        }
      else if(ussr_pop==0)
        {
          print_string("WINNER: UNITED STATES\n\n");
        }
    }
  else
    {
      switch(winner)
        {
        case 1:
          print_string("WINNER: UNITED STATES\n\n");
          break;
        case 2:
          print_string("WINNER: SOVIET UNION\n\n");
          break;
        }
    }
}


