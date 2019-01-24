using namespace std;

#include <iostream>
#include "RowObject.h"

template <class DT> class DataFrame
{
	static const int DATAFRAME_CLASS_DEFAULT_SIZE = 100;

protected:
	// array of pointers to	DT object
	DT * * dataRows;
	char** colNames;
	int noRows, noCols;

public:
	DataFrame();
	DataFrame(int numberOfRows, int numberOfColumns);
	DataFrame(const DataFrame<DT>& obj);
	void copy(const DataFrame<DT>& obj);

	void display();
	void display(int n); // display the first n records

	void setColName(int col, const char* name);
	DT& operator[] (int i); //get the ith row
	char** getColNames();
	int getNumberRows();
	DataFrame<DT>* getRows(int* rows, int rLen);

	void addRow(DT& newRow); // add a new row at the last row

	void removeRow(int i); //remove the ith row
	void insertRow(int position, DT& newRow);
	virtual ~DataFrame();

	void stringcopy(char* dest, const char* src);

	//write the ostream operator
	friend ostream& operator<< (ostream& s, DataFrame<DT>& obj)
	{
		for (int i = 0; i < obj.noRows; i++)
		{
			if (i == 0)
			{
				for (int j = 0; j < obj.noCols; j++)
				{
					if (j < (obj.noCols - 1))
					{
						s << obj.getColNames()[j];
						s << ",";
					}
					else
					{
						s << obj.getColNames()[j];
						s << endl;
					}
				}
			}
			s << obj[i] << endl;
		}
		return s;
	}

	//write the = operator for an extra 10 points
	DataFrame<DT>& operator=(const DataFrame<DT>& obj);
};

template <class DT>
void DataFrame<DT>::stringcopy(char* dest, const char* src) 
{
	int length = 0;
	while (src[length] != '\0') 
	{
		length++;
	}
	dest = new char[length + 1];
	
	int i = 0;
	while (src[i] != '\0') 
	{
		i++;
		dest[i] = src[i];
	}
	dest[length] = '\0';
}

// default const
template <class DT>
DataFrame<DT>::DataFrame()
{
	noRows = 0;
	noCols = 0;

	colNames = new char*[DATAFRAME_CLASS_DEFAULT_SIZE];
	//	if (colNames == NULL) throw ArrayMemoryException();

	dataRows = new DT*[DATAFRAME_CLASS_DEFAULT_SIZE];
	//	if (dataRows == NULL) throw ArrayMemoryException();
}

// constructor
template <class DT>
DataFrame<DT>::DataFrame(int numberOfRows, int numberOfColumns)
{
	noRows = numberOfRows;
	noCols = numberOfColumns;

	dataRows = new DT*[noRows+1];
	colNames = new char*[noCols];

	// row being a key for iterating through rows
	for (int row = 0; row < (noRows+1); row++)
	{
		// created new int array of number of columns and stored in each index of table.
		// just the spaces for its internal data
		//dataRows[row] = NULL;

		dataRows[row] = new DT[numberOfColumns];

	}

	for (int col = 0; col < noCols; col++)
	{
		colNames[col] = new char[DATAFRAME_CLASS_DEFAULT_SIZE];

		for (int value = 0; value < 100; value++)
		{
			colNames[col][value] = '\0';
		}
	}
}

template <class DT>
DataFrame<DT>::DataFrame(const DataFrame<DT>& obj)
{
	if (&obj != this) // disallow copying the obj on to itself
		copy(obj);
}

// protected method copy() to do the actual copying to make the copy constructor much simpler
template <class DT>
void DataFrame<DT>::copy(const DataFrame<DT>& obj)
{
	this->noRows = obj.noRows;
	this->noCols = obj.noCols;
	//Initialize the array
	this->dataRows = new DT*[noRows];
	//Deep copy each row
	//Have to make sure that = operator of the
	//Row Object also deep copies
	for (int i = 0; i<noRows; i++) {
		this->dataRows[i] = obj.dataRows[i];
	}

	for (int i = 0; i<noCols; i++) {
		stringcopy((this->colNames)[i], obj.colNames[i]);
	}


}

template <class DT>
void DataFrame<DT>::display()
{
	// TODO --- copied from proj1

	// for printing columns names
	for (int col = 0; col < noCols; col++)
	{
		// if col reaches the end, new lines is printed
		// else , is printed in between names of the columns
		if ((col + 1) == noCols)
		{
			std::cout << colNames[col] << "\n";
		}
		else
		{
			std::cout << colNames[col] << ",";
		}
	}
}

template <class DT>
void DataFrame<DT>::display(int n)
{
	// TODO -- not yet

	// ostream <--?? (ostream& s) <--- instead of int n??????
}

// display the first n records
template <class DT>
void DataFrame<DT>::setColName(int col, const char* name)
{
	int value = 0;
	while ((*this).colNames[col][value] != '\0')
	{
		(*this).colNames[col][value] = '\0';
		value++;
	}

	value = 0;
	while (name[value] != '\0')
	{
		(*this).colNames[col][value] = name[value];
		value++;
	}

	//	colNames[col] = strdup(name);
}

template <class DT>
DT& DataFrame<DT>::operator[] (int i)
{
	//	if ((i < 0) || (i >= noRows)) throw ArrayBoundsException();
	//return *dataRows[i];
	return *(dataRows[i]);
}

// returns the protected member of DF
template <class DT>
char** DataFrame<DT>::getColNames() { return colNames; };

// returns the protected member of DF
template <class DT>
int DataFrame<DT>::getNumberRows() { return noRows; };

template <class DT>
DataFrame<DT>* DataFrame<DT>::getRows(int* rows, int rLen)
{
	// same process as getColumns but this time for getRows for pointer obj accessing rows that the user wants
	DataFrame<DT>* df = new DataFrame(rLen, noCols);

	// same as above or very similiar steps taken
	for (int row = 0; row < (*df).noRows; row++)
	{
		// TODO fix this method...
		// setting created obj's row names with original data using rows (passed param from this method) and row as key
		//(*df).setRowName(row, (*this).rowNames[rows[row]]);

	}

	// same as above or very similiar steps taken
	for (int col = 0; col < (*df).noCols; col++)
	{
		(*df).setColName(col, (*this).colNames[col]);
	}

	// returns the created obj
	return df;
}

// add a new row at the last row
template <class DT>
void DataFrame<DT>::removeRow(int i)
{
	if ((i < 0) || (i >= noRows))
	{
		//		throw ArrayBoundsException();
	}
	for (int row = i; row < noRows - 1; row++)
	{
		(*this)[row] = (*this)[row + 1];
	}
	noRows--;
}

template <class DT>
void DataFrame<DT>::addRow(DT& newRow)
{
	insertRow(noRows, newRow);
}

//remove the ith row
template <class DT>
void DataFrame<DT>::insertRow(int position, DT& newRow)
{

	/*for (int i = noRows - 1; i > position; i--)
	{
	(*this)[i] = (*this)[i - 1];
	}
	(*this)[position] = newRow;*/
	//*((this->dataRows)[position]) = newRow;
	*((*this).dataRows[position]) = newRow;
	//*(this->dataRows[position]) = newRow;
}

// overloaded operator= for this class of type DataType
template <class DT>
DataFrame<DT>& DataFrame<DT>::operator=(const DataFrame<DT>& obj)
{
	//DataFrame dataFrame;
	//dataFrame.copy(obj);
	//*this = dataFrame;
	(*this).copy(obj);
	return *this;
}

template <class DT>
DataFrame<DT>::~DataFrame()
{
	// TODO: nearly copied from porj1

	if (dataRows != NULL)
	{
		// iterating through number of rows
		for (int row = 0; row < noRows; row++)
		{
			// delete the values stored using row as key
			delete[] dataRows[row];
		}
		// deleting the table itself after deleting the values inside the array
	}
	if (colNames != NULL)
	{
		for (int col = 0; col < noCols; col++)
		{
			delete[] colNames[col];
		}
	}
	delete[] dataRows;
	delete[] colNames;
}
