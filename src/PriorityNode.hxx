#pragma once
class PriorityNode{
	public:
	int index;
	int priority;

	PriorityNode(int i, int p)
	{
		index = i;
		priority = p;
	}

};
bool operator<(const PriorityNode& lhs, const PriorityNode& rhs);
bool operator>(const PriorityNode& lhs, const PriorityNode& rhs);
