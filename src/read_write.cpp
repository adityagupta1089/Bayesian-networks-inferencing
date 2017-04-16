#ifndef READ_WRITE_CPP
#define READ_WRITE_CPP

#include <factors.hpp>
#include <network.hpp>
#include <read_write.hpp>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================
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
		/* TODO maybe push id in parents? */
		_network.nodes[id].cpt.parent_ids.push_back(id);
		_network.nodes[id].cpt.parent_ids_set.insert(id);


		/* Process parent ids */
		int pid;
		while (iss >> pid) {
			pid--;
			_network.nodes[id].cpt.id = id;
			_network.nodes[id].cpt.parent_ids.push_back(pid);
			_network.nodes[id].cpt.parent_ids_set.insert(pid);
		}

		/* Process CPT */
		int total_parents = _network.nodes[id].cpt.parent_ids.size();
		int rows = 1 << total_parents;

		_network.nodes[id].cpt.matrix = new double[rows];

		for (int i = 0; i < rows / 2; i++) {
			std::getline(in, line);
			std::istringstream iss(line);
			/* P(x|parents) */
			iss >> _network.nodes[id].cpt.matrix[i];
			/* P(~x|parents) */
			iss >> _network.nodes[id].cpt.matrix[i + rows / 2];
		}
	}
}
//=============================================================================
// WRITE
//=============================================================================
void write_output(factor& _factor, char* file_name) {
	std::ofstream out;
	out.open(file_name);
	if (out.is_open()) {
		//TODO
	} else {
		printf("Couldn't open output file\n");
	}
}
#endif /*READ_WRITE_CPP*/
