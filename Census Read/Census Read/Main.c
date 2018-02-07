// --------------------------------------------------------------------------------
// Name: Kate Wamsley
// Project Abstract: Census Read - Application for Census data to be analyzed
// Script Description: Core execution instructions for application to run
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
const int intArraySize = 100;
const int intCounties = 5;
const int intStates = 2;
const int intRaces = 5;
// --------------------------------------------------------------------------------
// User Defined Types (UDT)
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
// Prototypes
// --------------------------------------------------------------------------------
// Initialize Forms
void InitializeCensusForms(udtCensusFields audtCensusForms[]);
	void InitializeCensus(udtCensusFields* pudtCensuses);

// Action Menu
void PrintEntryActions();
void EntryActions(udtCensusFields* audtCensusForms, udtCensusCodes* pudtCensusCodesList);

// Print Forms
void PrintCensusForms(udtCensusFields audtCensusForms[]);
	void PrintCensusCompleted(int intIndex, udtCensusFields* pudtCensus);


// --------------------------------------------------------------------------------
//	Name: Main
//	Abstract: This is where the program starts
// --------------------------------------------------------------------------------
void main()
{
	//--------- Initialize Components ---------//
	// Declare Census codes instance
	udtCensusCodes audtCensusCodesList;

	// Pass code instance and print census code		--> codes are used for input validation and console HEADER
	CensusCodes(&audtCensusCodesList);				// Send closed suitcase containing all Census codes

	// Declare Census Froms instances
	udtCensusFields audtCensusForms[100];			// Max number of Census forms that can be entered
													// Analogy - 7 FIELDS of data are collected on each FORM and a maximum 100 FORMS can be collected
	// Initialize Census Froms
	InitializeCensusForms(audtCensusForms);			// Send closed suitcase containing all forms
													// Result - each field on each form a defualt 0 or ""
	
	FileRead(audtCensusForms, &audtCensusCodesList);

	//------ User Interaction Components ------//
	// Ask user what action to perform next						 
	EntryActions(audtCensusForms, &audtCensusCodesList);	

	//-------------- END PROGRAM --------------//
	printf("\nThank you and have a nice day!\n");
	system("pause");
}



// --------------------------------------------------------------------------------
//	Name: PrintEntryActions
//	Abstract: Ask user what action they would like to perform
// --------------------------------------------------------------------------------
void PrintEntryActions()
{
	//header
	printf("\n------------------------------------------------------------------------------\n");
	printf("       MAIN MENU\n");
	printf("[ 01 ] Review Data\n");
	printf("[ 02 ] Total Surveyed\n");
	printf("[ 03 ] Total Surveyed By County\n");
	printf("[ 04 ] Total Surveyed By Race\n");
	printf("[ 05 ] Average Household Income\n");
	printf("[ 06 ] Average Household Income by County and State\n");
	printf("[ 07 ] Average Household Income by Race\n");
	printf("[ 08 ] Percentage Below Poverty\n");
	printf("[ 09 ] Percentage Below Poverty by County and State\n");
	printf("[ 10 ] Percentage Below Poverty by Race\n");
	printf("[ 99 ] Exit program\n");
	printf("\n");
}


// --------------------------------------------------------------------------------
//	Name: EntryActions
//	Abstract: Ask user what action they would like to perform
// --------------------------------------------------------------------------------
void EntryActions(udtCensusFields* audtCensusForms, udtCensusCodes* pudtCensusCodesList)
{
	booleen blnValid = 0; //false
	booleen blnChange = 0; //false
	int intEntry = -1;
	int intInput = 0;
	char charSave;
	
	// Print action options for user
	PrintEntryActions();

	do
	{
		// Reset
		intEntry = -1;
		intInput = 0;
		charSave = "";

		while (intEntry < 1 || (intEntry > 10 && intEntry != 99))
		{
			// Prompt user for entry number
			printf("\nWhat would you like to do? ");
			intInput = scanf("%d", &intEntry);

			// Flush the input buffer
			while ((getchar()) != '\n');
		}

		switch (intEntry)
		{
		case 1:
			// Print Census Forms
			PrintCensusForms(audtCensusForms);							// Result - show each field on each form completed
			break;
		case 2:
			TotalCompleted(audtCensusForms);
			break;
		case 3:
			TotalCompletedByCounty(audtCensusForms, pudtCensusCodesList);
			break;
		case 4:
			TotalCompletedByRace(audtCensusForms, pudtCensusCodesList);
			break;
		case 5:
			AverageIncome(audtCensusForms);
			break;
		case 6:
			AverageIncomeByCountyState(audtCensusForms, pudtCensusCodesList);
			break;
		case 7:
			AverageIncomeByRace(audtCensusForms, pudtCensusCodesList);
			break;
		case 8:
			PercentageBelowPoverty(audtCensusForms, pudtCensusCodesList);
			break;		
		case 9:
			PercentageBelowPovertyByCountyState(audtCensusForms, pudtCensusCodesList);
			break;
		case 10:
			PercentageBelowPovertyByRace(audtCensusForms, pudtCensusCodesList);
			break;
		case 99:
			blnValid = 1; //true
			break;
		default: 
			blnValid = 0;
		}

	} while (blnValid == 0); //false

}



#pragma region "Initialize Census Forms"
// --------------------------------------------------------------------------------
// Name: InitializeCensusForms
// Abstract: Intialize all the Fields of all Census Forms.
//			 In other words, pass each form individually to have its fields filled.
// --------------------------------------------------------------------------------
void InitializeCensusForms( udtCensusFields audtCensusForms[] ) // accept all the forms of fields sent
{
	int intIndex = 0;

	for (intIndex = 0; intIndex < intArraySize; intIndex += 1)	// loop through index of accepted forms
	{
		InitializeCensus( &audtCensusForms[intIndex] );			// pass each accepted form individually
	};
};



// --------------------------------------------------------------------------------
// Name: InitializeCensus
// Abstract: Fill each field of the individual form passed with a default value.
// --------------------------------------------------------------------------------
void InitializeCensus( udtCensusFields* pudtCensus )			// point to the individual form passed
{
	StringCopy(pudtCensus->strDate, "");						// date
	StringCopy(pudtCensus->strCounty, "");						// county
	StringCopy(pudtCensus->strState, "");						// state
	StringCopy(pudtCensus->strRace, "");						// race
	pudtCensus->intHouseholdSize = 0;							// # in household
	pudtCensus->intHouseholdIncome = 0;							// yearly income of household
	pudtCensus->blnCompleted = 0;								// (not) completed
};
#pragma endregion




#pragma region "Print Census Forms"
// --------------------------------------------------------------------------------
// Name: PrintCensusForms
// Abstract: Pass each form completed to be printed
// --------------------------------------------------------------------------------
void PrintCensusForms(udtCensusFields audtCensusForms[])	// accept all the forms of fields sent
{
	int intIndex = 0;
	printf("\n\n");
	printf("%-55s|%-10s|%-10s\n", "","Household", "Household");
	printf("%-5s|%-10s|%-10s|%-10s|%-16s|%-10s|%-10s|", "Entry", "Date", "County", "State", "Race", "Size", "Income");
	printf("\n------------------------------------------------------------------------------\n");
	for (intIndex = 0; intIndex < intArraySize; intIndex += 1)	// loop through index of accepted forms
	{
		PrintCensusCompleted(intIndex, &audtCensusForms[intIndex]);		// pass each accepted form individually		
	};
	printf("\n------------------------------------------------------------------------------\n");
};



// --------------------------------------------------------------------------------
// Name: PrintCensus
// Abstract: Print all the structure field values
//			 Prints specific form (NO COLUMN HEADER)
// --------------------------------------------------------------------------------
void PrintCensusCompleted(int intIndex, udtCensusFields* pudtCensus)	// point to the individual form passed
{	
	if (pudtCensus->blnCompleted)								// if completed, print
	{
		printf("%02d%4s", intIndex, "");
		printf("%-11s", pudtCensus->strDate);
		printf("%-11s", pudtCensus->strCounty);
		printf("%-11s", pudtCensus->strState);
		printf("%-17s", pudtCensus->strRace);
		printf("%9d ", pudtCensus->intHouseholdSize);
		printf("%10d\n", pudtCensus->intHouseholdIncome);
	};
};



// --------------------------------------------------------------------------------
// Name: PrintCensusFormEntry
// Abstract: Print all the structure field values, if entry previously completed
//			 Prints specific form WITH COLUMN HEADER
// --------------------------------------------------------------------------------
booleen PrintCensusFormEntry(int intIndex, udtCensusFields* pudtCensus)
// point to the individual form passed
{
	if (pudtCensus->blnCompleted)								// if completed, print
	{
		// Header
		printf("\n\n");
		printf("%-55s|%-10s|%-10s\n", "", "Household", "Household");
		printf("%-5s|%-10s|%-10s|%-10s|%-16s|%-10s|%-10s|", "Entry", "Date", "County", "State", "Race", "Size", "Income");
		printf("\n------------------------------------------------------------------------------\n");
		// Entry
		printf("%02d%4s", intIndex, "");
		printf("%-11s", pudtCensus->strDate);
		printf("%-11s", pudtCensus->strCounty);
		printf("%-11s", pudtCensus->strState);
		printf("%-17s", pudtCensus->strRace);
		printf("%9d ", pudtCensus->intHouseholdSize);
		printf("%10d", pudtCensus->intHouseholdIncome);
		printf("\n------------------------------------------------------------------------------\n");
		return 1;

	}
	else
	{
		printf("Entry %02d has not been previously completed.", intIndex);
		return 0;
	}
};
#pragma endregion
