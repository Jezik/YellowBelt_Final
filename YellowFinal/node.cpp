#include "node.h"

// EmptyNode Evaluate() always return true
bool EmptyNode::Evaluate(const Date& date, const string& event) {
	return true;
}

// Implementation of DateComparisionNode
DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& date) : cmp_(cmp), date_(date) {};

bool DateComparisonNode::Evaluate(const Date& date, const string& event) {
	switch (cmp_) {
	case Comparison::Less:
		return date < date_;
	case Comparison::LessOrEqual:
		return date <= date_;
	case Comparison::Greater:
		return date > date_;
	case Comparison::GreaterOrEqual:
		return date >= date_;
	case Comparison::Equal:
		return date == date_;
	case Comparison::NotEqual:
		return date != date_;
	}	
}

// Implementation of EventComparisonNode
EventComparisonNode::EventComparisonNode(const Comparison& cmp, const string& event) : cmp_(cmp), event_(event) {};

bool EventComparisonNode::Evaluate(const Date& date, const string& event) {
	switch (cmp_) {
	case Comparison::Less:
		return event < event_;
	case Comparison::LessOrEqual:
		return event <= event_;
	case Comparison::Greater:
		return event > event_;
	case Comparison::GreaterOrEqual:
		return event >= event_;
	case Comparison::Equal:
		return event == event_;
	case Comparison::NotEqual:
		return event != event_;
	}
}

// Implementation of LogicalOperationNode
LogicalOperationNode::LogicalOperationNode(const LogicalOperation op, const shared_ptr<Node>& lhs_node, const shared_ptr<Node>& rhs_node)
	: op_(op), lhs_node_(lhs_node), rhs_node_(rhs_node) {};

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) {
	switch (op_) {
	case LogicalOperation::Or:
		return lhs_node_->Evaluate(date, event) || rhs_node_->Evaluate(date, event);
	case LogicalOperation::And:
		return lhs_node_->Evaluate(date, event) && rhs_node_->Evaluate(date, event);
	}
}