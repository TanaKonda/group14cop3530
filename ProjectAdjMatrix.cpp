// ProjectAdjMatrix.cpp : Defines the entry point for the console application.
//

#include <limits>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
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

vector<int> longestIncreasingSubsequence(vector<int> & arrA) {
	int LIS[arrA.size()];
	for (int i = 0; i < arrA.size(); i++)
	{
		int max = -1;				// anything will be greater.
		for (int j = 0; j < i; j++)
		{
			// check if previous elements > current element
			if (arrA[i] > arrA[j])
			{
				// update the max from the previous entries
				if (max == -1 || max < LIS[j] + 1)
				{
					max = 1 + LIS[j];
				}
			}
		}
		if (max == -1)
		{
			// means none of the previous element has smaller than arrA[i]
			max = 1;
		}
		LIS[i] = max;
	}

	// find the max in the LIS[]
	int result = -1;
	int index = -1;
	for (int i = 0; i < arrA.size(); i++)
	{
		if (result < LIS[i])
		{
			result = LIS[i];
			index = i;
		}
	}
	// Print the result
	// cout << "result is : " << result << endl;
	// Start moving backwards from the end and
	vector<int> path;
	path.push_back(arrA[index]);
	result = result - 1;
	for (int i = index - 1; i >= 0; i--)
	{
		if (LIS[i] == result)
		{
			// cout << "at lis[i] " << LIS[i] << " we pushed in " << arrA[i] << endl;
			path.push_back(arrA[i]);
			result--;
		}
	}
	// cout << "Actual Elements: ";	
	return path;
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

void dijkstra(vector<vector<int>> graph, int src, int dest, int numWords, vector<int>& numGems, vector<realm> realms)
{
	int distance[numWords];

	bool shortestPath[numWords];

	for (int i = 0; i < numWords; i++)
	{
		distance[i] = numeric_limits<int>::max();
		shortestPath[i] = false;
	}

	distance[src] = 0;
	numGems[src] = 0;

	for (int i = 0; i < numWords - 1; i++)
	{
		int u = minDistance(distance, shortestPath, numWords);

		shortestPath[u] = true;

		for (int v = 0; v < numWords; v++)
		{
			if (shortestPath[v] == false && graph[u][v] != 0 && distance[u] != numeric_limits<int>::max() && distance[u] + graph[u][v] < distance[v])
			{
				distance[v] = distance[u] + graph[u][v];
				numGems[v] = numGems[u] + sum(realms[u].longestSub, graph[u][v]);
			}
		}
	}
	if (distance[dest] != numeric_limits<int>::max())
	{
		cout << distance[dest];
	}
	else
	{
		cout << "IMPOSSIBLE";
	}
}
int main()
{
	int numWords;
	cin >> numWords;

	vector<vector<int>> graph(numWords, vector<int>(numWords));
	for (int i = 0; i < numWords; i++)
	{
		for (int j = 0; j < numWords; j++)
		{
			graph[i][j] = 0;
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
			}
			y++;
		}
		x++;
	}
	vector<int> numGems(numWords);

	dijkstra(graph, src, dest, numWords, numGems, realms);
	cout << " ";
	if (numGems[dest] != 0)
	{
		cout << numGems[dest];
	}
	cout << endl;
	dijkstra(graph, dest, src, numWords, numGems, realms);
	cout << " ";
	if (numGems[src] != 0)
	{
		cout << numGems[src];
	}
	return 0;
}

