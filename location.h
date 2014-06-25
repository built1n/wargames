/* provide the GTNW with some geographical data to draw the missiles */
enum player_t { USA=1, USSR };
struct location_t {
  const char* name;
  int x;
  int y; /* x,y-coords on the map */
  unsigned int population; /* around 1980 */
  enum player_t owner;
  bool print;
  const char* print_name;
}; 
struct location_t world[]={
  /* US cities */
  {"las vegas", 5, 7, 150000, USA, true, "Las Vegas"},
  {"seattle", 3, 2, 500000, USA, true, "Seattle"},
  {"new york", 34, 5, 7000000, USA, true, "New York City"},
  {"new orleans", 25, 10, 500000, USA, true, "New Orleans"},
  {"washington dc", 33, 6, 650000, USA, true, "Washington, DC"},
  {"winston-salem", 30, 7, 150000, USA, true, "Winston-Salem"},
  {"san francisco", 1, 6, 700000, USA, true, "San Francisco"},
  {"chicago", 24, 4, 3000000, USA, true, "Chicago"},
  {"miami", 33, 11, 1000000, USA, true, "Miami"},
  
  /* Soviet cities */
  /* NOTE: These cities are not accurate! */
  {"murmansk", 74, 1, 500000, USSR, true,"Murmansk"},
  {"moscow", 70, 5, 8000000, USSR, true, "Moscow"},
  {"minsk", 66, 4, 1500000, USSR, true, "Minsk"},
  {"chelyabinsk", 64, 8, 1250000, USSR, true, "Chelyabinsk"}
};
