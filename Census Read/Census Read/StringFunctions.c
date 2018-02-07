// --------------------------------------------------------------------------------
// Author: Kate Wamsley
// Project Abstract: Census Read - Application for Census data to be analyzed
// Script Description: String functions for data processing
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
// Includes
// --------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Main.h"
// --------------------------------------------------------------------------------
// Constants
// --------------------------------------------------------------------------------
#define true 1
#define false 0
extern int intArraySize;
extern int intCounties;
extern int intStates;
extern int intRaces;
// --------------------------------------------------------------------------------
// User Defined Types (UDT)
// --------------------------------------------------------------------------------



// --------------------------------------------------------------------------------
// Prototypes
// --------------------------------------------------------------------------------

// String Functions
void StringCopy(char strDestination[], char strSource[]);
void StringEmpty(char strSource[]);
int StringLength(char strSource[]);
void StringMid(char strDestination[], char strSource[], int intStartIndex, int intLength);
void StringTrimStart(char strSource[], int intCharIndex);
int FindLetterNextIndex(char strSource[], char charLetterToFind, int intStartIndex);
void TrimWhiteSpace(char strSource[]);
void TrimStartWhiteSpace(char strSource[]);
void TrimEndWhiteSpace(char strSource[]);
void PrintWhiteSpace(int intCount);
void StringToProperCase(char strSource[]);
void StringToLowerCase(char strSource[]);



// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
// STRING FUNCTIONS
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------



#pragma region "Basics: Copy, Empty, Length"
// --------------------------------------------------------------------------------
// Name: StringCopy
// Abstract: Copy the source to the destination
// --------------------------------------------------------------------------------
void StringCopy(char strDestination[], char strSource[])
{
	int intIndex = 0;

	// Copy each character
	while (strSource[intIndex] != 0)
	{

		strDestination[intIndex] = strSource[intIndex];
		intIndex += 1;
	}

	// Terminate
	strDestination[intIndex] = 0;
};



// --------------------------------------------------------------------------------
// Name: StringEmpty
// Abstract: Clear chars from string array
// --------------------------------------------------------------------------------
void StringEmpty(char strSource[])
{
	int intIndex = 0;

	while (strSource[intIndex] != 0)
	{
		strSource[intIndex] = 0;
		intIndex += 1;
	};

};



// --------------------------------------------------------------------------------
// Name: StringLength
// Abstract: Return the string length
// --------------------------------------------------------------------------------
int StringLength(char strSource[])
{
	int intIndex = 0;
	int intLength = 0;

	//Pretest because string may be empty
	while (strSource[intIndex] != 0)
	{
		intIndex += 1;
	}

	intLength = intIndex;
	return intLength;
};
#pragma endregion



// --------------------------------------------------------------------------------
// Name: StringMid
// Abstract: Copy source starting at [Index] for [Length] of characters to destination.
// --------------------------------------------------------------------------------
void StringMid(char strDestination[], char strSource[], int intStartIndex, int intLength)
{
	int intIndex = 0;
	int intSourceLength = 0;

	intSourceLength = StringLength(strSource);


	if ((intStartIndex + intLength) > intSourceLength)
	{
		printf("StringMid Error: Not enough characters in Source string to print %d starting at %d.\n", intLength, intStartIndex);
	}
	else
	{
		StringEmpty(strDestination);

		for (intIndex = 0; intLength > 0; intIndex += 1, intLength -= 1, intStartIndex += 1)
		{
			strDestination[intIndex] = strSource[intStartIndex];
		};
	};

};



// --------------------------------------------------------------------------------
// Name: StringTrimStart
// Abstract: Trim off the start of a string, removing beginning [0] to [Index]
// --------------------------------------------------------------------------------
void StringTrimStart(char strSource[], int intCharIndex)
{
	int intStringLength = 0;
	int intCharAmount = 0;
	char strTrimmed[150] = "";

	// Remove name
	intStringLength = StringLength(strSource);
	intCharAmount = intStringLength - intCharIndex - 1;
	StringMid(strTrimmed, strSource, intCharIndex + 1, intCharAmount);

	// Reset source string
	StringEmpty(strSource);

	// Copy temp string to source
	StringCopy(strSource, strTrimmed);

}



// --------------------------------------------------------------------------------
// Name: FindLetterNextIndex
// Abstract: Find first instance of passed letter from left to right
// --------------------------------------------------------------------------------
int FindLetterNextIndex(char strSource[], char charLetterToFind, int intStartIndex)
{
	int intIndex = 0;
	int intLetterToFindIndex = -1;

	// Set start index
	intIndex = intStartIndex;

	//Pretest because string may be empty
	while (strSource[intIndex] != 0)
	{
		if (strSource[intIndex] == charLetterToFind)
		{
			intLetterToFindIndex = intIndex;
			break;
		}
		intIndex += 1;
	}

	return intLetterToFindIndex;
};



#pragma region "Trim White Space"
// --------------------------------------------------------------------------------
// Name: TrimWhiteSpace
// Abstract: Remove leading and tailing white space
// --------------------------------------------------------------------------------
void TrimWhiteSpace(char strSource[])
{
	TrimStartWhiteSpace(strSource);
	TrimEndWhiteSpace(strSource);
}



// --------------------------------------------------------------------------------
// Name: TrimStartWhiteSpace
// Abstract: Remove leading white space
// --------------------------------------------------------------------------------
void TrimStartWhiteSpace(char strSource[]) {
	char charSpace = 32;
	char charTab = 9;
	int intStringLength = 0;
	int intIndex = 0;
	int intLetterToFindIndex = -1;
	char strTrimmed[150] = "";

	// Find total length for StringMid
	intStringLength = StringLength(strSource);

	//Pretest because string may be empty
	while (strSource[intIndex] != 0 && intLetterToFindIndex < 0)
	{
		while (strSource[intIndex] != charSpace && strSource[intIndex] != charTab) // stop at first non-space
		{
			intLetterToFindIndex = intIndex;
			break;
		}
		intIndex += 1;
	}

	// Extract string without leading white space to temp string
	StringMid(strTrimmed, strSource, intLetterToFindIndex, intStringLength - intLetterToFindIndex);
	// Reset source string
	StringEmpty(strSource);
	// Copy temp string to source
	StringCopy(strSource, strTrimmed);
	// Done
}



// --------------------------------------------------------------------------------
// Name: TrimEndWhiteSpace
// Abstract: Remove tailing white space -- same as TrimSTART, excepts loops in opposite direction
// --------------------------------------------------------------------------------
void TrimEndWhiteSpace(char strSource[]) {
	char charSpace = 32;
	char charTab = 9;
	int intStringLength = 0;
	int intIndex = 0;
	int intLetterToFindIndex = -1;
	char strTrimmed[150] = "";


	// Find total length for StringMid
	intStringLength = StringLength(strSource);

	// Set index to count down
	intIndex = intStringLength - 1;

	//Pretest because string may be empty
	while (strSource[intIndex] != 0 && intLetterToFindIndex < 0)
	{
		while (strSource[intIndex] != charSpace && strSource[intIndex] != charTab) // stop at first non-space and non-tab
		{
			intLetterToFindIndex = intIndex;
			break;
		}
		intIndex -= 1;
	}

	// Extract string without tailing white space to temp string
	StringMid(strTrimmed, strSource, 0, intLetterToFindIndex + 1);
	// Reset source string
	StringEmpty(strSource);
	// Copy temp string to source
	StringCopy(strSource, strTrimmed);
	// Done
}
#pragma endregion



// --------------------------------------------------------------------------------
// Name: PrintWhiteSpace
// Abstract: Print to console the amount of space specified
//			 Intended use is for console presentation.
// --------------------------------------------------------------------------------
void PrintWhiteSpace(int intCount)
{
	while (intCount > 0)
	{
		printf(" ");
		intCount -= 1;
	}
}



// --------------------------------------------------------------------------------
// Name: StringToProperCase
// Abstract: Capitalize the first letter of each word
// --------------------------------------------------------------------------------
void StringToProperCase(char strSource[])
{
	char strDestination[50] = "";
	int intIndex = 0;
	char charThis = 0;
	char charLast = 0;

	StringToLowerCase(strSource);

	while (strSource[intIndex] != 0)
	{
		charThis = strSource[intIndex];

		if (charThis >= 97 && charLast <= 122 && (charLast == 32 || charLast == 13 || charLast == 9 || charLast <= 2))
		{
			strSource[intIndex] = strSource[intIndex] - 32;
		};

		charLast = charThis;
		charThis = 0;

		intIndex += 1;
	};
};



// --------------------------------------------------------------------------------
// Name: StringToLowerCase
// Abstract: Convert the string to all lowercase
// --------------------------------------------------------------------------------
void StringToLowerCase(char strSource[])
{
	int intIndex = 0;

	while (strSource[intIndex] != 0)
	{
		if (strSource[intIndex] >= 65 && strSource[intIndex] <= 90)
		{
			strSource[intIndex] = strSource[intIndex] + 32;
		};

		intIndex += 1;
	};
};








