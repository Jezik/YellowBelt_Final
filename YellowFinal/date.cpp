#include "date.h"

#include <iomanip>

// Constructor
Date::Date(const int& year, const int& month, const int& day) : year_(year), month_(month), day_(day) {};

// Getters
int Date::GetYear() const {
	return year_;
}

int Date::GetMonth() const {
	return month_;
}

int Date::GetDay() const {
	return day_;
}

// Creating Date object from an input stream
Date ParseDate(istream& input) {
	int year, month, day;
	input >> year;
	input.ignore(1);
	input >> month;
	input.ignore(1);
	input >> day;

	return Date(year, month, day);
}

// Operator < to use Date as a key in map
bool operator< (const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() != rhs.GetYear()) {
		return lhs.GetYear() < rhs.GetYear();
	}
	else if (lhs.GetMonth() != rhs.GetMonth()) {
		return lhs.GetMonth() < rhs.GetMonth();
	}
	else if (lhs.GetDay() != rhs.GetDay()) {
		return lhs.GetDay() < rhs.GetDay();
	}

	return false;
}

// Operator << to give Date object to output stream
ostream& operator<< (ostream& stream, const Date& date) {
	stream << setfill('0') << setw(4) << date.GetYear()
		<< '-' << setfill('0') << setw(2) << date.GetMonth()
		<< '-' << setfill('0') << setw(2) << date.GetDay() << " ";
}