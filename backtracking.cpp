//Andrew Jones
//This algorithm uses the N-Queens problem backtracking algorithm to solve the 0-1 Knapsack problem
#include <iostream>
#include <iomanip>
#include<fstream>
#include<string>
#include<cstdlib>
#include<ctime>
#include <stdio.h>    
#include <stdlib.h>     
#include <time.h> 
#include <new>
#include <algorithm>
#include<functional>
using namespace std;
#include "randGenFile.h"

int i, n, W; //given from the person (or from reading a file)
int *bestset = new int[n];
int *include = new int[n];
int *p = new int[n];  //index from 1 to n, sorted by p[i]/w[i]
int *w = new int[n]; //index from 1 to n, sorted by p[i]/w[i]
string name;
int weight;
int profit;
int numbest = 0;
int maxprofit = 0;
string name1;
double ratio;

void file() {
	randGenFile();

	ifstream inFile; 	//reading from a specified file
	string filename;
	cout << "Please enter a file name: ";
	cin >> filename;
	inFile.open (filename.c_str());
	//int W; //this is causing SegFault when removed!!
	inFile >> n >> W >> name >> profit >> weight;
	for(int u=0; u<n;u++) {
		inFile >> name1;
		inFile >> p[n];   //insert column values for profit into dynamic array p
		inFile >> w[n];  //insert column values for weight into dynamic array w
	}
	
	std::sort(p, p+n, std::greater<int>());   //sort the p array
	std::sort(w, w+n, std::greater<int>()); //sort the w array

	while(inFile >> name >> profit >> weight)
	{
		ratio = (double)profit/weight;
	}

	inFile.close();
}

bool promising(int i) {
	int j, k;
	int totweight;
	float bound;
	
	if(weight >= W) {
		return false;
		cout << "test";
	}
	else {
		j = i+1;
		bound = profit;
		totweight = weight;
		while (j<= n && totweight + w[j] <= W) {
			totweight = totweight + w[j];
			bound = bound + p[j];
			j++;
		}
		k = j;
		if (k <= n) {
			bound = bound + (W-totweight) * p[k]/w[k];
		}
		return bound > maxprofit;
	}
}

void backtracking(int i, int profit, int weight) {
	if(weight <= W && profit > maxprofit) {
		maxprofit = profit;
		numbest = i;
		bestset = include;
	}
	
	if(promising(i)) {
		include[i+1] = 1;					// include w[i+1]
		backtracking(i+1, profit + p[i+1], weight + w[i+1]);
		include[i+1] = 0;						// do not include w[i+1]
		backtracking(i+1, profit, weight);
	}
}

int main() 
{
	cout<< "Welcome to the Backtracking algorithm for the 0-1 Knapsack problem!" << endl;
	
	file();

	backtracking(i, profit, weight);
	cout << "The maximum profit is: " << maxprofit << endl;			//maximum profit
	cout << "The best set is: ";
	for (i=1; i <= n; i++) {
		cout << bestset[i];		//show optimal set of items
	}
	cout << endl;
	delete [] bestset;  //delete the dynamic arrays
	delete[] include;
	delete[] p;
	delete[] w;
	return 0;
}