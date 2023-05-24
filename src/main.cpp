#include "common.h"
#include "game.hpp"
#include "termio.hpp"

using namespace std;

int main()
{
   srand(time(NULL));
   SequentialSelectionGame game(10);
   cout << "Crew with " << N << " players!!!" << endl << endl;
   game.task_selection_phase();
   game.trick_phase();
   cout << endl;
   cout << (game.is_successful()? (fg::green + "SUCCESS!!" + fg::dflt):(fg::red + "FAIL!!" + fg::dflt)) <<endl;
}