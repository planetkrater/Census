// --------------------------------------------------------------------------------
// Author: Kate Wamsley
// Project Abstract: Census Read - Application for Census data to be analyzed
// Script Description: Controls excepted Census values for location and race
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
extern int intArraySize0;
extern int intCounties;
extern int intStates;
extern int intRaces;

// --------------------------------------------------------------------------------
// User Defined Types (UDT)
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
// Prototypes
// --------------------------------------------------------------------------------
// Print Census header
void CensusCodes(udtCensusCodes* pudtCensusCodesList);
void InitializeCensusCodes(char(*strCountyCode)[5][50], char(*strStateCode)[50], char(*strStateAbbr)[50], char(*strRaceCode)[50]);
void PopulateCensusCodes(char(*strCountyCode)[5][50], char(*strStateCode)[50], char(*strStateAbbr)[50], char(*strRaceCode)[50]);
void PrintCensusCodes(char(*strCountyCode)[5][50], char(*strStateCode)[50], char(*strRaceCode)[50]);



// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
// CENSUS CODES
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------



// --------------------------------------------------------------------------------
//	Name: CensusCodes
//	Abstract: Queue to initialize, populate and print Census Codes
// --------------------------------------------------------------------------------
void CensusCodes(udtCensusCodes* pudtCensusCodesList)
{
	InitializeCensusCodes(pudtCensusCodesList->strCountyCodes, pudtCensusCodesList->strStateCodes, pudtCensusCodesList->strStateAbbr, pudtCensusCodesList->strRaceCodes);

	PopulateCensusCodes(pudtCensusCodesList->strCountyCodes, pudtCensusCodesList->strStateCodes, pudtCensusCodesList->strStateAbbr, pudtCensusCodesList->strRaceCodes);

	PrintCensusCodes(pudtCensusCodesList->strCountyCodes, pudtCensusCodesList->strStateCodes, pudtCensusCodesList->strRaceCodes);

	printf("\n");
}



// --------------------------------------------------------------------------------
//	Name: InitializeCensusCodes
//	Abstract: 
// --------------------------------------------------------------------------------
void InitializeCensusCodes(char(*strCountyCode)[5][50], char(*strStateCode)[50], char(*strStateAbbr)[50], char(*strRaceCode)[50])
{
	int intStateIndex = 0;
	int intCountyIndex = 0;
	int intRaceIndex = 0;

	// Initialize State and Counties
	for (intStateIndex = 0; intStateIndex < intStates; intStateIndex += 1)
	{
		for (intCountyIndex = 0; intCountyIndex < intCounties; intCountyIndex += 1)
		{
			StringCopy(strCountyCode[intStateIndex][intCountyIndex], "");
		};
		StringCopy(strStateCode[intStateIndex], "");
		StringCopy(strStateAbbr[intStateIndex], "");
	};

	// Initialize Race
	for (intRaceIndex = 0; intRaceIndex < intRaces; intRaceIndex += 1)
	{
		StringCopy(strRaceCode[intRaceIndex], "");
	};
}



// --------------------------------------------------------------------------------
//	Name: PopulateCensusCodes
//	Abstract: 
// --------------------------------------------------------------------------------
void PopulateCensusCodes(char(*strCountyCode)[5][50], char(*strStateCode)[50], char(*strStateAbbr)[50], char(*strRaceCode)[50])
{
	// Populate - County
	StringCopy(strCountyCode[0][0], "Hamilton");
	StringCopy(strCountyCode[0][1], "Butler");
	StringCopy(strCountyCode[0][2], "Clermont");
	StringCopy(strCountyCode[0][3], "Warren");
	StringCopy(strCountyCode[1][0], "Campbell");
	StringCopy(strCountyCode[1][1], "Boone");
	StringCopy(strCountyCode[1][2], "Kenton");
	// Populate - State
	StringCopy(strStateCode[0], "Ohio");
	StringCopy(strStateCode[1], "Kentucky");
	// Populate - State
	StringCopy(strStateAbbr[0], "OH");
	StringCopy(strStateAbbr[1], "KY");
	// Populate - Race
	StringCopy(strRaceCode[0], "Caucasian");
	StringCopy(strRaceCode[1], "African American");
	StringCopy(strRaceCode[2], "Hispanic");
	StringCopy(strRaceCode[3], "Asian");
	StringCopy(strRaceCode[4], "Other");
}



// --------------------------------------------------------------------------------
//	Name: PrintCensusCodes
//	Abstract: 
// --------------------------------------------------------------------------------
void PrintCensusCodes(char(*strCountyCode)[5][50], char(*strStateCode)[50], char(*strRaceCode)[50])
{
	int intStateIndex = 0;
	int intCountyStateIndex = 0;
	int intCountyIndex = 0;
	int intRaceIndex = 0;

	// Print headers
	printf("Census Codes:\n");
	printf("%-6s %-17s %s", "|", "Counties", "|");
	printf("%-6s %-7s %s", "|", "States", "|");
	printf("%-6s %-15s %s", "|", "Races", "|");
	printf("\n------------------------------------------------------------------------------\n");

	// Get 1D of Counties array
	for (intCountyStateIndex = 0; intCountyStateIndex < intStates; intCountyStateIndex += 1)
	{
		// Get 2D of Counties array
		for (intCountyIndex = 0; intCountyIndex < intCounties; intCountyIndex += 1, intStateIndex += 1, intRaceIndex += 1)
		{
			// Do any more counties need to be printed
			if (StringLength(strCountyCode[intCountyStateIndex][intCountyIndex]) != 0)
			{
				// Yes, print the next county
				printf("[ %d%d ] %-8s, %-10s", intCountyStateIndex, intCountyIndex, strCountyCode[intCountyStateIndex][intCountyIndex], strStateCode[intCountyStateIndex]);

				// Do any more states need to be printed 
				if (StringLength(strStateCode[intStateIndex]) != 0 && intStateIndex < 2)
				{
					// Yes, print the next state
					printf("[ %d ] %-10s", intStateIndex, strStateCode[intStateIndex]);
				}
				else
				{
					// No, print white space for column alignment
					PrintWhiteSpace(16);
				}

				// Do any more races need to be printed 
				if (StringLength(strRaceCode[intRaceIndex]) != 0 && intRaceIndex < 5)
				{
					// Yes, print the next state
					printf("[ %d ] %-16s", intRaceIndex, strRaceCode[intRaceIndex]);
				}

				printf("\n");
			}
		}
	}
	printf("------------------------------------------------------------------------------\n");
	printf("------------------------------------------------------------------------------\n");
}