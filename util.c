#include <util.h>
#include <curses.h>
#include "strings.h"
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
