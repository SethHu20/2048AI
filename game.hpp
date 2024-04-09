#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum Direction {
  LEFT,
  RIGHT,
  UP,
  DOWN
};

class Game {
  private:
  vector<vector<int>> board;
  void spawn();
  vector<int> merge(vector<int>& row);
  void shift(Direction dir);

  public:
  Game();
  Game(vector<vector<int>> board);
  vector<Game> allPotentialSpawns();
  bool makeMove(Direction dir);
  bool gameOver();
  void render();
};