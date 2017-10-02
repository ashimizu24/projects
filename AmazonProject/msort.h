#include <iostream>
#include <vector>
#include "review.h"
#include "product.h"
#include "mydatastore.h"

using namespace std; 
template <class T, class Comparator>
void mergeSort (std::vector<T>& myArray, Comparator comp);

template <class T, class Comparator>
void msort(std::vector<T>& myArray, std::vector<T>& output, int start, int end, Comparator comp);

template <class T, class Comparator>
void merge(std::vector<T>& myArray, std::vector<T>& output, int s1, int e1, int s2, int e2, Comparator comp);

struct suggestionsComp {
	bool operator()(const std::pair<std::string, double> first, const std::pair<std::string, double> second) 
    {  
      return (first.second > second.second); 
    }
};

struct intComp {
    bool operator()(const int first, const int second) 
    {  
      return first < second; 
    }
};

struct reviewComp{
	bool operator()(const Review* r1, const Review* r2) 
    {  
      return r1->date < r2->date; 
    }
};

struct prodNameComp{
	bool operator()(const Product* p1, const Product* p2) 
    {  
      return p1->getName() < p2->getName(); 
    }
};

struct prodReviewComp{
	bool operator()(const Product* p1, const Product* p2) 
    { 
      return p1->getAvgRating() > p2->getAvgRating(); 
    }
};

template <class T, class Comparator>
void mergeSort (std::vector<T>& myArray, Comparator comp)
{
	if(myArray.size()<=1){
		return;
	}
	std::vector<T> copy(myArray);
	msort(copy, myArray, 0, myArray.size(), comp);
}	

template <class T, class Comparator>
void msort(std::vector<T>& myArray, std::vector<T>& output, int start, int end, Comparator comp){
	if((end-start)==1){

	}
	else {
		int mid = (start+end)/2;
		msort(myArray, output, start, mid, comp);
		msort(myArray, output, mid, end, comp);
		merge(output, start, mid, mid, end, comp);
		}
}

template <class T, class Comparator>
void merge(std::vector<T>& output, int s1, int e1, int s2, int e2, Comparator comp){
	vector<T> temp;
	T last;
	
	while(s1 < e1 && s2 < e2 ){
		if(s1==s2) break;
		if(comp(output[s1], output[s2])){ //s1 is less
			temp.push_back(output[s1]);
			last = output[s2];
			s1++;
		}
		else{
			temp.push_back(output[s2]);
			last = output[s1];
			s2++;
		}
	}
	temp.push_back(last);

	int j=0;
	int start = e2-temp.size();
	for(int i=start; i<e2; i++){
		output[i] = temp[j];
		j++;
	}	
}
