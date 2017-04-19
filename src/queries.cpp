//#ifndef QUERIES_CPP
//#define QUERIES_CPP

#include <queries.hpp>
#include <read_write.hpp>
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>

//=============================================================================
// CONSTANTS
//=============================================================================
#define VARIABLE_ELIMINATION "ve"
#define REJECTION_SAMPLING "rs"

#define QUERY_VARIABLES 'q'
#define EVIDENCE_VARIABLES 'e'

#define NEGATION '~'

//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================
struct network;

//=============================================================================
// QUERIES
//=============================================================================

void process_queries(char* input_file_name, network& _network,
		char* output_file_name) {
	std::ifstream in(input_file_name);
	std::ofstream out;
	out.open(output_file_name);
	std::string line;
	char variable_type=' ';
	while (std::getline(in, line)) {
		std::vector<int> query_variables;
		std::vector<int> evidence_variables;
		std::istringstream iss(line);
		std::string inference_technique;
		iss >> inference_technique;
		std::string token;
		while (iss >> token) {
			if (token[0] == QUERY_VARIABLES) variable_type = QUERY_VARIABLES;
			else if (token[0] == EVIDENCE_VARIABLES) variable_type =
			EVIDENCE_VARIABLES;
			else {
				bool negated = token[0] == NEGATION;
				int variable = atoi(
						(negated ? token.substr(1) : token).c_str());
				variable = negated ? -variable : variable;
				if (variable_type == QUERY_VARIABLES) query_variables.push_back(
						variable);
				else if (variable_type == EVIDENCE_VARIABLES) evidence_variables.push_back(
						variable);
			}
		}
		if (inference_technique.compare(VARIABLE_ELIMINATION) == 0) process_query_variable_elimination(
				_network, query_variables, evidence_variables, out);
		else if (inference_technique.compare(REJECTION_SAMPLING) == 0) process_query_rejection_sampling(
				_network, query_variables, evidence_variables, out);
	}
}

//#endif /*QUERIES_CPP*/
