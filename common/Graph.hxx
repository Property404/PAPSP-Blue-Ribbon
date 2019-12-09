#pragma once
class Graph
{
	int** edge_matrix;
	int number_of_nodes;

	public:
	Graph(int n);

	void display(bool show_columns = false)const;

	int get_number_of_nodes()const;

	int get_length(int row, int column)const;

	~Graph();
};
