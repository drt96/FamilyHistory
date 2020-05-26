/***********************************************************************
 * Header:
 *    Week 13, Genealogy
 *    Brother Ercanbrack, CS 235
 * Author:
 *    Daniel Thomson
 * Summary:
 *    This is a class definition for an individual entry from
 *		genealogical record.
 ************************************************************************/

#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <iostream>
#include <string>

using namespace std;

class Individual
{
public:
	// Default constructor
	Individual()
	{
		this->id = "";
		this->firstName = "";
		this->lastName = "";
		this->dateOfBirth = "";
	}

	// Non-Default constructor
	Individual(const string & id,
		const string & firstName,
		const string & lastName,
		const string & dateOfBirth);

	// Destructor
	~Individual() {}

	// Display function
	const void display();

	// The insertion operator for the Individual class.
	friend ostream & operator << (ostream & out, const Individual & rhs);

	// Smaller than to operator
	bool operator < (const Individual & rhs) const;

	// Getters
	const string getID() { return id; }
	const string getFirstName() { return firstName; }
	const string getLastName() { return lastName; }
	const string getDateOfBirth() { return dateOfBirth; }

	// Setters
	void setID(const string & id) { this->id = id; }
	void setFirstName(const string & firstName) { this->firstName = firstName; }
	void setLastName(const string & lastName) { this->lastName = lastName; }
	void setDateOfBirth(const string & dateOfBirth) { this->dateOfBirth = dateOfBirth; }

private:
	string id;
	string firstName;
	string lastName;
	string dateOfBirth;
};

/***********************************************************
 * Insertion Operator
 * Display the data
 ************************************************************/
inline ostream & operator << (ostream & out, const Individual & rhs)
{
	if (!rhs.firstName.empty())
	{
		if (rhs.lastName.empty())
		{
			out << rhs.firstName;
		}
		else
		{
			out << rhs.firstName << " ";
		}
	}

	if (!rhs.lastName.empty())
	{
		out << rhs.lastName;
	}

	if (!rhs.dateOfBirth.empty())
	{
		out << ", b. " << rhs.dateOfBirth;
	}

	out << endl;

	return out;
}

/***********************************************************
 * smaller than Operator
 * Get individual sort significance
 ************************************************************/
inline bool Individual :: operator < (const Individual & rhs) const
{
	// temp variables
	string firstNameLHS, firstNameRHS, lastNameLHS, lastNameRHS, yearLHS, yearRHS;

	firstNameLHS = this->firstName;
	lastNameLHS = this->lastName;
	firstNameRHS = rhs.firstName;
	lastNameRHS = rhs.lastName;

	if (this->dateOfBirth.size() == 4)
	{
		yearLHS = this->dateOfBirth;
	}
	else if (!(this->dateOfBirth.empty()))
	{
		yearLHS = this->dateOfBirth.substr((this->dateOfBirth.length() - 4), 4);
	}

	if (rhs.dateOfBirth.size() == 4)
	{
		yearRHS = rhs.dateOfBirth;
	}
	else if (!(rhs.dateOfBirth.empty()))
	{
		yearRHS = rhs.dateOfBirth.substr((rhs.dateOfBirth.length() - 4), 4);
	}

	// Handles the finicky cases
	if (islower(this->firstName[0]) || islower(this->lastName[0])
		|| islower(rhs.firstName[0]) || islower(rhs.lastName[0]))
	{
		firstNameLHS[0] = toupper(this->firstName[0]);
		firstNameRHS[0] = toupper(rhs.firstName[0]);
		lastNameLHS[0] = toupper(this->lastName[0]);
		lastNameRHS[0] = toupper(rhs.lastName[0]);
	}

	if (lastNameLHS < lastNameRHS)
	{
		return true;
	}
	else if (lastNameLHS == lastNameRHS &&
		firstNameLHS < firstNameRHS)
	{
		return true;
	}
	else if (lastNameLHS == lastNameRHS &&
		firstNameLHS == firstNameRHS &&
		yearLHS < yearRHS)
	{
		return true;
	}

	return false;
}
#endif // INDIVIDUAL_H