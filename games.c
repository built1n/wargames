#include <games.h>
#include <curses.h>
#include <map.h>
#include <util.h>
void global_thermonuclear_war(void)
{
  clear();
  for(int i=0;i<sizeof(map)/sizeof(const char*);++i)
    {
      print_string(map[i]);
      print_string("\n");
    }
  print_string("\nWHICH SIDE DO YOU WANT?\n\n  1.  UNITED STATES\n  2.  SOVIET UNION\n\nPLEASE CHOOSE ONE:  ");
}
