#include <iostream>
#include <vector>
#include <queue>
#include "serial_sssp.hxx"
#include "PriorityNode.hxx"

void serialSSSP
(
	const Graph& graph,
	int source,
	std::vector<int>& dist,
	std::vector<int>& prev
)
{
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

	while(!nodes.empty())
	{
		if(nodes.top().priority != dist[nodes.top().index])	
		{
			nodes.pop();
			continue;
		}
		const int u = nodes.top().index;nodes.pop();
		visited[u] = true;

		for(int v=0;v<num_nodes;v++)
		{
			if(visited[v]) continue;
			const int alt = dist[u] + graph.get_length(u,v);
			if(alt<dist[v])
			{
				dist[v] = alt;
				prev[v] = u;
				nodes.emplace(v, alt);
			}
		}
	}
}
