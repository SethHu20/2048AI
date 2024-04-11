#include "game.hpp"
#include "bitboardgame.hpp"
#include "engine.hpp"
#include "lookuptables.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <ctime>
using namespace std;

Direction getInput() {
  string input;
  while (true) {
    cin >> input;
    if      (input == "w") return UP;
    else if (input == "a") return LEFT;
    else if (input == "s") return DOWN;
    else if (input == "d") return RIGHT;
  }
}

void playGame() {
  Game state;
  state.render();
  while (!state.gameOver()) {
    Direction dir = getInput();
    if (state.makeMove(dir, true)) state.render();
  }
  cout << "Game over" << endl;
}


void playBitboardGame() {
  BitboardGame state;
  state.render();
  while (!state.gameOver()) {
    Direction dir = getInput();
    if (state.makeMove(dir, true)) state.render();
  }
  cout << "Game over" << endl;
}


int totalGames = 1000000;

void simulateGames() {
  int t = totalGames;
  clock_t start = clock();
  queue<Game> q;
  Game game(vector<vector<int>>(4, vector<int>(4, 0)));
  Direction dirs[] = {UP, DOWN, LEFT, RIGHT};
  for (auto [g, p] : game.allPotentialSpawns()) q.push(g);
  while (!q.empty()) {
    if (t == 0) break;
    t--;
    Game cur = q.front(); q.pop();
    //cur.render();
    for (Direction dir : dirs) {
      Game temp = cur;
      if (temp.makeMove(dir, true)) {
        q.push(temp);
      }
    }
  }

  clock_t end = clock();
  float duration = (float)(end - start) / (float)CLOCKS_PER_SEC;
  cout << duration << endl;
}

void simulateBitboardGames() {
  int t = totalGames;
  clock_t start = clock();
  queue<BitboardGame> q;
  BitboardGame game(0);
  Direction dirs[] = {UP, DOWN, LEFT, RIGHT};
  for (auto [g, p] : game.allPotentialSpawns()) q.push(g);
  while (!q.empty()) {
    if (t == 0) break;
    t--;
    BitboardGame cur = q.front(); q.pop();
    //cur.render();
    for (Direction dir : dirs) {
      BitboardGame temp = cur;
      if (temp.makeMove(dir, true)) {
        q.push(temp);
      }
    }
  }

  clock_t end = clock();
  float duration = (float)(end - start) / (float)CLOCKS_PER_SEC;
  cout << duration << endl;
}

void playEngine() {
  Engine engine;
  BitboardGame game;
  while (!game.gameOver()) {
    Direction dir = engine.makeMove(game, 3);
    if (dir != NONE) game.makeMove(dir, true);
    game.render();
    cout << game.gameOver() << endl;
  }
}

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