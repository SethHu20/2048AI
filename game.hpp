#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum Direction {
  LEFT,
  RIGHT,
  UP,
  DOWN,
  NONE
};

class Game {
  private:
  void spawn();
  vector<int> merge(vector<int>& row);
  void shift(Direction dir);

  public:
  vector<vector<int>> board;
  Game();
  Game(vector<vector<int>> board);
  vector<pair<Game, float>> allPotentialSpawns();
  bool makeMove(Direction dir, bool spawnAfter);
  bool gameOver();
  void render();
};