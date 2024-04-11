#include "game.hpp"
#include "bitboardgame.hpp"

class Engine {
  public:
  Engine();
  Direction makeMove(BitboardGame game, int depth);
  private:
  float expecti(BitboardGame game, int depth);
  float max(BitboardGame game, int depth);
  float eval(BitboardGame game);
};