# Sparse matrix

A sparse matrix implementation in C.  

## Description

In numerical analysis and scientific computing, a sparse matrix is a matrix in which most of the elements are zero. [Read more](https://en.wikipedia.org/wiki/Sparse_matrix). Sparse data is by nature more easily compressed and thus requires significantly less storage. The usual operations over this kind of matrix (for example, sum and multiplication) can also be done more efficiently if we do not store the positions that contains zeros. This project is a implementation of a sparse matrix as well as some operations that can be performed over it.

## How to get started

First you should define your matrices. 

### Matrix format
Some examples of matrix formats can be found on the folder `example input files`. 

The first line represents the number of columns and lines of the matrix. The following lines represents the position (line and column) and value of the matrix. All values in a line are separated by spaces.

For example, the input:

```
4 4
1 1 50.0
2 1 10.0
2 3 20.0
4 1 -30.0
4 3 -60.0
4 4 5.0
```
Would result in the following matrix:

```
50.00	0.00	0.00	0.00
10.00	0.00	20.00	0.00
0.00	0.00	0.00	0.00
-30.00	0.00	-60.00	5.00
```
### Available operations

The following operations are available:
 - Read
 - Insert
 - Print
 - Sum
 - Multiply
 - Delete

On the file `main.c` some examples of usage of the operations are available. Change it according to your needs.

### Run the project

In order to run it you can just open your terminal within the project root and type:

```bash
make
```
The used compiler is [gcc](https://gcc.gnu.org/).
