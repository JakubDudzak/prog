#include <string.h>
#include <ctype.h>
#include <malloc.h>
#include <stdbool.h>
void encode_char(const unsigned char character, bool bits[8]){
    for(int i=0;i<8;i++){
        bits[i]=false;
    }
    int n =  character;
    bool ud[8];
    int i;
    for(i=0;n>0;i++)
    {
        ud[i]=n%2;
        n=n/2;
    }

    for(i=i-1;i>=0;i--)
    {
        bits[7-i]=ud[i];
    }

}
int decode_byte(const bool bits[8]){
    int r = 0;
    if(bits[0])
        r=r+128;
    if(bits[1])
        r=r+64;
    if(bits[2])
        r=r+32;
    if(bits[3])
        r=r+16;
    if(bits[4])
        r=r+8;
    if(bits[5])
        r=r+4;
    if(bits[6])
        r=r+2;
    if(bits[7])
        r=r+1;
    return r;
}
bool check_key(const char *key){
    while (*key!='\0'){
        if(!isalpha(*key))
            return false;
        key++;
    }
    return true;
}
char* reverse(const char* text){
    if (text==NULL)
        return NULL;
    int len = strlen(text);
    char* string = calloc(len+1, sizeof (char));
    const char* end = text+len-1;
    for (int i = 0; i<len;i++){
        string[i] = toupper(*end);
        end--;
    }
    string[len] = '\0';
    return string;
};
char* vigenere_encrypt(const char* key, const char* text){
    if ((key==NULL) || (text==NULL) || strlen(key)==0 || strlen(text)==0 || !check_key(key))
        return NULL;
    int key_len = strlen(key);
    int text_len = strlen(text);
    char* string = calloc(text_len+1,1);
    char* key_stream = calloc(text_len+1,1);

    // keyStream

    int index=0;
    for (int i = 0; i < text_len; i++) {
        key_stream[i]= toupper(*key);
        if(index!=key_len-  1){
            key++;
            index++;}
        else{
            key-=index;
            index=0;}
    }
    //endof keystream


    for (int i = 0, notAlpha = 0; i < text_len; ++i) {
        char temp = 'A' + toupper(key_stream[i-notAlpha])-'A' + toupper(text[i])-'A';
        if(isalpha(text[i])){
            if((temp)>'Z')
                temp-=26;
            string[i] = temp;
        } else{
            string[i] = text[i];
            notAlpha++;
        }
    }
    free(key_stream);
    return string;

}
char* vigenere_decrypt(const char* key, const char* text){
    if ((key==NULL) || (text==NULL) || strlen(key)==0 || strlen(text)==0  || !check_key(key))
        return NULL;
    int key_len = strlen(key);
    int text_len = strlen(text);
    char* string = calloc(text_len+1,1);
    char* key_stream = calloc(text_len+1,1);
    int index=0;
    //keyStream
    for (int i = 0; i < text_len; i++) {
        key_stream[i]= toupper(*key);
        if(index!=key_len-  1){
            key++;
            index++;}
        else{
            key-=index;
            index=0;}
    }
    //endof keystream


    for (int i = 0, notAlpha = 0; i < text_len; ++i) {
        char temp = 'A' - toupper(key_stream[i-notAlpha])+ toupper(text[i]);
        if(isalpha(text[i])){
            if((temp)<'A')
                temp+=26;
            string[i] = temp;
        } else{
            string[i] = text[i];
            notAlpha++;
        }
    }
    free(key_stream);
    return string;

}
unsigned char* bit_encrypt(const char* text){
    if ((text==NULL) || strlen(text)==0 )
        return NULL;
    int len = strlen(text);
    bool bits[8];
    bool firstFour[4];
    bool secondFour[4];
    unsigned char * ret = calloc(len+1,1);
    for (int i = 0; i < len; ++i) {
        encode_char(text[i],bits);

        firstFour[0] = bits[1];
        firstFour[1] = bits[0];
        firstFour[2] = bits[3];
        firstFour[3] = bits[2];
        for (int j = 0; j < 4; ++j) {
            if(((firstFour[j] == false )&& (bits[j+4] == true ))||((firstFour[j] == true )&& (bits[j+4] == false )))
                secondFour[j] = true;
            else
                secondFour[j] = false;
        }


        for (int j = 0; j < 4; ++j) {
            bits[j] = firstFour[j];
        }
        for (int j = 4; j < 8; ++j) {
            bits[j] = secondFour[j-4];
        }
        ret[i]=decode_byte(bits);
    }
    return  ret;
}
char* bit_decrypt(const unsigned char* text){
    if (text==NULL || strlen((const char *)text)==0)
        return NULL;

    int len = strlen((const char*)text);
    bool bits[8];
    bool firstFour[4];
    bool secondFour[4];
    char * ret = calloc(len+1,1);
    for (int i = 0; i < len; ++i) {
        encode_char(text[i],bits);

        firstFour[0] = bits[1];
        firstFour[1] = bits[0];
        firstFour[2] = bits[3];
        firstFour[3] = bits[2];
        for (int j = 0; j < 4; ++j) {
            if(((bits[j] == false )&& (bits[j+4] == true ))||((bits[j] == true )&& (bits[j+4] == false )))
                secondFour[j] = true;
            else
                secondFour[j] = false;
        }


        for (int j = 0; j < 4; ++j) {
            bits[j] = firstFour[j];
        }
        for (int j = 4; j < 8; ++j) {
            bits[j] = secondFour[j-4];
        }
        //printf("%c",ret[i]);

        ret[i]=decode_byte(bits);
    }
    return ret;
}
unsigned char* bmp_encrypt(const char* key, const char* text){
    if ((key==NULL) || (text==NULL) || strlen(key)==0 || strlen(text)==0 || !check_key(key))
        return NULL;
    char* text2 = reverse(text);
    char* text3 = vigenere_encrypt(key,text2);
    unsigned char* ret = bit_encrypt(text3);
    free(text2);
    free(text3);
    return ret;
}

char* bmp_decrypt(const char* key, const unsigned char* text){
    if ((key==NULL) || (text==NULL) || strlen(key)==0 || strlen((const char*)text)==0 || !check_key(key))
        return NULL;
    char* text2 = bit_decrypt(text);
    char* text3 = vigenere_decrypt(key, text2);
    char* ret = reverse(text3);
    free(text2);
    free(text3);
    return ret;
}