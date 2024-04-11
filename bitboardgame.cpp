#include "bitboardgame.hpp"
#include <iostream>
#include <vector>
#include <string>

inline int BitboardGame::indexToShift(int i, int j) {
  return (4 * i + j) * 5;
}

int BitboardGame::indexBoard(int i, int j, u128 board) {
  int shift = indexToShift(i, j);
  int res = (board >> shift) & 0b11111;
  return res;
}

int BitboardGame::indexBoard(int i, int j) {
  int shift = indexToShift(i, j);
  int res = (board >> shift) & 0b11111;
  return res;
}

u128 BitboardGame::transpose(u128 board) {
  u128 res = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      int val = indexBoard(j, i, board);
      res |= ((u128)val << (indexToShift(i, j)));
    }
  }
  return res;
}

BitboardGame::BitboardGame() {
  board = 0;
  srand(time(NULL));
  spawn();
}

BitboardGame::BitboardGame(u128 board) {
  this->board = board;
  srand(time(NULL));
}


void BitboardGame::render() {
  for (int i = 0; i < 10; i++) cout << "\n";
  for (int i = 3; i >= 0; i--) {
    for (int j = 0; j < 4 * 5 + 1; j++) cout << '-';
    cout << "\n";
    for (int j = 3; j >= 0; j--) {
      int x = indexBoard(i, j, board);
      if (x == 0 )      cout << "|    ";
      else if (x >= 10) cout << "| " << x << " ";
      else                        cout << "|  " << x << " ";
    }
    cout << "|\n";
  }
  for (int j = 0; j < 4 * 5 + 1; j++) cout << '-';
  cout << endl;
}

void BitboardGame::shift(Direction dir) {
  if (dir == UP) {
    u128 res = 0;
    u128 transposed = transpose(board);
    for (int i = 0; i < 4; i++) {
      u32 row = (transposed >> (i * 20)) & 0b11111111111111111111;
      u32 shifted = Lookup::leftShifts[row];
      res |= ((u128)shifted << (i * 20));
    }
    board = transpose(res);
  }
  else if (dir == DOWN) {
    u128 res = 0;
    u128 transposed = transpose(board);
    for (int i = 0; i < 4; i++) {
      u32 row = (transposed >> (i * 20)) & 0b11111111111111111111;
      u32 shifted = Lookup::rightShifts[row];
      res |= ((u128)shifted << (i * 20));
    }
    board = transpose(res);
  }
  else if (dir == LEFT) {
    u128 res = 0;
    for (int i = 0; i < 4; i++) {
      u32 row = (board >> (i * 20)) & 0b11111111111111111111;
      u32 shifted = Lookup::leftShifts[row];
      res |= ((u128)shifted << (i * 20));
    }
    board = res;
  }
  else if (dir == RIGHT) {
    u128 res = 0;
    for (int i = 0; i < 4; i++) {
      u32 row = (board >> (i * 20)) & 0b11111111111111111111;
      u32 shifted = Lookup::rightShifts[row];
      res |= ((u128)shifted << (i * 20));
    }
    board = res;
  }
}

bool BitboardGame::gameOver() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (indexBoard(i, j, board) == 0) return false;
      if ((i != 3 && indexBoard(i, j, board) == indexBoard(i + 1, j, board)) || (j != 3 && indexBoard(i, j, board) == indexBoard(i, j + 1, board))) return false;
    }
  }
  return true;
}

void BitboardGame::spawn() {
  vector<pair<int, int>> possibleSpawns;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (indexBoard(i, j, board) == 0) possibleSpawns.push_back({i, j});
    }
  }
  int r = rand() % possibleSpawns.size();
  int z = rand() % 10;
  int shift = indexToShift(possibleSpawns[r].first, possibleSpawns[r].second);
  int toSpawn = (z == 0) + 1;
  board |= ((u128)toSpawn << shift);
}

vector<pair<BitboardGame, float>> BitboardGame::allPotentialSpawns() {
  vector<pair<BitboardGame, float>> res;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (this->indexBoard(i, j) == 0) {
        u128 a = board;
        u128 b = board;
        int shift = indexToShift(i, j);
        a |= ((u128)1 << shift);
        b |= ((u128)2 << shift);
        res.push_back({BitboardGame(a), 0.9f});
        res.push_back({BitboardGame(b), 0.1f});
      }
    }
  }
  for (int i = 0; i < res.size(); i++) {
    res[i].second /= (res.size() / 2);
  }
  return res;
}

bool BitboardGame::makeMove(Direction dir, bool spawnAfter) {
  u128 oldBoard = board;
  shift(dir);
  if (oldBoard != board) {
    if (spawnAfter) spawn();
    return true;
  }
  return false;
}