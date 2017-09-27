#include "msort.h"
#include <iostream>
using namespace std;



int main()
{
	intComp myIntComp;
	AlphaStrComp myAlphaStrComp;
	LengthStrComp myLengthStrComp;


	vector<string> arrA;
	vector<int> arrB;
	vector<string> arrC;

	arrA.push_back("apple");
	arrA.push_back("bbananan");
	arrA.push_back("eegg");
	arrA.push_back("dance");
	arrA.push_back("ccar");

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

	merge_sort(arrC, myLengthStrComp);
	merge_sort(arrA, myAlphaStrComp);

	for(unsigned int i=0; i<arrC.size(); i++)
		cout << arrC[i] << " ";

	for(unsigned int i=0; i<arrA.size(); i++)
		cout << arrA[i] << " ";

	//merge_sort(arrA, myIntComp);
	//for(unsigned int i=0; i<arrA.size(); i++)
	//	cout << arrA[i] << " ";



	cout << endl;
	return 0;
}