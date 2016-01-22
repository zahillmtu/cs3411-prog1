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

/* Returns the next bit in the file, either a 1 or 0 */
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
            data[i] = val;
        }
        hasChanged = false;
    }

    // return the next bit in byte
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

    return type;

}

int main () {

    char type;
    int data = 0;
    char numOfBits = 0;

    // Create a union to do bit operations on the floating point number
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

    // Run while to keep finding the next element until type 11 is reached
    while (1) {
        data = 0;
        floatBits.dataBits = 0;
        numOfBits = 0;
        type = removeType(fp);


        switch (type) {
            case (0):
                // if type 0 then char and is always 7 bit
                for (int i = 0; i < 7; i++) {
                    data = (data << 1) | readBin(fp);
                }

                printf("'char = '%c''\n", data);
                break;

            case (1):
                // if type 01 then int
                // First check for the number of bits in int (always 5 bit indicator)
                for (int i = 0; i < 5; i++) {
                    numOfBits = (numOfBits << 1) | readBin(fp);
                }
                // Use number of bits to find the data for the int
                numOfBits = numOfBits + 1;
                for (int i = 0; i < numOfBits; i++) {
                    data = (data << 1) | readBin(fp);
                }

                printf("'int = %d'\n", data);
                break;

            case (2):
                // if type 10 then float and is always 32 bits
                for (int i = 0; i < 32; i++) {
                    floatBits.dataBits = (floatBits.dataBits << 1) | readBin(fp);
                }

                printf("'float = %f'\n", floatBits.f);

                break;

            case (3):
                // if type 11 then end of file so close
                fclose(fp);
                exit(0);

            default:
                // if type is anything else, error and exit
                printf("Invalid data type - Exiting\n");
                fclose(fp);
                exit(1);
        }
    }

    fclose(fp);
    return 0;
}

/*
 * References
 *  Masking
 *      http://crasseux.com/books/ctutorial/Masks.html
 */
