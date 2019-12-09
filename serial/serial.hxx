#pragma once
#include "common.hxx"
#include "Graph.hxx"
#include "serial_sssp.hxx"
#include <vector>

void serialAPSP
(
	const Graph& graph,
	std::vector<std::vector<int>>& dist_matrix,
	std::vector<std::vector<int>>& prev_matrix
);
