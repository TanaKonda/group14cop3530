#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
 
/* 
   We're trying to find the longest increasing subsequence of magi power levels. 
   The first vector is just the magi info. The second vector tells you which magi to use and this is the "answer" for the function.
   However instead of returning a vector, it will simply populate an empty vector from the struct calling the function so as to not create a scope problem.
 */
void findthelongestincreasingsubsequence(vector<int> & in, vector<int> & sub) // a , b
{
	vector<int> longestsubsequence(in.size()); 	// local vector.
	
	int x, y; // variable to use in binary search later
 
	sub.push_back(0); // Add zero to this vector so any power level we compare it to will be greater.
 
	for (int i = 1; i < in.size(); i++) // run n times where n is size of input vector
        {
        // If the next power level is greater than power level of the newest magi in the subseqeuence then we can add this one to add to the subsequence!
		if (in[sub.back()] < in[i]) 
                {
			longestsubsequence[i] = sub.back(); // copy
			sub.push_back(i); // added to end of subsequence
			continue; // go to the end of this iteration & skip remaining code within for loop. Don't need it. 
		}
 
	 // If the above case is not triggered then, the following should happen. 

         // We do a binary search on the subsequence to find the magi in it who is the closest to and bigger than the current magi from the overall sequence
         // Note : Binary search is performed on sub (and not in).    
		for (x = 0, y = sub.size()-1; x < y;)  // Run from first to last element of magi's that are part of subsequence. Search will be halved every time.
                {
			int c = (x + y) / 2; // find the floor of the midpoint of subsequence length 
			if (in[i] < in[sub[c]] )  // if value of midpoint magi in overall sequence is less than value of the magi we're looking at right now
			{
				y=c; // keep looking in lower half
			}
			else  // otherwise 
			{
				x = c+1; // Keep looking in upper half
			}
		}
 
                // Update subsequence if the new magi turns out to be lesser in power than the biggest magi in subsequence 
		if (in[i] < in[sub[x]]) 
                {
			if (x > 0) 
			{
				longestsubsequence[i] = sub[x-1]; // move i's value into the one fewer position
			}
			sub[x] = i; // and move i up to x. 
		}	
	}
 
	for (x = sub.size(), y = sub.back(); x--; y = longestsubsequence[y]) 
	{
		sub[x] = y; // x indicates the last magi and y is their power level. 
	}
}