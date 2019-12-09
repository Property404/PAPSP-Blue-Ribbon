#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <queue>
#include "args.hxx"
#include "Graph.hxx"
#include "PriorityNode.hxx"

using namespace std;
#define DJ_INFINITY 100
#define DEFAULT_NUMBER_OF_NODES 6

void dijkstraSSSP(const Graph& graph, int source, bool show_columns)
{
	const int num_nodes = graph.get_number_of_nodes();

	vector<int> dist(num_nodes, DJ_INFINITY);
	vector<int> prev(num_nodes, -1);
	vector<bool> visited(num_nodes, false);
	dist[source] = 0;


	priority_queue<PriorityNode, vector<PriorityNode>, std::greater<PriorityNode>> nodes;
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
	
	
	for(int i=0;i<num_nodes;i++)
	{
		if(show_columns)
			cout<<"\t"<<static_cast<char>('A'+prev[i]);
		else
			cout<<prev[i]<<"\t";
	}
	cout<<"\n";

	if (show_columns)
	{
		for(int i=0;i<num_nodes;i++)
		{
			cout<<"\t"<<dist[i];
		}
		cout<<"\n";
	}
	else
	{
		cout<<dist[num_nodes-1]<<endl;
	}
}

int main(int argc, const char* argv[])
{
	args::ArgumentParser parser("Shortest path calculator", "");
	args::HelpFlag help(parser, "help", "Display this tedxt", {'h', "help"});
	args::Flag show_columns(parser, "show columns", "Show columns", {'c', "show-columns"});
	args::Flag show_meta(parser, "meta", "Display meta", {'m', "display-meta"});
	args::ValueFlag<int> size_opt(parser, "size", "Set number of nodes", {'n', "nodes"});
	args::ValueFlag<int> seed_opt(parser, "seed", "Set seed", {'s', "seed"});

	
	try
	{
		parser.ParseCLI(argc, argv);
	}
	catch(const args::Help&)
	{
		cout << parser;
		return 0;
	}
	catch(const args::ParseError& e)
	{
		cerr << e.what() << endl;
		cerr << parser;
		return 1;
	}

	const int size = size_opt?args::get(size_opt):DEFAULT_NUMBER_OF_NODES;
	const int seed = seed_opt?args::get(seed_opt):time(NULL);

	if(args::get(show_meta))
	{
		cout << size << " " << seed << endl;
	}

	srand(seed);

	Graph graph(size);
	graph.display(args::get(show_columns));
	if(show_columns)
		cout<<"\n";
	dijkstraSSSP(graph, 0, show_columns);
}
