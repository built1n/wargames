#include "strings.h"
#include "util.h"

#include <ctype.h>
#include <curses.h>
#include <string.h>
#include <unistd.h>

void allLower(char* str)
{
  for(int i=0;str[i];++i)
    {
      str[i]=tolower(str[i]);
    }
}
void print_string(const char* str) /* print string, slowly */
{
  int window_height;
  int junk;
  getmaxyx(stdscr, window_height, junk);
  int i=0;
  while(str[i])
    {
      addch(str[i]);
      int cursx, cursy;
      getyx(stdscr, cursy, cursx);
      if(cursy==window_height)
	{
	  scroll(stdscr);
	}
      usleep(SLEEP_TIME);
      refresh();
      ++i;
    }
}
void remove_punct(char* buf)
{
  for(int i=0;buf[i];++i)
    {
      for(int j=0;j<sizeof(punctuation_marks)/sizeof(char);++j)
        {
          if(buf[i]==punctuation_marks[j])
            {
              memmove(&buf[i], &buf[i+1], strlen(buf)-i);
            }
        }
    }
}
