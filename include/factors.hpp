#ifndef INCLUDE_FACTORS_HPP_
#define INCLUDE_FACTORS_HPP_

//=============================================================================
// STRUCTS
//=============================================================================
struct factor {
		double** matrix; //change to appropriate name
		//add more members
};

/*
class factor {
    public:
		double* matrix; //change to appropriate name
		std::vector<int> parent_ids;// let parent_ids= 1 2 3
                                    // then matrix=123 12-3 1-23 1-2-3 -123 -12-3 -1-23 -1-2-3
		int total_parents;
		std::vector<int> evidences;// unused
		int len;
		//add more members
};
void reduce(factor& x, std::vector<int>& evidence_variables, factor& result);
void reduce_matrix(factor& x,factor& y,std::vector<int>& evidence_variables,
                   int begin_x,int begin_y,int len_x,int len_y,int start_x=0,int start_y=0);

*/
//=============================================================================
// PROTOTYPES
//=============================================================================
void reduce(factor& x, factor& y, factor& result);
void join(factor& x, factor& y, factor& result);
void sum(factor& x, factor& y, factor& result);
void normalize(factor& x, factor& result);

#endif /* INCLUDE_FACTORS_HPP_ */
