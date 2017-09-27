#ifndef MSORT_H
#define MSORT_H

#include <string>
#include <iostream>
#include <set>
#include <vector>
#include <iostream>
#include <vector>
#include "product.h"
#include <sstream>

using namespace std;

struct intComp {
    bool operator()(const int lhs, const int rhs) 
    { 
      return lhs < rhs; 
    }
  };

  struct AlphaStrComp {
      bool operator()(const string& lhs, const string& rhs) 
      { 
        return lhs < rhs; 
      }
    };

    struct LengthStrComp {
    bool operator()(const string& lhs, const string& rhs) 
    { 
      return lhs.size() < rhs.size(); 
    }
  };
  struct ProductName {
  	bool operator()(const Product* lhs, const Product* rhs)
  	{
  		return lhs->getName() < rhs->getName();
  	}
  };
  struct Ratings {
  	bool operator()(Product* lhs, Product* rhs)
  	{
  		vector<int> rating1 = lhs->getRatings();
  		vector<int> rating2 = rhs->getRatings();

  		double sum1 = 0; 
  		double sum2 = 0;
  		for (unsigned int i = 0; i < rating1.size(); i++)
  			sum1 += rating1[i];
  		for (unsigned int i = 0; i < rating2.size(); i++)
  			sum2 += rating2[i];

  		sum1 = sum1/rating1.size();
  		sum2 = sum2/rating2.size();

  		return sum2 < sum2; 
  	}
  };
  struct ReviewDate {
  	bool operator()(const Review* lhs, const Review* rhs)
  	{
  		stringstream ss1(lhs->date);
  		stringstream ss2(rhs->date);

  		int y1;
  		int y2;
  		int m1;
  		int m2;
  		int d1;
  		int d2;
  		ss1 >> y1 >> m1 >> d1;
  		ss2>> y2 >> m2 >> d2;

  		if (y1 != y2)
  			return y2 < y1;
  		else if (m1 != m2)
  			return m2 < m1;
  		else
  			return d2 < d1;
  	}

  };


template <class T, class Comparator>
void merge(std::vector<T> &mylist, std::vector<T> &output, int s1, int e1, int s2, int e2, Comparator comp) {

    int index = s1;
    while (s1 <= e1 && s2 <= e2) {
        if (comp(mylist[s1],mylist[s2])) {
            output[index++] = mylist[s1++];
        } else {
            output[index++] = mylist[s2++];
        }
    }
    while (s1 <= e1) {
        output[index++] = mylist[s1++];
    }
    while (s2 <= e2) {
        output[index++] = mylist[s2++];
    }
}

template <class T, class Comparator>
void msort(std::vector<T> &mylist, std::vector<T> &output, int start, int end, Comparator comp) {

    // base case
    if (start >= end) {
        return;
    }

    // recursive calls
    int mid = (start + end) / 2;

    msort(mylist, output, start, mid, comp);
    msort(mylist, output, mid + 1, end, comp);

    // merge
    merge(mylist, output, start, mid, mid + 1, end, comp);
    mylist = output;
}

template <class T, class Comparator>
void merge_sort(std::vector<T> &mylist, Comparator comp) {

    std::vector<T> other(mylist);  // copy of array

    // use other as the source array, mylist as the output array
    msort(other, mylist, 0, other.size() - 1, comp);
}
#endif
