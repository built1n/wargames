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

#include "strings.h"

const char* stage1_triggers[] = {
  "im fine",
  "im fine how are you",
  "i am fine",
  "i am fine how are you",
  "how are you"
};
const char* stage2_triggers[] = {
  "people sometimes make mistakes",
  "sometimes people make mistakes",
  "mistakes are make by people sometimes",
  "people make mistakes sometimes",
  "people make mistakes",
  "people sometimes make mistak" /* this is no typo. in the movie, at one scene, it appears like this */
};
const char* stage3_triggers[] = {
  "love to how about global thermonuclear war",
  "love to",
  "how about global thermonuclear war",
  "global thermonuclear war"
};
const char* stage4_triggers[] = {
  "no lets play global thermonuclear war",
  "no lets play global thermonuclear war instead",
  "later lets play global thermonuclear war",
  "later lets play global thermonuclear war instead",
  "later",
  "lets play global thermonuclear war",
  "global thermonuclear war is better"
};
const char* tictactoe_triggers[] = {
  "lets play tic tac toe",
  "lets play tic-tac-toe",
  "lets play tictactoe",
  "how about tic-tac-toe",
  "how about tic tac toe",
  "play tic-tac-toe",
  "play tictactoe",
  "play tic tac toe"
};
const char* exit_triggers[] = {
  "goodbye",
  "good-bye",
  "bye",
  "bye-bye",
  "see you later",
  "logout"
};
const char* exit_responses[] = {
  "GOODBYE.",
  "BYE.",
  "BYE-BYE.",
  "GOOD-BYE.",
};
const char* greetings_triggers[] = {
  "hi", 
  "hello", 
  "hiya", 
  "sup", 
  "whats up", 
  "how are you", 
  "hey", 
  "how are you doing"
};
const char* greetings_responses[] = {
  "HELLO.",
  "HI.",
  "GREETINGS.",
  "HELLO.",
  "HELLO."
};
const char punctuation_marks[] = {
  '\'', '?', '.', '/', '`', '~', ',', '+', '!'
};

