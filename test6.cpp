#include <iostream>
#include <vector>
#include <stack>

using namespace std;

/* 	   Function takes the magi powers list and finds a longest increasing sequence.
	   There may be distinct increasing subsequence of the same length (which is longest),
	   in this case, the function favors the one with the least gem count. 
	   This was not on purpose but just how it worked out.					  */

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

int main() 
{
	ios_base::sync_with_stdio(false);						// not using C stream so no need to sync those with C++ streams. Increase execution time. 
	vector<int> A;
	int vecsize;
	cin >> vecsize;
	int dummy;
	for ( int i = 0 ; i < vecsize ; i++)
	{
		cin >> dummy;
		A.push_back(dummy);
	}
	vector<int> longestsubsequence = findlongestincreasingsubsequence(A);
	for ( int i = 0 ;  i < longestsubsequence.size() ; i++)
		cout << longestsubsequence[i] << " ";
	return 0;
}

