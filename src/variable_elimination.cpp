#include <iostream>
#include <vector>

struct network;

void process_query_variable_elimination(network& _network,
		std::vector<int>& query_variables, std::vector<int>& evidence_variables,
		std::ofstream& out) {
	//TODO
	/* Start with initial factors (Local CPTs instantiated by evidence variable) */
	/* For each hidden variable H */
	{
		/* Join all factors with H */
		/* Eliminate/Sum H */
	}
	/* Join all remaining factors */
	/* Normalize */
	/* Write to output file*/
}

/*
void process_query_variable_elimination(network& _network,
//reduce
		std::vector<int>& query_variables, std::vector<int>& evidence_variables,
		std::ofstream& out) {
        std::vector<int> evidence(_network.total_nodes);
        network query_network=_network;
        for(int i=0;i<_network.total_nodes;i++)
            evidence[i]=-1;
        for(unsigned int i=0;i<evidence_variables.size();i++){
            printf("%d ",evidence_variables[i]);
            evidence[abs(evidence_variables[i])-1]=(evidence_variables[i]>0?1:0);
        }
        query_network.nodes=new factor[query_network.total_nodes];
        for(int i=0;i<_network.total_nodes;i++){
            printf("per:%d\n",_network.nodes[i].total_parents);
            reduce(_network.nodes[i],evidence,query_network.nodes[i]);
        }

        for(int i=0;i<_network.total_nodes;i++){
            for(int j=0;j<_network.nodes[i].len;j++)
                printf("%f ",_network.nodes[i].matrix[j]);
            printf("\n");
        }
        for(int i=0;i<query_network.total_nodes;i++){
            for(int j=0;j<query_network.nodes[i].len;j++)
                printf("%f ",query_network.nodes[i].matrix[j]);
            printf("\n");
        }
}


*/