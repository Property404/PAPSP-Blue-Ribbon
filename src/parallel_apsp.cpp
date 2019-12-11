#include "parallel.hxx"
#include "serial.hxx"
#include <cassert>
#include <iostream>
#include <algorithm>
#include <omp.h>

void parallelAPSP
(
	const Graph& graph,
	std::vector<std::vector<int>>& dist_matrix,
	std::vector<std::vector<int>>& prev_matrix,
	int num_threads,
	// If this is -1, use the overflow from num_threads
	int num_subthreads
)
{
	const auto num_nodes = graph.get_number_of_nodes();
	const int num_top_level_threads = std::min(num_threads, num_nodes);
#ifdef DEBUG
	std::cout<<"APSP-Threads: "<<num_threads<<"("<<num_subthreads<<")"<<std::endl;
	std::cout<<"Top-level thds:"<<num_top_level_threads<<std::endl;
#endif


	// matrices should be all allocated already and shit
	// We're not here to time how long allocation takes
	assert(dist_matrix.size() == (size_t)graph.get_number_of_nodes());
	assert(dist_matrix[0].size() == (size_t)graph.get_number_of_nodes());
	assert(prev_matrix.size() == (size_t)graph.get_number_of_nodes());
	assert(prev_matrix[0].size() == (size_t)graph.get_number_of_nodes());

	// If there's any kind of overflow, num_subthreads should be -1
	// so we can dictate what threads go where.
	assert(!(num_subthreads!=-1 && num_threads>graph.get_number_of_nodes()));

#pragma omp parallel for num_threads(num_top_level_threads)
	for(int i=0;i<graph.get_number_of_nodes();i++)
	{
		assert(omp_get_num_threads() == num_top_level_threads);
#if 0
		serialSSSP(graph, i, dist_matrix[i], prev_matrix[i]);
#else
		
		int local_num_subthreads = num_subthreads;

		// Calculate local number of subthreads based on num_threads' overflow
		if(num_subthreads == -1)
		{

			// Consider 4 nodes:
			//
			// 								0 1 2 3
			// 								-------
			// 		1 thread: 1 1 1 1 (0:1) 1 0 0 0 (base 0)
			// 		2 thread: 1 1 1 1 (0:2) 1 1 0 0
			// 		3 thread: 1 1 1 1 (0:3) 1 1 1 0
			// 		4 thread: 1 1 1 1 (1:0) 1 1 1 1 (base 1)
			// 		5 thread: 2 1 1 1 (1:1) 2 1 1 1
			// 		6 thread: 2 2 1 1 (1:2) 2 2 1 1 
			// 		7 thread: 2 2 2 1 (1:3) 2 2 2 1
			// 		8 thread: 2 2 2 2 (2:0) 2 2 2 2 (base 2)
			// 		9 thread: 3 2 2 2 (2:1) 3 2 2 2

			local_num_subthreads = num_threads/num_nodes;
			if (num_threads % num_nodes > i)
				local_num_subthreads += 1;

			// Lowest number of threads possible 1
			local_num_subthreads = std::max(1, local_num_subthreads);
		}
		assert(local_num_subthreads >= 1);

		parallelSSSP(graph, i, dist_matrix[i], prev_matrix[i], local_num_subthreads);
#endif
	}
}
