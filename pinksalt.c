    /**
    ** Created by Josjuar Lister 2022 
    ** Using https://github.com/amosnier/sha-2 for sha256 implementation
    **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "sha-256.h"

#ifndef SALT_CAP
#define SALT_CAP 0xfffff
#endif

int data2salt(int position, int salt, int new){
    if (new > 0xf) {
        printf("That is not a correct hex number!");
        return 0xbaa115;
    }
    switch (position) {
        case 1:
            return salt ^ new ;
            break;
        case 2:
            return salt ^ (new << 0x4);
            break;
        case 3:
            return salt ^ (new << 0x8);
            break;
        case 4:
            return salt ^ (new << 0xc);
            break;
        case 5:
            return salt ^ (new << 0x10);
            break;
        default:
            return 0xbaa115;
            break;
    }
}

static void hash_to_string(char string[65], const uint8_t hash[32])
{
	size_t i;
	for (i = 0; i < 32; i++) {
		string += sprintf(string, "%02x", hash[i]);
	}
}

int main(int argv, char *argc[])
{   

    char string[32];
    if (argv > 1){
        strcpy(string, argc[1]);
    }
    else {
        printf("Please provide string: ");
        scanf("%s", string);
    }

    int reply, n, data = 0x0;
    int p1, p2, p3, p4, p5;
    char salt[32];
    char salted[sizeof(string) + sizeof(salt)];
    __uint8_t hash[32];
    char hash_str[65], *target_hash;

    printf("Would you like to make a hash or read one?\n");
    printf("1 - make\n");
    printf("2 - read\n");
    printf("[Option]: ");
    scanf("%1d", &reply);

    if (reply == 1){

        printf("Okay!\n");

        printf("position 1? (1-f): ");
        scanf("%2d", &p1);
        data = data2salt(1, data, p1);
        printf("%x\n", data);
        
        printf("position 2? (1-f): ");
        scanf("%2d", &p2);
        data = data2salt(2, data, p2);
        printf("%x\n", data);

        printf("position 3? (1-f): ");
        scanf("%2d", &p3);
        data = data2salt(3, data, p3);
        printf("%x\n", data);
        
        printf("position 4? (1-f): ");
        scanf("%2d", &p4);
        data = data2salt(4, data, p4);
        printf("%x\n", data);

        printf("position 5? (1-f): ");
        scanf("%2d", &p5);
        data = data2salt(5, data, p5);
        printf("%x\n", data);
        
        //make hash
        snprintf(salt, sizeof(string) + sizeof(salt), "%x", data);
        strcpy(salted, string);
        strcat(salted, salt);

        calc_sha_256(hash, salted, strlen(salted));
        hash_to_string(hash_str, hash);
        printf("%s - %s\n", salted, hash_str);
    }
    else if(reply == 2){
        printf("Please provide a hash or a file containing hashes: \n");
        //Get hash
        char hash_scr[128];
        scanf("%128s", &hash_scr);
        int hash_scr_len = strlen(hash_scr);

        if(hash_scr_len == 64 && strstr(hash_scr, ".") == NULL){
            printf("--- Hash detected ---\n\n");

            printf("target = '%s'\n", hash_scr);
            for (n=0x0; n<=SALT_CAP; n++) {
                snprintf(salt, sizeof(string) + sizeof(salt), "%x", n);
                strcpy(salted, string);
                strcat(salted, salt);

                calc_sha_256(hash, salted, strlen(salted));
                hash_to_string(hash_str, hash);
                fflush(stdout);
                printf("%s - %s\r", salted, hash_str);
                if(!strcmp(hash_str, hash_scr)){
                    printf("\nFound the hash! %s\n", salted);
                    return 0;
                }
            }
            fflush(stdout);
            printf("\nCouldn't match hash.\n");
            return 1;
        }
        else {
            char *line = NULL;
            size_t linelen;
            ssize_t read;
            FILE *hash_scr_f;

            hash_scr_f = fopen(hash_scr, "r");
            if(hash_scr_f == NULL){
                printf("Error can't open that file");
                return 1;
            }
            
            printf("Reading: %s\n", hash_scr);

            
            while ((read = getline(&line, &linelen, hash_scr_f)) != -1) {
                target_hash = line;
				target_hash[strlen(target_hash) -1] = '\0';
                printf("target = '%s'", line);

                printf("\n");
                for (n=0x0; n<=SALT_CAP; n++) {
                    snprintf(salt, sizeof(string) + sizeof(salt), "%x", n);
                    strcpy(salted, string);
                    strcat(salted, salt);

                    calc_sha_256(hash, salted, strlen(salted));
                    hash_to_string(hash_str, hash);
                    fflush(stdout);
                    printf("%s - %s\r", salted, hash_str);
                    if(!strcmp(hash_str, target_hash)){
                        printf("\n\nFound the hash! %s\n", salted);
                        return 0;
                    }
                }
                fflush(stdout);
                printf("\nCouldn't match hash.\n");
            }
        }
    }
}