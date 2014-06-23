#include <joshua.h>
#include <chatbot.h>
#include <curses.h>
#include <stdlib.h>
#include <util.h>
#define RANDOM_TIME 1
void random_stuff(void) /* print random junk on the screen for about 3 seconds */
{
  clear();
  /* credit for this text goes to David Brownlee and Chirs Carter */
  print_string("#45 11456 11009 11893 11972 11315\nPRT CON. 3.4.5. SECTRAN 9.4.3. PORT STAT: SD-345\n\n(311) 699-7305\n");
  clear();
  print_string("\n\n\n\n\n\n\n");
  print_string("(311) 767-8739\n(311) 936-2364\n- PRT. STAT. CRT. DEF.\n||||||||||||||==================================================\nFSKDJLSD: SDSDKJ: SBFJSL: DKSJL: SKFJJ: SDKFJLJ:\nSYSPROC FUNCT READY ALT NET READY\nCPU AUTH RY-345-AX3 SYSCOMP STATUS ALL PORTS ACTIVE\n22/34534.90/3209 11CVB-3904-3490\n(311) 935-2364\n");
  usleep(500000);
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
  usleep(SLEEP_TIME*25);
  print_string("GREETINGS, PROFESSOR FALKEN.\n\n");
  refresh();
  getnstr(buf, 32); /* ignore this */
  print_string("\n\nHOW ARE YOU FEELING TODAY?\n\n");
  refresh();
  do_chatbot();
  endwin();
}
