#pragma once

#include <string>

using namespace std;

class Date {
public:
	Date(const int& year, const int& month, const int& day);

	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
	
	string ToString() const;

private:
	const int year_;
	const int month_;
	const int day_;
};

Date ParseDate(istream& stream);

bool operator< (const Date& lhs, const Date& rhs);
bool operator<= (const Date& lhs, const Date& rhs);
bool operator> (const Date& lhs, const Date& rhs);
bool operator>= (const Date& lhs, const Date& rhs);
bool operator== (const Date& lhs, const Date& rhs);
bool operator!= (const Date& lhs, const Date& rhs);

ostream& operator<< (ostream& stream, const Date& date);