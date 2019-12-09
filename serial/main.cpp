#include <cstdlib>
#include <ctime>
#include <iostream>
#include "args.hxx"
#include "serial.hxx"
using namespace std;


int main(int argc, const char* argv[])
{
	args::ArgumentParser parser("Shortest path calculator", "");
	args::HelpFlag help(parser, "help", "Display this tedxt", {'h', "help"});
	args::Flag show_meta(parser, "meta", "Display meta info", {'m', "meta"});
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
	graph.display(true);
	cout<<"\n";

	vector<vector<int>> dist_matrix(size, vector<int>(size));
	vector<vector<int>> prev_matrix(size, vector<int>(size));

	serialAPSP(graph, dist_matrix, prev_matrix);

	for(int i=0;i<size;i++)
	{
		cout << static_cast<char>('A'+i) << "-prev";
		for(const int p:prev_matrix[i])
			cout<<"\t"<<static_cast<char>('A'+p);
		cout<<"\n";
		cout << static_cast<char>('A'+i) << "-dist";
		for(const int d:dist_matrix[i])
			cout<<"\t"<<d;
		cout<<"\n";
	}
}
