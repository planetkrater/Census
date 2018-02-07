// --------------------------------------------------------------------------------
// Author: Kate Wamsley
// Project Abstract: Census Read - Application for Census data to be analyzed
// Script Description: Connects app to local txt file to READ new data
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
void FileRead(udtCensusFields audtCensusForms[], udtCensusCodes* pudtCensusCodesList);

int OpenInputFile(char strFileName[], FILE** ppfilInput);

void FormatAndStorageQueue(char strSource[], udtCensusFields* pudtCensus, udtCensusCodes* pudtCensusCodesList);
	void InitializeFileCensus(udtFileCensusFields* pudtFileCensus);	
		void FormatSection(char strSource[], udtFileCensusFields* pudtFileCensusFields, udtCensusCodes* ppudtCensusCodesList);
			void CopyFileToCensus(udtCensusFields* pudtCensus, udtFileCensusFields* pudtFileCensusFields);


// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
// FILE
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
// Name: PopulateAddressList
// Abstract: Load the addresses from a file into the array.
// --------------------------------------------------------------------------------
void FileRead(udtCensusFields audtCensusForms[], udtCensusCodes* pudtCensusCodesList)
{
	// Declare a file pointer
	FILE* pfileInput = 0;
	int intResultFlag = 0;
	char chrLetter = 0;
	int intCharIndex = 0;
	char strBuffer[150] = "";
	int intBufferIndex = 0;
	int intArrayIndex = 0;

	// Try to open the file for reading 
	pfileInput = fopen("CensusData.txt", "rb");

	// Was the file opened?
	if (pfileInput)
	{
		// Yes, read in records until end of file( EOF )
		while (feof(pfileInput) == 0)
		{
			// Read one character
			chrLetter = fgetc(pfileInput);

			// Print out line to screen
			if (chrLetter == 13)		//carriage return
			{
				//printf("%s\n", strBuffer);

				// Send line to be formated and stored in structure
				FormatAndStorageQueue(strBuffer, &audtCensusForms[intArrayIndex], pudtCensusCodesList); //send as single closed "suitcase" -- single structure

				// Increment AddressList array
				intArrayIndex += 1;
				
			}
			else if (chrLetter == 10)	//newline
			{
				// Reset buffer and index
				StringEmpty(strBuffer);
				intBufferIndex = 0;
			}
			else
			{
				//Place in buffer array
				strBuffer[intBufferIndex] = chrLetter;
				intBufferIndex += 1;
			}
		};
		// Clean up
		fclose(pfileInput);
	};
};



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
// Name: FormatAndStorageQueue
// Abstract: 
// --------------------------------------------------------------------------------
void FormatAndStorageQueue(char strSource[], udtCensusFields* pudtCensus, udtCensusCodes* pudtCensusCodesList)
{
	// Declare variables
	udtFileCensusFields audtFileCensusFields;

	// Initialize instance
	InitializeFileCensus(&audtFileCensusFields);

	// Clean up string leading end
	TrimStartWhiteSpace(strSource);

	// Get file fields
	FormatSection(strSource, &audtFileCensusFields, pudtCensusCodesList);

	// Copy file fields to census fields
	CopyFileToCensus(pudtCensus, &audtFileCensusFields);
}



// --------------------------------------------------------------------------------
// Name: InitializeFileCensus
// Abstract: Fill each field of the individual form passed with a default value.
// --------------------------------------------------------------------------------
void InitializeFileCensus(udtFileCensusFields* pudtFileCensus)			// point to the individual form passed
{
	StringCopy(pudtFileCensus->strFileDate, "");						// date
	StringCopy(pudtFileCensus->strFileCounty, "");						// county
	StringCopy(pudtFileCensus->strFileState, "");						// state
	StringCopy(pudtFileCensus->strFileRace, "");						// race
	pudtFileCensus->intFileHouseholdSize = 0;							// # in household
	pudtFileCensus->intFileHouseholdIncome = 0;							// yearly income of household
	pudtFileCensus->blnFileCompleted = 0;								// (not) completed
};



// --------------------------------------------------------------------------------
// Name: FormatSection
// Abstract: 
// --------------------------------------------------------------------------------
void FormatSection(char strSource[], udtFileCensusFields* pudtFileCensusFields, udtCensusCodes* ppudtCensusCodesList)
{
	int intStructIndex = 0;
	int intLength = 0;
	char charLetterToFind = 44;	
	int intCommaIndex = 0;

	char strSection[100] = "";
	char strSection2[100] = "";
	int intStateCode = 0;
	int intCountyCode = 0;
	int intRaceCode = 0;
	int intSize = 0;
	int intIncome = 0;
	booleen blnComp = 0;

	// Prep source string
	TrimStartWhiteSpace(strSource);
	intLength = StringLength(strSource);
	while(intLength > 0 && intCommaIndex >= 0)
	{
		// Find location of the next
		intCommaIndex = FindLetterNextIndex(strSource, charLetterToFind, 0);

		// Get Record ID as string, cast to integer, store in array
		if (intCommaIndex >= 0)
		{
			StringMid(strSection, strSource, 0, intCommaIndex);
		}		
		TrimWhiteSpace(strSection);

		// Store
		switch (intStructIndex)
		{
		case 0:
			if (!ValidateDate(&strSection))
			{
				printf("Date %s is not valid.", strSection);
				GetDate(strSection);
			}
			StringCopy(pudtFileCensusFields->strFileDate, strSection);
			break;
		case 1:
			// hold county, wait for state
			StringCopy(strSection2, strSection);
			break;
		case 2:
			intStateCode = ValidOneDimCensusCode(strSection, ppudtCensusCodesList->strStateCodes, intStates);
			if (intStateCode >= 0)
			{
				intCountyCode = ValidCountyCode(strSection2, ppudtCensusCodesList->strCountyCodes, intStateCode);
			};
			if (intStateCode < 0 || intCountyCode < 0)
			{
				printf("--> County and State combination do not match.\n %s, %s", strSection2, strSection);
				GetCountyState(strSection2, strSection, pudtFileCensusFields->strFileCounty, pudtFileCensusFields->strFileState);
			}
			else
			{
				StringCopy(pudtFileCensusFields->strFileState, strSection);
				StringCopy(pudtFileCensusFields->strFileCounty, strSection2);
			}
			break;
		case 3:
			intRaceCode = ValidOneDimCensusCode(strSection, ppudtCensusCodesList->strRaceCodes, intRaces);
			if (intRaceCode < 0)
			{
				printf("--> Race does not match accepted list.\n");
				GetRace(strSection, pudtFileCensusFields->strFileRace);
			}
			else
			{
				StringCopy(pudtFileCensusFields->strFileRace, strSection);
			}
			break;
		case 4:
			if (!ValidateNumeric(strSection))
			{
				printf("--> Household Size must be numeric with no special characters.\n");
				GetHouseholdSize(intSize);
			}
			intSize = atoi(strSection);
			if (intSize < 0)
			{
				printf("--> Household Size must be greater than 0.\n");
				GetHouseholdSize(intSize);
			}
			pudtFileCensusFields->intFileHouseholdSize = intSize;
			break;
		case 5:
			if (!ValidateNumeric(strSection))
			{
				printf("--> Household Annual Income must be numeric with no special characters.\n");
				GetHouseholdIncome(intIncome);
			}
			intIncome = atoi(strSection);
			if (intIncome < 0)
			{
				printf("--> Household Annual Income must be greater than 0.\n");
				GetHouseholdSize(intIncome);
			}
			pudtFileCensusFields->intFileHouseholdIncome = intIncome;
			break;
		case 6:
			//blnComp = atoi(strSection);
			//if (!ValidateNumeric(strSection) || blnComp < 0 || blnComp > 1)
			//{
			//	blnComp = 1;
			//}
			pudtFileCensusFields->blnFileCompleted = 1;
			break;
		default:
			printf("error");

		}
		intStructIndex += 1;

		// Trim Source
		if (intCommaIndex >= 0)
		{
			StringTrimStart(strSource, intCommaIndex);
		}
		intLength -= intCommaIndex + 1;

	}


}



// --------------------------------------------------------------------------------
// Name: CopyFileToCensus
// Abstract: 
// --------------------------------------------------------------------------------
void CopyFileToCensus(udtCensusFields* pudtCensus, udtFileCensusFields* pudtFileCensusFields)
{
	StringCopy(pudtCensus->strDate, pudtFileCensusFields->strFileDate);
	StringCopy(pudtCensus->strCounty, pudtFileCensusFields->strFileCounty);
	StringCopy(pudtCensus->strState, pudtFileCensusFields->strFileState);
	StringCopy(pudtCensus->strRace, pudtFileCensusFields->strFileRace);
	pudtCensus->intHouseholdSize = pudtFileCensusFields->intFileHouseholdSize;
	pudtCensus->intHouseholdIncome = pudtFileCensusFields->intFileHouseholdIncome;
	pudtCensus->blnCompleted = pudtFileCensusFields->blnFileCompleted;
}