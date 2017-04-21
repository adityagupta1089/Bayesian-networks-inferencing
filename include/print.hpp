#ifndef INCLUDE_PRINT_HPP_
#define INCLUDE_PRINT_HPP_

#define UNDEFINED "These evidences don't occur at the same time, i.e. P(e) = 0, thus P(Q|e) is undefined.\n"
//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================
struct factor;

//=============================================================================
// PROTOTYPES
//=============================================================================
void print_factor(factor& _factor);

#endif /* INCLUDE_PRINT_HPP_ */
