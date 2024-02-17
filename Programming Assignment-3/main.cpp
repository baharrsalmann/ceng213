#include "CENGFlight.h"
#include "MultiGraph.h"
#include "HashTable.h"
#include <iostream>
#define INF (float)((1e+300) * (1e+300) )
#include "IntPair.h"

    struct EdgeNameCount
{
    int count;
    std::string name; 
};
bool isIn(std::vector<EdgeNameCount>& EdgeNameCounts,std::string name){
    for(int i=0;i<EdgeNameCounts.size();i++){
        if (EdgeNameCounts[i].name==name) {
            EdgeNameCounts[i].count++;
            return true;
        }
    }
    return false;
}

int main(int argc, const char* argv[])
{
    // For testing from VPL
    //  ...


    std::vector<EdgeNameCount> EdgeNameCounts;

    return isIn(EdgeNameCounts,"bahar");
}