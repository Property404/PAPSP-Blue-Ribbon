#pragma once
#include "common.hxx"
#include "Graph.hxx"
#include <vector>

void serialSSSP
(
	const Graph& graph,
	int source,
	std::vector<int>& dist,
	std::vector<int>& prev
);
