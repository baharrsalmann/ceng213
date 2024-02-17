#include "CENGFlight.h"
#include <iostream>

//=======================//
// Implemented Functions //
//=======================//
void CENGFlight::PrintCanNotHalt(const std::string& airportFrom,
                                 const std::string& airportTo,
                                 const std::string& airlineName)
{
    std::cout << "A flight path between \""
              << airportFrom << "\" and \""
              << airportTo << "\" via "
              << airlineName
              << " airlines is not found and cannot be halted"
              << std::endl;
}

void CENGFlight::PrintCanNotResumeFlight(const std::string& airportFrom,
                                         const std::string& airportTo,
                                         const std::string& airlineName)
{
    std::cout << "A flight path between \""
              << airportFrom << "\" and \""
              << airportTo << "\" via "
              << airlineName
              << " airlines cannot be resumed"
              << std::endl;
}

void CENGFlight::PrintFlightFoundInCache(const std::string& airportFrom,
                                         const std::string& airportTo,
                                         bool isCostWeighted)
{
    std::cout << "A flight path between \""
              << airportFrom << "\" and \""
              << airportTo << "\" using "
              << ((isCostWeighted) ? "cost" : "price")
              <<  " is found in cache." << std::endl;
}

void CENGFlight::PrintFlightCalculated(const std::string& airportFrom,
                                       const std::string& airportTo,
                                       bool isCostWeighted)
{
    std::cout << "A flight path is calculated between \""
              << airportFrom << "\" and \""
              << airportTo << "\" using "
              << ((isCostWeighted) ? "cost" : "price")
              <<  "." << std::endl;
}

void CENGFlight::PrintPathDontExist(const std::string& airportFrom,
                                    const std::string& airportTo)
{
    std::cout << "A flight path does not exists between \""
              << airportFrom << "\" and \""
              << airportTo <<"\"." << std::endl;
}

void CENGFlight::PrintSisterAirlinesDontCover(const std::string& airportFrom)
{
    std::cout << "Could not able to generate sister airline list from \""
              << airportFrom <<"\"." << std::endl;
}

void CENGFlight::PrintMap()
{
    navigationMap.PrintEntireGraph();
}

void CENGFlight::PrintCache()
{
    lruTable.PrintTable();
}

CENGFlight::CENGFlight(const std::string& flightMapPath)
    : navigationMap(flightMapPath)
{}

//=======================//
//          TODO         //
//=======================//

void CENGFlight::HaltFlight(const std::string& airportFrom,
                            const std::string& airportTo,
                            const std::string& airlineName)
{
    /* TODO */
    //find public methodunu yazıp ekle.



    try{
    HaltedFlight halted;
    halted.airline=airlineName;
    halted.airportFrom=airportFrom;
    halted.airportTo=airportTo;
    halted.w0=navigationMap.FindEdge(airlineName,airportFrom,airportTo).weight[0];
    halted.w1=navigationMap.FindEdge(airlineName,airportFrom,airportTo).weight[1];
    navigationMap.RemoveEdge(airlineName,airportFrom,airportTo);
    haltedFlights.push_back(halted);
    }
    catch(...){
        PrintCanNotHalt(airportFrom,airportTo,airlineName);

    }

}



    // (Direct Function call)
void CENGFlight::ContinueFlight(const std::string& airportFrom,
                                const std::string& airportTo,
                                const std::string& airlineName)
{
    /* TODO */
   try{
    int i=0;
    bool flag=false;
    for(;i<haltedFlights.size();i++){
        if((haltedFlights[i].airline==airlineName) && (haltedFlights[i].airportFrom==airportFrom) && (haltedFlights[i].airportTo==airportTo)) {
            flag=true;
            break;
        }
    }
    if(flag==false) throw EdgeNotFoundException(airportFrom,airlineName);

    navigationMap.AddEdge(airlineName,airportFrom,airportTo,haltedFlights[i].w0,haltedFlights[i].w1);
    haltedFlights.erase(haltedFlights.begin()+i);
   }
   catch(...) {
    PrintCanNotResumeFlight(airportFrom,airportTo,airlineName);
   }
}

void CENGFlight::FindFlight(const std::string& startAirportName,
                            const std::string& endAirportName,
                            float alpha)
{
    /* TODO */
        bool isCostWeighted=0;
        if(alpha==0) isCostWeighted=1; 
        std::vector<int> empty_array;
    try{
        int startInt= navigationMap.FindVertex(startAirportName);
        int endInt=navigationMap.FindVertex(endAirportName);



        if ((alpha==0 || alpha==1) && (lruTable.Find(empty_array,startInt,endInt,isCostWeighted,1)==true)) {
            if (alpha==0 || alpha==1) PrintFlightFoundInCache(startAirportName,endAirportName,isCostWeighted);
            navigationMap.PrintPath(empty_array,alpha,true);
            return;
        }
        else if(navigationMap.HeuristicShortestPath(empty_array,startAirportName,endAirportName,alpha)){
            if (alpha==0 || alpha==1) PrintFlightCalculated(startAirportName,endAirportName,isCostWeighted);
            navigationMap.PrintPath(empty_array,alpha,true);
            if(alpha==0 || alpha==1) lruTable.Insert(empty_array,isCostWeighted); //table capacity fullsa throwluyor
            return;
        }
        else PrintPathDontExist(startAirportName,endAirportName);
    }   
        catch(TableCapFullException&){
            lruTable.RemoveLRU(1);
            lruTable.Insert(empty_array,isCostWeighted);
        }
        catch(VertexNotFoundException&){
            PrintPathDontExist(startAirportName,endAirportName);
        }




    }

void CENGFlight::FindSpecificFlight(const std::string& startAirportName,
                                    const std::string& endAirportName,
                                    float alpha,
                                    const std::vector<std::string>& unwantedAirlineNames) const
{
    /* TODO */
        bool isCostWeighted=0;
        if(alpha==0) isCostWeighted=1;
   try{
        int startInt= navigationMap.FindVertex(startAirportName);
        int endInt=navigationMap.FindVertex(endAirportName);
        std::vector<int> empty_array;
        if(navigationMap.FilteredShortestPath(empty_array,startAirportName,endAirportName,alpha,unwantedAirlineNames)) {
            //if (alpha==0 || alpha==1) PrintFlightCalculated(startAirportName,endAirportName,isCostWeighted);
            navigationMap.PrintPath(empty_array,alpha,true);
            return;
        }
        else PrintPathDontExist(startAirportName,endAirportName);
    }
    catch(...){
        PrintPathDontExist(startAirportName,endAirportName);
    }
}
int CENGFlight::selecting_next_airport(const std::vector<bool> &visited, const std::vector<bool> &selected, int start)const {
    int i=0;
    int maks=0;
    int prospective=-1;
    for(;i<visited.size();i++){
        if(visited[i]==1 && selected[i]==0){
            GraphVertex temp=navigationMap.FindVertex(i);
            int count=0;
            for(int b=0;b<temp.edges.size();b++){
                if(visited[temp.edges[b].endVertexIndex]==0) count++;
            }
            if(count>maks) {
                maks=count;
                prospective=i;
            }  
        }
    }
    return prospective;
}
void CENGFlight::FindSisterAirlines(std::vector<std::string>& airlineNames,
                               const std::string& startAirlineName,
                               const std::string& airportName) const
{
    /* TODO */
    try{
    std::vector<bool> visited(navigationMap.GetSize(),0);
    std::vector<bool> selected(navigationMap.GetSize(),0);
    int prospective=navigationMap.FindVertex(airportName);
    std::vector<std::string> my_sisters;
    my_sisters.push_back(startAirlineName);
    visited[prospective]=1;
    selected[prospective]=1;
    bool bhr=true;
    bfs(visited,my_sisters,prospective,bhr);

    while(1){
        prospective=selecting_next_airport(visited,selected,prospective);
        if(prospective==-1){
            airlineNames=my_sisters;
            airlineNames.erase(airlineNames.begin());
            if(airlineNames.size()==0) PrintSisterAirlinesDontCover(airportName);
            return;
        }
        
        selected[prospective]=1;
        bool canselect=true;
        selecting_airline(visited,my_sisters,prospective,canselect);
        if(canselect==false){ PrintSisterAirlinesDontCover(airportName); return;}
        bool flag=false;
        bfs(visited,my_sisters,prospective,flag);
        bool finished=true;
            for(int g=0;g<visited.size();g++){
                if(visited[g]==0) finished=false;
            }
            if(flag==false && finished==false) { PrintSisterAirlinesDontCover(airportName); return;}
            if(flag==false) {
                my_sisters.pop_back();
                airlineNames=my_sisters;
                airlineNames.erase(airlineNames.begin());
                if(airlineNames.size()==0) PrintSisterAirlinesDontCover(airportName);
                return;
            } 
    }
    }
    catch(...){
        PrintSisterAirlinesDontCover(airportName);
    }
}

void CENGFlight::bfs(std::vector<bool> &visited,std::vector<std::string>& airlineNames,
                                    const int start_index,bool &flag) const
{   

    std::vector<bool> known(navigationMap.GetSize(),0);
    MaxPairHeap<int, int>  my_que;
    Pair<int,int> temp;
    temp.key=1;
    temp.value=start_index;
    my_que.push(temp);

    while(!my_que.empty()) {
        int curr_vertex_index= my_que.top().value; //yani şimdi edgelerini gezeceğimiz vertexin indexi
        my_que.pop();
        if(known[curr_vertex_index]==1) continue;
        GraphVertex temp=navigationMap.FindVertex(curr_vertex_index);
        visited[curr_vertex_index]=1;
        for(int b=0; b<temp.edges.size();b++){
            int adj=temp.edges[b].endVertexIndex;
            bool isIn=false;
            for(int j=0;j<airlineNames.size();j++){
                if(airlineNames[j]==temp.edges[b].name) {isIn=true; break;}
            }
            if(visited[adj]==0 && isIn ){
                Pair<int,int> new_vertex;
                new_vertex.key=1;
                new_vertex.value=adj;
                my_que.push(new_vertex);
                visited[adj]=1;
                flag=true;
            }
        }
    }

}

void CENGFlight::selecting_airline(std::vector<bool> &visited, std::vector<std::string>& airlineNames,
                                    const int start_index, bool &canselect) const
{   
        GraphVertex temp=navigationMap.FindVertex(start_index);
        for(int b=0; b<temp.edges.size();b++){
            int adj=temp.edges[b].endVertexIndex;
            bool flag=false;
            for(int j=0;j<airlineNames.size();j++){
                if(temp.edges[b].name==airlineNames[j]|| visited[temp.edges[b].endVertexIndex]==1) {flag=true; break;}
            }
            if(flag==false) {
                std::string new_airline=temp.edges[b].name;
                airlineNames.push_back(temp.edges[b].name);
                return;
            }
        }
            canselect=false;
    }





int CENGFlight::FurthestTransferViaAirline(const std::string& airportName,
                                           const std::string& airlineName) const
{
    try{
        return navigationMap.MaxDepthViaEdgeName(airportName,airlineName);
    }
    catch(...){
        return -1;
    }
}