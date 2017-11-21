//
// Created by jf on 11/21/17.
//

#include "algorithm.h"


bool deep_search(std::vector<CGraph::Graph> &tree, int source, int dest,std::vector<CGraph::Graph> &pth, int start_ind  ){
    int i,j,k=0;
    bool found;
    std::list<CGraph::Node> neighbord;
    for(i=0;tree[i].id!=source && i<tree.size();i++);
    if(tree[i].PassedOn){
        return false;
    }
    tree[i].PassedOn= false;
    found= false;
    for(auto it=neighbord.begin();it!=neighbord.end(),found!= true;it++){
        for(j=0;tree[j].id!=it->id && j<tree[i].nb_nodes;j++);
        if(tree[j].id==dest){
            found=true;
            pth[start_ind+1]=tree[j];
        }
        else{
            found=deep_search(tree,tree[j].id,dest,pth,(start_ind+1));
        }
    }

    if(found){
        pth[start_ind]=tree[i];
    }
    tree[i].PassedOn=found;
}
