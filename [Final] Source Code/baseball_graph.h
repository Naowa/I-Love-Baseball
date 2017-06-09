#ifndef BASEBALL_GRAPH_H
#define BASEBALL_GRAPH_H
#include <Graph.h>
#include <stadium.h>

class Baseball_Graph : public Graph<ILB::Stadium,int>
{
public:
    Baseball_Graph();
    Baseball_Graph(int);
    bool initialize_from_file(std::string file_name,int);//int default is 0=initialize edge values, 1=initialize stadiums(american), 2=initialize stadiums(national)
    std::string* get_vert_name(); //return stadium name
    void update_stadium(ILB::Stadium); //update an existing Stadium
    ILB::Stadium& get_stadium(std::string); //returns a copy of the stadium requested
    ILB::Stadium& get_stadium_admin(std::string); //returns the address of stadium object from graph
    int* shortest_path(std::string, std::string); //returns distances then # of stadiums visited of shortest path
    int* shortest_path(ILB::Stadium,ILB::Stadium); //returns distances then # of stadiums visited of shortest path
    int* planned_path(std::string*,int); //returns distances then # of stadiums visited of planned path
    int find_index(std::string); //returns index of the stadium in the graph
    bool vertice_exists(std::string); //returns true if a stadium with a matching name exists
    int find_index(ILB::Stadium); //returns index of the stadium in the graph
    bool vertice_exists(ILB::Stadium); //returns true if a stadium with a matching name exists
    int shortest_ham_path(int); //returns distance of shortest hamitonian path
    int get_american_count(); //returns number of american stadiums
    int get_national_count(); //returns number of national stadiums
//    void addEdge(std::string src, ILB::Stadium dest, int dist);






};

#endif // BASEBALL_GRAPH_H
