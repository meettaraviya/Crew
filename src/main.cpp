#include "common.h"
#include "game.hpp"
#include "termio.hpp"
#include "ai.hpp"

using namespace std;

int main()
{
      srand(time(NULL));
   for(int j=0; j<100; j++){
      int success_count = 0;
      for(int i=0; i<N_GAMES; i++){
         FreeSelectionGame game(1);
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
      cout << "Gen " << j+1 << ": Won " << success_count << "/" << N_GAMES << " games!" << endl;   
      
      fann_train_data *train_data = fann_create_train_array(CACHE_SIZE, Q_NET_IN, AIPlayer1::q_cache_in[0].data(), Q_NET_OUT, AIPlayer1::q_cache_out[0].data());
      fann_train_on_data(AIPlayer1::q_net, train_data, 10, 1, 1e-6);
      delete train_data;
   }
}