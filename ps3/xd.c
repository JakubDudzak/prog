#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
int scitaj(int cislo){

    int sucet = 0;

    for (int i=0; cislo > 0; i++){
        sucet = sucet + cislo % 10;
        cislo = cislo / 10;
    }
    return sucet;
}
int main(){

    unsigned char cislo;
    int sucet = 0;

    cislo = getchar();
    sucet = sucet +( cislo - 48);

    while (cislo != '\n'){
        scanf("%c", &cislo);
        sucet = sucet +( cislo - 48);
    }

    sucet = sucet + 38;

    while (sucet > 9){
        sucet = scitaj(sucet);
    }

    printf("%d \n" , sucet );
}//
// Created by jakub on 3. 4. 2022.
//

