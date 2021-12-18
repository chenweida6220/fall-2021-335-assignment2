/*
  Name: Wei Da Chen
  Date: 10/11/2021
*/

/*
Main file for Part2(c) of Homework 2.
This file contains the executable test_tree_mod and when run, the results should be
the same as Part2(b).
*/

// Code will compile and run after you have completed sequence_map.h.

#include "avl_tree.h"
#include "bst_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

namespace {
  string extraction(string &db_line) {
    size_t slash = db_line.find('/');
    string str = db_line.substr(0, slash);
    db_line = db_line.substr(slash+1);
    return str;
  }

// @db_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType> void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree) {
  // Code for running Part2(c)

  // Part1: Parses the	database and	construct	a	search tree
  // Parse input file @db_filename and feel tree @a_tree
  ifstream input_file(db_filename);
  string db_line;
  string enzAcronym;
  string recSequence;

  if (input_file.fail()) {
    cerr << "Error in opening File" << endl;
    exit(EXIT_FAILURE);
  }

  // Skips over the first 10 header lines in rebase210.txt
  for (int i = 0; i < 10; i++) {
    getline(input_file, db_line);
  }

  // Parsing the data
  while (getline(input_file, db_line)) {
    if (db_line.empty()) {
      continue;
    }

    enzAcronym = extraction(db_line);

    while(db_line.length() > 2) {
      recSequence = extraction(db_line);
      SequenceMap sequence_map(recSequence, enzAcronym);
            a_tree.insert(sequence_map);
        }
  }
  input_file.close();

  // Part2: Prints the	number of nodes	in your tree n
  int sumNodes = a_tree.totalNodes();
  cout << "2: " << sumNodes << endl;

  // Part3: Computes the average depth of the search tree (internal path divided by n)
  // Part3(a): Prints the average depth
  float averageDepth = float(a_tree.depthOfTree(0)) / float(sumNodes);
  cout << "3a: " << averageDepth << endl;
  // Part3(b): Prints the ratio of the average depth to log2n
  float ratio = averageDepth / log2(sumNodes);
  cout << "3b: " << ratio << endl;

  /* Part4: Searches the tree for each string in sequences.txt. Also counts the total
  number of recursive calls for all executions of find()*/
  // Part4(a): Prints the total number of successful queries (# of strings found)
  string word;
  int counter = 0;
  ifstream seq_file(seq_filename);
  int successful_queries = 0;
  while(seq_file >> word)
  {
    SequenceMap tempMap(word, "");

    if (a_tree.contains(tempMap, counter)) {
      successful_queries++;
    }
  }
  seq_file.close();
  cout << "4a: " << successful_queries << endl;
  // Part4(b): Prints the average # of recursion calls (# of recursion calls/# of queries)
  seq_file.open(seq_filename);
  int recursion_counter = 0;
  while(seq_file >> word)
  {
    SequenceMap map(word, "");
    a_tree.contains(map, recursion_counter);
  }
  seq_file.close();
  cout << "4b: " << float(recursion_counter) / successful_queries << endl;

  /* Part5: Removes every other sequence in sequences.txt from the tree. Also counts the total #
  of recursion calls for all executions of remove()*/
  // Part5(a): Prints the total number of successful removes.
  seq_file.open(seq_filename);
  int state = 0;
  int delete_counter = 0;
  while(getline(seq_file, word)) {
    if(state % 2 == 0) {
      SequenceMap tempMap(word, "");
      if (a_tree.contains(tempMap, counter)) {
        a_tree.remove(tempMap, delete_counter);
      }
    }
    state++;
  }
  seq_file.close();
  cout << "5a: " << (sumNodes - a_tree.totalNodes()) << endl;
  // Part5(b): Prints the average # of recursion calls (total # of recursion calls/# of remove calls)
  cout << "5b: " << float(delete_counter) / (sumNodes - a_tree.totalNodes()) << endl;

  // Part6: Redo steps 2 and 3
  // Part6(a): Prints # of nodes in tree
  sumNodes = a_tree.totalNodes();
  cout << "6a: " << sumNodes << endl;
  // Part6(b): Prints the average depth
  averageDepth = float(a_tree.depthOfTree(0)) / sumNodes;
  cout << "6b: " << averageDepth << endl;
  // Part6(b): Prints the ratio of the average depth to log2n
  ratio = averageDepth / log2(sumNodes);
  cout << "6c: " << ratio << endl;
}

}  // namespace

int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string seq_filename(argv[2]);
  cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
  AvlTree<SequenceMap> a_tree;
  TestTree(db_filename, seq_filename, a_tree);

  return 0;
}
