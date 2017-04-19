#ifndef READ_WRITE_CPP
#define READ_WRITE_CPP

#include <factors.hpp>
#include <network.hpp>
#include <read_write.hpp>
#include <print.hpp>
#include <cstdlib>
#include <iostream>
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
	T_SORT(_network);
}
void T_SORT(network &_network){
	std::vector<int> L;
	std::vector<int> S;
	std::set<int> parents[_network.total_nodes];
	int i;
	for(i:_network.ids){
		if(_network.nodes[i].cpt.len==2)
			S.push_back(i);
			parents[i]=_network.nodes[i].cpt.parent_ids_set;
	}
while (S.size()){
		n=S.pop_back();
		L.push_back(n);
    for(i:_network.nodes[n].cpt.child_ids){
			parents[i].remove(n);
      if(parents[i].size()==1){
        S.push_back(i);
			}
		}
	}
	_network.ids=L;
}//=============================================================================
// WRITE
//=============================================================================
void write_output(factor& _factor, std::ofstream& out, int teq) {
	if(teq){
		printf("FROM REJECTION_SAMPLING:\n");
	}else{
		printf("FROM VARIABLE_ELIMINATION:\n");
	}
	print_factor(_factor);
	if (out.is_open()) {
		//TODO
	} else {
		printf("Couldn't open output file\n");
	}
}
#endif /*READ_WRITE_CPP*/
