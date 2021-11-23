/* Program to assist in the challenge of solving sudoku puzzles.

   Skeleton program written by Alistair Moffat, ammoffat@unimelb.edu.au,
   August 2021, with the intention that it be modified by students
   to add functionality, as required by the assignment specification.

   Student Authorship Declaration:

   (1) I certify that except for the code provided in the initial skeleton
   file, the  program contained in this submission is completely my own
   individual work, except where explicitly noted by further comments that
   provide details otherwise.  I understand that work that has been developed
   by another student, or by me in collaboration with other students, or by
   non-students as a result of request, solicitation, or payment, may not be
   submitted for assessment in this subject.  I understand that submitting for
   assessment work developed by or in collaboration with other students or
   non-students constitutes Academic Misconduct, and may be penalized by mark
   deductions, or by other penalties determined via the University of
   Melbourne Academic Honesty Policy, as described at
   https://academicintegrity.unimelb.edu.au.

   (2) I also certify that I have not provided a copy of this work in either
   softcopy or hardcopy or any other form to any other student, and nor will I
   do so until after the marks are released. I understand that providing my
   work to other students, regardless of my intention or any undertakings made
   to me by that other student, is also Academic Misconduct.

   (3) I further understand that providing a copy of the assignment
   specification to any form of code authoring or assignment tutoring service,
   or drawing the attention of others to such services and code that may have
   been made available via such a service, may be regarded as Student General
   Misconduct (interfering with the teaching activities of the University
   and/or inciting others to commit Academic Misconduct).  I understand that
   an allegation of Student General Misconduct may arise regardless of whether
   or not I personally make use of such solutions or sought benefit from such
   actions.

   Signed by: Lok-Hymn Chow 1245550
   Dated:     1/9/2021

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* these #defines provided as part of the initial skeleton */

#define NDIM 3		/* sudoku dimension, size of each inner square */
#define NDIG (NDIM*NDIM)
			/* total number of values in each row */
#define NGRP 3		/* number of sets each cell is a member of */
#define NSET (NGRP*NDIG)
			/* total number of sets in the sudoku */
#define NCLL (NDIG*NDIG)
			/* total number of cells in the sudoku */

#define ERROR	(-1)	/* error return value from some functions */

/* these global constant arrays provided as part of the initial skeleton,
   you may use them in your code but must not alter them in any way,
   regard them as being completely fixed. They describe the relationships
   between the cells in the sudoku and provide a basis for all of the
   sudoku processing loops */

/* there are 27 different different sets of elements that need to be
   checked against each other, this array converts set numbers to cells,
   that's why its called s2c */
int s2c[NSET][NDIM*NDIM] = {
	/* the first group of nine sets describe the sudoku's rows */
	{  0,  1,  2,  3,  4,  5,  6,  7,  8 },
	{  9, 10, 11, 12, 13, 14, 15, 16, 17 },
	{ 18, 19, 20, 21, 22, 23, 24, 25, 26 },
	{ 27, 28, 29, 30, 31, 32, 33, 34, 35 },
	{ 36, 37, 38, 39, 40, 41, 42, 43, 44 },
	{ 45, 46, 47, 48, 49, 50, 51, 52, 53 },
	{ 54, 55, 56, 57, 58, 59, 60, 61, 62 },
	{ 63, 64, 65, 66, 67, 68, 69, 70, 71 },
	{ 72, 73, 74, 75, 76, 77, 78, 79, 80 },
	/* the second group of nine sets describes the sudoku's columns */
	{  0,  9, 18, 27, 36, 45, 54, 63, 72 },
	{  1, 10, 19, 28, 37, 46, 55, 64, 73 },
	{  2, 11, 20, 29, 38, 47, 56, 65, 74 },
	{  3, 12, 21, 30, 39, 48, 57, 66, 75 },
	{  4, 13, 22, 31, 40, 49, 58, 67, 76 },
	{  5, 14, 23, 32, 41, 50, 59, 68, 77 },
	{  6, 15, 24, 33, 42, 51, 60, 69, 78 },
	{  7, 16, 25, 34, 43, 52, 61, 70, 79 },
	{  8, 17, 26, 35, 44, 53, 62, 71, 80 },
	/* the last group of nine sets describes the inner squares */
	{  0,  1,  2,  9, 10, 11, 18, 19, 20 },
	{  3,  4,  5, 12, 13, 14, 21, 22, 23 },
	{  6,  7,  8, 15, 16, 17, 24, 25, 26 },
	{ 27, 28, 29, 36, 37, 38, 45, 46, 47 },
	{ 30, 31, 32, 39, 40, 41, 48, 49, 50 },
	{ 33, 34, 35, 42, 43, 44, 51, 52, 53 },
	{ 54, 55, 56, 63, 64, 65, 72, 73, 74 },
	{ 57, 58, 59, 66, 67, 68, 75, 76, 77 },
	{ 60, 61, 62, 69, 70, 71, 78, 79, 80 },
};


/* there are 81 cells in a dimension-3 sudoku, and each cell is a
   member of three sets, this array gets filled by the function 
   fill_c2s(), based on the defined contents of the array s2c[][] */
int c2s[NCLL][NGRP];

void
fill_c2s() {
	int s=0, d=0, c;
	for ( ; s<NSET; s++) {
		/* record the first set number each cell is part of */
		for (c=0; c<NDIM*NDIM; c++) {
			c2s[s2c[s][c]][d] = s;
		}
		if ((s+1)%(NGRP*NDIM) == 0) {
			d++;
		}
	}
#if 0
	/* this code available here if you want to see the array
	   cs2[][] that gets created, just change that 0 two lines back
	   to a 1 and recompile */
	for (c=0; c<NCLL; c++) {
		printf("cell %2d: sets ", c);
		for (s=0; s<NGRP; s++) {
			printf("%3d", c2s[c][s]);
		}
		printf("\n");
	}
	printf("\n");
#endif
	return;
}

/* find the row number a cell is in, counting from 1
*/
int
rownum(int c) {
	return 1 + (c/(NDIM*NDIM));
}

/* find the column number a cell is in, counting from 1
*/
int
colnum(int c) {
	return 1 + (c%(NDIM*NDIM));
}

/* find the minor square number a cell is in, counting from 1
*/
int
sqrnum(int c) {
	return 1 + 3*(c/NSET) + (c/NDIM)%NDIM;
}

/* If you wish to add further #defines, put them below this comment,
   then prototypes for the functions that you add

   The only thing you should alter above this line is to complete the
   Authorship Declaration 
*/

/****************************************************************/

#define FIRST_ARRAY_ELEMENT 0
#define HORIZONTAL_PIPE "------+-------+------"
#define VERTICAL_PIPE "|"
#define WHITESPACE " "
#define EMPTY_CELL_VALUE 0
#define EMPTY_CELL "."
#define TRUE 1
#define FALSE 0

/****************************************************************/

void read_data(int arr[], int limit);
void print_sudoku_array(int arr[]);
void print_cell_count(int cell_count);
int unknown_cell_count(int arr[], int num);
int set_to_group_num(int num);
int value_in_array(int num, int arr[], int limit);
int unique_element(int Before[], int After[], int totalnums);
void int_swap(int *p1, int *p2);
void insertion_sort(int A[], int n);
int check_valid_array(int arr[], int *set_violations, int *total_violations);
void array_is_invalid(int valid, int *set_violations, int *total_violations);
void strategy_one(int arr[]);
void ta_daa(int cell_count);

/****************************************************************/

/* Traffic control */
int main(int argc, char *argv[]) {
    fill_c2s();
    int set_violations = 0, total_violations = 0, valid_array = 0;

    /******************* STAGE 1 - READING AND PRINTING *******************/

    // Initializes array, and assigns each cell with a number from the data
    int arr[NCLL];
    read_data(arr, NCLL);

    print_sudoku_array(arr);
    print_cell_count(unknown_cell_count(arr, EMPTY_CELL_VALUE));
    
    /********************** STAGE 2 - GRID CHECKING ***********************/

    valid_array = check_valid_array(arr, &set_violations, &total_violations);

    // Exit immediately if grid chiecking has errors
    array_is_invalid(valid_array, &set_violations, &total_violations);

    /***************** STAGE 3 - IMPLEMENTING STRATEGY ONE ****************/

    strategy_one(arr);
    print_sudoku_array(arr);

    // After exhausting all valid options from Strategy One
    int cell_count = unknown_cell_count(arr, EMPTY_CELL_VALUE);
    print_cell_count(cell_count);
    ta_daa(cell_count);

	return 0;
}

/****************************************************************/

/**
 * @brief Reads an integer into an array arr up to integer limit.
 * 
 * @param    arr                 Array to assign data into.
 * @param    limit               Amount of cells to read data into.
 */
void read_data(int arr[], int limit) {
    for (int i = 0; i < limit; i++) {
        scanf("%d", &arr[i]);
    }
}

/****************************************************************/

/**
 * @brief This function formats a 1-D array into a 9x9 grid, separated
 * by dividers every 3 columns and every 3 lines.
 * 
 * @param    arr                 Sudoku array.
 */
void print_sudoku_array(int arr[]) {
    int line_count = 0;
    printf("\n");
    for (int i = 0; i < NCLL; i++) {
        // Newline at the end of each row
        if (i > FIRST_ARRAY_ELEMENT && !(i % NDIG)) {
            line_count++;
            printf("\n");
        }
        /* Whitespace between each element, 
        excluding the start and end of each row */
        else if (i % NDIG) {
            printf("%s", WHITESPACE);
        }
        // Dividing row every 3 rows
        if (line_count == NDIM) {
            printf("%s\n", HORIZONTAL_PIPE);
            line_count = 0;
        }
        // Dividing column every 3 elements
        else if (i > FIRST_ARRAY_ELEMENT && !(i % NDIM) && (i % NDIG)) {
            printf("%s%s", VERTICAL_PIPE, WHITESPACE);
        }
        // Prints out elements, but period character if element is 0
        if (arr[i] == EMPTY_CELL_VALUE) {
            printf("%s", EMPTY_CELL);
        }
        else {
            printf("%d", arr[i]);
        }
    }
    printf("\n\n");
}

/****************************************************************/

/**
 * @brief Prints out how many cells are unknown.
 * 
 * @param    cell_count          Amount of unknown cells.
 */
void print_cell_count(int cell_count) {
    printf("%2d cells are unknown\n", cell_count);
}

/****************************************************************/

/**
 * @brief Linear search to count how many times integer num appears in the 
 * Sudoku array.
 * 
 * @param    arr                 Sudoku array.
 * @return   int                 Amount of times 0 appears in the array.
 */
int unknown_cell_count(int arr[], int num) {
    int count = 0;
    for (int i = 0; i < NCLL; i++) {
        if (arr[i] == 0) {
            count++;
        }
    }
    return count;
}

/****************************************************************/

/**
 * @brief Returns the group number of a set of a particular cell, if
 * the row, column or square it belongs to is not known.
 * 
 * @param    num                 A set number of a particular cell.
 * @return   int                 The group number of the set number.
 */
int set_to_group_num(int num) {
    return (num % NDIG) + 1;
}

/****************************************************************/

/**
 * @brief Linear search to check if integer num appears in an array.
 * 
 * @param    num                 Integer to look for.
 * @param    arr                 Array to search for num.
 * @param    limit               Amount of elements in the array.
 * @return   int                 Returns 1 if num is in the array, 0 otherwise.
 */
int value_in_array(int num, int arr[], int limit) {
    for (int i = 0; i < limit; i++) {
        if (arr[i] == num) {
            return TRUE;
        }
    }
    return FALSE;
}

/****************************************************************/

/**
 * @brief This function adds unique numbers from array Before to array After.
 * 
 * @param    Before              Array to look for unique elements not in After.
 * @param    After               Empty array that stores unique elements.
 * @param    totalnums           Amount of elements in array Before.
 * @return   int                 Amount of elements in array After.
 */
int unique_element(int Before[], int After[], int totalnums) {
    int distinct_nums = 0;
    for (int i = 0; i < totalnums; i++) {
        int found = 0;
        /* Checks if Before[i] is in array After */
        for (int j = 0; j < distinct_nums; j++) {
            if (Before[i] == After[j]) {
                found = 1;
            }
        }
        /* If Before[i] is not in array After, add Before[i] to array After 
        and increment distinct_nums */
        if (!found) {
            After[distinct_nums++] = Before[i];
        }
    }
    return distinct_nums;
}

/****************************************************************/

/**
 * @brief Swaps two integers using pointers that point to the integer's
 * location in memory.
 * 
 * @param    p1                  Pointer to the first integer.
 * @param    p2                  Pointer to the second integer.
 */
void int_swap(int *p1, int *p2) {
    int tmp;
    tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

/****************************************************************/

/**
 * @brief Sorts an array in ascending order with an average time complexity of
 * O(n^2).
 * 
 * @param    arr                 Array to sort in ascending order.
 * @param    limit               Amount of elements in the array.
 */
void insertion_sort(int arr[], int limit) {
    for (int i = 1; i < limit; i++) {
        for (int j = i - 1; j >= 0 && arr[j+1] < arr[j]; j--) {
            int_swap(&arr[j], &arr[j + 1]);
        }
    }
}

/****************************************************************/

/**
 * @brief This function loop through all 27 sets and checks if there are any
 * duplicate numbers in each set. If there are any, it counts as a violation, 
 * and prints out the group where the violations occur.
 * 
 * @param    arr                 Sudoku array.
 * @param    set_violations      Pointer to the amount of violations that occur
 *                               in the current set (row/column/square).
 * @param    total_violations    Pointer to the amount of total violations.
 * @return   int                 Returns 1 if there is a violation.
 */
int check_valid_array(int arr[], int *set_violations, int *total_violations) {
    int valid_array = 1; // Array is valid until proven false
    /* Loop through every row, column and square to find
    duplicates (if any) of non-zero integers.
    */
    for (int i = 0; i < NSET; i++) {
        int set_array[NDIG] = {0};
        int elements_counted[NDIG] = {0}, elements_counted_index = 0;
        int current_set_violation = 0;
        
        // Determines group name based on set number
        char* set_name = "row";
        if (i >= NDIG && i < NDIG*2) {
            set_name = "col";
        }
        else if (i >= NDIG*2) {
            set_name = "sqr";
        }

        // Assigns each element in each set to set_array
        for (int j = 0; j < NDIG; j++) {
            set_array[j] = arr[s2c[i][j]];
        }

        /* Sorts array in ascending order. Since this array is only 9 elements
        27 times, I don't think qsort will make a big difference in time 
        complexity unless the Sudoku board is expanded. */
        insertion_sort(set_array, NDIG);

        /* Compares each element in set_array against itself. If the element 
        has not been iterated through yet, then increment the counter every
        time it encounters itself, and append to array of elements that have 
        been counted in this set. */
        for (int j = 0; j < NDIG; j++) {
            int count = 0; // Amount of times element J appears
            if (!value_in_array(set_array[j], elements_counted, NDIG) && 
            set_array[j] != 0) {
                for (int k = j; k < NDIG; k++) {
                    if (set_array[j] == set_array[k]) {
                        // Increments count by 1 if it encounters itself
                        count++;
                    }
                }
                elements_counted[elements_counted_index++] = set_array[j];
            }
            if (count > 1) { // Duplicate element found
                valid_array = 0;
                printf("\nset %2d (%s %d): %d instances of %d", i, set_name, 
                    set_to_group_num(i), count, set_array[j]);
                // If previous elements in this current set has duplicates.
                if (current_set_violation) {
                    (*total_violations)++;
                }
                else {
                    (*set_violations)++;
                    (*total_violations)++;
                }
                current_set_violation = 1;
            }
        }
    }
    return valid_array;
}

/****************************************************************/

/**
 * @brief If the array is invalid after being checked with check_valid_array,
 * print out how many violations occured and exit immediately.
 * 
 * @param    valid               0 if array is invalid, 1 if array is valid.
 * @param    set_violations      Pointer to the amount of violations that occur
 *                               in the current set (row/column/square).
 * @param    total_violations    Pointer to the amount of total violations.
 */
void array_is_invalid(int valid, int *set_violations, int *total_violations) {
    if (!valid) {
        printf("\n\n%d different sets have violations\n"
            "%d violations in total\n", *set_violations, *total_violations);
        exit(EXIT_FAILURE);
    }
}

/****************************************************************/

/**
 * @brief Strategy One solves easy-grade sudokus on a pass-by-pass basis. It 
 * loops through all 81 cells in the Sudoku array and checks the 24 
 * 'cell mates' to see if there is 1 valid option left. If so, the valid number 
 * will be added to an empty 81-element array 'checking array' in its 
 * corresponding location.
 * 
 * Once valid options are added to the checking array, the function will loop
 * through the checking array and checks if the valid options have any
 * duplicate cellmates. If not, this number is valid and is added onto the
 * real Sudoku array.
 * 
 * If a valid option is added from the checking array to the Sudoku array,
 * this function will be called again to see if the updated Sudoku array can
 * yield any more valid options. 
 * 
 * @param    arr                 Sudoku array.
 */
void strategy_one(int arr[]) {
    int checking_array[NCLL] = {0};
    int updated_array = 0;
    int printed_header = 0; // If this pass printed the header already

    // Loop  through all 81 cells that need to be solved.
    for (int i = 0; i < NCLL; i++) {
        if (arr[i] == 0) {
            // Contains the 3 sets of cell i.
            int cell_set_nums[NDIM] = {0};
            // Up to 24 cell mates of cell i.
            int cell_mates[(NDIG-1)*NDIM] = {0}, cell_mates_index = 0;
            int distinct_cell_mates[NDIG] = {0};

            /* The total sum of numbers 1 to 9 is 45. Used to calculate 
            missing and final number of an empty cell, if there are 8 unique 
            cell mates. */
            int total_1_9 = 45, count = 0, missing_num = 0;

            for (int j = 0; j < NDIM; j++) {
                cell_set_nums[j] = c2s[i][j]; // 3 sets of cell i
            }

            /* Loops through all positions of each 3 sets in cell_set_nums
            in the array. */
            for (int j = 0; j < NDIM; j++) { 
                for (int k = 0; k < NDIG; k++) {
                    if (arr[s2c[cell_set_nums[j]][k]] != 0) {
                        /* Append each element the 3 sets to cell_mates 
                        except for 0's (which includes itself). */
                        cell_mates[cell_mates_index++] = 
                            arr[s2c[cell_set_nums[j]][k]];
                    }
                }
            }

            // Finds unique elements of array cell_mates
            int distinct_num = unique_element(cell_mates, 
                distinct_cell_mates, cell_mates_index);

            /* Find remaining number (it is a valid number) and adds it to 
            the checking array in its corresponding position in the real
            Sudoku array. */
            if (distinct_num == 8) {
                for (int n = 0; n < distinct_num; n++) {
                    count += distinct_cell_mates[n];
                }
                missing_num = total_1_9 - count;
                checking_array[i] = missing_num;
            }
        }
    }
    
    /* Go through values in checking_array, and if the value is valid (it does
    not have any duplicate cell mates), put that in the actual Sudoku array */
    for (int i = 0; i < NCLL; i++) {
        if (checking_array[i] != 0) {
            int valid = 1;
            int cell_set_nums[NDIM] = {0};

            // 3 sets of cell i
            for (int j = 0; j < NDIM; j++) {
                cell_set_nums[j] = c2s[i][j];
            }

            /* Loops through all positions of each 3 sets in cell_set_nums
            in the array. */
            for (int j = 0; j < NDIM; j++) {
                for (int k = 0; k < NDIG; k++) {
                    /* If the element in the array is the same, but the 
                    position in the array is different */
                    if (checking_array[s2c[cell_set_nums[j]][k]] == 
                        checking_array[i] && 
                        s2c[cell_set_nums[j]][k] != i) {
                        valid = 0;
                    }
                } 
            }
            
            // If all of the elements in checking_array are valid
            if (valid) {
                if (!printed_header) {
                    printf("\nstrategy one\n");
                    printed_header = 1;
                }
                updated_array = 1;
                arr[i] = checking_array[i];
                printf("row %d col %d must be %d\n", rownum(i), colnum(i), 
                    checking_array[i]);
            } 
        }
    }

    // Recurses to see if the new positions can yield more valid positions
    if (updated_array && unknown_cell_count(arr, EMPTY_CELL_VALUE)) {
        strategy_one(arr);
    }
}

/****************************************************************/

/**
 * @brief If there are no unknown cells remaining, celebrate.
 * 
 * @param    cell_count          Amount of unknown cells.
 */
void ta_daa(int cell_count) {
    if (!cell_count) {
        printf("\nta daa!!!\n");
    }
}

/****************************************************************/

/* Algorithms are fun :) */