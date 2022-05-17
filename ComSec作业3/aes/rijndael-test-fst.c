#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rijndael-api-fst.h"

void menu(){
    printf("\nThis is a stupid AES tool by nerdy m0d1.\n");
    printf("You better run.\n");
    printf("\n");
    return;
}

BYTE unhex_sub(char x) {
    if (x >= '0' && x <= '9') {
        return x - '0';
    }
    else if (x >= 'a' && x <= 'f') {
        return x - 'a' + 10;
    }
    else if (x >= 'A' && x <= 'F') {
        return x - 'A' + 10;
    }
    else {
        return 0xff;
    }
}


int unhex(char* hex, BYTE* bin, int hexLen) {
    for (int i = 0; i < hexLen; i += 2) {
        bin[i / 2] = 0;
        for (int j = 0; j < 2; j++) {
            BYTE tmp = unhex_sub(hex[i + j]);
            if (tmp == 0xff) {
                return FALSE;
            }
            bin[i / 2] <<= 4;
            bin[i / 2] |= tmp;
        }
    }
    return TRUE;
}

typedef struct {
    int len;
    BYTE* text;
} textInstance;

void printBytes(textInstance* text) {
    for (int i = 0; i < text->len; i++) {
        printf("%02x", text->text[i]);
    }
    printf("\n");
    return;
}


//Input:plaintext
//Output:
void get_constant(keyInstance* key, cipherInstance* cipher, textInstance* input, textInstance* output){
    
    BYTE direction;
    int textlen;
    char * textHex;
    printf("\n0 for Encryption and 1 for Decryption.\n");
    printf("please Input your choice:");
    while (1) {
        scanf("%hhd", &direction);
        if (direction != DIR_DECRYPT && direction != DIR_ENCRYPT) {
            printf("\nplease Input your legal choice,which is 0 or 1:");
        }
        else{
            if (direction == DIR_DECRYPT) {
                printf("\nDecrypting.\n");
                printf("please Input the length of your ciphertext(in HEX encoding):");
                while (1){
                    scanf("%d", &textlen);
                    if ((textlen & 1) != 0){
                        printf("please Input the legal length : ");
                    }
                    else {
                        break;
                    }
                }

                textHex = malloc(textlen);
                input->len = textlen / 2;
                input->text = malloc(input->len);
                printf("please Input your ciphertext(in HEX encoding):");
                while (1) {
                    scanf("%s", textHex);
                    if (unhex(textHex, input->text, textlen) != 1) {
                        printf("please Input the legal ciphertext:");
                    }
                    else { 
                        break;
                    };
                }

            }
            else{
                printf("\nEncrypting.\n");
                printf("please Input the length of your plaintext(in HEX encoding):");
                while (1) {
                    scanf("%d", &textlen);
                    if ((textlen & 1) != 0) {
                        printf("please Input the legal length : ");
                    }
                    else {
                        break;
                    }
                }

                textHex = malloc(textlen);
                input->len = textlen / 2;
                input->text = malloc(input->len);
                printf("please Input your plaintext(in HEX encoding):");
                while (1) {
                    scanf("%s", textHex);
                    if (unhex(textHex, input->text, textlen) != 1) {
                        printf("please Input the legal plaintext:");
                    }
                    else {
                        break;
                    };
                }
                
            }
            break;
        }
    }

  

    BYTE mode;
    char IV[MAX_IV_SIZE + 1] = { 0 };
    printf("\n1 for ECB mode and 2 for CBC.\n");
    printf("please Input your choice:");
    while (1) {
        scanf("%hhd", &mode);
        if (mode != MODE_CBC && mode != MODE_ECB) {
            printf("\nplease Input your legal choice,which is 1 or 2:");
            continue;
        }
        else {
            if (mode == MODE_ECB) {
                printf("\nECBing\n");
                cipherInit(cipher, mode, NULL);

            }
            else {
                printf("\nplease Input your IV which is in HEX encoding:");
                while (1){
                    scanf("%32s", IV);
                    if (cipherInit(cipher, mode, IV) != 1) {
                        printf("\nillegal IV,please Input again:");
                    }
                    else {
                        //cipherInit(cipher, mode, IV);        ��if��ʱ���ʼ���ˣ����Բ�������һ��
                        break; 
                    }

                }
                printf("\nCBCing.\n");
            }
            break;
        }
    }

    char keyMaterial[MAX_KEY_SIZE + 1];
    printf("please Input your KEY(in HEX encoding)and don't tell anybody else:");
    while (1) {
        scanf("%64s", keyMaterial);
        int keylen = strlen(keyMaterial);
        if (makeKey(key, direction, keylen * 4, keyMaterial) != 1) {
            printf("you idiot,just tell me the correct key:");
        }
        else {
            //makeKey(key, direction, keyLen * 4, keyMaterial);
            printf("Done.\n");
            break;
        }
    }

    output->len = ((textlen / 2 - 1) / 8 + 1) * 8;
    output->text = malloc(output->len);
    free(textHex);
    return;
}

void rijndaelAPI(keyInstance* key, cipherInstance* cipher, textInstance* input, textInstance* output) {
    switch (key->direction) {
    case DIR_ENCRYPT:
        padEncrypt(cipher, key, input->text, input->len, output->text);
        break;
    case DIR_DECRYPT:
        padDecrypt(cipher, key, input->text, input->len, output->text);
        break;
    }
    return;
}

int main() {
    keyInstance keyInst;
    cipherInstance cipherInst;
    textInstance inputInst, outputInst;
    menu();
    get_constant(&keyInst,&cipherInst,&inputInst,&outputInst);
    rijndaelAPI(&keyInst, &cipherInst, &inputInst, &outputInst);
    printf("\nFinal output:\n");
    printBytes(&outputInst);
    printf("\n");
    free(inputInst.text);
    free(outputInst.text);
    return 0;
}
