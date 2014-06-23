/* provide the GTNW with some geographical data to draw the missiles */
struct location_t {
  const char* name;
  int x;
  int y; /* x,y-coords on the map */
};
struct location_t world[]={
  /* US cities */
  {"las vegas", 5, 7},
  {"seattle", 3, 2},
  {"new york", 34, 5},
  {"new orleans", 25, 10},
  {"washington", 33, 6},
  {"washington dc", 33, 6},
  {"winston-salem", 30, 7},
  {"san francisco", 1, 6},
  {"chicago", 24, 4},
  {"miami", 32, 11},
  
  /* Soviet cities */
  /* NOTE: These are not neccessarily correct. I simply eyed them relative to Murmansk */
  {"murmansk", 74, 1},
  {"moscow", 70, 5},
  {"minsk", 66, 4},
};
