/*
  Name: Wei Da Chen
  Date: 10/11/2021
*/

/*
Main file for Part2(a) of Homework 2.
This file includes program, query_tree, which uses the parser to create a search tree
and then allow the user to query it using a recognition sequence. If that	sequence
exists in	the	tree then	this routine should	print	all	the	corresponding	enzymes
that correspond	to that recognition	sequence.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

#include "avl_tree.h"
#include "bst_tree.h"
#include "sequence_map.h"

namespace {

string extraction(string &db_line) {
  size_t slash = db_line.find('/');
  string str = db_line.substr(0, slash);
  db_line = db_line.substr(slash+1);
  return str;
}

// @db_filename: an input filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void QueryTree(const string &db_filename, TreeType &a_tree) {
  // Code for running Part2(a)
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

  // Then prompt the user for exactly three strings (do a loop) and
  // provide the results of find() as described in the assignment.
  vector<string> recSequenceInput;
  int j = 0;
  while (j < 3) {
    cin >> recSequence;
    recSequenceInput.push_back(recSequence);
    j++;
  }

  for (int k = 0; k < 3; k++) {
    a_tree.getSeq(recSequenceInput[k]);
  }

}

}  // namespace

int
main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string param_tree(argv[2]);
  cout << "Input filename is " << db_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST") {
    BinarySearchTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  } else if (param_tree == "AVL") {
    AvlTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  } else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
