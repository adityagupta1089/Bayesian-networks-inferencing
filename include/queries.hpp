#ifndef INCLUDE_QUERIES_HPP_
#define INCLUDE_QUERIES_HPP_

#include <iostream>
#include <vector>

//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================
struct network;

//=============================================================================
// PROTOTYPES
//=============================================================================
void process_queries(char* input_file_name, network& _network, char* output_file_name);
void process_query_variable_elimination(network& _network, std::vector<int>& query_variables, std::vector<int>& evidence_variables, std::ofstream& out);
void process_query_rejection_sampling(network& _network, std::vector<int>& query_variables, std::vector<int>& evidence_variables, std::ofstream& out);

#endif /* INCLUDE_QUERIES_HPP_ */
