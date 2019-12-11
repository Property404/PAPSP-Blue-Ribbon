#pragma once
#include "Graph.hxx"
#include "common.hxx"
#include <vector>

void parallelAPSP
(
	const Graph& graph,
	std::vector<std::vector<int>>& dist_matrix,
	std::vector<std::vector<int>>& prev_matrix,
	int num_threads,
	// If this is -1, use the overflow from num_threads
	int num_sub_threads = -1
);

void parallelSSSP
(
	const Graph& graph,
	int source,
	std::vector<int>& dist,
	std::vector<int>& prev,
	int num_threads
);
