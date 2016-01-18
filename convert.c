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

#define FILENAME "file.dat"
#define CURRENTBYTE
#define CURRENTBIT

char readBin (fp) {

    static int data[8];
    unsigned char mask = 00000001;
    int val = -1;
    bool hasChanged;

    // Check if intialized, if not then do so
    if CURRENTBYTE == NULL {
        fread(CURRENTBYTE, sizeof(char), 1, fp);
        CURRENTBIT = 0;
        hasChanged = TRUE;
    }

    // if all bits have been used, read in new bits
    if (CURRENTBIT == 8) {
        fread(CURRENTBYTE, sizeof(char), 1, fp);
        CURRENTBIT = 0;
        hasChanged = TRUE;
    }

    // update array if needed
    if (hasChanged) {
        for (i = 0, i < 8, i++) {
            val = mask & (CURRENTBYTE << i);
            data[i] = val;
        }
        hasChanged = FALSE;
    }

    return (data[CURRENTBYTE++])

}

removeType () {


}

shiftBits (data, shiftNum) {

}

char returnType () {


}

int main () {

	FILE *fp = fopen(FILENAME, "r")
	// Check for valid file
	if(fp == NULL) {
		perror("fopen");
		exit(EXIT_FAILURE)
	}

}

/*
 * References
 *  Masking
 *      http://crasseux.com/books/ctutorial/Masks.html
 */
