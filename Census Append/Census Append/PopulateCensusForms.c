// --------------------------------------------------------------------------------
// Author: Kate Wamsley
// Project Abstract: Census Append - Application for Census surveyors to enter collected information
// Script Description: Gets user input data and calls for validation, etc.
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

// Populate Forms
void PopulateCensusForms(udtCensusFields audtCensusForms[], udtCensusCodes* pudtCensusCodesList);
booleen PopulateNextEmptyIndex(udtCensusFields* pudtCensus);
void PopulateCensusPrompt(udtCensusFields* pudtCensuses, udtCensusCodes* pudtCensusCodesList);
void GetDate(char* strDate);
void GetCountyState(char* strCounty, char* strState, char(*strCountyCode)[5][50], char(*strStateCode)[50]);
void GetRace(char* strRace, char(*strRaceCode)[50]);
void GetHouseholdSize(int* intHouseholdSize);
void GetHouseholdIncome(int* intHouseholdIncome);



// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
// POPULATE CENSUS FORMS
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------



// --------------------------------------------------------------------------------
//	Name: PopulateCensusForms
//	Abstract: Populate each form's fields with user input values.
// --------------------------------------------------------------------------------
void PopulateCensusForms(udtCensusFields audtCensusForms[], udtCensusCodes* pudtCensusCodesList)
																// accept all the forms of fields sent
{
	int intCensusIndex = 0;
	int intIndex = 0;
	booleen blnEnterData = 1;
	char charResult = 0;
	
	// Get next open index value
	while(intCensusIndex < intArraySize)
	{
		if (PopulateNextEmptyIndex(&audtCensusForms[intCensusIndex]))
		{
			intIndex = intCensusIndex;
			break;
		}
		else
		{
			intCensusIndex += 1;
		}		
	};

	// display header
	printf("%-19s%s%19s\n", "", "Enter New Census Information", ""); // Display action to user

	while (blnEnterData == 1)									// true(1) --> continue to collect data
	{
		// Print index
		printf("Entry: %0d\n", intIndex);

		// Pass indexed-form to be filled by user
		PopulateCensusPrompt(&audtCensusForms[intIndex], pudtCensusCodesList);
		// pass each accepted form individually, 
		// pass the Census Code pointer 

		intIndex += 1;											// increment CensusForm index
		printf("\n");

		// Prompt user to enter more data
		printf("--> Enter Y to enter another census:  ");
		scanf(" %c", &charResult);
		if (charResult == 89 || charResult == 121)				// 'Y' or 'y'
		{
			blnEnterData = 1;									// true(1) --> collect data
		}
		else
		{
			blnEnterData = 0;									// false(0) --> stop data collection 
		}
		printf("\n");
	};

	printf("Thank you.\n");
}



// --------------------------------------------------------------------------------
// Name: PopulateNextEmptyIndex
// Abstract: Determine the next unused entry
// --------------------------------------------------------------------------------
booleen PopulateNextEmptyIndex(udtCensusFields* pudtCensus)	// point to the individual form passed
{
	if (pudtCensus->blnCompleted)								// if completed, print
	{
		return false;
	}
	else
	{
		return true;
	};
};



// --------------------------------------------------------------------------------
//	Name: PopulateCensusPrompt
//	Abstract: Prompt user to input data for each form field
// --------------------------------------------------------------------------------
void PopulateCensusPrompt(udtCensusFields* pudtCensus, udtCensusCodes* pudtCensusCodesList)
																// point to the individual form passed, 
																// point to the Census Code pointer passed
{
	// Get date from user, validate, store in Census Field of current Form
	GetDate(pudtCensus->strDate);								// Pass the date field of the individual form

																// Get County and State from user, validate, store in Census Field of current Form
	GetCountyState(pudtCensus->strCounty, pudtCensus->strState, pudtCensusCodesList->strCountyCodes, pudtCensusCodesList->strStateCodes);
	// Pass the county and state fields of the individual form
	// Pass the county and state Census Codes for validation 
	// Get Race, validate, store in Census Field of current Form
	GetRace(pudtCensus->strRace, pudtCensusCodesList->strRaceCodes);
	// Pass the race field of the individual form
	// Pass the race Census Codes for validation
	// Get Size, validate, store in Census Field of current Form
	GetHouseholdSize(&pudtCensus->intHouseholdSize);				// Pass the size field of the individual form

																	// Get Income, validate, store in Census Field of current Form
	GetHouseholdIncome(&pudtCensus->intHouseholdIncome);			// Pass the race field of the individual form

																	// Mark form completed
	pudtCensus->blnCompleted = 1;								// completed
}



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

