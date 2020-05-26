/***********************************************************************
 * Implementation:
 *    Week 13, Genealogy
 *    Brother Ercanbrack, CS 235
 * Author:
 *    Daniel Thomson
 * Summary:
 *    This is a class definition for an individual entry from
 *		genealogical record.
 ************************************************************************/

#include "individual.h"

 /***********************************************************
  * Non Default Constructor
  * Assign the variables
  ************************************************************/
Individual::Individual(const string & id,
	const string & firstName,
	const string & lastName,
	const string & dateOfBirth)
{
	this->id = id;
	this->firstName = firstName;
	this->lastName = lastName;
	this->dateOfBirth = dateOfBirth;
}

/***********************************************************
 * DISPLAY
 * Print the data
 ************************************************************/
const void Individual :: display()
{
	if (!this->firstName.empty())
	{
		if (this->lastName.empty())
		{
			cout << this->firstName;
		}
		else
		{
			cout << this->firstName << " ";
		}
	}

	if (!this->lastName.empty())
	{
		cout << this->lastName;
	}
	if (!this->dateOfBirth.empty())
	{
		cout << ", b. " << this->dateOfBirth;
	}
	cout << endl;
}