#include "PriorityNode.hxx"
bool operator<(const PriorityNode& lhs, const PriorityNode& rhs)
{
	if(lhs.priority < rhs.priority)
	{
		return true;
	}
	return false;
}

bool operator>(const PriorityNode& lhs, const PriorityNode& rhs)
{
	if(lhs.priority > rhs.priority)
	{
		return true;
	}
	return false;
}
