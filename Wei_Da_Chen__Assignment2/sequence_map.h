/*
  Name: Wei Da Chen
  Date: 10/11/2021
	Header file: sequence_map.h
*/

/*
This file is a header for sequence_map.cpp

sequence_map nontemplated class has private data members of:
        string	recognition_sequence_	;
				vector<string>	enzyme_acronyms_;
and will be used in the following programs.
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class SequenceMap {
private:
    string recognition_sequence_;
    vector<string> enzyme_acronyms_;

public:
  // Start of Big-Five
  SequenceMap(const SequenceMap &rhs) = default; // Copy constructor
  SequenceMap(SequenceMap &&rhs) = default; // Move constructor
  SequenceMap &operator=(const SequenceMap &rhs) = default; // Copy-assignment operator
  SequenceMap &operator=(SequenceMap &&rhs) = default; // Move-assignment operator
  ~SequenceMap() = default; // Destructor
  // End of Big-Five

  // Constructs a SequenceMap from 2 strings
  SequenceMap(const string &a_rec_seq, const string &an_enz_acro) {
    recognition_sequence_ = a_rec_seq;
    enzyme_acronyms_.push_back(an_enz_acro);
  }

  // Operates based on the regular string comparison between the recognition_sequence_ strings//String comparison operator
  bool operator<(const SequenceMap &rhs) const {
    return recognition_sequence_ < rhs.recognition_sequence_;
  }

  // Overloaded << operator for SequenceMap
  friend ostream &operator<<(ostream &out, const SequenceMap &anotherMap) {
    for (unsigned i = 0; i < anotherMap.enzyme_acronyms_.size(); i++) {
      out << anotherMap.enzyme_acronyms_[i] << " ";
    }
    return out;
  }

  /* The function	Merge() merges	the	other_sequence.enzyme_acronym_ with	the
  object’s	enzyme_acronym_. The	other_sequence object	will	not	be affected. This
  function assumes	that	the	object’s	recognition_sequence_ and
  other_sequence.recognition_sequence_ are	equal	to	each	other.*/
  void Merge(const SequenceMap &other_sequence)
  {
      if (recognition_sequence_ == other_sequence.recognition_sequence_) {
        for (unsigned i = 0; i < other_sequence.enzyme_acronyms_.size(); i++) {
          enzyme_acronyms_.push_back(other_sequence.enzyme_acronyms_[i]);
        }
      }
  }

  void printEnzAcronyms() {
      for (unsigned i = 0; i < enzyme_acronyms_.size(); i++) {
        cout << enzyme_acronyms_[i] << " ";
      }
      cout << endl;
  }

  string getRecSequence() {
      return recognition_sequence_;
  }

};
