#include <games.h>
#include <curses.h>
#include <map.h>
#include <util.h>
#include <location.h>
#include <unistd.h>
#include <string.h>
static int max(int a, int b)
{
  if(a>b)
    return a;
  else
    return b;
}
static void print_map_with_pops(void)
{
  for(int i=0;i<sizeof(map)/sizeof(char*);++i)
    {
      print_string(map[i]);
      print_string("\n");
    }
  unsigned int us_pop=0, ussr_pop=0;
  /* calculate populations */
  for(int i=0;i<sizeof(world)/sizeof(struct location_t);++i)
    {
      if(world[i].owner==USSR)
	ussr_pop+=world[i].population;
      else
	us_pop+=world[i].population;
    }
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
	  snprintf(buf, 512, "%s: %d %*s: %d", us_cities[i].print_name, us_cities[i].population, 64-strlen(us_cities[i].print_name), ussr_cities[i].print_name, ussr_cities[i].population);
	}
      else if(us_cities[i].print && !ussr_cities[i].print)
	snprintf(buf, 512, "%s: %d", us_cities[i].print_name, us_cities[i].population);
      else
	{
	  memset(buf, ' ', 255);
	  buf[255]=0;
	  snprintf(buf+64, 512-64, "%s: %d", ussr_cities[i].print_name, ussr_cities[i].population);
	}
      print_string(buf);
      print_string("\n");
    }
}
void global_thermonuclear_war(void)
{
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
  attr_on(WA_UNDERLINE, 0);
  print_string("AWAITING FIRST STRIKE COMMAND");
  attr_off(WA_UNDERLINE, 0);
  print_string("\n\n\nPLEASE LIST PRIMARY TARGETS BY\nCITY AND/OR COUNTY NAME:\n\n");
  char target_names[32][129];
  good=true;
  int num_targets=0;
  struct location_t targets[32];
  int num_targets_found=0;
  for(int i=0;i<32 && good;++i)
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
		      targets[num_targets_found]=world[j];
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
                              targets[num_targets_found]=world[j];
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
      map[targets[i].y][targets[i].x]='X';
    }
  clear();
  print_map_with_pops();
}
