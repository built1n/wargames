#include <joshua.h>
#include <curses.h>
#include <stdlib.h>
#define RANDOM_LOOPS 3
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
      refresh();
      ++i;
    }
}
void random_stuff(void) /* print random junk on the screen for about 3 seconds */
{
  int maxx, maxy;
  getmaxyx(stdscr, maxy, maxx);
  for(int i=0;i<RANDOM_LOOPS;++i)
    {
      for(int x=0;x<maxx;++x)
        {
          for(int y=0;y<maxy;++y)
            {
              mvaddch(y, x, (rand()%255)+1);
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
  color_set(COLOR_PAIR(COLOR_BLUE), 0);
  char buf[33];
  do {
    print_string("LOGON: ");
    refresh();
    int ret=getnstr(buf, 32);
    allLower(buf);
    usleep(SLEEP_TIME*25);
    if(ret==ERR || strcmp(buf, "joshua"))
      {
        print_string("Unknown user.\n");
        refresh();
      }
  } while(strcmp(buf, "joshua"));
  random_stuff();
  print_string("GREETINGS, PROFESSOR FALKEN.\n\n");
  refresh();
  getnstr(buf, 32); /* ignore this */
  print_string("\nHOW ARE YOU FEELING TODAY?\n\n");
  refresh();
  endwin();
}
