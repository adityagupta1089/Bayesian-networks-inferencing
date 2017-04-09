#ifndef READ_WRITE_CPP
#define READ_WRITE_CPP

#include <functions.hpp>
#include <network.hpp>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct network;

//=============================================================================
// READ
//=============================================================================
void read_input(char* file_name, network& _network) {
	std::ifstream in(file_name);
	std::string line;
	std::getline(in, line);
	int n = _network.total_nodes = atoi(line.c_str());
	_network.nodes = new node[n];
	for (int i = 0; i < n; i++) {
		std::getline(in, line);
		std::istringstream iss(line);
		int id;
		iss >> id;
		id--;
		int pid;
		while (iss >> pid) {
			pid--;
			_network.nodes[id].parent_ids.push_back(pid);
		}
		int total_parents = _network.nodes[id].parent_ids.size();
		int rows = 1 << total_parents;
		_network.nodes[id].conditional_probability_table = new double*[rows];
		for (int i = 0; i < rows; i++) {
			std::getline(in, line);
			std::istringstream iss(line);
			_network.nodes[id].conditional_probability_table[i] = new double[2];
			iss >> _network.nodes[id].conditional_probability_table[i][0];
			iss >> _network.nodes[id].conditional_probability_table[i][1];
		}
	}
}
#endif /*READ_WRITE_CPP*/
