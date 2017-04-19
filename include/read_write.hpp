#ifndef INCLUDE_READ_WRITE_HPP_
#define INCLUDE_READ_WRITE_HPP_

#include <fstream>
#include <sstream>
//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================
struct network;
struct factor;

//=============================================================================
// PROTOTYPES
//=============================================================================
void read_input(char* file_name, network& _network);
void write_output(factor& _factor, std::vector<int>& query_variables,
		std::ofstream& out);
void T_SORT(network& _network);
#endif /* INCLUDE_READ_WRITE_HPP_ */
