#include <curses.h>
#include <util.h>
#include "strings.h"
#include <games.h>
#include <string.h>
#include <unistd.h>
void do_chatbot(void)
{
  int stage=0; /* stage 0: i'm fine how are you... -> 
                  stage 1: people sometimes make mistakes -> 
                  stage 2: love to. how about global thermonuclear war? -> 
                  stage 3: no lets play global thermonuclear war -> 
                  stage 4: GLOBAL THERMONUCLEAR WAR!!! */
  while(1)
    {
      char buf[513];
      int ret=getnstr(buf, 512);
      usleep(SLEEP_TIME*100);
      if(ret==ERR)
        {
          print_string("\n\n");
          print_string("SORRY?");
          print_string("\n\n");
        }
      else
        {
          allLower(buf);
          remove_punct(buf);
          bool valid=false;
          switch(stage)
            {
            case 0:
              for(int i=0;i<sizeof(stage1_triggers)/sizeof(const char*);++i)
                {
                 if(strcmp(buf, stage1_triggers[i])==0)
                   {
                     print_string("\n\nEXCELLENT. IT'S BEEN A LONG TIME. CAN YOU EXPLAIN\nTHE REMOVAL OF YOUR USER ACCOUNT ON 6/23/73?\n\n");
                     ++stage;
                     valid=true;
                   }
                }
            case 1:
              for(int i=0;i<sizeof(stage2_triggers)/sizeof(const char*);++i)
                {
                  if(strcmp(buf, stage2_triggers[i])==0)
                    {
                      print_string("\n\nYES THEY DO. SHALL WE PLAY A GAME?\n\n");
                      ++stage;
                     valid=true;
                    }
                }
            case 2:
              for(int i=0;i<sizeof(stage3_triggers)/sizeof(const char*);++i)
                {
                  if(strcmp(buf, stage3_triggers[i])==0)
                    { 
                      print_string("\n\nWOULDN'T YOU PREFER A GOOD GAME OF CHESS?\n\n");
                      ++stage;
                     valid=true;
                    }
                }
            case 3:
              for(int i=0;i<sizeof(stage4_triggers)/sizeof(const char*);++i)
                {
                  if(strcmp(buf, stage4_triggers[i])==0)
                    {
                      print_string("\n\nFINE.\n\n");
                      valid=true;
                      usleep(SLEEP_TIME*100);
                      global_thermonuclear_war();
                    }
                }
            } // switch
          if(!valid)
            {
              print_string("\n\n");
              print_string("SORRY?");
              print_string("\n\n");
            }
        } // else
    } // while
}
