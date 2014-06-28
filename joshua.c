/*
 *   WarGames - a WOPR emulator written in C
 *   Copyright (C) 2014 Franklin Wei
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *   
 *   Contact the author at contact@fwei.tk
 */

#include "chatbot.h"
#include "joshua.h"
#include "strings.h" /* predefined strings */
#include "util.h"

#include <curses.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void cleanup(int signum)
{
  endwin();
  exit(0);
}
void random_stuff(void) /* print random junk on the screen for about 3 seconds */
{
  clear();
  /* credit for this text goes to David Brownlee and Chirs Carter */
  print_string("#45 11456 11009 11893 11972 11315\nPRT CON. 3.4.5. SECTRAN 9.4.3. PORT STAT: SD-345\n\n(311) 699-7305\n");
  clear();
  print_string("\n\n\n\n\n\n\n");
  print_string("(311) 767-8739\n(311) 936-2364\n- PRT. STAT. CRT. DEF.\n||||||||||||||==================================================\nFSKDJLSD: SDSDKJ: SBFJSL: DKSJL: SKFJJ: SDKFJLJ:\nSYSPROC FUNCT READY ALT NET READY\nCPU AUTH RY-345-AX3 SYSCOMP STATUS ALL PORTS ACTIVE\n22/34534.90/3209 11CVB-3904-3490\n(311) 935-2364\n");
  usleep(100000);
  clear();
}
void be_joshua()
{
  initscr();
  clear();
  signal(SIGINT, &cleanup);
  /*
  start_color();
  init_pair(1, COLOR_BLUE, COLOR_BLACK);
  attron(COLOR_PAIR(1));*/
  scrollok(stdscr, true);
  bool gamesPhase=false;
  char buf[33];
  int maxx, maxy;
  getmaxyx(stdscr, maxy, maxx);
  for(int i=0;i<maxx*2;++i)
    {
      print_string(" ");
    }
  do {
    if(!gamesPhase)
      print_string("LOGON: ");
    refresh();
    int ret=getnstr(buf, 32);
    allLower(buf);
    usleep(SLEEP_TIME*100);
    if(strcmp(buf, "help logon")==0 && !gamesPhase)
      {
        print_string("\nHELP NOT AVAILABLE\n\n\n");
      }
    else if(strcmp(buf, "help games")==0)
      {
        print_string("\n'GAMES' REFERS TO MODELS, SIMULATIONS AND GAMES\nWHICH HAVE TACTICAL AND STRATEGIC APPLICATIONS.\n\n\n");
        gamesPhase=true;
      }
    else if(strcmp(buf, "list games")==0 && gamesPhase)
      {
        print_string("\nFALKEN'S MAZE\nBLACK JACK\nGIN RUMMY\nHEARTS\nBRIDGE\nCHECKERS\nCHESS\nPOKER\nFIGHTER COMBAT\nGUERRILLA ENGAGEMENT\nDESERT WARFARE\nAIR-TO-GROUND ACTIONS\nTHEATERWIDE TACTICAL WARFARE\nTHEATERWIDE BIOTOXIC AND CHEMICAL WARFARE\n\nGLOBAL THERMONUCLEAR WAR\n\n\n");
      }
    else if(ret==ERR || strcmp(buf, "joshua") && !gamesPhase)
      {
        print_string("\nIDENTIFICATION NOT RECOGNIZED BY SYSTEM\n--CONNECTION TERMINATED--");
        return;
      }
  } while(strcmp(buf, "joshua") || gamesPhase);
  random_stuff();
  usleep(SLEEP_TIME*100);
  print_string("GREETINGS, PROFESSOR FALKEN.\n\n");
  refresh();
  getnstr(buf, 32);
  allLower(buf);
  remove_punct(buf);
  for(int i=0;i<sizeof(exit_triggers)/sizeof(const char*);++i)
    {
      if(strcmp(buf, exit_triggers[i])==0)
	{
	  print_string("\n\n");
	  print_string(exit_responses[rand()%sizeof(exit_responses)/sizeof(const char*)]);
	  print_string("\n--CONNECTION TERMINATED--");
	  return;
	}
    }
  print_string("\n\nHOW ARE YOU FEELING TODAY?\n\n");
  refresh();
  do_chatbot();
  endwin();
}

