#include "serial.hxx"
#include <cassert>

void serialAPSP
(
	const Graph& graph,
	std::vector<std::vector<int>>& dist_matrix,
	std::vector<std::vector<int>>& prev_matrix
)
{
	// matrices should be all allocated already and shit
	// We're not here to time how long allocation takes
	assert(dist_matrix.size() == (size_t)graph.get_number_of_nodes());
	assert(dist_matrix[0].size() == (size_t)graph.get_number_of_nodes());
	assert(prev_matrix.size() == (size_t)graph.get_number_of_nodes());
	assert(prev_matrix[0].size() == (size_t)graph.get_number_of_nodes());

	for(int i=0;i<graph.get_number_of_nodes();i++)
	{
		serialSSSP(graph, i, dist_matrix[i], prev_matrix[i]);
	}
}
