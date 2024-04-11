#pragma once
#include "lookuptables.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <stdint.h>
#define u128 __uint128_t
#define u32 uint32_t
using namespace std;

class BitboardGame {
  private:
  __uint128_t board;
  void spawn();
  void shift(Direction dir);
  inline int indexToShift(int i, int j);
  int indexBoard(int i, int j, u128 board);
  u128 transpose(u128 board);
  

  public:
  BitboardGame();
  BitboardGame(__uint128_t board);
  int indexBoard(int i, int j);
  vector<pair<BitboardGame, float>> allPotentialSpawns();
  bool makeMove(Direction dir, bool spawnAfter);
  bool gameOver();
  void render();
};