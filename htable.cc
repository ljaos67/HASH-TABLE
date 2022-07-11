/*************************************************************************************
CSCI 340 - Assignment 10 - Fall 2020 
 
Programmer: Leonart Jaos 
Z-ID: z1911688
Section: 0002
Date Due: November 16, 2020

Purpose: The purpose of this program is to implement insertion and deletion with the
concept of hash tables. Insertion and search is performed using a given hash function
in the interest of reducing insertion and search time. This is the class definition
file that defines the hash function for indexing, constructor and destructor,
insertion, search, and print functions for the values and the hash table
  
**************************************************************************************/
#include "htable.h"

#define N1 10  // num of decimal digits
#define N2 26  // num of upper-case letters
 
// Hash function, you may NOT modify this function
int HT::hash(const string &s) {
  int n = (N2 * N1) * (s[0] - 'A') + N1 * (s[1] - 'A') + (s[2] - '0');

  return n % hsize;
}

// You will complete the code below ...
// creates a Hash Table of size HS
// pointer table is empty
HT::HT(const unsigned &hs) 
{
	hsize = hs;
	hTable.resize(hs);
	list<Entry> l;
	Entry R;
	R.key = "";
	R.desc = "";
	R.num = 0;
	l.push_front(R);
	for(int i = 0; i < hs; ++i)
	{
		hTable[i] = l;
	}
}
// frees memory of htable
// starts with list and then clears vector
HT::~HT() 
{

	// Lists in Hash table
	for(int i = 0; i < hsize; i++)
	{
		hTable[i].erase(hTable[i].begin(), hTable[i].end());
		hTable[i].clear();
	}
	// hash table	
	hTable.erase(hTable.begin(),hTable.end());
	hTable.clear();
	// pointer table
	pTable.erase(pTable.begin(),pTable.end()); 
}
// true, meaning that the vector is in there
// helper function for insert that doesn't print anything, unlike search
bool IsKey(const vector<list<Entry>> &a, const Entry &e)
{
	for(int i = 0; i < a.size(); i++)
	{
		auto it = a[i].begin();
		while(it != a[i].end())
		{
			if(it->key == e.key)
				return true;
			++it;
		}
	}
	return false;
}
// uses hash function to find insertion index
// inserts based on whether or not list empty
// two methods are used
// prints inserted value granted its not a duplicate
void HT::insert(const Entry &e) 
{
	int a;
	if(IsKey(hTable,e))
	{
		cout << " not inserted - duplicate key!!!\n";
	}
	else
	{
		a = hash(e.key);
		cout << " entry =" << setw(3) << right << a << "\n";
		if(hTable[a].front().key == "")
		{
			hTable[a].front().key = e.key;
			hTable[a].front().desc = e.desc;
			hTable[a].front().num = e.num;
			Entry * R;
			R = &hTable[a].front();
			pTable.push_back(R);
		}
		else
		{				
			hTable[a].push_front(e);
			Entry * R;
			R = &hTable[a].front();
			pTable.push_back(R);
		}
	}
}
// performs a search using hash function for index
// if function is in hash index a printing sequence is initiated
// if not then the string is not in the hash table and a message is printed
void HT::search(const string &s) 
{
	bool found = false;
	int a = hash(s);
	auto it = hTable[a].begin();
	while(it != hTable[a].end())
	{
		if(it->key == s)
		{
			found = true;
			cout << " ==> number: " << setw(4) << right << it->num << " - item: " << it->desc << "\n";
		}
		++it;
	}
	if(!found)
	{
		cout << " not in table!!\n";
	}
}
// function that goes through each entry in each list of the hash table
// prints entry members
// specific spacing sequences are inititated to match reference
void HT::hTable_print() 
{
	for(int i = 0; i < hTable.size(); i++)
	{
		if(hTable[i].front().key != "")
		{
			auto it = hTable[i].begin();
			while(it != hTable[i].end())
			{
				cout << setw(4) << right << i << ":  " << it->key << "  -  " << setw(4) << right << it->num << "  -  " << it->desc << "\n";
				++it;
			}
			if( i < hsize-1)
			{
				if((hTable[i+1].front().key == ""))
				{
					cout << "\n";
				}
			}
		}
		if((i == 0) && (hTable[i].front().key == ""))
		{
			cout << "\n";
		}
	}
	

}
// compare function for sort
// compares two strings
bool cmp(Entry *p, Entry *q)
{
	return(p->key < q->key);
}
// sorts pointer table of entry values
// prints each pointer
void HT::pTable_print() 
{
	sort(pTable.begin(), pTable.end(), cmp);
	for(auto it = pTable.begin(); it != pTable.end(); ++it)
	{
		cout << "   " <<(*it)->key << "  -  " << setw(4) << (*it)->num << "  -  " << (*it)->desc << "\n";
	}
}
