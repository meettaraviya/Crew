#include "common.h"
#include "game.hpp"
#include "termio.hpp"
#include "ai.hpp"

using namespace std;

#define N_GAMES 100

int main()
{
   srand(time(NULL));
   int success_count = 0;
   for(int i=0; i<N_GAMES; i++){
      SequentialSelectionGame game(1);
      game.players[0] = shared_ptr<Player>(new AIPlayer1(&game, 0));
      game.players[1] = shared_ptr<Player>(new AIPlayer1(&game, 1));
      game.players[2] = shared_ptr<Player>(new AIPlayer1(&game, 2));
      #if N>3
      game.players[3] = shared_ptr<Player>(new AIPlayer1(&game, 3));
      #endif
      #if N>4
      game.players[4] = shared_ptr<Player>(new AIPlayer1(&game, 4));
      #endif
      game.initialize_hands();
      game.task_selection_phase();
      game.trick_phase();
      success_count += game.is_successful();
      game.cleanup();
   }
   cout << "Won " << success_count << "/" << N_GAMES << " games!" << endl;   
   
}