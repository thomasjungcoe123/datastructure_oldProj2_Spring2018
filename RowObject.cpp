using namespace std;

#include <iostream>
#include "RowObject.h"

// static value of RowObject for default initialization
const int ROWOBJECT_CLASS_DEFAULT_SIZE = 100;

// default constructor

// helper function for copy by reference (deep copy)
void stringcopy(char* dest, const char* src){
    int length = 0;

    while(src[length] != '\0'){
        length++;
    }
    dest = new char[length+1];
    int i=0;
    while(src[i] != '\0'){
        dest[i] = src[i];
		i++;
    }
    dest[length] = '\0';
}

RowObject::RowObject()
{
    //Data from Leading Causes of Death in the USAprotected:
    ID = 1;
    year = 2000;
    numberOfDeaths = 1566;
    averageAge = 44.9;

    causeName = new char[ROWOBJECT_CLASS_DEFAULT_SIZE];
//	if (causeName == NULL) throw ArrayMemoryException();
	//causeName = "Unitentional Injuries";
	stringcopy(this->causeName, "Unintentional Injuries");

    State = new char[ROWOBJECT_CLASS_DEFAULT_SIZE];
//	if (State == NULL) throw ArrayMemoryException();
	//State = "Oklahoma";
	stringcopy(this->State, "Oklahoma");
}

// constructor
RowObject::RowObject(int rid, int y, const char* cn, const char* s, int n, float age)
{
    ID = rid;
    year = y;

    //causeName = new char[cn];
    causeName = new char[ROWOBJECT_CLASS_DEFAULT_SIZE];
	State = new char[ROWOBJECT_CLASS_DEFAULT_SIZE];

	stringcopy(this->causeName, cn);
	stringcopy(this->State, s);

	//	if (causeName == NULL) throw ArrayMemoryException();
//    int i = 0;
 //   while (cn[i] != '\0')
  //  {
   //     causeName[i] = cn[i];
    //    i++;
    //}
//    causeName[i] = '\0';

//	if (State == NULL) throw ArrayMemoryException();
 //   i = 0;
  //  while (s[i] != '\0')
   // {
    //    State[i] = s[i];
     //   i++;
   // }
    //State[i] = '\0';

    numberOfDeaths = n;
    averageAge = age;
}

// copy constructor
RowObject::RowObject(const RowObject& _ro)
{
    if (&_ro != this) // disallow copying the obj onto itself
        copy(_ro);
}

// protected method copy() to do the actual copying to make the copy constructor much simpler
void RowObject::copy(const RowObject& _ro)
{

    (*this).ID = _ro.ID;
    (*this).year = _ro.year;
	// right now it's copy by value??
	//(*this).causeName = _ro.causeName;
	//(*this).State = _ro.State;
	// need copy by ref?
	stringcopy(this->causeName, _ro.causeName);
    stringcopy(this->State, _ro.State);
    (*this).numberOfDeaths = _ro.numberOfDeaths;
    (*this).averageAge = _ro.averageAge;
}

void RowObject::display()
{
    cout << ID << ',' << year << ',' << causeName << ',' << State << ',' << numberOfDeaths << ',' << averageAge << endl;
}

//write the overloaded = operator for an extra 10 points
RowObject& RowObject::operator=(const RowObject& _ro)
{
    //RowObject rowObject;
	//rowObject.copy(_ro);
	(*this).copy(_ro);
	return *this;
}

//write the destructor
RowObject::~RowObject()
{
    // deleting one pointer is enough for this class??

    if (causeName != NULL)
    {
        delete[] causeName;
    }
    // delete the field too? <--- not sure yet
    //		delete causeName;

    if (State != NULL)
    {
        delete[] State;
    }
    //		delete State;
}

//get the ith row
RowObject& RowObject::operator[] (int i)                    { return (*this)[i];                       }
int RowObject::getID()						                { return ID;                               }
int RowObject::getYear()					                { return year;                             }
char* RowObject::getCauseName()				                { return causeName;                        }
char* RowObject::getState()					                { return State;                            }
int RowObject::getNumberOfDeaths()			   			    { return numberOfDeaths;                   }
float RowObject::getAverageAge()							{ return averageAge;                       }
void RowObject::setID(int _ID)								{ this->ID = _ID;                          }
void RowObject::setYear(int _year)							{ this->year = _year;                      }
void RowObject::setCauseName(char* _causeName){
    int i=0;
    do{
        this->causeName[i] = _causeName[i];
        i++;
    }while (_causeName[i] != '\0');
    this->causeName[i] = '\0';
}
void RowObject::setState(char* _State){
    int i=0;
    do{
        this->State[i] = _State[i];
        i++;
    }while (_State[i] != '\0');
    this->State[i] = '\0';
}
void RowObject::setNumberOfDeaths(int _numberOfDeaths)		{ this->numberOfDeaths = _numberOfDeaths;  }
void RowObject::setAverageAge(float _averageAge)			{ this->averageAge = _averageAge;          }
