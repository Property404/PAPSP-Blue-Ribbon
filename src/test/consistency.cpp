#include "catch.hpp"
#include "Graph.hxx"
#include "serial.hxx"
#include "parallel.hxx"
#include <iostream>
#include <vector>
using namespace std;

static void check(Graph& graph, int size, int threads, int subthreads) 
{
	vector<vector<int>> serial_dist_matrix(size, vector<int>(size));
	vector<vector<int>> serial_prev_matrix(size, vector<int>(size));
	vector<vector<int>> parallel_dist_matrix(size, vector<int>(size));
	vector<vector<int>> parallel_prev_matrix(size, vector<int>(size));

	serialAPSP(graph, serial_dist_matrix, serial_prev_matrix);
	parallelAPSP(
			graph,
			parallel_dist_matrix,
			parallel_prev_matrix,
			threads,
			subthreads
	);

	for(int i=0;i<size;i++)
	{
		for(int j=0;j<size;j++)
		{
			REQUIRE(serial_dist_matrix[i][j] == parallel_dist_matrix[i][j]);
			REQUIRE(serial_prev_matrix[i][j] == parallel_prev_matrix[i][j]);

			// Make sure it is within bounds
			REQUIRE(serial_prev_matrix[i][j] < size);
			REQUIRE(serial_prev_matrix[i][j] >= -1);
			REQUIRE(serial_dist_matrix[i][j] >= 0);
		}
	}
}

#define MIN_SIZE 2
#define LOWER_MAX_SIZE 10
#define HIGHER_MAX_SIZE 100

TEST_CASE( "Serial and parallel results are consistent with each other", "[serial parallel]" )
{

	for(int size=MIN_SIZE;size<=LOWER_MAX_SIZE;size++)
	{
		Graph graph(size);
		for(int threads=1;threads<size*4;threads++)
		{

			if(threads <= size)
				for(int subthreads=-1;subthreads<size;subthreads++)
				{
					if(subthreads == 0)
						continue;
					check(graph, size, threads, subthreads);
				}
			else
				check(graph, size, threads, -1);
		}
	}
}

TEST_CASE( "Serial and parallel results are consistent for large values", "[serial parallel]" )
{

	for(int size=MIN_SIZE;size<=HIGHER_MAX_SIZE;size++)
	{
		Graph graph(size);
		check(graph, size, 1+rand()%size, -1);
	}
}
