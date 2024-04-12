#include <bits/stdc++.h>

using namespace std;

#define u128 unsigned __int128

inline int indexToShift(int i, int j) {
  return (4 * i + j) * 5;
}

int indexBoard(int i, int j, u128 board) {
  int shift = indexToShift(i, j);
  int res = (board >> shift) & 0b11111;
  return res;
}

u128 transpose(u128 board) {
  u128 res = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      int val = indexBoard(j, i, board);
      res |= ((u128)val << (indexToShift(i, j)));
    }
  }
  
  return res;
}

const u128 tpMat1 = ((u128) 0b1111100000000000 << 64) | 0b0000000001111100000000000000000000111110000000000000000000011111;
const u128 tpMat2 = ((u128) 0b0000011111000000 << 64) | 0b0000000000000011111000000000000000000001111100000000000000000000;
const u128 tpMat3 = ((u128) 0b0000000000000000 << 64) | 0b0000111110000000000000000000011111000000000000000000001111100000;
const u128 tpMat4 = ((u128) 0b0000000000111110 << 64) | 0b0000000000000000000111110000000000000000000000000000000000000000;
const u128 tpMat5 = ((u128) 0b0000000000000000 << 64) | 0b0000000000000000000000000000000000000000000011111000000000000000;
const u128 tpMat6 = ((u128) 0b0000000000000000 << 64) | 0b0000000000000000000000001111100000000000000000000111110000000000;
const u128 tpMat7 = ((u128) 0b0000000000000001 << 64) | 0b1111000000000000000000000000000000000000000000000000000000000000;

u128 fastTranspose(u128 board) {
  u128 res = 
     (board & tpMat1)
  | ((board & tpMat2) >> (3 * 5))
  | ((board & tpMat3) << (3 * 5))
  | ((board & tpMat4) >> (6 * 5))
  | ((board & tpMat5) << (9 * 5))
  | ((board & tpMat6) << (6 * 5))
  | ((board & tpMat7) >> (9 * 5));
  
  return res;
}

int main() {
    int n = 1e7;
    vector<u128> boards(n);
    for (int i = 0; i < n; i++) {
        boards[i] = ((u128) rand() << (5 * 16 - 64)) ^ ((u128) rand() << 32) | rand();
    }

    float totalDuration1 = 0;
    float totalDuration2 = 0;
    timespec start, end;
    int k = 0;

    timespec_get(&start, TIME_UTC);
    for (size_t i = 0; i < n; i++) {
        u128 board = boards[i];
        u128 res1 = transpose(board);
        // To prevent O3 flag realising res1 is not used
        k += res1;
    }
    timespec_get(&end, TIME_UTC);
    totalDuration1 = (float)(end.tv_sec - start.tv_sec) + (float)(end.tv_nsec - start.tv_nsec) / 1e9;

    timespec_get(&start, TIME_UTC);
    for (size_t i = 0; i < n; i++) {
        u128 board = boards[i];
        u128 res2 = fastTranspose(board);
        // To prevent O3 flag realising res1 is not used
        k += res2;
    }
    timespec_get(&end, TIME_UTC);
    totalDuration2 = (float)(end.tv_sec - start.tv_sec) + (float)(end.tv_nsec - start.tv_nsec) / 1e9;

    cout << "Total duration for transpose: " << totalDuration1 << "s" << endl;
    cout << "Total duration for fastTranspose: " << totalDuration2 << "s" << endl;
    cout << "k: " << k << endl;
}