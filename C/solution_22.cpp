/**
 * Names scores
 * 
 * Using names.txt (right click and 'Save Link/Target As...'), a 46K text file containing over five-thousand first names, begin by sorting it into alphabetical order.
 * Then working out the alphabetical value for each name, multiply this value by its alphabetical position in the list to obtain a name score.
 * For example, when the list is sorted into alphabetical order, COLIN, which is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN would obtain a score of 938 × 53 = 49714.
 * What is the total of all the name scores in the file?
 */

/**
 * 1) Read in and parse the file
 * 2) Convert each name to 2 uint64's - the sum of the characters, and the characters as base 'Z'-'A'+2
 * 3) ???
 * 4) Profit!
 */



// Common includes
#include "common.h"



// The struct to store each name
struct NameValuePair {
	uint64_t mValue;	// The name in base 'Z'-'A'+2
	uint64_t mSum;	// The sum of the characters in the name
};



// Begin the solution
SOLUTION_BEGIN(22, uint64_t)
{
	// The reason for +2 rather than +1 is because we need 'A' to not be 0
	const uint64_t base = 'Z'-'A'+2;
	// base^(highestPower+1) < 2^64, => highestPower = 64 * log(2) / log(base) - 2
	const uint64_t highestPower = (64 * log(2)) / log(base) - 2;
	
	// Open the file
	FILE *f = fopen("p022_names.txt", "rb");
	
	if (f == nullptr)
	{
		printf("Couldn't open names file\n");
		return 0;
	}
	
	// Read the file characterinto a buffer
	fseek(f, 0, SEEK_END);
	long length = ftell(f);
	fseek(f, 0, SEEK_SET);
	char * data = new char[length];
	fread(data, sizeof(char), length, f);
	
	// A vector to hold all the names
	std::vector<NameValuePair> names;
	
	// Each name entry must at least contain "*" so reserve a third of the filesize
	names.reserve(length/3);
	
	// Parse the file
	long position = 0;
	while (position < length)
	{
		// Get the next char
		const char c = data[position++];
		
		// See if it's another name
		if (c == '\"')
		{
			// Get the start and end positions
			const char *strStart = data + position;
			const char *strEnd = strStart;
			while (*strEnd != '\"') strEnd++;
			size_t nameLength = strEnd - strStart;
			
			if (nameLength > highestPower)
				printf("Name too long - can't hash it into a uint64!\n");
			
			// Calculate the value and the sum for this name
			NameValuePair name = { 0, 0 };
			for (size_t i=0; i<nameLength; i++)
			{
				const uint64_t character = strStart[i] - 'A' + 1;
				name.mSum += character;
				name.mValue += character * std::pow(base, highestPower - i);
			}
			
			// Add the name to the list
			names.push_back(name);
			
			// Move to the end of the string
			position += nameLength + 1;
		}
	}
	
	// Sort it
	std::sort(names.begin(), names.end(), [](const NameValuePair& a, const NameValuePair& b) { return a.mValue < b.mValue; });
	
	// Add up the scores
	result = 0;
	const size_t nameCount = names.size();
	for (size_t i=0; i<nameCount; i++)
	{
		result += (i+1) * names[i].mSum;
	}
	
	// Remember to free the data and close the file
	delete [] data;
	fclose(f);
}
SOLUTION_END()
