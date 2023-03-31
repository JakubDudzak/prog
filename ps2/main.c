#include <stdio.h>
#include <string.h>
#include <curses.h>
#include "k.h"
#include "hof.h"
#include "ui.h"

int main() {
// move right
    initscr();
    struct game game = {
            .score=7206,
            .board={
                    {' ', 'J', ' ', ' '},
                    {' ', ' ', ' ', 'A'},
                    {' ', 'C', ' ', ' '},
                    {' ', ' ', ' ', ' '}
            }};
    render(game);
    while (is_move_possible(game)&&!is_game_won(game)){
        char choice=getchar();
        switch (choice) {
            case 'a':
                update(&game,0,-1);
                add_random_tile(&game);
                render(game);
                break;
            case 'd':
                update(&game,0,1);
                add_random_tile(&game);
                render(game);
                break;
            case 'w':
                update(&game,-1,0);
                add_random_tile(&game);
                render(game);
                break;
            case 's':
                update(&game,1,0);
                add_random_tile(&game);
                render(game);
                break;
            default:
                render(game);
                break;
        }


    }
   // printf("%i", is_move_possible(game));*/
    struct player jakub = {.name = "Jakub", .score = 420};
    struct player list[10];
    int size = 8;
    printf("%i",load(list));
    printf("%i",add_player(list, &size, jakub));
    printf("%d",size);
    save(list,10);
    endwin();
    return 0;
}
