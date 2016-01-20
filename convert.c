/*
 * Zachary Hill
 * cs3411
 * Jan 14th, 2016
 */


    /*
     * This program is designed to convert
     * the contents of a binary file to
     * either a char, int, or float
     */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>

#define FILENAME "file.dat"

int CURRENTBYTE = -1;
int CURRENTBIT = 0;

char readBin (FILE *fp) {



    static char data[8];
    unsigned char mask = 1;
    char val = -1;
    bool hasChanged = false;

    // Check if intialized, if not then do so
    if (CURRENTBYTE == -1) {
        fread(&CURRENTBYTE, sizeof(char), 1, fp);
        CURRENTBIT = 0;
        hasChanged = true;
    }

    // if all bits have been used, read in new bits
    if (CURRENTBIT == 8) {
        fread(&CURRENTBYTE, sizeof(char), 1, fp);
        CURRENTBIT = 0;
        hasChanged = true;
    }

    // update array if needed
    if (hasChanged) {
        for (int i = 0; i < 8; i++) {
            val = mask & (CURRENTBYTE >> (7 - i));
            printf("val: %d\n", val);
            data[i] = val;
        }
        hasChanged = false;
    }

    return (data[CURRENTBIT++]);

}

/* Return the type of data stored next */
char removeType (FILE *fp) {
    char type = 0;
    char val;

    // find the value of the first bit and shift
    type = readBin (fp);
    type = type << 1;
    // do again for second bit
    val = readBin (fp);
    type = type | val;

    printf("TYPE IS: %d\n", type);
    return type;

}


int main () {

    char type;
    int data = 0;
    char numOfBits = 0;
    uint8_t temp;
    int k = 0;


    typedef union {
        uint32_t dataBits;
        uint8_t b[4];
        float f;

    } floatData;

    floatData floatBits;

    FILE *fp = fopen(FILENAME, "r");
    // Check for valid file
    if(fp == NULL) {
	perror("fopen");
	exit(EXIT_FAILURE);
    }

    while (1) {
        data = 0;
        floatBits.dataBits = 0;
        numOfBits = 0;
        type = removeType(fp);


        switch (type) {
            case (0):
                for (int i = 0; i < 7; i++) {
                    data = (data << 1) | readBin(fp);
                }

                printf("'char = %c'\n", data);
                k++;
                if (k == 4) {
                    exit(1);
                }
                break;

            case (1):
                for (int i = 0; i < 5; i++) {
                    numOfBits = (numOfBits << 1) | readBin(fp);
                }
                numOfBits = numOfBits + 1;
                for (int i = 0; i < numOfBits; i++) {
                    data = (data << 1) | readBin(fp);
                }

                printf("'int = %d'\n", data);
                break;

            case (2):
                temp = 0;
                for (int i = 0; i < 32; i++) {
                    floatBits.dataBits = (floatBits.dataBits << 1) | readBin(fp);
                    printf("DATA: %d\n", floatBits.dataBits);
                }
                //for (int i = 0; i < 3; i++) {
                //    temp = floatBits.b[i];
                //    printf("b.%d: %d\n", i, floatBits.b[i]);
                //     printf("b.3: %d\n", floatBits.b[3]);
                //    floatBits.b[i] = floatBits.b[i + 1];
                //    floatBits.b[i + 1] = temp;
                //}
                // printf("final b.3: %d\n", floatBits.b[3]);
                //  printf("final b.2: %d\n", floatBits.b[2]);

                printf("'float = %f'\n", floatBits.f);

                break;

            case (3):
                exit(0);

            default:
                printf("Invalid data type - Exiting\n");
                exit(1);
        }
    }

    return 0;
}

/*
 * References
 *  Masking
 *      http://crasseux.com/books/ctutorial/Masks.html
 */
