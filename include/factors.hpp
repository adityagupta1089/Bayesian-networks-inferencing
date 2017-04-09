#ifndef INCLUDE_FACTORS_HPP_
#define INCLUDE_FACTORS_HPP_

//=============================================================================
// STRUCTS
//=============================================================================
struct factor {
		double** matrix; //change to appropriate name
		//add more members
};

//=============================================================================
// PROTOTYPES
//=============================================================================
void reduce(factor& x, factor& y, factor& result);
void join(factor& x, factor& y, factor& result);
void sum(factor& x, factor& y, factor& result);
void normalize(factor& x, factor& result);

#endif /* INCLUDE_FACTORS_HPP_ */
