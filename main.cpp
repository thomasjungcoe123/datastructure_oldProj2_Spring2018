using namespace std;

#include <iostream>
#include "DataFrame.h"
#include "RowObject.h"


char* strEmpty(char* toBeEmptied)
{
	int i = 0;
	while (i<100)
	{
		toBeEmptied[i] = '\0';
		i++;
	}
	return toBeEmptied;
}

// i want to build a function for the reading process in the future as the project
// develops or before working on proj2
void headerProcess(DataFrame<RowObject> *DBT_ref)
{
	char* tempChar1 = new char[100];
	char* tempChar2 = new char[100];
	// indicator for length of character
	int charLength = 0;
	// counter
	int token = 0;
	// used for cutting the line of characters into a string of words
	int wordCutter = 0;
	int fieldCounter = 0;

	strEmpty(tempChar2);

	// read first line and store it inside tempChar1
	fgets(tempChar1, 1024, stdin);
	fgets(tempChar1, 1024, stdin);
	//cin >> tempChar1;

	// while tempChar1 has values inside started at index of 0
	while (tempChar1[charLength] != '\0')
	{
		// increment charLength by one each operation of this while loop
		charLength++;
		// stop reading at the instance of reading the new line
		if (tempChar1[charLength] == '\n')
			break;
	}

	// since now i have the length counted for c++
	// i will use it to iterate through tempChar1
	for (int i = 0; i <= charLength; i++)
	{
		// looking for ',' while going thru each keys
		if (tempChar1[i] == ',')
		{
			// storing new line
			tempChar2[wordCutter] = '\0';
			// storing a word/value cut from the line of characters from input file
			// into the proper param
			(*DBT_ref).setColName(token, tempChar2);

			strEmpty(tempChar2);

			// increment the counter
			token++;
			// reset the wordCutter
			wordCutter = 0;
		}
		// in case of reaching the end of the line of characters that were read
		else if (i == charLength)
		{
			// set it to nothing
			// reset it all
			tempChar2[wordCutter] = '\0';
			(*DBT_ref).setColName(token, tempChar2);

			token = 0;
			wordCutter = 0;
		}
		else
		{
			// strcpy into the second char array.
			tempChar2[wordCutter] = tempChar1[i];
			// increment the key
			wordCutter++;
		}
	}

	delete[] tempChar1;
	delete[] tempChar2;
}

void dataProcess(DataFrame<RowObject> *DBT_ref, RowObject *ro_ref, int position)
{
	char* tempChar1 = new char[100];
	char* tempChar2 = new char[100];
	// indicator for length of character
	int charLength = 0;
	// counter
	int token = 0;
	// used for cutting the line of characters into a string of words
	int wordCutter = 0;
	int fieldCounter = 0;

	strEmpty(tempChar2);

	// read first line and store it inside tempChar1
	fgets(tempChar1, 1024, stdin);



	// while tempChar1 has values inside started at index of 0
	while (tempChar1[charLength] != '\0')
	{
		// increment charLength by one each operation of this while loop
		charLength++;
		// stop reading at the instance of reading the new line
		if (tempChar1[charLength] == '\n')
			break;
	}

	// since now i have the length counted for c++
	// i will use it to iterate through tempChar1
	ro_ref->setID(position);
	for (int i = 0; i <= charLength; i++)
	{


		// looking for ',' while going thru each keys
		if (tempChar1[i] == ',')
		{
			// storing new line
			tempChar2[wordCutter] = '\0';
			// storing a word/value cut from the line of characters from input file
			// into the proper param

			if (fieldCounter == 0)
			{
				int tempIntYear = atoi(tempChar2);
				(*ro_ref).setYear(tempIntYear);
				fieldCounter++;
			}
			else if (fieldCounter == 1)
			{
				(*ro_ref).setCauseName(tempChar2);
				fieldCounter++;
			}
			else if (fieldCounter == 2)
			{
				(*ro_ref).setState(tempChar2);
				fieldCounter++;
			}
			else
			{
				int tempIntNumberOfDeaths = atoi(tempChar2);
				(*ro_ref).setNumberOfDeaths(tempIntNumberOfDeaths);
				fieldCounter++;
			}

			strEmpty(tempChar2);

			// increment the counter
			token++;
			// reset the wordCutter
			wordCutter = 0;

			if (fieldCounter == 4)
			{
				fieldCounter == 0;
			}

		}
		// in case of reaching the end of the line of characters that were read
		else if (i == charLength)
		{
			// set it to nothing
			// reset it all
			tempChar2[wordCutter] = '\0';
			float tempIntAverageAge = atof(tempChar2);
			(*ro_ref).setAverageAge(tempIntAverageAge);
			token = 0;
			wordCutter = 0;
		}
		else
		{
			// strcpy into the second char array.
			tempChar2[wordCutter] = tempChar1[i];
			// increment the key
			wordCutter++;
		}
	}

	(*DBT_ref).insertRow(position, *ro_ref);

	delete[] tempChar1;
	delete[] tempChar2;
}

int main()
{
	int noRows;

	//read the number of rows that needs to be read
	DataFrame<RowObject>* DBT;
	//freopen("input.txt", "r", stdin);

	int selectR[10];

	for (int i = 0; i < 10; i++)
	{
		// 0 -> 2;  1 -> 3; 2 -> 4; ... ++
		selectR[i] = i + 2;
	}

	// Read the dataframe from input
	// First line: A single number indicating the number of rows to be read (not including the header);
	// In this case there are 5 columns (plus ID, see below)
	cin >> noRows;
	DBT = new DataFrame<RowObject>(noRows, 5);
	
	for (int i = 0; i < (18); i++)
	{
		if (i > 0)
		{
			RowObject* roTemp = new RowObject();
			dataProcess(DBT, roTemp, i);
		}
		else
		{
			headerProcess(DBT);
		}
	}

	// Execute the following code
	// Change the column names of selected columns
	(*DBT).setColName(4, "Number Deaths");
	(*DBT).setColName(2, "Cause Name");

	cout << (*DBT);
	cout << endl;

	// Extract the rows in SelectR

	DataFrame<RowObject>* tempRows = (*DBT).getRows(selectR, 10);
	(*tempRows).display();

	// Code to test other methods

	// Testing [] operator on DataFrame object and ostream on RowObject

	cout << (*DBT)[4];
	cout << (*DBT)[5];
	cout << (*DBT)[10];

	// Testing addRow, constructor for RowObject and getNumberRows method
	RowObject* newRow;
	newRow = new RowObject((*DBT).getNumberRows(), 2018, "Cancer", "Oklahoma", 200, 58.2);
	(*DBT).addRow(*newRow);

	// Testing destructor for RowObject
	newRow = new RowObject((*DBT).getNumberRows(), 2018, "Opiod", "Texas", 2000, 32.4);
	(*DBT).addRow(*newRow);

	delete newRow;

	cout << (*DBT)[(*DBT).getNumberRows() - 2];
	cout << (*DBT)[(*DBT).getNumberRows() - 1];

	// Testing insertRow
	newRow = new RowObject((*DBT).getNumberRows(), 2016, "Cancer", "Texas", 500, 72.1);
	(*DBT).insertRow(1, *newRow);

	delete newRow;

	newRow = new RowObject((*DBT).getNumberRows(), 2016, "Stroke", "Oklahoma", 400, 68.1);
	(*DBT).insertRow(4, *newRow);

	delete newRow;
	(*DBT).display(10);

	// Testing removeRow
	(*DBT).removeRow(1);
	(*DBT).removeRow(3);
	(*DBT).display(10);

	// Extra Points 10 points for overloaded = operator for RowObject - uncomment to test

	/* newRow = new RowObject((*DBT).getNumberRows(),2016,"Stroke","Arizona",400, 68.1);
	RowObject anotherOne;
	anotherOne = *newRow;
	cout << anotherOne;
	delete newRow;
	*/

	// Extra Points 10 points for overloaded = operator for DataFrame - uncomment to test

	/* DataFrame<RowObject> newDF;
	newDF = (*DBT);
	newDF.display(10);
	*/

	delete DBT;
}
