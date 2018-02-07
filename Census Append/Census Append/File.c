// --------------------------------------------------------------------------------
// Author: Kate Wamsley
// Project Abstract: Census Append - Application for Census surveyors to enter collected information
// Script Description: Connects app to local txt file to APPEND new data
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
// Declare structs
typedef struct
{
	char strFileDate[50];
	char strFileCounty[50];
	char strFileState[50];
	char strFileRace[50];
	int intFileHouseholdSize;
	int intFileHouseholdIncome;
	booleen blnFileCompleted;
} udtFileCensusFields;


// --------------------------------------------------------------------------------
// Prototypes
// --------------------------------------------------------------------------------
void FileAppend(udtCensusFields audtCensusForms[]);
int OpenInputFile(char strFileName[], FILE** ppfilInput);
void FilePrintCensus(FILE* pfileInput, udtCensusFields* pudtCensus);

// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
// FILE
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
// Name: FileAppend
// Abstract: Open the file for APPENDING.  Return true if successful.
// --------------------------------------------------------------------------------
void FileAppend(udtCensusFields audtCensusForms[])
{
	// Declare a file pointer
	FILE* pfileInput = 0;
	int intIndex = 0;

	// Try to open the file for reading 
	pfileInput = fopen("CensusData.txt", "a+");

	// Was the file opened?
	if (pfileInput)
	{
		for (intIndex = 0; intIndex < intArraySize; intIndex += 1)	// loop through index of accepted forms
		{
			FilePrintCensus(pfileInput, &audtCensusForms[intIndex]);		// pass each accepted form individually
		};
		printf("\nCensus Data .txt file has been appended.\n");
	}
	else
	{
		// No
		printf("\nError opening \"CensusData.txt\" for appending!!!\n");
	}
	// Clean up
	fclose(pfileInput);
}



// --------------------------------------------------------------------------------
// Name: OpenInputFile
// Abstract: Open the file for reading.  Return true if successful.
// --------------------------------------------------------------------------------
int OpenInputFile(char strFileName[], FILE** ppfilInput)
{
	int intResultFlag = 0;

	// Open the file for reading
	*ppfilInput = fopen(strFileName, "r");

	// Success?
	if (*ppfilInput != 0)
	{
		// Yes
		intResultFlag = 1;
	}
	;
	return intResultFlag;
};



// --------------------------------------------------------------------------------
// Name: FilePrintAddress
// Abstract: Print to file all the structure field values
// --------------------------------------------------------------------------------
void FilePrintCensus(FILE* pfileInput, udtCensusFields* pudtCensus)	// point to the individual form passed
{
	if (pudtCensus->blnCompleted)								// if completed, print
	{
		fprintf(pfileInput, "%s, ", pudtCensus->strDate);
		fprintf(pfileInput, "%s, ", pudtCensus->strCounty);
		fprintf(pfileInput, "%s, ", pudtCensus->strState);
		fprintf(pfileInput, "%s, ", pudtCensus->strRace);
		fprintf(pfileInput, "%d, ", pudtCensus->intHouseholdSize);
		fprintf(pfileInput, "%d, ", pudtCensus->intHouseholdIncome);
		fprintf(pfileInput, "%d\n", pudtCensus->blnCompleted);
	};
};

