/* provide the GTNW with some geographical data to draw the missiles */
enum player_t { USA=1, USSR };
struct location_t {
  const char* name;
  int x;
  int y; /* x,y-coords on the map */
  int population; /* around 1980 */
  enum player_t owner;
}; 
struct location_t world[]={
  /* US cities */
  {"las vegas", 5, 7, 150000, USA},
  {"seattle", 3, 2, 0, 500000, USA},
  {"new york", 34, 5, 7000000, USA},
  {"new orleans", 25, 10, 500000, USA},
  {"washington dc", 33, 6, 650000, USA},
  {"winston-salem", 30, 7, 150000, USA},
  {"san francisco", 1, 6, 700000, USA},
  {"chicago", 24, 4, 3000000, USA},
  {"miami", 33, 11, 1000000, USA},
  
  /* Soviet cities */
  /* NOTE: These cities are not accurate! */
  {"murmansk", 74, 1, 500000, USSR},
  {"moscow", 70, 5, 8000000, USSR},
  {"minsk", 66, 4, 1500000, USSR},
  {"chelyabinsk", 64, 8, 1250000, USSR}
};
