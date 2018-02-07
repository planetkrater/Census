// --------------------------------------------------------------------------------
// Author: Kate Wamsley
// Project Abstract: Census Append - Application for Census surveyors to enter collected information
// Script Description: Holds global variable to be used across application
// --------------------------------------------------------------------------------


// --------------------------------------------------------------------------------
// User Defined Types (UDT)
// --------------------------------------------------------------------------------
typedef int booleen;

typedef struct
{
	char strCountyCodes[2][5][50];	//5 counties max per state
	char strStateCodes[2][50];		//2 states max	
	char strStateAbbr[2][50];		//2 states max
	char strRaceCodes[5][50];		//5 races max	
} udtCensusCodes;

typedef struct
{
	char strDate[50];		// 0
	char strCounty[50];		// 1
	char strState[50];		// 2
	char strRace[50];		// 3
	int intHouseholdSize;	// 4
	int intHouseholdIncome;	// 5
	booleen blnCompleted;	// 6
} udtCensusFields;