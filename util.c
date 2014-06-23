#include <util.h>
#include <curses.h>
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
