#include "game.hpp"
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
    if (state.makeMove(dir)) state.render();
  }
  cout << "Game over" << endl;
}

int totalGames = 10000;

void simulateGames() {
  queue<Game> q;
  Game game(vector<vector<int>>(4, vector<int>(4, 0)));
  Direction dirs[] = {UP, DOWN, LEFT, RIGHT};
  for (Game g : game.allPotentialSpawns()) q.push(g);
  while (!q.empty()) {
    if (totalGames == 0) break;
    totalGames--;
    Game cur = q.front(); q.pop();
    //cur.render();
    for (Direction dir : dirs) {
      Game temp = cur;
      if (temp.makeMove(dir)) {
        q.push(temp);
      }
    }
  }
}

int main() {
  //playGame();
  clock_t start = clock();
  simulateGames();
  clock_t end = clock();
  float duration = (float)(end - start) / (float)CLOCKS_PER_SEC;
  cout << duration << endl;


  __uint128_t initialFixed = 0;
  __uint128_t initialSuperFixed = 0;
  for (int i = 0; i < 4; i++) {
    initialFixed |= ((__uint128_t)0b11111111 << 64);
  }
  cout << (initialFixed > 0) << endl;
}