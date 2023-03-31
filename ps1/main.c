#include <stdio.h>
#include "bmp.h"
#include "playfair.h"
#include <stdlib.h>
#include <string.h>

int main(){
    char *decrypted;
    char *encrypted;
    char *text = "sleeveless";
    char *key = "fortifiers";

    encrypted = playfair_encrypt(key, text);
    decrypted = playfair_decrypt(key, encrypted);
    free(decrypted);
    free(encrypted);
    unsigned char *encrypt;
    char *decrypt;

    encrypt = bmp_encrypt("key", "text");
    decrypt = bmp_decrypt("key", encrypt);
    free(encrypt);
    free(decrypt);

    //printf("%s",reverse("Ach poveda kdeze si mi tak dlho ako tazko za tebou cakam"));

    return 0;
}
