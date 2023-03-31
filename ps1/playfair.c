#include <string.h>
#include "playfair.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void seekAndDestroyDuplicates(char *key){

    int len= strlen(key);

    for(int i=0; i < len; i++){
        for(int j=i+1; j < len; ){

            if(key[i] == key[j]){
                for(int k=j; k < len; k++){
                    key[k] = key[k + 1];
                }
                len--;

            } else {
                j++;
            }
        }
    }
}
void capitalize(char *key){
    for(int i = 0; i < strlen(key); i++)
    {
        if(isalpha(key[i]))
            key [i] = toupper(key[i]);
    }
}
void removeSpaces(char *str)
{
    // To keep track of non-space character count
    int count = 0;

    // Traverse the given string. If current character
    // is not space, then place it at index 'count++'
    for (int i = 0; str[i]; i++)
        if (str[i] != ' ')
            str[count++] = str[i]; // here count is
    // incremented
    str[count] = '\0';
}
bool isValidString( const char* string) {
    for (int i = 0; i < strlen(string); i++) {
        if (!isalpha(string[i]) && !isspace(string[i]))
            return false;
    }
    if(string[0]==' ')
        return false;
    return true;
}
char* formatText(const char* text){
    int len = strlen(text) * 2;
    char *string = calloc(len + 2, sizeof(char));
    strcpy(string, text);
    int at = 0;

    for (int i = 0; string[i] != '\0'; i += 2) {
        if (text[i] == '\0' || text[i + 1] == '\0')
            break;
        if (text[i] == text[i + 1] && text[i + 1] != 'X') {
            int make_room_at = at + i + 1;
            memmove(
                    string + make_room_at + 1,
                    string + make_room_at,
                    len - (make_room_at + 1)
            );

            string[i + at + 1] = 'X';
            at++;
        }
        else{
            string[i+at] = text[i];
            string[i+at+1] = text[i+1];
        }
    }
    len = strlen(string);
    if(len%2!=0){
        string[len]='X';
        string[len+1]='\0';
    }

    return string;
}
void replaceWs(char*key){
    char* ptr;
    while (strchr(key,'W') != NULL){
        ptr = strchr(key,'W');
        *ptr = 'V';
    }
}
void removeKeyChars(const char* key, char* text){
    char* ptr;
    for (int i = 0; i < strlen(key); i++) {
        char charToDel = key[i];
        ptr = strchr(text,charToDel);
        if(ptr) {
            int index = ptr - text;
            memmove(&text[index], &text[index + 1], strlen(text) - index);
        }
    }
}


char* playfair_encrypt(const char* key, const char* text) {
    //char first = text[0];
    if (key==NULL || text==NULL || strlen(key)==0 || strlen(text)==0 ||!(isValidString(key)) || !(isValidString(text))) { //|| !(isValidString(key)) || !(isValidString(text))
        return NULL;
    }
    char* key2 = calloc(strlen(key)+1,sizeof (char ));
    int textlength = strlen(text);
    if (textlength%2 != 0)
        textlength++;

    char* text2 = calloc(textlength+1, sizeof (char));
    strcpy(key2,key);
    strcpy(text2,text);

    capitalize(key2);
    replaceWs(key2);
    removeSpaces(key2);
    seekAndDestroyDuplicates(key2);

    capitalize(text2);
    //printf("%s\n",text2);
    replaceWs(text2);
    char*string = formatText(text2);
    removeSpaces(string);
    //printf("%s\n",string);
    char alpha[26] = ALPHA;
    char betterAlpha[26];
    betterAlpha[0] = '\0';

    removeKeyChars(key2,alpha);
    strcat(betterAlpha,key2);
    strcat(betterAlpha,alpha);
    /*for (int i = 0; i < strlen(string); i+=2) {
        printf("%c%c ",string[i],string[i+1]);
    }*/
   // printf("\n");
    struct Letter {
        char value;
        int row;
        int col;
    };
    struct Letter first;
    struct Letter second;
    for(int i = 0;i< strlen(string);i+=2){
        first.value = string[i];
        second.value = string[i+1];
        first.row = (strchr(betterAlpha,first.value) - betterAlpha)/5;
        second.row = (strchr(betterAlpha, second.value) - betterAlpha)/5;
        first.col = (strchr(betterAlpha,first.value) - betterAlpha)%5;
        second.col = (strchr(betterAlpha, second.value) - betterAlpha)%5;
        if(first.col==second.col){
            if(first.row!=4){
                string[i] = betterAlpha[(first.row+1)*5+first.col];
            }
            else
                string[i] = betterAlpha[first.col];;
            if(second.row!=4){
                string[i+1] = betterAlpha[(second.row+1)*5+second.col];
            }
            else
                string[i+1] = betterAlpha[first.col];;
        }
        else if(first.row == second.row){
            if(first.col!=4){
                string[i] = betterAlpha[first.row*5+first.col+1];
            }
            else
                string[i] = betterAlpha[first.row*5];
            if(second.col!=4){
                string[i+1] = betterAlpha[second.row*5+second.col+1];
            }
            else
                string[i+1] = betterAlpha[second.row*5];
        }
        else{
                if(first.col<second.col){
                    string[i+1] = betterAlpha[second.row*5+ first.col];
                    string[i] = betterAlpha[first.row*5+second.col];}
                else{
                    //printf("%i els\n",i);
                    string[i] = betterAlpha[first.row*5+second.col];
                    string[i+1] = betterAlpha[second.row*5+first.col];}
        }

    }
    int len = strlen(string);
    char* ret = calloc(len*3/2+2,1);
    while (*string!='\0'){
        *ret = *string;
        //printf("%c",*ret);
        ret++; string++;
        *ret = *string;
        //printf("%c",*ret);
        ret++;
        string += 2;
        if (*string != '\0') {
            *ret = ' ';
            ret++;
        } else {
            ret++;
        }
        string--;
    }


/*    for (int i = 0; i < 5; ++i) {
        for (int j = i * 5; j < i * 5 + 5; ++j) {
            printf("%c", betterAlpha[j]);
        }
        printf("\n");
    }*/



    string -= len;
    ret -= len * 3 / 2;
    len = strlen(ret);
    while (ret[len-1]==' '){
        //printf("%c\n",ret[len-1]);
        ret[len-1]='\0';
        len--;
    }
    free(string);
    free(key2);
    free(text2);
    return ret;
}
char* playfair_decrypt(const char* key, const char* text) {
    if (key==NULL || text==NULL || strlen(key)==0 || strlen(text)==0  || !(isValidString(key)) || !(isValidString(text)) || strchr(text,'W')|| strchr(text,'w')) { //   || !(isValidString(key)) || !(isValidString(text))
        return NULL;
    }
    char* key2 = calloc(strlen(key)+1,sizeof (char ));
    int textlength = strlen(text);
    if (textlength%2 != 0)
        textlength++;

    char* string = calloc(textlength+1, sizeof (char));
    strcpy(key2,key);
    strcpy(string,text);

    capitalize(key2);
    replaceWs(key2);
    removeSpaces(key2);
    seekAndDestroyDuplicates(key2);

    capitalize(string);
    replaceWs(string);
    removeSpaces(string);

    char alpha[26] = ALPHA;
    char betterAlpha[26];
    betterAlpha[0] = '\0';

    removeKeyChars(key2,alpha);
    strcat(betterAlpha,key2);
    strcat(betterAlpha,alpha);

    struct Letter {
        char value;
        int row;
        int col;
    };
    struct Letter first;
    struct Letter second;
    for(int i = 0;i< strlen(string);i+=2){
        first.value = string[i];
        second.value = string[i+1];
        first.row = (strchr(betterAlpha,first.value) - betterAlpha)/5;
        second.row = (strchr(betterAlpha, second.value) - betterAlpha)/5;
        first.col = (strchr(betterAlpha,first.value) - betterAlpha)%5;
        second.col = (strchr(betterAlpha, second.value) - betterAlpha)%5;

        if(first.col==second.col){
            if(first.row!=0){
                string[i] = betterAlpha[(first.row-1)*5+first.col];
            }
            else
                string[i] = betterAlpha[20+first.col];;
            if(second.row!=0){
                string[i+1] = betterAlpha[(second.row-1)*5+second.col];
            }
            else
                string[i+1] = betterAlpha[20+first.col];
        }
        else if(first.row == second.row){
            if(first.col!=0){
                string[i] = betterAlpha[first.row*5+first.col-1];
            }
            else
                string[i] = betterAlpha[first.row*5+4];
            if(second.col!=0){
                string[i+1] = betterAlpha[second.row*5+second.col-1];
            }
            else
                string[i+1] = betterAlpha[second.row*5+4];
        }
        else{
            if(first.col<second.col){
                string[i+1] = betterAlpha[second.row*5+ first.col];
                string[i] = betterAlpha[first.row*5+second.col];}
            else{
                //printf("%i els\n",i);
                string[i] = betterAlpha[first.row*5+second.col];
                string[i+1] = betterAlpha[second.row*5+first.col];}
        }

    }
    /*for (int i = 0; i < 5; ++i) {
        for (int j = i*5; j < i*5+5; ++j) {
            printf("%c",betterAlpha[j]);
        }
        printf("\n");}*/
    free(key2);
    return string;
}
