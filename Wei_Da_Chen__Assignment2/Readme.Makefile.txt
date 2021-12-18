i.) All parts of Assignment 2 have been completed and compiles successfully.
ii.) Majority of the bugs I encountered were runtime errors from not accessing
the right elements and objects.
iii.)
To compile on terminal
  make clean
  make all
  ./query_tree rebase210.txt BST
  ./test_tree rebase210.txt	sequences.txt	AVL

To run with a given file that is redirected to standard input:
  ./query_trees	rebase210.txt	BST	<	input_part2a.txt
  ./query_trees	rebase210.txt	AVL	<	input_part2a.txt

iv.)
Part2(a)
Input:
  CC'TCGAGG
  TTA'TAA
  TC'C

Output:
  AbsI
  AanI PsiI
  Not Found

Input files:
	input_part2a.txt
	rebase210.txt
	sequences.txt

<------------------------------------------------------------>

You will use this exact Makefile for your Homework 2. Do not submit it!

You can compile everything by typing

make all

You can compile one program individually by just typing make <Program Name>, for example

make query_tree

By typing

make clean

You delete all .o files and executables.
