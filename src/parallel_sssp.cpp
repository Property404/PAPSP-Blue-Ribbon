#include "parallel.hxx"
#include "PriorityNode.hxx"
#include <pthread.h>
#include <iostream>
#include <queue>
#include <cassert>

struct ReductionArgs
{
	int from;
	int to;
	int u;
	const Graph*const graph;
	const std::vector<bool>*const visited;
	std::vector<int>*const dist;
	std::vector<int>*const prev;
	std::priority_queue<PriorityNode, std::vector<PriorityNode>, std::greater<PriorityNode>>*const nodes;

};

static void* reduceSection(ReductionArgs* args);

void parallelSSSP
(
	const Graph& graph,
	int source,
	std::vector<int>& dist,
	std::vector<int>& prev,
	int num_threads
)
{
#ifdef DEBUG
	std::cout<<"Subthreads: "<<num_threads<<"\n";
#endif
	const int num_nodes = graph.get_number_of_nodes();

	std::vector<bool> visited(num_nodes, false);
	for(int i=0;i<num_nodes;i++)
	{
		dist[i] = DJ_INFINITY;
		prev[i] = -1;
	}
	dist[source] = 0;

	std::priority_queue<PriorityNode, std::vector<PriorityNode>, std::greater<PriorityNode>> nodes;
	for (int i=0;i<num_nodes;i++)
	{
		nodes.emplace(i, dist[i]);
	}
	
	// Pthread preparation
	std::vector<pthread_t> threads(num_threads);
	// Prepare list of arguments
	// for pthreads
	std::vector<ReductionArgs> args_vector(num_threads, 
			{
			.from=-1,
			.to=-1,
			.u=-1,
			.graph=&graph,
			.visited=&visited,
			.dist=&dist,
			.prev=&prev,
			.nodes=&nodes
			}
	);



	while(!nodes.empty())
	{
		if(nodes.top().priority != dist[nodes.top().index])	
		{
			nodes.pop();
			continue;
		}
		const int u = nodes.top().index;nodes.pop();
		visited[u] = true;


		// Reduce in parallel
		for(int i=0; i<num_threads;i++)
		{
			//i*num_nodes/num_threads to (i+1)*num_nodes/num_threads - 1
			args_vector[i].from = i*num_nodes/num_threads;
			args_vector[i].to = (i+1)*num_nodes/num_threads - 1;
			args_vector[i].u = u;

			// First one is done on the master thread
			if(i==0)
				continue;

			pthread_create(
					&(threads[i]),
					NULL,
					(void* (*)(void*))(reduceSection),
					&(args_vector[i])
			);
		}

		reduceSection(&(args_vector[0]));
		for(int i=1;i<num_threads;i++)
		{
			pthread_join(threads[i], NULL);
		}

		/*
		#pragma omp parallel for num_threads(num_threads)
		for(int v=0;v<num_nodes;v++)
		{
			if(omp_get_num_threads() != num_threads)
			{
				std::cerr << "Fuck: expected "<< num_threads << " but got "<<omp_get_num_threads()<<"\n";
				std::cerr << "Max: " << omp_get_max_threads() <<"\n";
			}
			assert(omp_get_num_threads() == num_threads);

			if(visited[v]) continue;
			const int alt = dist[u] + graph.get_length(u,v);
			if(alt<dist[v])
			{
				dist[v] = alt;
				prev[v] = u;
#pragma omp critical
				{
				nodes.emplace(v, alt);
				}
			}
		}
		*/
	}
}

// Mutex for the priority_queue
static pthread_mutex_t pq_mutex = PTHREAD_MUTEX_INITIALIZER;

static void* reduceSection(ReductionArgs*const args)
{
	for(int v=args->from; v<=args->to; v++)
	{
		if((*(args->visited))[v]) continue;
		const int alt = (*(args->dist))[args->u] + args->graph->get_length(args->u,v);
		if(alt<(*(args->dist))[v])
		{
			(*(args->dist))[v] = alt;
			(*(args->prev))[v] = args->u;

			pthread_mutex_lock(&pq_mutex);
			args->nodes->emplace(v, alt);
			pthread_mutex_unlock(&pq_mutex);
		}
	}
	return NULL;
}
