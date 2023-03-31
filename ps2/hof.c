#include <stddef.h>
#include "hof.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp_by_score(const void *p1,const void *p2){
    struct player* player1 = (struct player *)p1;
    struct player* player2= (struct player *)p2;
    if(player1->score>player2->score)
        return -1;
    else if(player1->score<player2->score)
        return 1;
    return 0;
}
int load(struct player list[]){
    if(list==NULL)
        return -1;
    FILE* fp = fopen(HOF_FILE,"r");
    if(fp == NULL)
        return -1;
    size_t input_counter = 0;
    int count = 0;
    do{
        //fread(list[input_counter].name, sizeof(char), 30, fp);
        //count = fread(&list[input_counter].score, sizeof(int ), 1, fp);
        fscanf(fp,"%s",list[input_counter].name);
        count = fscanf(fp,"%d",&list[input_counter].score);
        //
        //printf("%s %i\n",list[input_counter].name,list[input_counter].score);
        //printf("%i\n",list[input_counter].score);
        input_counter++;
    }while(count > 0 && input_counter!=10);
    fclose(fp);
    qsort(list,input_counter,sizeof list[0],cmp_by_score);
    return (int)input_counter-1;
}
bool save(const struct player list[], const int size){
    FILE* fp = fopen(HOF_FILE,"w");
    if(fp == NULL)
        return false;
    for (int i = 0; i < size; ++i) {
        //fwrite(list[i].name, sizeof (char), 30,fp);
        fprintf(fp, "%s %d\n", list[i].name, list[i].score);
        //fwrite(&list[i].score, sizeof (int), 1,fp);
    }
    fclose(fp);
    return true;
}
bool add_player(struct player list[], int* size, const struct player player){
    qsort(list,(size_t)*size+1,sizeof list[0],cmp_by_score);
    /*for (int i = 0; i < *size; ++i) {
        printf("%s %d\n", list[i].name,list[i].score);
    }*/
    if(*size>9){
        if(player.score<list[9].score)
            return false;
    }
    /*
 * daj memmove ak sa skore rovna existujucemu, vymaz posledny lement ak je ich viac jak 10
 * for each(item from list)
 *      if(src == item)
 *          memmove sprav miesto
 *          list[itemindex] = src
 *          counter++
 *          if counter == 11
 *              list[10]=\0
 *
 */
    for (int i = 0; i < *size; ++i) {
        if (player.score == list[i].score){
            for (int j = (int )*size-2; j >= i; j--)
                list[j] = list[j - 1];
            list[i] = player;
            return true;
        }
    }
    list[*size] = player;
    qsort(list,(size_t)*size+1,sizeof list[0],cmp_by_score);
    /*for (int i = 0; i < *size+1; ++i) {
        printf("%s %d\n", list[i].name,list[i].score);
    }*/
    if(*size<10)
        *size = *size+1;
    return true;

}


