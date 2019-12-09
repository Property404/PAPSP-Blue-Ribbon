#include <cstdlib>
#include <iostream>
#include "graph.hxx"

Graph::Graph(int n)
{
	number_of_nodes = n;
	edge_matrix = new int*[n];
	for(int i=0;i<n;i++)
	{
		edge_matrix[i] = new int[n];
	}

	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		{
			edge_matrix[i][j] = rand()%2?rand()%10:rand()%100;
			edge_matrix[j][i] = edge_matrix[i][j];

			if(i==j)edge_matrix[i][j] = 0;
		}
}

void Graph::display(bool show_columns)const
{
	const auto n = number_of_nodes;

	if(show_columns)
	{
		std::cout<<"\t";
		for(int i=0;i<n;i++)
		{
			std::cout<<static_cast<char>(i+'A')<<'\t';
		}
	}

	for(int row=0;row<n;row++)
	{
		std::cout<<"\n";

		if(show_columns)
			std::cout<<static_cast<char>(row+'A')<<"\t";

		for(int column=0;column<n;column++)
		{
			std::cout<<get_length(row, column)<<'\t';
		}

	}
	std::cout<<"\n";
}

int Graph::get_number_of_nodes()const
{
	return number_of_nodes;
}

int Graph::get_length(int row, int column)const
{
	return edge_matrix[row][column];
}

Graph::~Graph(){
	for(int i=0;i<number_of_nodes;i++)
	{
		delete edge_matrix[i];
	}
	delete edge_matrix;
}

