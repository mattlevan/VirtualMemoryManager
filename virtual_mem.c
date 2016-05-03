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

/* Global definitions. */
#define PAGE_SIZE 256 // Page size, in bytes.
#define PAGE_ENTRIES 256 // Max page table entries.
#define PAGE_NUM_BITS 8 // Page number size, in bits.
#define FRAME_SIZE 256 // Frame size, in bytes.
#define FRAME_ENTRIES 256 // Number of frames in physical memory.
#define TLB_ENTRIES 16 // Max TLB entries.
#define MEM_SIZE (FRAME_SIZE * FRAME_ENTRIES) // Mem size, in bytes.

/* Global variables. */
int virtual; // Virtual address.
int physical; // Physical address.
int page_table[PAGE_ENTRIES]; // Page table.
char memory[MEM_SIZE]; // Physical memory. Each char is 1 byte.

/* Statistics variables. */
int fault_counter; // Count the page faults.
int tlb_hit_rate; // TLB hit rate.

/* Functions. */
int get_physical(int virtual) {
    /* Calculate the physical address value. */
    return 0;
}

int get_page_number(int virtual) {
    /* Shift virtual to the right by n bits. */
    return virtual >> PAGE_NUM_BITS;
}

int get_offset(int virtual) {
    /* Mask is decimal representation of 8 binary 1 digits.
     * It is actually 2^8-1. */
    int mask = 255;

    return virtual & mask;
}

void initialize_page_table(int n) {
    for (int i = 0; i < PAGE_ENTRIES; i++) {
        page_table[i] = n;
    }
}

int main(int argc, char *argv[]) {
    /* File I/O variables. */
    char* in_file; // Address file name.
    char* out_file; // Output file name.
    char line[8]; // Temp string for holding each line in in_file.
    FILE* in_ptr; // Address file pointer.
    FILE* out_ptr; // Output file pointer.

    /* Initialize page_table, set all elements to -1. */
    initialize_page_table(-1);

    /* Get command line arguments. */
    if (argc != 3) {
        printf("Enter input and output file names!");

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
            printf("Input file could not be opened.\n");

            exit(1);
        }

        /* Open the output file. */
        if ((out_ptr = fopen(out_file, "a")) == NULL) {
            /* If fopen fails, print error and exit. */
            printf("Output file could not be opened.\n");

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
