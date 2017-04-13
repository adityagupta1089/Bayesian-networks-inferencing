#ifndef READ_WRITE_CPP
#define READ_WRITE_CPP

#include <factors.hpp>
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

	/* Input n, total nodes */
	std::getline(in, line);
	int n = _network.total_nodes = atoi(line.c_str());
	_network.nodes.resize(n);

	/* Process each line */
	for (int i = 0; i < n; i++) {
		std::getline(in, line);
		std::istringstream iss(line);

		/* Current node's id */
		int id;
		iss >> id;
		id--;

		/* Process parent ids */
		int pid;
		while (iss >> pid) {
			pid--;
			_network.nodes[id].cpt.parent_ids.push_back(pid);
		}

		/* Process CPT */
		int total_parents = _network.nodes[id].cpt.parent_ids.size();
		int rows = 1 << total_parents;

		_network.nodes[id].cpt.matrix = new double*[rows];

		for (int i = 0; i < rows; i++) {
			std::getline(in, line);
			std::istringstream iss(line);
			_network.nodes[id].cpt.matrix[i] = new double[2];
			/* P(x|parents) */
			iss >> _network.nodes[id].cpt.matrix[i][0];
			/* P(~x|parents) */
			iss >> _network.nodes[id].cpt.matrix[i][1];
		}
	}
}
#endif /*READ_WRITE_CPP*/
