#include "args.hxx"
#include "Timer.hxx"
#include "serial.hxx"
#include "parallel.hxx"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <omp.h>
using namespace std;


int main(int argc, const char* argv[])
{
	args::ArgumentParser parser("Shortest path calculator", "");
	args::HelpFlag help(parser, "help", "Display this tedxt", {'h', "help"});

	args::Flag use_parallel_version(parser, "parallel", "Use parallel APSP", {'P', "parallel"});
	args::Flag use_serial_version(parser, "serial", "Use serial APSP", {'S', "serial"});

	args::Flag show_meta(parser, "meta", "Display meta info", {'m', "meta"});
	args::Flag quiet(parser, "quiet", "surpress results", {'q', "quiet"});

	args::ValueFlag<int> size_opt(parser, "size", "Set number of nodes", {'n', "nodes"});
	args::ValueFlag<int> seed_opt(parser, "seed", "Set seed", {'s', "seed"});
	args::ValueFlag<int> threads_opt(parser, "threads", "Number of threads for APSP algo", {'t', "threads"});
	args::ValueFlag<int> subthreads_opt(parser, "subthreads", "Number of subthreads for SSSP algo", {'j', "subthreads"});


	// Turn off IO synchronization
#ifndef DEBUG
	std::ios_base::sync_with_stdio(false);
#endif

	
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
	const int threads = threads_opt?args::get(threads_opt):-1;
	const int subthreads = subthreads_opt?args::get(subthreads_opt):-1;
	srand(seed);

	if(args::get(show_meta))
	{
		cout << size << " " << seed << endl;
	}


	Graph graph(size);
	if(!quiet)
	{
		graph.display(true);
		cout<<"\n";
	}

	vector<vector<int>> dist_matrix(size, vector<int>(size));
	vector<vector<int>> prev_matrix(size, vector<int>(size));

	if(use_parallel_version)
	{
		if(threads==-1)
		{
			cerr << "Please specify number of threads" << endl;
			exit(1);
		}
		omp_set_num_threads(threads);
	}

	Timer timer;
	timer.start();

	// Choose algorithm then run
	if(use_serial_version && !use_parallel_version)
		serialAPSP(graph, dist_matrix, prev_matrix);
	else if(use_parallel_version && !use_serial_version)
		parallelAPSP(graph, dist_matrix, prev_matrix, threads, subthreads);
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
