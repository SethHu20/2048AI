// #include "bitboardgame.hpp"
// #include <iostream>
// #include <vector>
// #include <string>
// using namespace std;

// #define u128 __uint128_t


// inline int BitboardGame::indexToShift(int i, int j) {
//   return (15 - (4 * i + j)) * 8;
// }

// inline int BitboardGame::indexBoard(int i, int j) {
//   int shift = indexToShift(i, j);
//   int res = (board >> shift) & 0b11111111;
//   return res;
// }

// BitboardGame::BitboardGame() {
//   board = 0;
//   srand(time(NULL));
//   spawn();
// }

// BitboardGame::BitboardGame(u128 board) {
//   this->board = board;
//   srand(time(NULL));
// }


// void BitboardGame::render() {
//   for (int i = 0; i < 50; i++) cout << "\n";
//   for (int i = 0; i < 4; i++) {
//     for (int j = 0; j < 4 * 5 + 1; j++) cout << '-';
//     cout << "\n";
//     for (int j = 0; j < 4; j++) {
//       int x = indexBoard(i, j);
//       if (x == 0 )      cout << "|    ";
//       else if (x >= 10) cout << "| " << x << " ";
//       else                        cout << "|  " << x << " ";
//     }
//     cout << "|\n";
//   }
//   for (int j = 0; j < 4 * 5 + 1; j++) cout << '-';
//   cout << endl;
// }

// void BitboardGame::shift(Direction dir) {
//   vector<int> temp;
//   if (dir == UP) {
//   }
//   else if (dir == DOWN) {
//   }
//   else if (dir == LEFT) {
//     u128 fixed = ~(u128)0;
//     u128 superFixed = ~(u128)0;
//     for (int i = 0; i < 4; i++) {
//       fixed &= ~((u128)0b11111111 << indexToShift(i, 0));
//     }
//     for (int i = 0; i < 4; i++) { //we need to shift at most 4 times
//       u128 toShift = board & fixed;
//       u128 shifted = toShift << 8;
//       //00 11 11 11 (fixed)
//       //11 11 11 11 (superFixed)
//       //01 01 00 10 (toShift)
//       //01 00 10 00 (shifted)
//       //toShift & shifted
//       //01 00 00 00 //how the fuck do we turn this 01 into 10
//     }
//   }
//   else if (dir == RIGHT) {
//   }
// }

// bool BitboardGame::gameOver() {
//   for (int i = 0; i < 4; i++) {
//     for (int j = 0; j < 4; j++) {
//       if (board[i][j] == 0) return false;
//       if ((i != 3 && board[i][j] == board[i + 1][j]) || (j != 3 && board[i][j] == board[i][j + 1])) return false;
//     }
//   }
//   return true;
// }

// void BitboardGame::spawn() {
//   vector<pair<int, int>> possibleSpawns;
//   for (int i = 0; i < 4; i++) {
//     for (int j = 0; j < 4; j++) {
//       if (board[i][j] == 0) possibleSpawns.push_back({i, j});
//     }
//   }
//   int r = rand() % possibleSpawns.size();
//   board[possibleSpawns[r].first][possibleSpawns[r].second] = rand() % 2 + 1;
// }

// vector<BitboardGame> BitboardGame::allPotentialSpawns() {
//   vector<Game> res;
//   for (int i = 0; i < 4; i++) {
//     for (int j = 0; j < 4; j++) {
//       if (board[i][j] == 0) {
//         vector<vector<int>> a = this->board;
//         vector<vector<int>> b = this->board;
//         a[i][j] = 1;
//         b[i][j] = 2;
//         res.push_back(Game(a));
//         res.push_back(Game(b));
//       }
//     }
//   }
//   return res;
// }

// bool BitboardGame::makeMove(Direction dir) {
//   vector<vector<int>> oldBoard = board;
//   shift(dir);
//   bool changed = false;
//   for (int i = 0; i < 4; i++) {
//     for (int j = 0; j < 4; j++) {
//       if (board[i][j] != oldBoard[i][j]) {
//         changed = true;
//       }
//     }
//   }
//   if (changed) {
//     spawn();
//     return true;
//   }
//   return false;

// }
