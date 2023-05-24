#include "common.h"
#include "game.hpp"
#include "termio.hpp"
#include "ai.hpp"

using namespace std;

int main()
{
   srand(time(NULL));
   SequentialSelectionGame game(10);
   game.players[0] = shared_ptr<Player>(new AIPlayer1(&game, 0));
   game.players[1] = shared_ptr<Player>(new AIPlayer1(&game, 1));
   game.players[2] = shared_ptr<Player>(new AIPlayer1(&game, 2));
   #if N>3
   game.players[3] = shared_ptr<Player>(new AIPlayer1(&game, 3));
   #endif
   #if N>4
   game.players[4] = shared_ptr<Player>(new AIPlayer1(&game, 4));
   #endif
   cout << "Crew with " << N << " players!!!" << endl << endl;
   game.initialize_hands();
   game.task_selection_phase();
   game.trick_phase();
   cout << endl;
   cout << (game.is_successful()? (fg::green + "SUCCESS!!" + fg::dflt):(fg::red + "FAIL!!" + fg::dflt)) <<endl;
}