#ifndef INCLUDE_READ_WRITE_HPP_
#define INCLUDE_READ_WRITE_HPP_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================
struct network;
struct factor;

//=============================================================================
// PROTOTYPES
//=============================================================================
void read_input(char* file_name, network& _network);
void write_output(factor& _factor, char* file_name);

#endif /* INCLUDE_READ_WRITE_HPP_ */
