#pragma once
#include "Graph.hxx"
#include "common.hxx"
#include <vector>

void serialSSSP
(
	const Graph& graph,
	int source,
	std::vector<int>& dist,
	std::vector<int>& prev
);

void serialAPSP
(
	const Graph& graph,
	std::vector<std::vector<int>>& dist_matrix,
	std::vector<std::vector<int>>& prev_matrix
);
