#ifndef READ_WRITE_CPP
#define READ_WRITE_CPP

#include <factors.hpp>
#include <network.hpp>
#include <read_write.hpp>
#include <cstdio>
#include <cstdlib>
#include <iterator>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <utility>
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
		_network.nodes[id].cpt.parent_ids.push_back(id);
		_network.nodes[id].cpt.parent_ids_set.insert(id);
		_network.ids.push_back(id);

		/* Process parent ids */
		int pid;
		while (iss >> pid) {
			pid--;
			_network.nodes[id].cpt.id = id;
			_network.nodes[id].cpt.parent_ids.push_back(pid);
			_network.nodes[id].cpt.parent_ids_set.insert(pid);
			_network.nodes[pid].cpt.child_ids.push_back(id);
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

	topological_sort(_network);
}

void topological_sort(network &_network) {
	/* Empty list that will contain the sorted elements */
	std::vector<int> sorted_elements;
	/* nodes without an incoming edge */
	std::stack<int> nodes;
	std::set<int>* parents = new std::set<int>[_network.total_nodes];
	for (int i : _network.ids) {
		if (_network.nodes[i].cpt.len == 2) nodes.push(i);
		parents[i] = _network.nodes[i].cpt.parent_ids_set;
	}
	while (nodes.size()) {
		int n = nodes.top();
		nodes.pop();
		sorted_elements.push_back(n);
		for (int i : _network.nodes[n].cpt.child_ids) {
			parents[i].erase(n);
			if (parents[i].size() == 1) {
				nodes.push(i);
			}
		}
	}
	delete[] parents;
	_network.ids = sorted_elements;
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
