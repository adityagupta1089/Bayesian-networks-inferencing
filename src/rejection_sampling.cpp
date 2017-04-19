#include <iostream>
#include <vector>
#include <factors.hpp>
#include <network.hpp>
#include <print.hpp>
#include <read_write.hpp>
#include <algorithm>
#define SAMPLE_COUNT 1000000

//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================
struct network;

//=============================================================================
// FUNCTIONS
//=============================================================================
void process_query_rejection_sampling(network& _network,
		std::vector<int>& query_variables, std::vector<int>& evidence_variables,
		std::ofstream& out) {
	//TODO
	factor _factor;
	for(int i:query_variables){
		_factor.parent_ids.push_back(abs(i)-1);
	}
	_factor.len=1<<_factor.parent_ids.size();
	_factor.matrix=new double[_factor.len];
	unsigned int values[_network.total_nodes];
	/* Processing Values of evidence variables */
	std::vector<int> evidence(_network.total_nodes);
	std::fill(evidence.begin(), evidence.begin() + _network.total_nodes,
	HIDDEN);
	for (int x : query_variables)
		evidence[abs(x) - 1] = NONE;
	for (int x : evidence_variables)
		evidence[abs(x) - 1] = (x > 0 ? TRUE : FALSE);
	int count=0;
	for (int _i = 0; _i < SAMPLE_COUNT; _i++) {
		double sample=rand()/(double)RAND_MAX;
		unsigned int index=0;
		bool reject=false;
		/* for each node x_i in query?*/
		for (int x_i : _network.ids) {
			index=0;
			for(int i:_network.nodes[x_i].cpt.parent_ids){
				if(i==x_i)
					continue;
				index<<=1;
				index|=values[i];
			}
			if(index>_network.nodes[x_i].cpt.len){
				printf("%d,%d\n", x_i,index);
				return;
			}
			if(sample<_network.nodes[x_i].cpt.matrix[index]){
				if(evidence[x_i]==FALSE){
					reject=true;
					break;
				}
				values[x_i]=0;
				sample/=_network.nodes[x_i].cpt.matrix[index];
			}else{
				if(evidence[x_i]==TRUE){
					reject=true;
					break;
				}
				values[x_i]=1;
				sample-=_network.nodes[x_i].cpt.matrix[index];
				sample/=(1-_network.nodes[x_i].cpt.matrix[index]);
			}
		}
		if(reject)
			continue;
		index=0;
		for(int x_i:query_variables){
			index<<=1;
			index|=values[abs(x_i)-1];
		}
		_factor.matrix[index]++;
		count++;
	}
	for(int i=0;i<_factor.len;i++){
		_factor.matrix[i]/=count;
	}
	write_output(_factor, out,1);
	/* calculate probability for given query */
}
