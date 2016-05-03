/* Project 5 
 * CSC341 Operating Systems
 * Dr. Bin Tang
 * Matt Levan
 *
 * Virtual Memory Manager
 * 256 pages in virtual address space.
 * 256 frames in physical memory space.
 * BACKING_STORE.bin simulates a hard drive.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Global variables. */
int page_size = 256; // 2^8 bytes.
int n = 8; // 8-bit page number.
int virtual; // Virtual address.
int physical; // Physical address.

/* Functions. */
int get_physical(int virtual) {
    /* Calculate the physical address value. */
    return 0;
}

int get_page_number(int virtual) {
    /* Shift virtual to the right by n bits. */
    return virtual >> n;
}

int get_offset(int virtual) {
    /* Mask is decimal representation of 8 binary 1 digits.
     * It is actually 2^8-1. */
    int mask = 255;

    return virtual & mask;
}

int main(int argc, char *argv[]) {
    /* File I/O variables. */
    char* in_file; // Address file name.
    char* out_file; // Output file name.
    char line[8]; // Temp string for holding each line in in_file.
    FILE* in_ptr; // Address file pointer.
    FILE* out_ptr; // Output file pointer.

    /* Get command line arguments. */
    if (argc != 3) {
        perror("Enter input and output file names!");
        
        exit(1);
    }
    /* Else, proceed execution. */
    else {
        /* Get the file names from argv[]. */
        in_file = argv[1];
        out_file = argv[2];

        /* Open the address file. */
        if ((in_ptr = fopen(in_file, "r")) == NULL) {
            /* If fopen fails, print error and exit. */
            perror("Input file could not be opened.\n");

            exit(1);
        }

        /* Open the output file. */
        if ((out_ptr = fopen(out_file, "a")) == NULL) {
            /* If fopen fails, print error and exit. */
            perror("Output file could not be opened.\n");

            exit(1);
        }

        /* Loop through the file one line at a time. */
        while (fgets(line, sizeof(line), in_ptr)) {
            /* Read a single address from file, assign to virtual. */
            virtual = atoi(line);

            /* Append the results to out_file. */
            fprintf(out_ptr, "Virtual address: %d ", virtual); 
            fprintf(out_ptr, "Physical address: %d ", get_physical(virtual));
            fprintf(out_ptr, "Value: \n");
        }

        /* Close both files. */
        fclose(in_ptr);
        fclose(out_ptr);
    }

    return EXIT_SUCCESS;
}
