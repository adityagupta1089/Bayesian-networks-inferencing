#ifndef INCLUDE_FUNCTIONS_HPP_
#define INCLUDE_FUNCTIONS_HPP_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================
struct network;

//=============================================================================
// PROTOTYPES
//=============================================================================
void read_input(char* file_name, network& _network);
void process_queries(char* input_file_name, network& _network,
		char* output_file_name);
void process_query_variable_elimination(std::vector<int>& query_variables,
		std::vector<int>& evidence_variables, std::ofstream& out);
void process_query_rejection_sampling(std::vector<int>& query_variables,
		std::vector<int>& evidence_variables, std::ofstream& out);

#endif /* INCLUDE_FUNCTIONS_HPP_ */
