/*#include "msort.h"
#include <iostream>
using namespace std;



struct intComp {
    bool operator()(const int lhs, const int rhs) 
    { // Uses string's built in operator< 
      // to do lexicographic (alphabetical) comparison
      return lhs < rhs; 
    }
  };

  struct AlphaStrComp {
      bool operator()(const string& lhs, const string& rhs) 
      { // Uses string's built in operator< 
        // to do lexicographic (alphabetical) comparison
        return lhs < rhs; 
      }
    };

    struct LengthStrComp {
    bool operator()(const string& lhs, const string& rhs) 
    { // Uses string's built in operator< 
      // to do lexicographic (alphabetical) comparison
      return lhs.size() < rhs.size(); 
    }
  };
  


int main()
{
	// vector<int> arrA = {1, 8, 11, 79, 91};
	// vector<int> arrB = {2, 12, 60 , 80, 100, 102};
		
	// vector<int> arrC = merge(arrA, arrB);

	intComp myIntComp;
	AlphaStrComp myAlphaStrComp;
	LengthStrComp myLengthStrComp;


	vector<string> arrA;
	vector<int> arrB;
	vector<string> arrC;

	arrA.push_back("a");
	arrA.push_back("b");
	arrA.push_back("e");
	arrA.push_back("d");
	arrA.push_back("c");

	arrB.push_back(10);
	arrB.push_back(8);
	arrB.push_back(6);
	arrB.push_back(4);
	arrB.push_back(2);
	arrB.push_back(1);
	arrB.push_back(3);
	arrB.push_back(5);
	arrB.push_back(7);
	arrB.push_back(9);

	arrC.push_back("1");
	arrC.push_back("333");
	arrC.push_back("22");
	arrC.push_back("55555");
	arrC.push_back("4444");

	mergeSort(arrC, myLengthStrComp);

	for(unsigned int i=0; i<arrC.size(); i++)
		cout << arrC[i] << " ";

	cout << endl;
}*/