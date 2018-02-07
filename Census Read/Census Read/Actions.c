// --------------------------------------------------------------------------------
// Author: Kate Wamsley
// Project Abstract: Census Read - Application for Census data to be analyzed
// Script Description: Data processing functions
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
void TotalCompleted(udtCensusFields audtCensusForms[]);
void TotalCompletedByCounty(udtCensusFields audtCensusForms[], udtCensusCodes* pudtCensusCodesList);
void TotalCompletedByRace(udtCensusFields audtCensusForms[], udtCensusCodes* pudtCensusCodesList);
void AverageIncome(udtCensusFields audtCensusForms[]);
void AverageIncomeByCountyState(udtCensusFields audtCensusForms[], udtCensusCodes* pudtCensusCodesList);
void AverageIncomeByRace(udtCensusFields audtCensusForms[], udtCensusCodes* pudtCensusCodesList);
void PercentageBelowPoverty(udtCensusFields audtCensusForms[], udtCensusCodes* pudtCensusCodesList);
void PercentageBelowPovertyByCountyState(udtCensusFields audtCensusForms[], udtCensusCodes* pudtCensusCodesList);
void PercentageBelowPovertyByRace(udtCensusFields audtCensusForms[], udtCensusCodes* pudtCensusCodesList);
booleen ValidatePoverty(int intSize, int intIncome);

// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
// ACTIONS
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
// Name: TotalCompleted
// Abstract: Find the number of surveys completed
// --------------------------------------------------------------------------------
void TotalCompleted(udtCensusFields audtCensusForms[])	// accept all the forms of fields sent
{
	int intIndex = 0;
	int intCount = 0;
	
	for (intIndex = 0; intIndex < intArraySize; intIndex += 1)	// loop through index of accepted forms
	{
		//intCount += CensusCompleted(&audtCensusForms[intIndex]);
		intCount += audtCensusForms[intIndex].blnCompleted; // pass each accepted form individually
	};
	printf("\n\n");
	printf("A. Total HouseHolds Surveyed : %d", intCount);
	printf("\n------------------------------------------------------------------------------\n");
};



// --------------------------------------------------------------------------------
// Name: TotalCompletedByCounty
// Abstract: Find the number of surveys completed by COUNTY
// --------------------------------------------------------------------------------
void TotalCompletedByCounty(udtCensusFields audtCensusForms[], udtCensusCodes* pudtCensusCodesList)	// accept all the forms of fields sent
{
	int intIndex = 0;
	int intStateIndex = 0;
	int intCountyIndex = 0;
	int intCount = 0;

	printf("\n\n");
	printf("B. Total HouseHolds Surveyed By Count: \n");
	for (intStateIndex = 0; intStateIndex < intStates; intStateIndex += 1)
	{
		for (intCountyIndex = 0; intCountyIndex < intCounties; intCountyIndex += 1)
		{
			// is county valid?
			if (*pudtCensusCodesList->strCountyCodes[intStateIndex][intCountyIndex] != '\0')
			{
				// reset Count
				intCount = 0;
				// loop to find county count
				for (intIndex = 0; intIndex < intArraySize; intIndex += 1)	// loop through index of accepted forms
				{
					// is form completed?
					if (audtCensusForms[intIndex].blnCompleted)
					{
						// yes, does the form have the correct state
						if (StringCompareSame(audtCensusForms[intIndex].strState, pudtCensusCodesList->strStateCodes[intStateIndex]))
						{
							// yes, does the form have the correct county
							if (StringCompareSame(audtCensusForms[intIndex].strCounty, pudtCensusCodesList->strCountyCodes[intStateIndex][intCountyIndex]))
							{
								intCount += 1;
							}
						}
					}
				}
				// county count complete, print count			
				printf("%-10s %-10s %s %d\n", pudtCensusCodesList->strCountyCodes[intStateIndex][intCountyIndex], pudtCensusCodesList->strStateCodes[intStateIndex], ":", intCount);
			}
		}

	};	
	printf("\n------------------------------------------------------------------------------\n");
};



// --------------------------------------------------------------------------------
// Name: TotalCompletedByRace
// Abstract: Find the number of surveys completed by RACE
// --------------------------------------------------------------------------------
void TotalCompletedByRace(udtCensusFields audtCensusForms[], udtCensusCodes* pudtCensusCodesList)	// accept all the forms of fields sent
{
	int intIndex = 0;
	int intRaceIndex = 0;
	int intCount = 0;

	printf("\n\n");
	printf("C. Total HouseHolds Surveyed By Race: \n");
	for (intRaceIndex = 0; intRaceIndex < intRaces; intRaceIndex += 1)
	{
		if (*pudtCensusCodesList->strRaceCodes[intRaceIndex] != '\0')
		{
			// reset Count
			intCount = 0;
			// loop to find county count
			for (intIndex = 0; intIndex < intArraySize; intIndex += 1)	// loop through index of accepted forms
			{
				// is form completed?
				if (audtCensusForms[intIndex].blnCompleted)
				{
					// yes, does the form have the correct race?
					if (StringCompareSame(audtCensusForms[intIndex].strRace, pudtCensusCodesList->strRaceCodes[intRaceIndex]))
					{
						intCount += 1;
					}
				}				
			}
			// race count complete, print count			
			printf("%-18s : %d\n", pudtCensusCodesList->strRaceCodes[intRaceIndex], intCount);
		}
	}

	printf("\n------------------------------------------------------------------------------\n");
}



// --------------------------------------------------------------------------------
// Name: AverageIncome
// Abstract: Find the Average household Income of surveys completed
// --------------------------------------------------------------------------------
void AverageIncome(udtCensusFields audtCensusForms[])	// accept all the forms of fields sent
{
	int intIndex = 0;
	int intCount = 0;
	float dblIncomeTotal = 0;
	float dblIncomeAvg = 0;

	for (intIndex = 0; intIndex < intArraySize; intIndex += 1)	// loop through index of accepted forms
	{
		// is form completed?
		if (audtCensusForms[intIndex].blnCompleted)
		{
			intCount += 1;
			dblIncomeTotal += audtCensusForms[intIndex].intHouseholdIncome;
		}
	};
	// find average
	dblIncomeAvg = dblIncomeTotal / intCount;
	printf("\n\n");
	printf("D. Average HouseHold Income : $%.2f", dblIncomeAvg);
	printf("\n------------------------------------------------------------------------------\n");
};



// --------------------------------------------------------------------------------
// Name: AverageIncomeByCountyState
// Abstract: Find the Average household Income of surveys completed by COUNTY and STATE
// --------------------------------------------------------------------------------
void AverageIncomeByCountyState(udtCensusFields audtCensusForms[], udtCensusCodes* pudtCensusCodesList)	// accept all the forms of fields sent
{
	int intIndex = 0;
	int intStateIndex = 0;
	int intCountyIndex = 0;
	
	int intStateHouseCount = 0; 
	int intCountyHouseCount = 0;
	float dblStateIncomeTotal = 0;
	float dblCountyIncomeTotal = 0;
	float dblStateIncomeAvg = 0;
	float dblCountyIncomeAvg = 0;

	printf("\n\n");
	printf("E. Average House Income By Count and State: \n\n");
	for (intStateIndex = 0; intStateIndex < intStates; intStateIndex += 1)
	{
		// reset vars
		intStateHouseCount = 0;
		dblStateIncomeTotal = 0;
		dblStateIncomeAvg = 0;

		for (intCountyIndex = 0; intCountyIndex < intCounties; intCountyIndex += 1)
		{
			// is county valid?
			if (*pudtCensusCodesList->strCountyCodes[intStateIndex][intCountyIndex] != '\0')
			{
				// reset Count
				intCountyHouseCount = 0;
				dblCountyIncomeTotal = 0.0;
				dblCountyIncomeAvg = 0.0;

				// yes, loop to find county count
				for (intIndex = 0; intIndex < intArraySize; intIndex += 1)	// loop through index of accepted forms
				{
					// is form completed?
					if (audtCensusForms[intIndex].blnCompleted)
					{
						// yes, does the form have the correct state
						if (StringCompareSame(audtCensusForms[intIndex].strState, pudtCensusCodesList->strStateCodes[intStateIndex]))
						{
							// yes, does the form have the correct county
							if (StringCompareSame(audtCensusForms[intIndex].strCounty, pudtCensusCodesList->strCountyCodes[intStateIndex][intCountyIndex]))
							{
								intCountyHouseCount += 1;
								dblCountyIncomeTotal += audtCensusForms[intIndex].intHouseholdIncome;
							}
						}
					}
				}

				// get county average
				if (dblCountyIncomeTotal != 0 && intCountyHouseCount != 0)
				{
					dblCountyIncomeAvg = dblCountyIncomeTotal / intCountyHouseCount;
				}
				// county count complete, print count			
				printf("%2s %-12s %s $%.2f\n", "", pudtCensusCodesList->strCountyCodes[intStateIndex][intCountyIndex], ":", dblCountyIncomeAvg);
				
				// add county totals to state counts
				intStateHouseCount += intCountyHouseCount;
				dblStateIncomeTotal += dblCountyIncomeTotal;
			}			
		}

		// get state average
		if (dblStateIncomeTotal != 0 && intStateHouseCount != 0)
		{
			dblStateIncomeAvg = dblStateIncomeTotal / intStateHouseCount;
		}
		// county count complete, print count			
		printf("%-15s : $%.2f\n\n", pudtCensusCodesList->strStateCodes[intStateIndex], dblStateIncomeAvg);

	};
	printf("\n------------------------------------------------------------------------------\n");
};



// --------------------------------------------------------------------------------
// Name: AverageIncomeByRace
// Abstract: Find the Average household Income of surveys completed by COUNTY and STATE
// --------------------------------------------------------------------------------
void AverageIncomeByRace(udtCensusFields audtCensusForms[], udtCensusCodes* pudtCensusCodesList)	// accept all the forms of fields sent
{
	int intIndex = 0;
	int intRaceIndex = 0;

	int intRaceHouseCount = 0;
	float dblRaceIncomeTotal = 0;
	float dblRaceIncomeAvg = 0;

	printf("\n\n");
	printf("F. Average House Income By Race: \n\n");

	for (intRaceIndex = 0; intRaceIndex < intRaces; intRaceIndex += 1)
	{
		if (*pudtCensusCodesList->strRaceCodes[intRaceIndex] != '\0')
		{
			// reset Count
			intRaceHouseCount = 0;
			dblRaceIncomeTotal = 0.0;
			dblRaceIncomeAvg = 0.0;

			// loop to find county count
			for (intIndex = 0; intIndex < intArraySize; intIndex += 1)	// loop through index of accepted forms
			{
				// is form completed?
				if (audtCensusForms[intIndex].blnCompleted)
				{
					// yes, does the form have the correct race?
					if (StringCompareSame(audtCensusForms[intIndex].strRace, pudtCensusCodesList->strRaceCodes[intRaceIndex]))
					{
						intRaceHouseCount += 1;
						dblRaceIncomeTotal += audtCensusForms[intIndex].intHouseholdIncome;
					}
				}
			}
			// get Race average
			if (dblRaceIncomeTotal != 0 && intRaceHouseCount != 0)
			{
				dblRaceIncomeAvg = dblRaceIncomeTotal / intRaceHouseCount;
			}
			// Race count complete, print count			
			printf("%-18s : %.2f\n", pudtCensusCodesList->strRaceCodes[intRaceIndex], dblRaceIncomeAvg);
		}
	}
	printf("\n------------------------------------------------------------------------------\n");
};



// --------------------------------------------------------------------------------
// Name: PercentageBelowPoverty
// Abstract: Find the Percentage Below Poverty 
// --------------------------------------------------------------------------------
void PercentageBelowPoverty(udtCensusFields audtCensusForms[], udtCensusCodes* pudtCensusCodesList)	// accept all the forms of fields sent
{
	int intIndex = 0;
	double dblCount = 0.0;
	double dblPoverty = 0.0;
	int intSize = 0;
	int intIncome = 0;
	float dblPercent = 0.0;

	printf("\n\n");
	
	// loop through all forms
	for (intIndex = 0; intIndex < intArraySize; intIndex += 1)	// loop through index of accepted forms
	{
		// is form completed?
		if (audtCensusForms[intIndex].blnCompleted)
		{
			//increment house count
			dblCount += 1;

			// get size and income
			intSize = audtCensusForms[intIndex].intHouseholdSize;
			intIncome = audtCensusForms[intIndex].intHouseholdIncome;

			if (ValidatePoverty(intSize, intIncome))
			{
				//increment poverty count
				dblPoverty += 1;
			}
		}
	}
	// get percent
	if (dblCount != 0 && dblPoverty != 0)
	{
		dblPercent = dblPoverty / dblCount * 100;
	}
	// print percent
	printf("G. Percentage Below Poverty: %0.1f %s\n\n", dblPercent, "%");
	printf("\n------------------------------------------------------------------------------\n");
}

// --------------------------------------------------------------------------------
// Name: PercentageBelowPovertyByCountyState
// Abstract: Find the Percentage Below Poverty by COUNTY and STATE
// --------------------------------------------------------------------------------
void PercentageBelowPovertyByCountyState(udtCensusFields audtCensusForms[], udtCensusCodes* pudtCensusCodesList)	// accept all the forms of fields sent
{
	int intIndex = 0;
	int intStateIndex = 0;
	int intCountyIndex = 0;

	float dblStateHouseCount = 0.0;
	float dblCountyHouseCount = 0.0;

	int intStateHouseSize = 0;
	int intCountyHouseSize = 0;

	int intStateIncomeTotal = 0;
	int intCountyIncomeTotal = 0;

	float dblStatePoverty = 0.0;
	float dblCountyPoverty = 0.0;

	float dblStatePercent = 0.0;
	float dblCountyPercent = 0.0;

	printf("\n\n");
	printf("H. Percentage Below Poverty By Count and State: \n\n");
	for (intStateIndex = 0; intStateIndex < intStates; intStateIndex += 1)
	{
		// reset vars
		dblStateHouseCount, dblStatePercent, dblStatePoverty = 0.0;
		intStateHouseSize, intStateIncomeTotal = 0;

		for (intCountyIndex = 0; intCountyIndex < intCounties; intCountyIndex += 1)
		{
			// is county valid?
			if (*pudtCensusCodesList->strCountyCodes[intStateIndex][intCountyIndex] != '\0')
			{
				// reset Count
				dblCountyHouseCount, dblCountyPercent, dblCountyPoverty = 0.0;
				intCountyHouseSize,intCountyIncomeTotal = 0;

				// yes, loop to find county count
				for (intIndex = 0; intIndex < intArraySize; intIndex += 1)	// loop through index of accepted forms
				{
					// is form completed?
					if (audtCensusForms[intIndex].blnCompleted)
					{
						// yes, does the form have the correct state
						if (StringCompareSame(audtCensusForms[intIndex].strState, pudtCensusCodesList->strStateCodes[intStateIndex]))
						{
							// yes, does the form have the correct county
							if (StringCompareSame(audtCensusForms[intIndex].strCounty, pudtCensusCodesList->strCountyCodes[intStateIndex][intCountyIndex]))
							{
								//increment house count
								dblCountyHouseCount += 1;

								// get size and income
								intCountyHouseSize = audtCensusForms[intIndex].intHouseholdSize;
								intCountyIncomeTotal = audtCensusForms[intIndex].intHouseholdIncome;

								if (ValidatePoverty(intCountyHouseSize, intCountyIncomeTotal))
								{
									//increment poverty count
									dblCountyPoverty += 1;
								}
							}
						}
					}
				}

				// get county average
				if (dblCountyHouseCount != 0 && dblCountyPoverty != 0)
				{
					dblCountyPercent = dblCountyPoverty / dblCountyHouseCount * 100;
				}
				// county count complete, print count			
				printf("%2s %-12s %s $%.1f\n", "", pudtCensusCodesList->strCountyCodes[intStateIndex][intCountyIndex], ":", dblCountyPercent);

				// add county totals to state counts
				dblStateHouseCount += dblCountyHouseCount;
				dblStatePoverty += dblCountyPoverty;
			}
		}

		// get State average
		if (dblStateHouseCount != 0 && dblStatePoverty != 0)
		{
			dblStatePercent = dblStatePoverty / dblStateHouseCount * 100;
		}
		// county count complete, print count			
		printf("%-15s : %.1f%s\n\n", pudtCensusCodesList->strStateCodes[intStateIndex], dblStatePercent, "%");

	};
	printf("\n------------------------------------------------------------------------------\n");
};



// --------------------------------------------------------------------------------
// Name: PercentageBelowPovertyByRace
// Abstract: Find the Percentage Below Poverty By RACE
// --------------------------------------------------------------------------------
void PercentageBelowPovertyByRace(udtCensusFields audtCensusForms[], udtCensusCodes* pudtCensusCodesList)	// accept all the forms of fields sent
{
	int intIndex = 0;
	int intRaceIndex = 0;

	float dblRaceHouseCount = 0.0;
	int intRaceSize = 0.0;
	int intRaceIncome = 0.0;
	float dblRacePoverty = 0.0;
	float dblRacePercent = 0.0;

	printf("\n\n");
	printf("I. Average House Income By Race: \n\n");

	for (intRaceIndex = 0; intRaceIndex < intRaces; intRaceIndex += 1)
	{
		if (*pudtCensusCodesList->strRaceCodes[intRaceIndex] != '\0')
		{
			// reset Count
			dblRaceHouseCount, dblRacePoverty, dblRacePercent = 0.0;
			intRaceSize, intRaceIncome = 0;

			// loop to find county count
			for (intIndex = 0; intIndex < intArraySize; intIndex += 1)	// loop through index of accepted forms
			{
				// is form completed?
				if (audtCensusForms[intIndex].blnCompleted)
				{
					// yes, does the form have the correct race?
					if (StringCompareSame(audtCensusForms[intIndex].strRace, pudtCensusCodesList->strRaceCodes[intRaceIndex]))
					{
						//increment house count
						dblRaceHouseCount += 1;

						// get size and income
						intRaceSize = audtCensusForms[intIndex].intHouseholdSize;
						intRaceIncome = audtCensusForms[intIndex].intHouseholdIncome;

						if (ValidatePoverty(intRaceSize, intRaceIncome))
						{
							//increment poverty count
							dblRacePoverty += 1;
						}
					}
				}
			}
			// get Race average
			if (dblRaceHouseCount != 0 && dblRacePoverty != 0)
			{
				dblRacePercent = dblRacePoverty / dblRaceHouseCount * 100;
			}
			// county count complete, print count			
			printf("%-18s : %.1f%s\n\n", pudtCensusCodesList->strRaceCodes[intRaceIndex], dblRacePercent, "%");
		}
	}
	printf("\n------------------------------------------------------------------------------\n");
};





// --------------------------------------------------------------------------------
// Name: ValidatePoverty
// Abstract: Determine if below poverty
//				house (1)  < $12000
//				house (2)  < $18000
//				house (3)  < $25000
//				house (4)  < $30000
//				house (5+) < $40000
// --------------------------------------------------------------------------------
booleen ValidatePoverty(int intSize, int intIncome)
{
	booleen blnValid = false;
	switch (intSize)
	{
		case 1:
			if (intIncome < 12000)
			{
				blnValid = true;
			}
			break;
		case 2:
			if (intIncome < 18000)
			{
				blnValid = true;
			}
			break;
		case 3:
			if (intIncome < 25000)
			{
				blnValid = true;
			}
			break;
		case 4:
			if (intIncome < 30000)
			{
				blnValid = true;
			}
			break;
		default:
			if (intIncome < 40000)
			{
				blnValid = true;
			}
	}
	return blnValid;
}

