//Name: Hridika Banik
//UCID: 30123716
// -------------------------------------------------------------------------------------
// this is the only file you need to edit
// -------------------------------------------------------------------------------------
//
// (c) 2021, Pavol Federl, pfedersl@ucalgary.ca
// Do not distribute this file.

#include "fatsim.h"
#include <iostream>
#include <stack>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <cstdio>
using namespace std;
// reimplement this function

//This part of the code and pseudocode has been adapted from TA: Stephane Dorottich's tutorial:
// https://github.com/stephanedorotich/t457/blob/main/6-FAT/FATgraph_v2.cpp
struct Graph {
    
    // list of nodes with other adjacent nodes around
    vector<vector<int>> adjlist;
   
    // list of nodes that are Spointing towards -1
    vector<int> terminatingnode; 

    
    // Constructor
    Graph (int n) {
        adjlist.resize(n);
        terminatingnode = vector<int>();
        std::fill(adjlist.begin(), adjlist.end(), std::vector<int>());
        
    }


};

void build_graph(Graph & g, const std::vector<long> & FAT) {
    
    unsigned long b = FAT.size();
    for(unsigned long a = 0; a < b; a= a +1) {
        
        int var = FAT[a];
        //adds the node to the terminating node list if it points to -1
        if(var == -1) {
            g.terminatingnode.push_back(a); 
        }
         //if the node does not point to -1 , the node is added to the adjacency list 
        else if(var != -1) {
            g.adjlist[FAT[a]].push_back(a);
        }
    }

}


std::vector<long> fat_check(const std::vector<long> & fat)
{
     //this will display the final result vector after the depth-first search
    vector<long> result;
    Graph g = Graph(fat.size());
    build_graph(g, fat);

    std::stack<std::pair<long, long>> stack; //stack.first shows the node and stack.second shows the current chain length
           
    std::stack<std::pair<long, long>> stack1; //stack1.first shows the current node and stack.second shows the longest chain length till that cycle
    
    long largest_chain;
    long nodecurrent;
    long currentchain;
    
    // performs depth-first search on each finishp point and records the longest chain length
    largest_chain = 0;
    for(long finishp : g.terminatingnode) { 
        
        stack.emplace(finishp, 1); 
        
        while(!stack.empty()) { 
            //
            nodecurrent = stack.top().first;
            //printf("the current node is: %ld\n\n", nodecurrent);
            currentchain = stack.top().second;
            stack.pop();
           

            //
            if(currentchain >=  largest_chain) {
                largest_chain = currentchain;
                //printf("longest chain till now is %ld\n", largest_chain);
                //printf("Corresponding node is %ld\n\n", nodecurrent);

                //stores the nodes along with the corresponding chain length in stack 1
                stack1.push({nodecurrent, largest_chain});
                
            }
            
            //printf("checking\n");
            for(auto temp : g.adjlist[nodecurrent]) { 
                //printf("Here\n");
                int x = currentchain+1;
                stack.emplace(temp, x);
            }
        }
        //printf("longest chain is %ld\n\n", largest_chain); //debugging
        //printf("longest chain startnode is %ld\n\n", nodecurrent);
        
       
    }
    //printf("size of stack 1 is %ld\n", stack1.size() );
    // stores the size of the stack 1 which contains all the nodes and corresponding chains
    uint64_t x = stack1.size();
    //This loop iterates through the stack 1 and gets the corresponding nodes to the largest chains and sends it back to the result vector
    for (uint64_t i = 0; i< x; i++){
        //printf("The i is %ld\n", i);
        //printf("Values from stack 1 are %ld\n", stack1.top().first);
        if (stack1.top().second == largest_chain){
            
            result.push_back(stack1.top().first);
            
        }
        //Gets rid of the nodes that has already been stored
        stack1.pop();
    }

    sort(result.begin(), result.end()); //sorts the result vector in ascending order
    //printf("DONE CODING");
    return result;
}

