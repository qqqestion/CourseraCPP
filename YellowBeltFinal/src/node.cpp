#include "node.h"

bool EmptyNode::Evaluate (const Date& date, const string& event) const {
    return true;
}

DateComparisonNode::DateComparisonNode(Comparison cmp, const Date& date) : cmp_(cmp), date_(date) {}

bool DateComparisonNode::Evaluate (const Date& date, const string& event) const {
    switch (cmp_){
        case Comparison::Less :
            return date < date_;
        case Comparison::LessOrEqual :
            return date <= date_;
        case Comparison::Greater :
            return date > date_;
        case Comparison::GreaterOrEqual :
            return date >= date_;
        case Comparison::Equal :
            return date == date_;
        case Comparison::NotEqual :
            return date != date_;
    }
}

EventComparisonNode::EventComparisonNode(Comparison cmp, const string& event) : cmp_(cmp), event_(event){}

bool EventComparisonNode::Evaluate (const Date& date, const string& event) const {
    switch (cmp_){
        case Comparison::Less :
            return event < event_;
        case Comparison::LessOrEqual :
            return event <= event_;
        case Comparison::Greater :
            return event > event_;
        case Comparison::GreaterOrEqual :
            return event >= event_;
        case Comparison::Equal :
            return event == event_;
        case Comparison::NotEqual :
            return event != event_;
    }
}

LogicalOperationNode::LogicalOperationNode (LogicalOperation logicalOperation, shared_ptr<const Node> left, shared_ptr<const Node> right) :
    logicalOperation_(logicalOperation), left_(left), right_(right){}

bool LogicalOperationNode::Evaluate (const Date& date, const string& event) const {
    switch (logicalOperation_){
        case LogicalOperation::And:
            return left_->Evaluate(date, event) && right_->Evaluate(date, event);
        case LogicalOperation::Or:
            return left_->Evaluate(date, event) || right_->Evaluate(date, event);
    }
}
