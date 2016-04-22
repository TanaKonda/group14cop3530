// ProjectAdjMatrix.cpp : Defines the entry point for the console application.
//

#include <limits>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stack>
using namespace std;

string IntToString(int number)
{
	ostringstream oss;

	oss << number;

	return oss.str();
}

struct realm {
	string charm;
	vector<int> longestSub;
	realm(string charm, vector<int> & magi) {
		this->charm = charm;
		longestSub = magi;
	}
};

int sum(vector<int> subSeq, int edits) {
	int sum = 0;
	for (int i = 0; i < edits; i++) {
		sum += subSeq[i];
	}
	return sum;
}

int minimum(int x, int y, int z)
{
	if (x < y)
	{
		if (x < z)
		{
			return x;
		}
		else
		{
			return z;
		}
	}
	else
	{
		if (y < z)
		{
			return y;
		}
		else
		{
			return z;
		}
	}
}

int editCount(string beginWord, string endWord, int wordOne, int wordTwo)
{
	vector<vector<int>> matrix(wordOne+1, vector<int>(wordTwo+1));

	for (int i = 0; i < wordOne; i++)
	{
		matrix[i][0] = i;
	}
	for (int j = 0; j < wordTwo; j++)
	{
		matrix[0][j] = j;
	}

	for (int i = 1; i <= wordOne; i++)
	{
		for (int j = 1; j <= wordTwo; j++)
		{
			int third;
			if (beginWord[i-1] == endWord[j-1])
			{
				third = matrix[i - 1][j - 1];
			}
			else
			{
				third = matrix[i - 1][j - 1] + 1;
			}
			matrix[i][j] = minimum(1 + matrix[i][j - 1], 1 + matrix[i - 1][j], third);
		}
	}
	return matrix[wordOne][wordTwo];
}

int GetCeilIndex(vector<int> A, int T[], int l, int r, int key) {
   int m;

   while( r - l > 1 ) {
      m = l + (r - l)/2;
      if( A[T[m]] >= key )
         r = m;
      else
         l = m;
   }

   return r;
}

vector <int> longestIncreasingSubsequence(vector<int> A) {
   // Add boundary case, when array size is zero
   // Depend on smart pointers
   int size=A.size();
    stack<int> LIS;
    int lis=0;
   int *tailIndices = new int[size];
   int *prevIndices = new int[size];
   int len;
   vector<int> finalLIS;
   memset(tailIndices, 0, sizeof(tailIndices[0])*size);
   memset(prevIndices, 0xFF, sizeof(prevIndices[0])*size);
   tailIndices[0] = 0;
   prevIndices[0] = -1;
   len = 1; // it will always point to empty location
   for( int i = 1; i < size; i++ ) {
      if( A[i] < A[tailIndices[0]] ) {
         // new smallest value
         tailIndices[0] = i;
      } else if( A[i] > A[tailIndices[len-1]] ) {
         // A[i] wants to extend largest subsequence
         prevIndices[i] = tailIndices[len-1];
         tailIndices[len++] = i;
      } else {
         // A[i] wants to be a potential condidate of future subsequence
         // It will replace ceil value in tailIndices
        int pos = GetCeilIndex(A, tailIndices, -1, len-1, A[i]);

        prevIndices[i] = tailIndices[pos-1];
        tailIndices[pos] = i;
      }
   }
   cout << "LIS of given input" << endl;
   for( int i = tailIndices[len-1]; i >= 0; i = prevIndices[i] )
        LIS.push(A[i]);
        lis++;

   delete[] tailIndices;
   delete[] prevIndices;
    while(!LIS.empty()){
        finalLIS.push_back(LIS.top());
        LIS.pop();
    }
   return finalLIS;
}
int minDistance(int distance[], bool shortestPath[], int numWords)
{
	int min = numeric_limits<int>::max();;
	int minIndex;

	for (int v = 0; v < numWords; v++)
	{
		if (shortestPath[v] == false && distance[v] <= min)
		{
			min = distance[v];
			minIndex = v;
		}
	}

	return minIndex;
}

string dijkstra(vector<vector<int>> graph, int src, int dest, int numWords)
{
	int distance[numWords];

	bool shortestPath[numWords];

	for (int i = 0; i < numWords; i++)
	{
		distance[i] = numeric_limits<int>::max();
		shortestPath[i] = false;
	}

	distance[src] = 0;

	for (int i = 0; i < numWords - 1; i++)
	{
		int u = minDistance(distance, shortestPath, numWords);

		shortestPath[u] = true;

		for (int v = 0; v < numWords; v++)
		{
			if (shortestPath[v] == false && graph[u][v] != 0 && distance[u] != numeric_limits<int>::max() && distance[u] + graph[u][v] < distance[v])
			{
				distance[v] = distance[u] + graph[u][v];
			}
		}
	}
	if (distance[dest] != numeric_limits<int>::max())
	{
		return IntToString(distance[dest]);
	}
	else
	{
		return "IMPOSSIBLE";
	}
}
int main()
{
	int numWords;
	cin >> numWords;

	vector<vector<int>> graph(numWords, vector<int>(numWords));
	vector<vector<int>> gemGraph(numWords, vector<int>(numWords));
	for (int i = 0; i < numWords; i++)
	{
		for (int j = 0; j < numWords; j++)
		{
			graph[i][j] = 0;
			gemGraph[i][j] = 0;
		}
	}

	vector<realm> realms;

	for (int i = 0; i < numWords; i++)
	{
		string word;
		cin >> word;


		int numMagi;
		cin >> numMagi;
		vector<int> magi;

		for (int j = 0; j < numMagi; j++)
		{
			int magus;
			cin >> magus;
			magi.push_back(magus);
		}

		vector<int> LIS = longestIncreasingSubsequence(magi);

		realm thisRealm = realm(word, LIS);
		realms.push_back(thisRealm);
	}
	string srcWord;
	cin >> srcWord;
	string destWord;
	cin >> destWord;

	int src;
	int dest;

	int x = 0;
	for (vector<realm>::const_iterator i = realms.begin(); i != realms.end(); i++)
	{
		int y = 0;
		if (i->charm == srcWord)
		{
			src = x;
		}
		if (i->charm == destWord)
		{
			dest = x;
		}
		for (vector<realm>::const_iterator j = realms.begin(); j != realms.end(); j++)
		{
			if (x != y && editCount(i->charm, j->charm, (i->charm).length(), (j->charm).length()) <= i->longestSub.size())
			{
				graph[x][y] = editCount(i->charm, j->charm, (i->charm).length(), (j->charm).length());
				gemGraph[x][y] = sum(i->longestSub, editCount(i->charm, j->charm, (i->charm).length(), (j->charm).length()));
			}
			y++;
		}
		x++;
	}
	cout << dijkstra(graph, src, dest, numWords);
	cout << " ";
	if (dijkstra(graph, src, dest, numWords) != "IMPOSSIBLE")
	{
		cout << dijkstra(gemGraph, src, dest, numWords);
	}
	cout << endl;
	cout << dijkstra(graph, dest, src, numWords);
	cout << " ";
	if (dijkstra(graph, dest, src, numWords) != "IMPOSSIBLE")
	{
		cout << dijkstra(gemGraph, dest, src, numWords);
	}
	return 0;
}

