#ifndef _ROWOBJECT_H
#define _ROWOBJECT_H

using namespace std;

class RowObject
{

	//Data from Leading Causes of Death in the USA
protected:
	int ID;
	int year;
	char* causeName;
	char* State;
	int numberOfDeaths;
	float averageAge;

public:
	RowObject();
	RowObject(int rid, int y, const char* cn, const char* s, int n, float age);
	RowObject(const RowObject& ro);
	//void operator=(const RowObject& ro);	//write the overloaded = operator for an extra 10 points
	void copy(const RowObject& ro);
	void display(); 	// display function for ostream operator
	~RowObject();	//write the destructor

	RowObject& operator=(const RowObject& ro);
	RowObject& operator[] (int i);

	//write the ostream operator
	friend ostream& operator<<(ostream& os, const RowObject& ro)
	{
		os << ro.ID << "," << ro.year << ",";
		
		int length = 0;
		while (ro.causeName[length] != '\0') {
			os << (ro.causeName)[length++];
		}
		os << ",";

		length = 0;
		while ((ro.State)[length] != '\0')
		{
			os << (ro.State)[length];
		}
		os << "," << ro.numberOfDeaths << "," << ro.averageAge;

		//os << ro.ID << "," << ro.year << "," << *(ro.causeName) << "," << *(ro.State) << "," << ro.numberOfDeaths << "," << ro.averageAge;
		return os;
	}

	int getID();
	int getYear();
	char* getCauseName();
	char* getState();
	int getNumberOfDeaths();
	float getAverageAge();

	void setID(int _ID);
	void setYear(int _year);
	void setCauseName(char* _causeName);
	void setState(char* _State);
	void setNumberOfDeaths(int _numberOfDeaths);
	void setAverageAge(float averageAge);
};

#endif