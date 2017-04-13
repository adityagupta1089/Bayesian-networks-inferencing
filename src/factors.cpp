//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================
struct factor;

//=============================================================================
// FUNCTIONS
//=============================================================================

/*
void reduce(factor& x, std::vector<int>& evidence_variables, factor& result) {// evidence_variable:::: true->1 false->0 none->-1
    result.total_parents=0;
    for(int i=0;i<x.total_parents;i++){
        if(evidence_variables[x.parent_ids[i]]==-1){
            result.total_parents++;
            result.parent_ids.push_back(x.parent_ids[i]);// here parent_ids also includes the query variable.
            printf("%d ",x.parent_ids[i]);
        }
    }
    int len=1 << result.total_parents;
    result.len=len;
    result.matrix=new double[len];
    reduce_matrix(x,result,evidence_variables,0,0,x.len,result.len);
}

void reduce_matrix(factor& x,factor& y,std::vector<int>& evidence_variables,
                   int begin_x,int begin_y,int len_x,int len_y,int start_x,int start_y){
    if(len_x==1){
        y.matrix[begin_y]=x.matrix[begin_x];
        return;
    }
    if(y.total_parents<=start_y || x.parent_ids[start_x]!=y.parent_ids[start_y]){
        if(evidence_variables[x.parent_ids[start_x]])
            reduce_matrix(x,y,evidence_variables,begin_x,begin_y,len_x/2,len_y,start_x+1,start_y);
        else
            reduce_matrix(x,y,evidence_variables,begin_x+len_x/2,begin_y,len_x/2,len_y,start_x+1,start_y);
        return;
    }
    reduce_matrix(x,y,evidence_variables,begin_x,begin_y,len_x/2,len_y/2,start_x+1,start_y+1);
    reduce_matrix(x,y,evidence_variables,begin_x+len_x/2,begin_y+len_y/2,len_x/2,len_y/2,start_x+1,start_y+1);
}

*/

void reduce(factor& x, factor& y, factor& result) {

}

void join(factor& x, factor& y, factor& result) {

}

void sum(factor& x, factor& y, factor& result) {

}

void normalize(factor& x, factor& result) {

}
