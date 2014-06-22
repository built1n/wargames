#include <joshua.h>
#include <curses.h>
#include <stdlib.h>
#define RANDOM_TIME 1
#define SLEEP_TIME 50000
void allLower(char* str)
{
  for(int i=0;str[i];++i)
    {
      str[i]=tolower(str[i]);
    }
}
void print_string(const char* str) /* print string, slowly */
{
  int i=0;
  while(str[i])
    {
      addch(str[i]);
      usleep(SLEEP_TIME);
      beep();
      refresh();
      ++i;
    }
}
void random_stuff(void) /* print random junk on the screen for about 3 seconds */
{
  int maxx, maxy;
  int stop=time(0)+RANDOM_TIME;
  getmaxyx(stdscr, maxy, maxx);
  clear();
  for(;time(0)<=stop;)
    {
      for(int x=0;x<maxx;++x)
        {
          for(int y=0;y<maxy;++y)
            {
              mvaddch(y, x, (rand()%255)+1);
              beep();
            }
        }
      refresh();
    }
  clear();
}
void be_joshua()
{
  initscr();
  clear();
  /*
  start_color();
  init_pair(1, COLOR_BLUE, COLOR_BLACK);
  attron(COLOR_PAIR(1));*/
  char buf[33];
  do {
    print_string("LOGON: ");
    refresh();
    int ret=getnstr(buf, 32);
    allLower(buf);
    usleep(SLEEP_TIME*25);
    if(strcmp(buf, "help logon")==0)
      {
        print_string("\nHELP NOT AVAILABLE\n\n\n");
      }
    else if(strcmp(buf, "help games")==0)
      {
        print_string("\n'GAMES' REFERS TO MODELS, SIMULATIONS AND GAMES\nWHICH HAVE TACTICAL AND STRATEGIC APPLICATIONS.\n\n\n");
      }
    else if(strcmp(buf, "list games")==0)
      {
        print_string("\nFALKEN'S MAZE\nBLACK JACK\nGIN RUMMY\nHEARTS\nBRIDGE\nCHECKERS\nCHESS\nPOKER\nFIGHTER COMBAT\nGUERRILLA ENGAGEMENT\nDESERT WARFARE\nAIR-TO-GROUND ACTIONS\nTHEATERWIDE TACTICAL WARFARE\nTHEATERWIDE BIOTOXIC AND CHEMICAL WARFARE\n\nGLOBAL THERMONUCLEAR WAR\n\n\n");
      }
    else if(ret==ERR || strcmp(buf, "joshua"))
      {
        print_string("\nIDENTIFICATION NOT RECOGNIZED BY SYSTEM\n--CONNECTION TERMINATED--");
        return;
      }
  } while(strcmp(buf, "joshua"));
  random_stuff();
  print_string("GREETINGS, PROFESSOR FALKEN.\n\n");
  refresh();
  getnstr(buf, 32); /* ignore this */
  print_string("\n\nHOW ARE YOU FEELING TODAY?\n\n");
  refresh();
  endwin();
}
