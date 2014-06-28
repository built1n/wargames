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

#include <stdbool.h>
/* provide the GTNW with some geographical data to draw the missiles with */
enum player_t { USA=1, USSR };
struct location_t {
  const char* name;
  int x;
  int y; /* x,y-coords on the map */
  long long population; /* around 1980 */
  enum player_t owner;
  bool print;
  const char* print_name;
}; 
struct location_t world[]={
  /* US cities */
  {"las vegas", 5, 7, 150000, USA, true, "LAS VEGAS"},
  {"seattle", 3, 2, 500000, USA, true, "SEATTLE"},
  {"new york", 34, 5, 7000000, USA, true, "NEW YORK CITY"},
  {"new orleans", 25, 10, 500000, USA, true, "NEW ORLEANS"},
  {"washington dc", 33, 6, 650000, USA, true, "WASHINGTON, DC"},
  {"winston-salem", 30, 7, 150000, USA, true, "WINSTON-SALEM"},
  {"san francisco", 1, 6, 700000, USA, true, "SAN FRANCISCO"},
  {"chicago", 24, 4, 3000000, USA, true, "CHICAGO"},
  {"miami", 33, 11, 1000000, USA, true, "MIAMI"},
  
  /* Soviet cities */
  /* NOTE: These cities are not accurate! */
  {"murmansk", 74, 1, 500000, USSR, true,"MURMANSK"},
  {"moscow", 70, 5, 8000000, USSR, true, "MOSCOW"},
  {"minsk", 66, 4, 1500000, USSR, true, "MINSK"},
  {"chelyabinsk", 64, 8, 1250000, USSR, true, "CHELYABINSK"}
};
