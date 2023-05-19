#include "common.h"
#include "game.hpp"

using namespace std;

int main()
{
   srand(time(NULL));
   SequentialSelectionGame game(1);
   cout << "Crew with " << N << " players!!!" << endl;
   game.task_selection_phase();
   game.trick_phase();
   cout << (game.is_successful()? "SUCCESS!!":"FAIL!!") <<endl;
}