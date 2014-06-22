#include <util.h>
#include <curses.h>
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
