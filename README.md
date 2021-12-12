# sudoku-solver

Sudoku assistant to help people solve easy-difficulty sudoku puzzles. 

# Introduction

The goal of Sudoku is to complete a square grid of 9x9 cells using the numbers from 1 to 9, in a way that has exactly one instance of each digit appearing in each column, row and 3x3 sub-square. For example in Figure 1, the cell marked with the red circle must be a "7" since every other possible value appears in at least one of the three sets (row, purple; column, blue; and sub-square, green) that cell is a member of. All the other cells in the example can be determined using the same strategy.

![Figure 1](https://github.com/lohchness/sudoku-solver/blob/main/fig1.png?raw=true)

*Figure 1: An "Easy" sudoku.*

This program is a sudoku assistant to help people solve sudoku puzzles. Functions carry out checking for numbering violations and identifying valid cells throughout each iteration.

### The program itself

The input is a set of 81 1-digit numbers, laid out as a sudoku grid, and "0" used to represent empty cells. Figure 2 illustrates this manner, and you can inspect the .txt files for more information.

![Figure 2](https://github.com/lohchness/sudoku-solver/blob/main/fig2.png?raw=true)

*Figure 2: Input data1.txt (left); corresponding Stage 1 output (center); input data2.txt (right)*

The program will first check through the input and detect any illegal cells, such as a set having the same instance of values, as shown in Figure 3.

![Figure 3](https://github.com/lohchness/sudoku-solver/blob/main/fig3.png?raw=true)

*Figure 3: Stage 2 output (data2.txt)*

Next, there are recursive algorithms of detecting possible values in the grid. The first algorithm  considers each cell `c` in turn. The three sets that cell is a member of should be examined, accumulating label counts from the (up to) 24 labeled cells in those three sets. Each of those labels is a number between 1-9. Hence if there is only one of those possible nine possible numbers that does not yet occur anywhere in `c`'s three sets, then it must be the label for `c`. Figure 4 visualizes this process.

![Figure 4](https://github.com/lohchness/sudoku-solver/blob/main/fig4.png?raw=true)

*Figure 4: The visualization of the linearization. The two-dimensional grid at the top shows the row-major mapping; the one-dimensional array at the bottom is what actually stores the sudoku grid values. The example shows the sudoku from Figure 1.*

The second algorithm determines which values remain possible options for every unlabeled cell `c`, eliminating based on the labeled cells in each of `c`'s three sets; and then checks out each of the 27 sets in order. If a set has only one unlabeled cell able to take on one of that set's unused labels, then that label can be assigned to that cell. 

The first and second algorithm are alternated, iterating until no further changes occur. In that case, the program prints the state of the puzzle, and if the sudoku has been solved, prints out the line "ta daa!!!" (Figure 5).

![Figure 5](https://github.com/lohchness/sudoku-solver/blob/main/fig5.png?raw=true)

*Figure 5: Stage 3 output for data1.txt*
