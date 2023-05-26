#include "game.hpp"
#include "utils.hpp"
#include "termio.hpp"
#include "task.hpp"
#include "player.hpp"
#include "card.hpp"

Game::Game(){}

void Game::allot_tasks(int diff=1){
    vector<int> task_ids(K);
    for(int i=0; i<task_ids.size(); i++) task_ids[i] = i;
    // random_shuffle(task_ids.begin(), task_ids.end());

    int total_diff = 0, i = 0;
    while(total_diff<diff){
        if(all_tasks[task_ids[i]]->difficulty <= diff - total_diff){
            total_diff += all_tasks[task_ids[i]]->difficulty;
            tasks.push_back(all_tasks[task_ids[i]]);
        }
        i++;
    }
}

void Game::trick_phase(){
    
    int leader = captain;
    #ifdef DBG
    for(int d=0; d<N; d++) cout << "Hand[" << d << "]: " << as_vector(players[d]->hand) << ", "; cout << endl;
    #endif
    for(int i=0; i<T; i++){
        tricks[i] =  shared_ptr<Trick>(new Trick(leader, i));
        for(int j=0; j<N; j++){
            int k = (j+leader)%N;
            Card play = players[k]->play_card(*tricks[i]);
            tricks[i]->add(play);
        }
        players[tricks[i]->winner]->won_cards |= tricks[i]->card_set;
        trick_winners[i] = tricks[i]->winner;
        leader = tricks[i]->winner;
        #ifdef DBG
        cout << *tricks[i] << endl;
        for(int d=0; d<N; d++) cout << "Hand[" << d << "]: " << as_vector(players[d]->hand) << ", "; cout << endl;
        #endif
    }
}

bool Game::is_successful(){
    for(auto t: tasks) if(!t->is_successful(this)) return false;
    return true;
}

void Game::initialize_hands(){
    vector<int> card_ids(40);
    for(int i=0; i<40; i++) card_ids[i] = i;
    random_shuffle(card_ids.begin(), card_ids.end());
    int j = 0;
    for(int i=0; i<N; i++){
        for(; j<(i+1)*T; j++){
            players[i]->hand |= (1LL<<card_ids[j]); 
        }
    }
    if(j!=40) players[0]->hand |= (1LL<<card_ids[39]);

    captain = 0;
    while(!(players[captain]->hand & BLACK_FOUR)) captain++;
}

void Game::cleanup(){
    players[captain] -> cleanup();
    for(auto t: tasks) t->owner = -1;
}

SequentialSelectionGame::SequentialSelectionGame(int diff=5): Game(), difficulty(diff){
    allot_tasks(diff);
}

void SequentialSelectionGame::task_selection_phase(){
    int left = tasks.size(), i = 0;
    while(left>0){
        players[i]->choose_task(tasks);
        left--; i=(i+1)%N;
    }
    #ifdef DBG
    for(int i=0; i<tasks.size(); i++){
        cout << "Task[" << i << "]: <" << tasks[i] << ">," << endl;
    }
    cout << endl;
    #endif
}

FreeSelectionGame::FreeSelectionGame(int diff=5): Game(), difficulty(diff){
    allot_tasks(diff);
}

void FreeSelectionGame::task_selection_phase(){
    players[captain] -> assign_tasks(tasks);
    #ifdef DBG
    for(int i=0; i<tasks.size(); i++){
        cout << "Task[" << i << "]: <" << tasks[i] << ">," << endl;
    }
    cout << endl;
    #endif
}

