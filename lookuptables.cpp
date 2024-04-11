#include "game.hpp"
#include "lookuptables.hpp"
#include <vector>
#include <algorithm>
#include <stdint.h>
using namespace std;

vector<int> merge(vector<int>& row) {
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


vector<int> bitsToVector(uint32_t bits) {
  vector<int> res(4);
  for (int i = 0; i < 4; i++) {
    res[3 - i] = bits & 0b11111;
    bits >>= 5;
  }
  return res;
}

uint32_t vectorToBits(vector<int>& row) {
  uint32_t res = 0;
  for (int i = 0; i < 4; i++) {
    res |= (row[i] << ((3 - i) * 5));
  }
  return res;
}

void Lookup::generateLookupTables() {
  vector<uint32_t> left(1 << 20, 0);
  cout << "awa" << endl;
  for (uint32_t i = 0; i < 1 << 20; i++) {
    vector<int> row = bitsToVector(i);
    vector<int> merged = merge(row);
    uint32_t bits = vectorToBits(merged);
    left[i] = bits;
  }
  leftShifts = left;




  vector<uint32_t> right(1 << 20, 0);
  for (uint32_t i = 0; i < 1 << 20; i++) {
    vector<int> row = bitsToVector(i);
    reverse(row.begin(), row.end());
    vector<int> merged = merge(row);
    reverse(merged.begin(), merged.end());
    uint32_t bits = vectorToBits(merged);
    right[i] = bits;
  }
  rightShifts = right;
}

vector<uint32_t> Lookup::leftShifts;
vector<uint32_t> Lookup::rightShifts;

void Lookup::test() {
  vector<int> test1 = {1, 1, 2, 3};
  vector<int> test2 = {1, 0, 0, 1};
  vector<int> test3 = {0, 2, 0, 17};
  
  vector<vector<int>> tests = {test1, test2, test3};
  for (int t = 0; t < 3; t++) {
    uint32_t bits = vectorToBits(tests[t]);
    vector<int> vec = bitsToVector(bits);
    reverse(vec.begin(), vec.end());
    vector<int> res = merge(vec);
    reverse(res.begin(), res.end());
    for (int i = 0; i < 4; i++) cout << res[i] << " ";
    cout << endl;
  }
}