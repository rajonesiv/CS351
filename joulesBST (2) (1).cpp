//Lauren Hannemann and Andrew Jones
//Joule Thief

#include <iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<ctime>
#include <stdio.h>    
#include <stdlib.h>     
#include <time.h> 
#include "randFileGen.hpp"
using namespace std;

class Item
{
	string name;
	int profit, weight;
	public:
	Item (string, int, int);
	double ratio() {return (double)profit/weight;}
};

Item::Item (string a, int y, int x) {
  name = a;
  weight = x;
  profit = y;
}

class BinarySearchTree
{
    public:
        struct tree_node
        {
           tree_node* left;
           tree_node* right;
           double ratio;
		   int profit; 
		   int weight;
		   string name;
		   	void print() {
				cout << "Item name: " << name << " Pesos: " << profit << " Weight: " << weight << " " << endl;
			}
        };
		

		tree_node* returnNodePrivate(double ratio, tree_node* Ptr);
		double findLargestPrivate(tree_node* Ptr);
		void removeNodePrivate(double ratio, tree_node* parent);
		void removeRootMatch();
		void removeMatch(tree_node* parent, tree_node* match, bool left);
		
        tree_node* root;
   
        BinarySearchTree()
        {
           root = NULL;
        }
       
        bool isEmpty() const { return root==NULL; }
        void insert(string, int, int, double);
		tree_node* returnNode(double ratio);
		double findLargest();
		void removeNode(double ratio);

};

void BinarySearchTree::insert(string m, int p, int w, double r)
{
    tree_node* t = new tree_node;
    tree_node* parent;
	t->name = m;
	t->profit = p;
	t->weight = w;
    t->ratio = r;
    t->left = NULL;
    t->right = NULL;
    parent = NULL;
    
	
    if(isEmpty()) root = t;
    else
    {
        tree_node* curr;
        curr = root;
        while(curr)
        {
            parent = curr;
            if(t->ratio > curr->ratio) curr = curr->right;
            else curr = curr->left;
        }
		

        if(t->ratio < parent->ratio)
           parent->left = t;
        else
           parent->right = t;
    }
}

BinarySearchTree::tree_node* BinarySearchTree::returnNode(double ratio)
{
	return returnNodePrivate(ratio, root);
}

BinarySearchTree::tree_node* BinarySearchTree::returnNodePrivate(double ratio, tree_node* Ptr)
{
	if(Ptr != NULL)
	{
		if(Ptr->ratio == ratio)
		{
			return Ptr;
		}
		else
		{
			if(ratio < Ptr->ratio)
			{
				return returnNodePrivate(ratio, Ptr->left);
			}
			else{
				return returnNodePrivate(ratio, Ptr->right);
			}
		}
	}
	else{
		return NULL;
	}
}

double BinarySearchTree::findLargest()
{
	return findLargestPrivate(root);
}

double BinarySearchTree::findLargestPrivate(tree_node* Ptr)
{
	if(root == NULL)
	{
		cout << "The tree is empty\n";
		return -1000;
	}
	else 
	{
		if(Ptr->right != NULL)
		{
			return findLargestPrivate(Ptr->right);
		}
		else
		{
			return Ptr->ratio;
		}
	}		
	
}

void BinarySearchTree::removeNode(double ratio)
{
	removeNodePrivate(ratio, root);
}

void BinarySearchTree::removeNodePrivate(double ratio, tree_node* parent)
{
	if(root != NULL)
	{
		if(root->ratio == ratio)
		{
			removeRootMatch();
		}
		else
		{
			if(ratio < parent->ratio && parent->left != NULL)
			{
				parent->left->ratio == ratio ?
				removeMatch(parent, parent->left, true):
				removeNodePrivate(ratio, parent->left); 
			}
			else if(ratio > parent->ratio && parent->right != NULL)
			{
				parent->right->ratio == ratio ?
				removeMatch(parent, parent->right, false):
				removeNodePrivate(ratio, parent->right); 
			}
			else
			{
				cout << "The ratio " << ratio << " was not found.\n";
			}
		}
	}
	else
	{
		cout << "Tree is empty\n";
	}
}

void BinarySearchTree::removeRootMatch()
{
	if(root!= NULL)
	{
		tree_node* delPtr =root;
		int rootratio = root->ratio;
		int largestInLeftSubtree;
		
		if(root->right ==NULL && root->left == NULL)
		{
			root =NULL;
			delete delPtr;
		}
		else if(root->left == NULL && root->right !=NULL)
		{
			root = root->right;
			delPtr->right = NULL;
			delete delPtr;
		}
		else if(root->left != NULL && root->right ==NULL)
		{
			root = root->left;
			delPtr->left = NULL;
			delete delPtr;
		}
		else
		{
			largestInLeftSubtree = findLargestPrivate(root->left);
			removeNodePrivate(largestInLeftSubtree, root);
			root->ratio = largestInLeftSubtree;
		}
	}
	else
	{
		cout << "Tree is empty.";
	}
}

void BinarySearchTree::removeMatch(tree_node* parent, tree_node* match, bool left)
{
	if(root != NULL)
	{
		tree_node* delPtr;
		int matchratio = match->ratio;
		int largestInLeftSubtree;
		
		if(match->left == NULL && match->right ==NULL)
		{
			delPtr = match;
			left == true ? parent->left = NULL : parent->right = NULL;
			delete delPtr;
		}
		else if(match->left == NULL && match->right !=NULL)
		{
			left == true ? parent->left = match->right : parent->right = match->right;
			match->right = NULL;
			delPtr = match;
			delete delPtr;
		}
		else if(match->left != NULL && match->right ==NULL)
		{
			left == true ? parent->left = match->left : parent->right = match->left;
			match->left = NULL;
			delPtr = match;
			delete delPtr;
		}
		else
		{
			largestInLeftSubtree = findLargestPrivate(match->left);
			removeNodePrivate(largestInLeftSubtree, match);
			match->ratio = largestInLeftSubtree;
		}
	}
	else{
		cout << "tree is empty\n";
	}
}

int main()
{
	
	randFileGen();
	
	BinarySearchTree b;
	
	ifstream inFile;
	string filename;
	cout << "Please enter a file name: ";
	cin >> filename;
	inFile.open (filename.c_str());
	int numberOfItems;
	int knapCap;
	inFile >> numberOfItems >> knapCap;
	string name1;
	int weight1;
	int profit1;
	double ratio1;

	while(inFile >> name1 >> profit1 >> weight1)
	{
		ratio1 = (double)profit1/weight1;
		b.insert(name1, profit1, weight1, ratio1);
	}
	
	inFile.close(); 
	
	double maxRatio;
	int totalProfit=0;
	int totalWeight=0;
	
	cout << endl;
	
	BinarySearchTree::tree_node* currNode;
	int numLeft = numberOfItems;
	int totalItemsAdded=0;
	
	int profit[numberOfItems];
	int weight[numberOfItems];
	string name[numberOfItems];
	
	int arrayPos = 0;
	
	while(numLeft > 0)
	{
		maxRatio = b.findLargest();
		currNode = b.returnNode(maxRatio);	

		if(currNode->weight < knapCap-totalWeight)
		{
			totalWeight += currNode->weight;
			totalProfit += currNode->profit;
			profit[arrayPos] = currNode->profit;
			weight[arrayPos] = currNode->weight;
			name[arrayPos] = currNode->name;
			b.removeNode(maxRatio);
			totalItemsAdded++;
			arrayPos++;
		}
		else
		{
			b.removeNode(maxRatio);
		}
		
		numLeft--;
		
	} 
	
	cout << "The total number of items in the solution is " << totalItemsAdded << endl;
	cout << "The total weight of the items in the solution is " << totalWeight << endl;
	cout << "The total profit of the items in the solution is " << totalProfit << endl;
	for(int i =0; i < arrayPos; i++)
	{
		cout << "Name: " << name[i];
		cout << ", Pesos: " << profit[i];
		cout << ", Weight: " << weight[i];
		cout << endl;
	}
	
	return 0;
}
