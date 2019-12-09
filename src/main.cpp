#include <cstdlib>
#include <ctime>
#include <iostream>
#include "args.hxx"
#include "Timer.hxx"
#include "serial.hxx"
#include "parallel.hxx"
using namespace std;


int main(int argc, const char* argv[])
{
	args::ArgumentParser parser("Shortest path calculator", "");
	args::HelpFlag help(parser, "help", "Display this tedxt", {'h', "help"});
	args::Flag show_meta(parser, "meta", "Display meta info", {'m', "meta"});
	args::ValueFlag<int> size_opt(parser, "size", "Set number of nodes", {'n', "nodes"});
	args::ValueFlag<int> seed_opt(parser, "seed", "Set seed", {'s', "seed"});

	args::Flag quiet(parser, "quiet", "surpress results", {'q', "quiet"});
	args::Flag use_parallel_version(parser, "parallel", "Use parallel APSP", {'P', "parallel"});
	args::Flag use_serial_version(parser, "serial", "Use serial APSP", {'S', "serial"});

	// Turn off IO synchronization
	std::ios_base::sync_with_stdio(false);

	
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
	if(!quiet)
	{
		graph.display(true);
		cout<<"\n";
	}

	vector<vector<int>> dist_matrix(size, vector<int>(size));
	vector<vector<int>> prev_matrix(size, vector<int>(size));

	Timer timer;
	timer.start();

	// Choose algorithm then run
	if(use_serial_version && !use_parallel_version)
		serialAPSP(graph, dist_matrix, prev_matrix);
	else if(use_parallel_version && !use_serial_version)
		parallelAPSP(graph, dist_matrix, prev_matrix, 8);
	else
	{
		cerr<<"Must select --serial or --parallel"<<endl;
		exit(1);
	}

	timer.stop();

	if(!quiet)
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
	cout<<"Execution time: "<<timer.getValue()<<std::endl;
}
