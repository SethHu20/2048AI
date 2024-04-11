#include "engine.hpp"

Engine::Engine() {}

Direction dirs[] = {UP, DOWN, LEFT, RIGHT};
int depthTable[] = {5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3};
Direction Engine::makeMove(BitboardGame game, int depth) {
  int freeSpaces = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      freeSpaces += game.indexBoard(i, j) == 0;
    }
  }
  
  depth = depthTable[freeSpaces];
  //depth = 1;
  float maxScore = -99999999.0f;
  Direction maxDir = NONE;
  for (Direction dir: dirs) {
    BitboardGame next = game;
    if (!next.makeMove(dir, false)) continue;
    float score = expecti(next, depth - 1);
    if (score > maxScore) {
      maxScore = score;
      maxDir = dir;
    }
  }
  return maxDir;
}

float Engine::expecti(BitboardGame game, int depth) {
  if (depth == 0) return eval(game);
  float expected = 0;
  for (auto [game, prob] : game.allPotentialSpawns()) {
    expected += max(game, depth) * prob;
  }
  return expected;
}


float Engine::max(BitboardGame game, int depth) {
  // cout << depth << endl;
  // game.render();
  

  float maxScore = -9999999.0f;
  for (Direction dir: dirs) {
    BitboardGame next = game;
    if (!next.makeMove(dir, false)) continue;
    float score = expecti(next, depth - 1);
    if (score > maxScore) {
      maxScore = score;
    }
  }
  return maxScore;
}

int maxi(int x, int y) {  
  return x > y ? x : y;
}
float Engine::eval(BitboardGame game) {
  if (game.gameOver()) return -9999999.0f;;
  float res = 0;
  int counter[18] {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int m = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      int curCell = game.indexBoard(i, j);
      if (curCell == 0) res += 10000;
      else {
        counter[game.indexBoard(i, j)]++;
        int a =          17 - (i == 0 ? 17 : abs(curCell - game.indexBoard(i - 1, j)));
        a = maxi(a, 17 - (i == 3 ? 17 : abs(curCell - game.indexBoard(i + 1, j))));
        a = maxi(a, 17 - (j == 0 ? 17 : abs(curCell - game.indexBoard(i, j - 1))));
        a = maxi(a, 17 - (j == 3 ? 17 : abs(curCell - game.indexBoard(i, j + 1))));

        res += a * curCell * curCell * curCell;
        int rowBonus = 1;
        for (int k = 0; k < 3 - i; k++) rowBonus *= curCell * 2;
        res += rowBonus;
      }
      m = maxi(m, curCell);
    }
  }
  for (int i = 1; i < 18; i++) {
    if (counter[i] > 2) {
      res -= counter[i] * 15 * i * i * i;
    }
  }

  res += 10 * m * m * m * m * (game.indexBoard(0, 0) == m);

  return res;
}
