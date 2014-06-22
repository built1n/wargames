#include <curses.h>
#include <util.h>
#include <strings.h>
void do_chatbot(void)
{
  while(1)
    {
      char buf[513];
      int ret=getnstr(buf, 512);
      if(ret==ERR)
        {
          print_string("\n\n");
          print_string(cantUnderstand_respond[sizeof(cantUnderstand_respond)/sizeof(const char*)]);
          print_string("\n\n");
        }
    }
}
