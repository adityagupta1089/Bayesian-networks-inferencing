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
#include <map>

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

		_network.nodes[id].cpt.len = rows;
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
void write_output(factor& _factor, std::vector<int>& query_variables,
		std::ofstream& out) {
	if (out.is_open()) {
		std::map<int, bool> sign;
		for (int x : query_variables)
			sign[abs(x) - 1] = x > 0;
		int ind = 0;
		for (auto it = _factor.parent_ids.rbegin();
				it != _factor.parent_ids.rend(); it++) {
			ind <<= 1;
			ind |= sign[*it] ? 0 : 1;
		}
		out << _factor.matrix[ind] << "\n";
	} else {
		fprintf(stderr, "Couldn't open output file\n");
		exit(0);
	}
}
#endif /*READ_WRITE_CPP*/
