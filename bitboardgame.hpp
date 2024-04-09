// #include <iostream>
// #include <vector>
// #include <string>
// using namespace std;

// enum Direction {
//   LEFT,
//   RIGHT,
//   UP,
//   DOWN
// };

// class BitboardGame {
//   private:
//   __uint128_t board;
//   void spawn();
//   void shift(Direction dir);
//   inline int indexToShift(int i, int j);
//   inline int indexBoard(int i, int j);

//   public:
//   BitboardGame();
//   BitboardGame(__uint128_t board);
//   vector<__uint128_t> allPotentialSpawns();
//   bool makeMove(Direction dir);
//   bool gameOver();
//   void render();
// };