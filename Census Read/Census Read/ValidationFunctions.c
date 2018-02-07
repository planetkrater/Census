// --------------------------------------------------------------------------------
// Author: Kate Wamsley
// Project Abstract: Census Read - Application for Census data to be analyzed
// Script Description: Validation functions for user input data
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

// Validation Functions
void GetDate(char* strDate);
void GetCountyState(char* strCounty, char* strState, char(*strCountyCode)[5][50], char(*strStateCode)[50]);
void GetRace(char* strRace, char(*strRaceCode)[50]);
void GetHouseholdSize(int* intHouseholdSize);
void GetHouseholdIncome(int* intHouseholdIncome);

booleen ValidateDate(char* strInput);
	booleen ValidateIfRealDate(int intMonth, int intDay, int intYear);

int ValidOneDimCensusCode(char* strInput, char(*strStoredCode)[50], int intLimit);
int ValidCountyCode(char* strInputCounty, char(*strCountyCode)[5][50], int intStateCode);

booleen ValidateNumeric(char strSource[]);
	booleen ValidateNumericWithChar(char strSource[], char charSpecial);
booleen StringCompareSame(char strStored[], char strInstance[]);



// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
// VALIDATION FUNCTIONS
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
// Name: GetDate
// Abstract: Ask user for a date, validate it
// --------------------------------------------------------------------------------
void GetDate(char* strDate)
{
	booleen blnValid = 0;
	char strInput[50] = "";
	char strTemp[50] = "";
	int intMonth = 0;
	int intDay = 0;
	int intYear = 0;
	char charSlash = 47;
	int intSlashIndex = 0;
	int intInputIndex = 0;
	int intDateCount = 0;
	int intLength = 0;

	do {
		// Reset variables
		StringEmpty(strInput);
		StringEmpty(strTemp);
		intMonth, intDay, intYear = 0;
		intLength = 0;

		// Prompt user, Collect response, Clean white space		
		printf("%-26s", "Census Date (MM/DD/YYYY): ");
		scanf(" %s", strInput);									//scanf("%d/%d/%d", &intMonth, &intDay, &intYear);
		TrimWhiteSpace(strInput);

		// Validate date
		blnValid = ValidateDate(strInput);

	} while (blnValid == 0);									// false(0) - date invalid

																// Print valid date as string to Census array
	StringCopy(strDate, strInput);
}




// --------------------------------------------------------------------------------
// Name: GetCountyState
// Abstract: 
// --------------------------------------------------------------------------------
void GetCountyState(char* strCounty, char* strState, char(*strCountyCode)[5][50], char(*strStateCode)[50])
{
	char strInputCounty[50] = "";
	char strInputState[50] = "";
	int intStateCode = -1;
	int intCountyCode = -1;

	do {
		// Reset input
		StringEmpty(strInputState);
		StringEmpty(strInputCounty);
		intStateCode = -1;
		intCountyCode = -1;

		// Prompt user, Collect response, Clean white space		
		printf("%-26s", "County: ");
		scanf(" %s", strInputCounty);
		TrimWhiteSpace(strInputCounty);
		StringToProperCase(strInputCounty);

		printf("%-26s", "State: ");
		scanf(" %s", strInputState);
		TrimWhiteSpace(strInputState);
		StringToProperCase(strInputState);

		intStateCode = ValidOneDimCensusCode(strInputState, strStateCode, intStates);
		if (intStateCode >= 0)
		{
			intCountyCode = ValidCountyCode(strInputCounty, strCountyCode, intStateCode);
		};

		if (intStateCode < 0 || intCountyCode < 0)
		{
			printf("--> County and State combination do not match.\n");
		};

	} while (intStateCode < 0 || intCountyCode < 0);

	// Print valid county and state to Census array
	StringCopy(strCounty, strInputCounty);
	StringCopy(strState, strInputState);
}



// --------------------------------------------------------------------------------
// Name: GetRace
// Abstract: 
// --------------------------------------------------------------------------------
void GetRace(char* strRace, char(*strRaceCode)[50])
{
	char strInputRace[50] = "";
	int intRaceCode = -1;

	do {
		// Reset input
		StringEmpty(strInputRace);
		intRaceCode = -1;

		// Prompt user, Collect response, Clean white space		
		printf("%-26s", "Race: ");
		scanf(" %s", strInputRace);
		TrimWhiteSpace(strInputRace);
		StringToProperCase(strInputRace);

		intRaceCode = ValidOneDimCensusCode(strInputRace, strRaceCode, intRaces);
		if (intRaceCode < 0)
		{
			printf("--> Race does not match accepted list.\n");
		};

	} while (intRaceCode < 0);

	// Print valid county and Race to Census array
	StringCopy(strRace, strInputRace);
}



// --------------------------------------------------------------------------------
// Name: GetHouseholdSize
// Abstract: 
// --------------------------------------------------------------------------------
void GetHouseholdSize(int* intHouseholdSize)
{
	int intNumber = -1;
	int intInput = 0;

	while (intInput == 0 || intNumber < 1)
	{
		// Reset variables
		intNumber = -1;
		intInput = 0;

		// Prompt user, Collect response, Clean white space		
		printf("%-26s", "Household Size: ");
		intInput = scanf("%d", &intNumber);

		// Flush the input buffer
		while ((getchar()) != '\n');

		if (intInput == 0)
		{
			printf("--> Household Size must be numeric with no special characters.\n");
		}
		else if (intNumber < 1)
		{
			printf("--> Household Size must be greater than 0.\n");
		}
	}

	*intHouseholdSize = intNumber;

}



// --------------------------------------------------------------------------------
// Name: GetHouseholdIncome
// Abstract: 
// --------------------------------------------------------------------------------
void GetHouseholdIncome(int* intHouseholdIncome)
{
	int intNumber = -1;
	int intInput = 0;

	while (intInput == 0 || intNumber < 1)
	{
		// Reset variables
		intNumber = -1;
		intInput = 0;

		// Prompt user, Collect response, Clean white space		
		printf("%-26s", "Household Annual Income: ");
		intInput = scanf("%d", &intNumber);

		// Flush the input buffer
		while ((getchar()) != '\n');

		if (intInput == 0)
		{
			printf("--> Household Annual Income must be numeric with no special characters.\n");
		}
		else if (intNumber < 1)
		{
			printf("--> Household Annual Income must be greater than 0.\n");
		}
	}

	*intHouseholdIncome = intNumber;
}



// --------------------------------------------------------------------------------
// Name: ValidateDate
// Abstract: Validate data by format, data type, numeric validity (ie. no Feb 30th)
// --------------------------------------------------------------------------------
booleen ValidateDate(char* strInput)
{
	booleen blnValid = 0;
	char strTemp[50] = "";
	int intMonth = 0;
	int intDay = 0;
	int intYear = 0;
	char charSlash = 47;
	int intSlashIndex = 0;
	int intInputIndex = 0;
	int intDateCount = 0;
	int intLength = 0;

	// Is the input data in numeric and in ##/##/#### format
	if (ValidateNumericWithChar(strInput, charSlash))
	{
		// Yes, get the string length for use as index limit
		intLength = StringLength(strInput);

		for (intInputIndex = 0, intDateCount = 0, intSlashIndex = 0; intInputIndex < intLength; intDateCount += 1, intInputIndex = intSlashIndex + 1)
		{
			// Find the next slash mark
			intSlashIndex = FindLetterNextIndex(strInput, charSlash, intInputIndex);

			// Are there no remaining slash marks?
			if (intSlashIndex == -1)
			{
				// Yes, set slash index to index limit (string length)
				intSlashIndex = intLength;
			}

			// Extract a section of the date
			StringMid(strTemp, strInput, intInputIndex, intSlashIndex - intInputIndex);

			// Cast extracted string to int of apprioprate date section
			if (intDateCount == 0)
			{
				intMonth = atoi(strTemp);
			}
			else if (intDateCount == 1)
			{
				intDay = atoi(strTemp);
			}
			else if (intDateCount == 2)
			{
				intYear = atoi(strTemp);
			}

		}

		// Are they date sections valid?
		blnValid = ValidateIfRealDate(intMonth, intDay, intYear);
	}

	return blnValid;
}



// --------------------------------------------------------------------------------
//	Name: ValidateIfRealDate
//	Abstract: Determine if date values (MM/DD/YYYY) provided are real
//			  Year must be between 1900 and 9999
//			  Month must be between 1 and 12
//			  Day must be between 1 and 28/29/30/31 
//				--> upper limit defined by Month and (Leap-)Year
// --------------------------------------------------------------------------------
booleen ValidateIfRealDate(int intMonth, int intDay, int intYear)
{
	// Verify year
	if (intYear >= 1900 && intYear <= 9999)
	{
		// Verify month
		if (intMonth >= 1 && intMonth <= 12)
		{
			// Verify days
			if ((intDay >= 1 && intDay <= 31) && (intMonth == 1 || intMonth == 3 || intMonth == 5 || intMonth == 7 || intMonth == 8 || intMonth == 10 || intMonth == 12))
				return 1;								// valid months with 31 days
			else if ((intDay >= 1 && intDay <= 30) && (intMonth == 4 || intMonth == 6 || intMonth == 9 || intMonth == 11))
				return 1;								// valid months with 30 days
			else if ((intDay >= 1 && intDay <= 28) && (intMonth == 2))
				return 1;								// valid days of February
			else if (intDay == 29 && intMonth == 2 && (intYear % 400 == 0 || (intYear % 4 == 0 && intYear % 100 != 0)))
				return 1;								// valid days of February on Leap Years
			else
				printf("--> Day (%d) is invalid for Month (%d) of Year (%d).\n", intDay, intMonth, intYear);
		}
		else
		{
			printf("--> Month (%d) is not valid.\n", intMonth);
		}
	}
	else
	{
		printf("--> Year (%d) is not valid.\n", intYear);
	}
	return 0;
}



// --------------------------------------------------------------------------------
// Name: ValidOneDimCensusCode
// Abstract: Verify that the StoredCode[][] and Input strings are the SAME
// --------------------------------------------------------------------------------
int ValidOneDimCensusCode(char* strInput, char(*strStoredCode)[50], int intLimit)
{
	int intIndex = 0;
	int intCode = -1;

	if (ValidateNumeric(strInput))
	{
		// cast to integer
		intCode = atoi(strInput);

		if (intCode >= 0 && intCode < intLimit)
		{
			StringCopy(strInput, strStoredCode[intCode]);
			return intCode;
		}
	}

	while (intIndex < intLimit)
	{
		if (StringCompareSame(strStoredCode[intIndex], strInput))
		{
			// They are a match. Return index as Race code
			return intIndex;
		}
		intIndex += 1;
	}


	// Not a match. Return offset.
	return -1;
}



// --------------------------------------------------------------------------------
// Name: ValidCountyCode
// Abstract: Verify that the StoredCode[][][] and Input strings are the SAME
// --------------------------------------------------------------------------------
int ValidCountyCode(char* strInputCounty, char(*strCountyCode)[5][50], int intStateCode)
{
	udtCensusCodes* audtCensusCodesList;
	int intIndex = 0;
	int intCode = -1;

	if (ValidateNumeric(strInputCounty))
	{
		// cast to integer
		intCode = atoi(strInputCounty);

		if (intStateCode == 1)
		{
			intCode -= 10;
		}

		if (intCode >= 0 && intCode < intCounties)
		{
			StringCopy(strInputCounty, strCountyCode[intStateCode][intCode]);
			return intCode;
		}
		
	}

	while (intIndex < intCounties)
	{
		if (StringCompareSame(strCountyCode[intStateCode][intIndex], strInputCounty))
		{
			// They are a match. Return index as State code
			return intIndex;
		}
		intIndex += 1;
	}
	// Not a match. Return offset.
	return -1;

}



// --------------------------------------------------------------------------------
//	Name: ValidateNumeric
//	Abstract: Determine if each character in a string is numeric
// --------------------------------------------------------------------------------
booleen ValidateNumeric(char strSource[])
{
	int intIndex = 0;
	int intLength = 0;

	intLength = StringLength(strSource);
	for (intIndex = 0; intIndex < intLength; intIndex += 1)
	{
		if (strSource[intIndex] < 48 || strSource[intIndex] > 57) // not '0'-'9' 
		{
			return false; //NOT numeric
		}
	}
	return true; //IS numeric
}



// --------------------------------------------------------------------------------
// Name: ValidateNumericWithChar
// Abstract: Determine if each character in a string is numeric, 
//			 allowing also one special character
//			 ex. for date format ##/##/####
// --------------------------------------------------------------------------------
booleen ValidateNumericWithChar(char strSource[], char charSpecial)
{
	int intIndex = 0;
	int intLength = 0;

	intLength = StringLength(strSource);
	for (intIndex = 0; intIndex < intLength; intIndex += 1)
	{
		if ((strSource[intIndex] < 48 || strSource[intIndex] > 57) && strSource[intIndex] != charSpecial) // not '0'-'9' and not special char
		{
			return false; //NOT numeric
		}
	}
	return true; //IS numeric
}



// --------------------------------------------------------------------------------
// Name: StringCompareSame
// Abstract: Verify that the Stored and Instance strings are the SAME
// --------------------------------------------------------------------------------
booleen StringCompareSame(char strStored[], char strInstance[])
{
	booleen blnValid = 0;		//false
	int intStoredLength = 0;
	int intInstanceLength = 0;
	int intIndex = 0;

	intStoredLength = StringLength(strStored);
	intInstanceLength = StringLength(strInstance);

	//Compare number of characters
	if (intStoredLength == intInstanceLength && intStoredLength != 0)
	{
		//Compare each character
		for (intIndex = 0; intIndex < intStoredLength; intIndex += 1)
		{
			if (strStored[intIndex] != strInstance[intIndex])
			{
				return blnValid; //NOT the same;
			}
		}
		// Strings are the same
		blnValid = 1; // true
	}
	return blnValid;
};