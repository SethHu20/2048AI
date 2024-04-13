#include <vector>
#include <algorithm>
#include <stdint.h>
#include <ctime>
#include <iostream>
#include <bitset>
using namespace std;

constexpr vector<int> merge(vector<int>& row) {
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

constexpr uint32_t bitmaskReverse(uint32_t x) {
  return (x & 0b11111000000000000000) >> 15
       | (x & 0b00000111110000000000) >> 5
       | (x & 0b00000000001111100000) << 5
       | (x & 0b00000000000000011111) << 15;
}

inline constexpr uint32_t bitMerge(uint32_t row) {
  uint32_t temp = 0;
  uint32_t tempSize = 0;
  bool canMerge = true;
  for (int i = 0; i < 4; i++) {
    uint32_t val = (row >> (i * 5)) & 0b11111;
    if (val != 0) {
      if (canMerge && ((temp & 0b11111) == val)) {
        temp = (temp & (0xffffffff ^ 0b11111)) | ((val + 1) & 0b11111);
        canMerge = false;
      }
      else {
        temp = (temp << 5) | val;
        tempSize++;
        canMerge = true;
      }
    }
  }
  while (tempSize < 4) {
    temp = (temp << 5);
    tempSize++;
  }
  return temp;
}


constexpr vector<int> bitsToVector(uint32_t bits) {
  vector<int> res(4);
  for (int i = 0; i < 4; i++) {
    res[3 - i] = bits & 0b11111;
    bits >>= 5;
  }
  return res;
}

constexpr uint32_t vectorToBits(vector<int>& row) {
  uint32_t res = 0;
  for (int i = 0; i < 4; i++) {
    res |= ((row[i] & 0b11111) << ((3 - i) * 5));
  }
  return res;
}

vector<uint32_t> generateLeftLookupTables() {
  vector<uint32_t> left(1 << 20, 0);
  for (uint32_t i = 0; i < 1 << 20; i++) {
    vector<int> row = bitsToVector(i);
    vector<int> merged = merge(row);
    uint32_t bits = vectorToBits(merged);
    left[i] = bits;
  }
  return left;
}



vector<uint32_t> generateRightLookupTables() {
  vector<uint32_t> right(1 << 20, 0);
  for (uint32_t i = 0; i < 1 << 20; i++) {
    vector<int> row = bitsToVector(i);
    reverse(row.begin(), row.end());
    vector<int> merged = merge(row);
    reverse(merged.begin(), merged.end());
    uint32_t bits = vectorToBits(merged);
    right[i] = bits;
  }
  return right;
}

pair<vector<uint32_t>, vector<uint32_t>> fastGenerateLookupTables() {
  vector<uint32_t> left(1 << 20);
  vector<uint32_t> right(1 << 20);
  for(uint32_t i = 0; i < 1 << 20; i++) {
    uint32_t bits = bitMerge(i);
    left[bitmaskReverse(i)] = bits;
    right[i] = bitmaskReverse(bits);
  }
  return {left, right};
}


int main() {
  timespec start, end;
  timespec_get(&start, TIME_UTC);
  vector<uint32_t> leftShifts = std::move(generateLeftLookupTables());
  vector<uint32_t> rightShifts = std::move(generateRightLookupTables());
  timespec_get(&end, TIME_UTC);
  cout << "Duration: " << (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9 << endl;

  timespec_get(&start, TIME_UTC);
  pair<vector<uint32_t>, vector<uint32_t>> lookupTables = std::move(fastGenerateLookupTables());
  vector<uint32_t> leftShifts2 = std::move(lookupTables.first);
  vector<uint32_t> rightShifts2 = std::move(lookupTables.second);
  timespec_get(&end, TIME_UTC);
  cout << "Duration: " << (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9 << endl;

  for (int i = 0; i < 1 << 20; i++) {
    if (leftShifts[i] != leftShifts2[i] || rightShifts[i] != rightShifts2[i]) {
      cout << "Mismatch at " << i << endl;
      cout << bitset<20>(i) << endl;
      cout << bitset<20>(leftShifts[i]) << endl;
      cout << bitset<20>(leftShifts2[i]) << endl;
      cout << bitset<20>(bitmaskReverse(i)) << endl;
      cout << bitset<20>(rightShifts[i]) << endl;
      cout << bitset<20>(rightShifts2[i]) << endl;
      return 1;
    }
    // if (leftShifts[i] != bitmaskReverse(rightShifts[bitmaskReverse(i)])) {
    //   cout << "Mismatch at " << i << endl;
    //   cout << bitset<20>(i) << endl;
    //   cout << bitset<20>(leftShifts[i]) << endl;
    //   cout << bitset<20>(bitmaskReverse(i)) << endl;
    //   cout << bitset<20>(rightShifts[bitmaskReverse(i)]) << endl;
    //   return 1;
    // }
  }
  return 0;
}