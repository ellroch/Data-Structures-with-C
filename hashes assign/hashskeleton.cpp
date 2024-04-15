#include <iostream>
#include <ctime>
using namespace std;

// Define SIZE to fit your needs
#define SIZE 71
int probe_counter = 0;

// You don't need to use an entire node for the assignment; all I ask is that you at least
// store the keys.
struct Node
{
	int id;
	int key;
};


bool insert(/*input the list to insert to, the index to insert at, and the data to insert*/)
{
	if(/*There is not data there already*/)
	{
		// Insert the data and return success
	}
	else
		// report failure
}

int HashingAlgorithm(int key)
{
	//Use the key in the hashing algorithm to calculate an isertion index.
	int insert_index = 0 // Dummy value for you to replace.
	
	return insert_index;
}

// Currently returns true if insertion is successful.
// Could have it return index to attempt an insert outside of this function.
bool CollisionResolutionAlgorithm(/*May need list to insert into, the previous index, and data to insert*/)
{
	//Do any prep needed to calculate the new index
	
	do
	{
		// calculate a new index using the given collision algorithm
	}while(/*Continue looping until insertion successful, or too many attempts fail.*/);
	
	//Again, another method would be to simpy have this function return the newly calculated index.
	//The implementation is up to you.
	if(/*too many attempts fail*/)
		return false;
	else
		return true;
}

int main()
{
	// Create a list to insert data. Should be about twice the number of inserts you want to do.
	// Fill the list with dummy indicators so you know if you can insert there.
	
	for(/*as many inserts as you want to do*/)
	{
		// Generate a new key randomly. This is unique to your assignment.
		// Usually, you're either given keys, or there is a specific method to their creation.
		
		// Use your hashing algorithm to calculate an index to insert to using a key.
		if(/*an insertion fails*/)
			//Generate a new insertion index using your collision resolution algorithm.
		
		if(/*multiple attempts to insert using collision resolution fail*/)
		{
			// Let the user know there was a failed insertion.
		}
	}
	
	// This will print out the hashed list so we can look for clustering.
	for(/*The size of your hashed list*/)
	{
		if(/*No data was inserted an a given index, you'll see the dummy variable*/)
			// output a space or something that marks a non-entry.
		else
			// output the data and key.
	}
	
	// Let me know how many total probes you did for each pair of hash/collision resolutionl.
	
	return 0;
}