#include <bits/stdc++.h>

using namespace std;

// priority_queue

priority_queue<int> pq;

// heapify
vector<int> stones;
priority_queue<int, vector<int>, less<int>> q(stones.begin(), stones.end());

//////////////////////////////////////////////////////////////

// priority queue with particualar, custom type and comparison

class mycomparison
{
		bool reverse;
	public:
		mycomparison(const bool& revparam=false) : reverse(revparam) {}
		bool operator() (const pair<int,int>& lhs, const pair<int,int>&rhs) const
		{
			if (reverse) return (lhs.first>rhs.first);
			else return (lhs.first<rhs.first);
		}
};
priority_queue< pair<int,int>, vector< pair<int,int> >, mycomparison> pq(mycomparison(true));

/////////////////////////////////////////////////////////////////////

// normal with custom comparison

priority_queue<int,vector<int>,less<int>> left_h; // max heap (default)
priority_queue<int,vector<int>,greater<int>> right_h; // min heap


/////////////////////////////////////////////////////////////////////////



