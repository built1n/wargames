/* provide the GTNW with some geographical data to draw the missiles */
enum player_t { USA=1, USSR };
struct location_t {
  const char* name;
  int x;
  int y; /* x,y-coords on the map */
  int population; /* around 1980 */
  enum player_t owner;
  bool print;
}; 
struct location_t world[]={
  /* US cities */
  {"las vegas", 5, 7, 150000, USA, true},
  {"seattle", 3, 2, 500000, USA, true},
  {"new york", 34, 5, 7000000, USA, true},
  {"new orleans", 25, 10, 500000, USA, true},
  {"washington dc", 33, 6, 650000, USA, true},
  {"winston-salem", 30, 7, 150000, USA, true},
  {"san francisco", 1, 6, 700000, USA, true},
  {"chicago", 24, 4, 3000000, USA, true},
  {"miami", 33, 11, 1000000, USA, true},
  
  /* Soviet cities */
  /* NOTE: These cities are not accurate! */
  {"murmansk", 74, 1, 500000, USSR, true},
  {"moscow", 70, 5, 8000000, USSR, true},
  {"minsk", 66, 4, 1500000, USSR, true},
  {"chelyabinsk", 64, 8, 1250000, USSR, true}
};
