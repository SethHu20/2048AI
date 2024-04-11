#include "game.hpp"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

Game::Game() {
  board = vector<vector<int>>(4, vector<int>(4, 0));
  // srand(time(NULL));
  spawn();
}

Game::Game(vector<vector<int>> board) {
  this->board = board;
  // srand(time(NULL));
}


void Game::render() {
  for (int i = 0; i < 50; i++) cout << "\n";
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4 * 5 + 1; j++) cout << '-';
    cout << "\n";
    for (int j = 0; j < 4; j++) {
      if (board[i][j] == 0 )      cout << "|    ";
      else if (board[i][j] >= 10) cout << "| " <<  board[i][j] << " ";
      else                        cout << "|  " << board[i][j] << " ";
    }
    cout << "|\n";
  }
  for (int j = 0; j < 4 * 5 + 1; j++) cout << '-';
  cout << endl;
}

void Game::shift(Direction dir) {
  vector<int> temp;
  if (dir == UP) {
    for (int j = 0; j < 4; j++) {
      vector<int> col;
      for (int i = 0; i < 4; i++) col.push_back(board[i][j]);
      vector<int> merged = merge(col);
      for (int i = 0; i < 4; i++) board[i][j] = merged[i];
    }
  }
  else if (dir == DOWN) {
    for (int j = 0; j < 4; j++) {
      vector<int> col;
      for (int i = 3; i >= 0; i--) col.push_back(board[i][j]);
      vector<int> merged = merge(col);
      for (int i = 3; i >= 0; i--) board[i][j] = merged[3 - i];
    }
  }
  else if (dir == LEFT) {
    for (int i = 0; i < 4; i++) {
      vector<int> merged = merge(board[i]);
      for (int j = 0; j < 4; j++) board[i][j] = merged[j];
    }
  }
  else if (dir == RIGHT) {
    for (int i = 0; i < 4; i++) {
      vector<int> row;
      for (int j = 3; j >= 0; j--) row.push_back(board[i][j]);
      vector<int> merged = merge(row);
      for (int j = 3; j >= 0; j--) board[i][j] = merged[3 - j];
    }
  }
}

bool Game::gameOver() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (board[i][j] == 0) return false;
      if ((i != 3 && board[i][j] == board[i + 1][j]) || (j != 3 && board[i][j] == board[i][j + 1])) return false;
    }
  }
  return true;
}

void Game::spawn() {
  vector<pair<int, int>> possibleSpawns;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (board[i][j] == 0) possibleSpawns.push_back({i, j});
    }
  }
  int r = rand() % possibleSpawns.size();
  int z = rand() % 10;
  board[possibleSpawns[r].first][possibleSpawns[r].second] = (z == 0) + 1;
}

vector<pair<Game, float>> Game::allPotentialSpawns() {
  vector<pair<Game, float>> res;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (board[i][j] == 0) {
        vector<vector<int>> a = board;
        vector<vector<int>> b = board;
        a[i][j] = 1;
        b[i][j] = 2;
        res.push_back({Game(a), 0.9f});
        res.push_back({Game(b), 0.1f});
      }
    }
  }
  for (int i = 0; i < res.size(); i++) {
    res[i].second /= (res.size() / 2);
  }
  return res;
}

vector<int> Game::merge(vector<int>& row) {
  vector<int> temp;
  bool canMerge = true;
  for (int i = 0; i < 4; i++) {
    if (row[i] != 0) {
      if (canMerge && temp.size() > 0 && temp[temp.size() - 1] == row[i]) {
        temp[temp.size() - 1]++;
        canMerge = false;
      }
      else {
        temp.push_back(row[i]);
        canMerge = true;
      }
    }
  }
  while (temp.size() < 4) temp.push_back(0);
  return temp;
}

bool Game::makeMove(Direction dir, bool spawnAfter) {
  vector<vector<int>> oldBoard = board;
  shift(dir);
  bool changed = false;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (board[i][j] != oldBoard[i][j]) {
        changed = true;
      }
    }
  }
  if (changed) {
    if (spawnAfter) spawn();
    return true;
  }
  return false;
}