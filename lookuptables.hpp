#pragma once
#include "game.hpp"
#include <vector>
#include <stdint.h>
using namespace std;

class Lookup {
  public:
  static void generateLookupTables();
  static vector<uint32_t> leftShifts;
  static vector<uint32_t> rightShifts;
  static void test();
};