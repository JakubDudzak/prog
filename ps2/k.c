#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "k.h"

void add_random_tile(struct game *game){
    int row, col;
    // find random, but empty tile
    do{
        row = rand() % SIZE;
        col = rand() % SIZE;
    }while(game->board[row][col] != ' ');

    // place to the random position 'A' or 'B' tile
    if(rand() % 2 == 0){
        game->board[row][col] = 'A';
    }else{
        game->board[row][col] = 'B';
    }
}

bool is_game_won(const struct game game){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (game.board[i][j] == 'K')
                return true;
        }
    }
    return false;
}

bool is_move_possible(const struct game game){
    for (int i = 0; i < SIZE-1; i++) {
        for (int j = 0; j < SIZE; j++) {
            if ((game.board[i][j] == game.board[i+1][j]) || game.board[i][j] == ' '|| game.board[i+1][j] == ' ')
                return true;
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE-1; j++) {
            if (game.board[i][j] == game.board[i][j+1])
                return true;
        }
    }
    return false;
}

bool update(struct game *game, int dy, int dx){
    if ((dx&&dy)||(!dx&&!dy))
        return false;
    bool ret = false;
    // spravne pouzitie
    if (dx == 1){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = SIZE-1; j > 0;) {
                if (game->board[i][j]==' ' && game->board[i][j-1]!=' '){
                    char temp = game->board[i][j-1];
                    game->board[i][j-1] = ' ';
                    game->board[i][j] = temp;
                    ret = true;
                    if(j!=SIZE-1)
                        j++;
                } else {
                    if (game->board[i][j]!=' ' && (game->board[i][j] == game->board[i][j - 1])) {
                        game->board[i][j]++;
                        game->score+=(int)pow(2,game->board[i][j]-'A'+1);
                        game->board[i][j - 1] = ' ';
                    } else if(j!=0){
                        j--;
                    }
                }
            }
        }
    }
    else if (dx == -1){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE-1;) {
                if (game->board[i][j]==' ' && game->board[i][j+1]!=' '){
                    char temp = game->board[i][j+1];
                    game->board[i][j+1] = ' ';
                    game->board[i][j] = temp;
                    ret = true;
                    if(j!=0)
                        j--;
                } else {
                    if (game->board[i][j]!=' ' && (game->board[i][j] == game->board[i][j + 1])) {
                        game->board[i][j]++;
                        game->score+=(int)pow(2,game->board[i][j]-'A'+1);
                        game->board[i][j + 1] = ' ';
                    } else if(j!=SIZE-1){
                        j++;
                    }
                }
            }
        }
    }
    else if (dy == -1){
        for (int j = 0; j < SIZE; j++) {
            for(int i = SIZE-1; i > 0; )  {
                if (game->board[i-1][j]==' ' && game->board[i][j]!=' ' && game->board[i][j]!=0){
                    char temp = game->board[i][j];
                    game->board[i][j] = ' ';
                    game->board[i-1][j] = temp;
                    ret = true;
                    if(i!=SIZE-1)
                        i++;
                }else {
                    if (game->board[i][j]!=' ' && (game->board[i][j] == game->board[i-1][j])) {
                        game->board[i-1][j]++;
                        game->score+=(int)pow(2,game->board[i-1][j]-'A'+1);
                        game->board[i][j] = ' ';
                    }
                    else if(i!=0){
                        i--;
                    }
                }
            }
        }
    }
    else if (dy == 1){
        for (int j = 0; j < SIZE; j++) {
            for(int i = 0; i < SIZE; )  {
                if (game->board[i+1][j]==' ' && game->board[i][j]!=' ' && game->board[i][j]!=0){
                    char temp = game->board[i][j];
                    game->board[i][j] = ' ';
                    game->board[i+1][j] = temp;
                    ret = true;
                    if(i!=0)
                        i--;
                }else {
                    if (game->board[i][j]!=' ' && (game->board[i][j] == game->board[i+1][j])) {
                        game->board[i+1][j]++;
                        game->score+=(int)pow(2,game->board[i+1][j]-'A'+1);
                        game->board[i][j] = ' ';
                    }
                    else{
                        if(i!=SIZE)
                            i++;
                    }
                }
            }
        }
    }
    return ret;
}

