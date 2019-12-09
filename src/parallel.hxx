#pragma once
#include "Graph.hxx"
#include "common.hxx"
#include <vector>

void parallelAPSP
(
	const Graph& graph,
	std::vector<std::vector<int>>& dist_matrix,
	std::vector<std::vector<int>>& prev_matrix,
	int num_of_threads
);
