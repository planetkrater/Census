// --------------------------------------------------------------------------------
// Name: Kate Wamsley
// Project Abstract: Census Append - Application for Census surveyors to enter collected information
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
void EntryActions(udtCensusFields* audtCensusForms, udtCensusCodes* pudtCensusCodesList);

// Edit Census Form
void PrintEntryActions();
void EditCensusForms(udtCensusFields audtCensusForms[], udtCensusCodes* pudtCensusCodesList);
	booleen PrintCensusFormEntry(int intIndex, udtCensusFields* pudtCensus);
		void EditCensusFormEntry(udtCensusFields audtCensusForms[], udtCensusCodes* pudtCensusCodesList, int intEntry);
			void EditCensusFormEntrySection(udtCensusFields* pudtCensus, udtCensusCodes* pudtCensusCodesList, int intSection);

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
	
	//------ User Interaction Components ------//
	// Ask user what action to perform next						 
	EntryActions(audtCensusForms, &audtCensusCodesList);	

	//-------------- END PROGRAM --------------//
	printf("\nThank you and have a nice day!\n");
	system("pause");
}



// --------------------------------------------------------------------------------
//	Name: PrintEntryActions
//	Abstract: Print list of possible entry actions
// --------------------------------------------------------------------------------
void PrintEntryActions()
{
	//header
	printf("\n------------------------------------------------------------------------------\n");
	printf("       MAIN MENU\n");
	printf("[ 01 ] Enter New Entries\n");
	printf("[ 02 ] Edit New Entries\n");
	printf("[ 03 ] Review\n");
	printf("[ 04 ] Save\n");
	printf("[ 05 ] Delete New Entries\n");
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
	
	// Print entry actions
	PrintEntryActions();

	do
	{
		// Reset
		intEntry = -1;
		intInput = 0;
		charSave = "";		

		while (intEntry < 1 || (intEntry > 5 && intEntry != 99))
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
			// Populate Census Forms
			PopulateCensusForms(audtCensusForms, pudtCensusCodesList);	// Result - allow user to enter data into each field on each form and validate input using codes
			blnChange = 1;
			break;
		case 2:
			// Print Census Forms
			PrintCensusForms(audtCensusForms);							// Result - show each field on each form completed
			// Edit Census Froms
			EditCensusForms(audtCensusForms, pudtCensusCodesList);		// Result - allow user to edit existing entries
			blnChange = 1;
			break;
		case 3:
			// Print Census Forms
			PrintCensusForms(audtCensusForms);							// Result - show each field on each form completed
			break;
		case 4:
			// Save Census Forms to file.txt
			FileAppend(audtCensusForms);							// Result - PRINT/SAVE to file each field on each form completed
			// re-initialize to default values
			InitializeCensusForms(audtCensusForms);
			printf("Entry list has been cleared.\n");
			blnChange = 0;
			break;
		case 5:
			printf("Are you sure you want to delete all new entries (Y/N)? ");
			scanf(" %c", &charSave);
			if (charSave == 89 || charSave == 121) // Y or y
			{	// re-initialize to default values
				InitializeCensusForms(audtCensusForms);
				printf("Entry list has been cleared.\n");
			}
			else
			{
				printf("Action aborted.\n");
			}
			blnChange = 0;
			break;
		case 99:
			if (blnChange == 1)
			{
				printf("Save changes to file before exiting (Y/N)? ");
				scanf(" %c", &charSave);
				if (charSave == 89 || charSave == 121) // Y or y
				{	// Save
					FileAppend(audtCensusForms);							// Result - PRINT/SAVE to file each field on each form completed
					blnChange = 0;
				}
			}
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



#pragma region "Edit Existing Census Forms"
// --------------------------------------------------------------------------------
// Name: EditCensusForms
// Abstract: Ask user what entry they would like to edit
// --------------------------------------------------------------------------------
void EditCensusForms(udtCensusFields audtCensusForms[], udtCensusCodes* pudtCensusCodesList)
{
	booleen blnValid = 0; //false
	int intEntry = -2;
	int intInput = 0;
	

	printf("\n[ -1 ] Quit Edit\n");
	do
	{
		// Reset
		intEntry = -2;
		intInput = 0;
		
		while (intInput == 0 && intEntry < -1)
		{
			// Prompt user for entry number
			printf("\nEnter the number of the Entry to edit: ");
			intInput = scanf("%d", &intEntry);

			// Flush the input buffer
			while ((getchar()) != '\n');
		}	
		
		// Has QUIT been entered
		if (intEntry == -1) {
			// Yes, quit EditCensusForm()
			blnValid = 1; //true
			break;
		}

		// If input Entry number a valid, print to console
		if (PrintCensusFormEntry(intEntry, &audtCensusForms[intEntry]))
		{
			// Determine how to edit form
			EditCensusFormEntry(audtCensusForms, pudtCensusCodesList, intEntry);
			
			// Tell user editting complete
			printf("\nEdits to Entry %02d have been accepted.\n\n", intEntry);
		}			
			
	} while (blnValid == 0); //false
}



// --------------------------------------------------------------------------------
// Name: EditCensusFormEntry
// Abstract: Ask user what entry section they would like to edit
// --------------------------------------------------------------------------------
void EditCensusFormEntry(udtCensusFields audtCensusForms[], udtCensusCodes* pudtCensusCodesList, int intEntry)
{
	booleen blnValid = 0; //false
	int intSection = -2;
	int intInput = 0;

	// Sections
	printf("%-5s|%-10s|%-10s|%-10s|%-16s|%-10s|%-10s|\n", "Sec:", "[ 1 ]", "[ 2 ]", "[ 3 ]", "[ 4 ]", "[ 5 ]", "[ 6 ]");

	do
	{
		// Reset
		intSection = -2;
		intInput = 0;


		while (intInput == 0 && intSection < -1)
		{
			// Prompt user for section or all
			printf("\nEnter Section number to edit or enter [ 0 ] to edit all: ");
			intInput = scanf("%d", &intSection);

			// Flush the input buffer
			while ((getchar()) != '\n');
		}

		// Has QUIT been entered
		if (intSection == -1) {
			// Yes, quit EditCensusFormEntry()
			blnValid = 1; //true
			break;
		}

		// Section or All?
		if (intSection == 0) 
		{
			// ALL SECTIONS --> module on PopulateCensusForm.c			//send form and codes
			PopulateCensusPrompt(&audtCensusForms[intEntry], pudtCensusCodesList); 
		}
		else if (intSection > 0 && intSection < 7)
		{
			// SPECIFIED SECTION										//send form, codes, and section number
			EditCensusFormEntrySection(&audtCensusForms[intEntry], pudtCensusCodesList, intSection);
		}
		else
		{
			printf("Section number not recognized.");
		}		
		
	} while (blnValid == 0);
}



// --------------------------------------------------------------------------------
// Name: EditCensusFormEntrySection
// Abstract: Command edit to field based section provided
// --------------------------------------------------------------------------------
void EditCensusFormEntrySection(udtCensusFields* pudtCensus, udtCensusCodes* pudtCensusCodesList, int intSection)
{
	switch (intSection) // case section --> module on PopulateCensusForm.c
	{
	case 1:
		GetDate(pudtCensus->strDate);
		break;
	case 2:
	case 3:
		printf("County and State must be editted together.\n");
		GetCountyState(pudtCensus->strCounty, pudtCensus->strState, pudtCensusCodesList->strCountyCodes, pudtCensusCodesList->strStateCodes);
		break;
	case 4:
		GetRace(pudtCensus->strRace, pudtCensusCodesList->strRaceCodes);
		break;
	case 5:
		GetHouseholdSize(&pudtCensus->intHouseholdSize);
		break;
	case 6:
		GetHouseholdIncome(&pudtCensus->intHouseholdIncome);
		break;
	default:
		printf("Section number not recognized.");
	}
}
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
