#include "database.h"

#include <algorithm>

void Database::Add(const Date& date, const string& event) {
	if (mapDBevents_.count(date) > 0) {
		if (find(begin(mapDBevents_[date]), end(mapDBevents_[date]), event) == mapDBevents_[date].end()) {
			mapDBevents_[date].push_back(event);
		}
	}
	else {
		mapDBevents_[date].push_back(event);
	}
}

void Database::Print(ostream& stream) const {
	for (const auto& entry : mapDBevents_) {
		for (const string& event : entry.second) {
			stream << entry.first << event << endl;
		}
	}
}

vector<pair<Date, string>> Database::FindIf(const function<bool(const Date&, const string&)> predicate) const {
	vector<pair<Date, string>> result;

	for (const auto& entry : mapDBevents_) {
		for (const string& event : entry.second) {
			if (predicate(entry.first, event)) {
				result.push_back(make_pair(entry.first, event));
			}
		}
	}

	return result;
}

int Database::RemoveIf(const function<bool(const Date&, const string&)> predicate) {
	int counter = 0;

	for (auto date_it = mapDBevents_.begin(); date_it != mapDBevents_.end();) {
		for (auto event_it = (*date_it).second.begin(); event_it != (*date_it).second.end(); ) {
			if (predicate((*date_it).first, *event_it)) {
				auto it = mapDBevents_[(*date_it).first].erase(event_it);
				counter++;
				event_it = it;
			}
			else {
				event_it++;
			}
		}
		if ((*date_it).second.size() == 0) {
			auto it = mapDBevents_.erase(date_it);
			date_it = it;
		}
		else {
			date_it++;
		}
	}

	return counter;
}

string Database::Last(const Date& date) const {
	auto it = mapDBevents_.upper_bound(date);

	if (it != mapDBevents_.begin()) {
		return (*prev(it)).first.ToString() + " " + (*prev(it)).second.back();
	}
	else {
		return "No entries";
	}
}

ostream& operator<< (ostream& stream, const pair<Date, string>& p) {
	stream << p.first << p.second;

	return stream;
}