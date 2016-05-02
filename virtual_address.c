/* Project EXTRA CREDIT
 * CSC341 Operating Systems
 * Dr. Bin Tang
 * Matt Levan
 *
 * 64-bit virtual address analysis.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Global variables. */
unsigned long int x; 
unsigned long int m = 64;
unsigned long int n = 17; // log2(128*1024)

/* Functions. */
unsigned long int get_page_number(unsigned long int x) {
    /* Shift x to the right by n bits. */
    return x >> n;
}

unsigned long int get_offset(unsigned long int x) {
    /* Mask is decimal representation of 17 binary 1 digits.
     * It is actually 2^17-1!.
     */
    unsigned long int mask = 131071;

    return x & mask;
}

int main(int argc, char *argv[]) {
    /* Result variables. */
    unsigned long int page_number;
    unsigned long int offset;

    /* Get command line arguments. */
    if (argc != 2) {
        printf("Enter a virtual address for analysis!");
        
        return 1;
    }

    /* Assign first command line arg to x. */
    x = atol(argv[1]);

    page_number = get_page_number(x);
    offset = get_offset(x);

    printf("The %lu-bit address %lu (%.fKB page size) contains:\n", \
        m, x, pow(2,n)/1024);
    printf("Page number: %lu\n", page_number);
    printf("Offset: %lu\n", offset);

    return EXIT_SUCCESS;
}
