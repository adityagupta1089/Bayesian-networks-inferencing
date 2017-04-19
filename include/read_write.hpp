#ifndef INCLUDE_READ_WRITE_HPP_
#define INCLUDE_READ_WRITE_HPP_

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

#endif /* INCLUDE_READ_WRITE_HPP_ */
