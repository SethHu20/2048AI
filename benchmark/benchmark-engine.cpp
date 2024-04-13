#include "../engine.hpp"
#include "../lookuptables.hpp"

void benchmarkEngine() {
  Engine engine;
  BitboardGame game;
  timespec base;
  timespec_get(&base, TIME_UTC);
  for (int i = 0; !game.gameOver(); ++i) {
    timespec start;
    timespec_get(&start, TIME_UTC);
    Direction dir = engine.makeMove(game, 3);
    if (dir == NONE) throw "L bozos"; 
    game.makeMove(dir, true);
    timespec end;
    timespec_get(&end, TIME_UTC);
    
    cout << "Step " << i 
         << " " << (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9 << "s "
         << " " << (end.tv_sec - base.tv_sec) + (end.tv_nsec - base.tv_nsec) / 1e9 << "s "
         << ((end.tv_sec - base.tv_sec) + (end.tv_nsec - base.tv_nsec) / 1e9) / (i + 1) << "s/step"
         << endl;
    // game.render();
    // cout << game.gameOver() << endl;
  }
  game.render();
}

int main() {
  Lookup::generateLookupTables();
  srand(333); 

  //playGame();
  //playBitboardGame();
  //simulateGames();
  //simulateBitboardGames();
  // playEngine();
  benchmarkEngine();
}