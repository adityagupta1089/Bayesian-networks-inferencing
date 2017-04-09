#ifndef READ_WRITE_CPP
#define READ_WRITE_CPP

#include <network.hpp>
#include <cstdlib>
#include <fstream>
#include <string>

struct network;

using namespace std;

//===================================================
// READ
//===================================================
void read_input(char* file_name, network& _network) {
	ifstream in(file_name);
	string line;
	getline(in, line);
	int n = _network.total_nodes = atoi(line.c_str());
	_network.nodes = new node[n];
	for (int i = 0; i < n; i++) {
		read_node(in, line, _network);
	}
}

void read_node(ifstream in, string& line, network& _network) {
	getline(in, line);
	//get node id
	int id;
	//get parents
	int n = _network.nodes[id].total_parents; // = parse
	_network.nodes[id].parent_ids = new int[n];
	for (int i = 0; i < n; i++) {
		//_network.nodes[id][i] = parse
	}
}

//===================================================
// WRITE
//===================================================
void write_results(char* file_name) {
}
#endif /*READ_WRITE_CPP*/
