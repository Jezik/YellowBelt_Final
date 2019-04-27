#pragma once
#include "date.h"

#include <string>
#include <memory>

using namespace std;

enum Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual
};

enum LogicalOperation {
	And,
	Or
};

class Node {
public:
	virtual bool Evaluate(const Date& date, const string& event) const = 0;
};

class EmptyNode : public Node {
public:
	bool Evaluate(const Date& date, const string& event) const override;
};

class DateComparisonNode : public Node {
public:
	DateComparisonNode(const Comparison& cmp, const Date& date) : cmp_(cmp), date_(date) {};
	bool Evaluate(const Date& date, const string& event) const override;

private:	
	const Comparison cmp_;
	const Date date_;
};

class EventComparisonNode : public Node {
public:
	EventComparisonNode(const Comparison& cmp, const string& event) : cmp_(cmp), event_(event) {};
	bool Evaluate(const Date& date, const string& event) const override;

private:
	const Comparison cmp_;
	const string event_;
};

class LogicalOperationNode : public Node {
public:
	LogicalOperationNode(const LogicalOperation op, const shared_ptr<Node>& lhs_node, const shared_ptr<Node>& rhs_node)
		: op_(op), lhs_node_(lhs_node), rhs_node_(rhs_node_) {};

	bool Evaluate(const Date& date, const string& event) const override;

private:
	const LogicalOperation op_;
	const shared_ptr<Node> lhs_node_;
	const shared_ptr<Node> rhs_node_;
};
