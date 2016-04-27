#include <limits>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

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

vector<int> findlongestincreasingsubsequence(vector<int> & listofmagi) 		
{

	vector<int> workspace(listofmagi.size(),-1);		

	for (int i = 0; i < listofmagi.size(); i++) 
	{		
		int maxsofar = -1;							// anything will be greater.
		for (int j = 0; j < i; j++) 
		{
			if (listofmagi[i] > listofmagi[j]) 				// check if the ith value is greater than any of the previous j values. 
			{
				if (maxsofar == -1 || maxsofar < workspace[j] + 1) 	// if so then update the maxsofar 
				{
					maxsofar = 1 + workspace[j];
				}
			}
		}
		if (maxsofar == -1) 							// if you can't find anything smaller than listofmagi[i], just set maxsofar to 1
		{									// b/c there must be at least one magi with power level 1 or higher
			maxsofar = 1;							// and having this value in workspace is harmless.
		}
			workspace[i] = maxsofar; 					// push the max for this run into workspace.
	}
		
											// now that we're done filling the workspace, find its max.

	int workmax = -1;								// for the max value in workspace, now called 'workmax'
	int workmaxpos = -1;								// for position of the workmax value
	for (int i = 0; i < listofmagi.size(); i++)
	{
		if (workspace[i] > workmax) 						// if new max found, update workmax & workmaxpos. 
		{
			workmax = workspace[i];
			workmaxpos = i;
		}
	}

	stack<int> lis;									// now create stack
	lis.push(listofmagi[workmaxpos]);						// push in max value
	int lookingfor = --workmax;							// this variable will be used to find next biggest values.
	for (int i = workmaxpos-1; i >= 0; i--) 					// run through workspace in reverse from the position before the one with the max value.
	{
		if(workspace[i]==lookingfor)						// if so add to stack
		{
			lis.push(listofmagi[i]);
			lookingfor--;
		}				
	}

	vector<int> answer;								// new vector, this is the one we will return. 
	
	while(!lis.empty())								// simply pop from stack into vector!
	{
		answer.push_back(lis.top());
		lis.pop();
	}

	return answer;
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

		vector<int> LIS = findlongestincreasingsubsequence(magi);

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
	cout << endl;
	return 0;
}

