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
#define MEM_SIZE (FRAME_SIZE * FRAME_ENTRIES) // Mem size, in bytes.
#define TLB_ENTRIES 16 // Max TLB entries.

/* Global variables. */
int virtual; // Virtual address.
int page_number; // Page number.
int offset; // Offset.
int physical; // Physical address.
int frame_number; // Frame number.
int page_table[PAGE_ENTRIES]; // Page table.
int tlb[TLB_ENTRIES][2]; // Translation look-aside buffer.
char memory[MEM_SIZE]; // Physical memory. Each char is 1 byte.

/* Statistics variables. */
int fault_counter = 0; // Count the page faults.
int tlb_hit_rate; // TLB hit rate.
int tlb_counter = 0; // TLB hit counter.

/* Functions declarations. */
int get_physical(int virtual);
int get_offset(int virtual);
int get_page_number(int virtual);
void initialize_page_table(int n);
void initialize_tlb(int n);
int consult_page_table(int page_number);
int consult_tlb(int page_number);

int main(int argc, char *argv[]) {
    /* File I/O variables. */
    char* in_file; // Address file name.
    char* out_file; // Output file name.
    char* store_file; // Store file name.
    char line[8]; // Temp string for holding each line in in_file.
    FILE* in_ptr; // Address file pointer.
    FILE* out_ptr; // Output file pointer.
    FILE* store_ptr;

    /* Initialize page_table, set all elements to -1. */
    initialize_page_table(-1);
    initialize_tlb(-1);

    /* Get command line arguments. */
    if (argc != 4) {
        printf("Enter input, output, and store file names!");

        exit(1);
    }
    /* Else, proceed execution. */
    else {
        /* Get the file names from argv[]. */
        in_file = argv[1];
        out_file = argv[2];
        store_file = argv[3];

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

        /* Open the store file. */
        if ((store_ptr = fopen(in_file, "r")) == NULL) {
            /* If fopen fails, print error and exit. */
            printf("Store file could not be opened.\n");

            exit(1);
        }

        /* Loop through the input file one line at a time. */
        while (fgets(line, sizeof(line), in_ptr)) {
            /* Read a single address from file, assign to virtual. */
            virtual = atoi(line);

            /* Get the page number from the virtual address. */
            page_number = get_page_number(virtual);
            offset = get_offset(virtual);
            frame_number = consult_tlb(page_number);

            /* Check frame_number returned by consult_tlb function. */ 
            if (frame_number != -1) {
                /* TLB lookup succeeded. */
                physical = frame_number + offset;
            }
            else {
                /* TLB lookup failed. */
                /* Look for frame_number in page table instead. */
                frame_number = consult_page_table(page_number);

                /* Check frame number from consult_page_table. */
                if (frame_number != -1) {
                    physical = frame_number + offset;
                }
                else {
                    /* Handle the page fault. */
                    /* When a page fault occurs, you will read in a 256-byte
                     * page from the file BACKING_STORE.bin and store it in 
                     * an available page frame in the physical memory. */
                }
            }

            /* Use the physical address to read value from memory. */
            /* If no value exists in the address in memory, page fault. */

            /* Append the results to out_file. */
            fprintf(out_ptr, "Virtual address: %d ", virtual); 
            fprintf(out_ptr, "Physical address: %d ", physical);
            fprintf(out_ptr, "Value: \n");
        }

        /* Close all three files. */
        fclose(in_ptr);
        fclose(out_ptr);
        fclose(store_ptr);
    }

    return EXIT_SUCCESS;
}

/* Functions. */
int get_physical(int virtual) {
    /* Calculate the physical address value. */
    physical = get_page_number(virtual) + get_offset(virtual);

    return physical;
}

int get_page_number(int virtual) {
    /* Shift virtual to the right by n bits. */
    return (virtual >> PAGE_NUM_BITS);
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

void initialize_tlb(int n) {
    for (int i = 0; i < TLB_ENTRIES; i++) {
        tlb[i][0] = -1;
        tlb[i][1] = -1;
    }
}

int consult_page_table(int page_number) {
    if (page_table[page_number] == -1) {
        fault_counter++;
    }

    return page_table[page_number];
}

int consult_tlb(int page_number) {
    /* If page_number is found, return the corresponding frame number. */
    for (int i = 0; i < TLB_ENTRIES; i++) {
        if (tlb[i][0] == page_number) {
            /* TLB hit! */
            tlb_counter++;
            return tlb[i][1];
        }
    }

    /* If page_number doesn't exist in TLB, return -1. */
    /* TLB miss! */
    return -1;
}
