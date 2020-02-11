//
//  playMove.cpp
//  TicTacTo
//
//  Updated by Tarek Abdelrahman on 2019-06-07.
//  Created by Tarek Abdelrahman on 2018-05-15.
//  Copyright © 2018-2019 Tarek Abdelrahman. All rights reserved.
//
#include "tictactoe.h"
#include "gameState.h"
using namespace std;

void playMove(gameState& game_state) {
    int x,y;
    int turn = -1;

    x = game_state.get_clickedRow();
    y = game_state.get_clickedColumn();
    
      
    if(game_state.get_gameBoard(x,y) != 0){
        
        game_state.set_gameOver(false);
        game_state.set_winCode(0);
        game_state.set_moveValid(false);
        return;
        
    } 
    game_state.set_moveValid(true);
        if(game_state.get_turn())
            turn = 1;

       
        game_state.set_gameBoard(x,y,turn);

        if(turn == 1)
            game_state.set_turn(false);
        else 
            game_state.set_turn(true);

        if((game_state.get_gameBoard(0,0) == 1 && game_state.get_gameBoard(0,1) == 1
           && game_state.get_gameBoard(0,2) == 1)||(game_state.get_gameBoard(0,0) == -1 
           && game_state.get_gameBoard(0,1) == -1 && game_state.get_gameBoard(0,2) == -1)){

            game_state.set_gameOver(true);
            game_state.set_winCode(1);

        } else if((game_state.get_gameBoard(1,0) == 1 && game_state.get_gameBoard(1,1) == 1
           && game_state.get_gameBoard(1,2) == 1)||(game_state.get_gameBoard(1,0) == -1 
           && game_state.get_gameBoard(1,1) == -1 && game_state.get_gameBoard(1,2) == -1)){

            game_state.set_gameOver(true);
            game_state.set_winCode(2);

        } else if((game_state.get_gameBoard(2,0) == 1 && game_state.get_gameBoard(2,1) == 1
           && game_state.get_gameBoard(2,2) == 1)||(game_state.get_gameBoard(2,0) == -1 
           && game_state.get_gameBoard(2,1) == -1 && game_state.get_gameBoard(2,2) == -1)){

            game_state.set_gameOver(true);
            game_state.set_winCode(3);

        } else if((game_state.get_gameBoard(0,0) == 1 && game_state.get_gameBoard(1,0) == 1
           && game_state.get_gameBoard(2,0) == 1)||(game_state.get_gameBoard(0,0) == -1 
           && game_state.get_gameBoard(1,0) == -1 && game_state.get_gameBoard(2,0) == -1)){

            game_state.set_gameOver(true);
            game_state.set_winCode(4);

        } else if((game_state.get_gameBoard(0,1) == 1 && game_state.get_gameBoard(1,1) == 1
           && game_state.get_gameBoard(2,1) == 1)||(game_state.get_gameBoard(0,1) == -1 
           && game_state.get_gameBoard(1,1) == -1 && game_state.get_gameBoard(2,1) == -1)){

            game_state.set_gameOver(true);
            game_state.set_winCode(5);

        } else if((game_state.get_gameBoard(0,2) == 1 && game_state.get_gameBoard(1,2) == 1
           && game_state.get_gameBoard(2,2) == 1)||(game_state.get_gameBoard(0,2) == -1 
           && game_state.get_gameBoard(1,2) == -1 && game_state.get_gameBoard(2,2) == -1)){

            game_state.set_gameOver(true);
            game_state.set_winCode(6);

        } else if((game_state.get_gameBoard(0,0) == 1 && game_state.get_gameBoard(1,1) == 1
           && game_state.get_gameBoard(2,2) == 1)||(game_state.get_gameBoard(0,0) == -1 
           && game_state.get_gameBoard(1,1) == -1 && game_state.get_gameBoard(2,2) == -1)){

            game_state.set_gameOver(true);
            game_state.set_winCode(7);

        } else if((game_state.get_gameBoard(2,0) == 1 && game_state.get_gameBoard(1,1) == 1
           && game_state.get_gameBoard(0,2) == 1)||(game_state.get_gameBoard(2,0) == -1 
           && game_state.get_gameBoard(1,1) == -1 && game_state.get_gameBoard(0,2) == -1)){

            game_state.set_gameOver(true);
            game_state.set_winCode(8);

        } else 
            game_state.set_winCode(0);
   
}

