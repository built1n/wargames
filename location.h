/* provide the GTNW with some geographical data to draw the missiles */
enum player_t { USA=1, USSR };
struct location_t {
  const char* name;
  int x;
  int y; /* x,y-coords on the map */
  enum player_t owner;
};
struct location_t world[]={
  /* US cities */
  {"las vegas", 5, 7, USA},
  {"seattle", 3, 2, USA},
  {"new york", 34, 5, USA},
  {"new orleans", 25, 10, USA},
  {"washington", 33, 6, USA},
  {"washington dc", 33, 6, USA},
  {"winston-salem", 30, 7, USA},
  {"san francisco", 1, 6, USA},
  {"chicago", 24, 4, USA},
  {"miami", 33, 11, USA},
  
  /* Soviet cities */
  /* NOTE: These cities are not accurate! */
  {"murmansk", 74, 1, USSR},
  {"moscow", 70, 5, USSR},
  {"minsk", 66, 4, USSR},
  {"chelyabinsk", 64, 8, USSR}
};
