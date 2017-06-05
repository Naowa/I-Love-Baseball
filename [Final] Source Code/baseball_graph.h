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
    std::string* get_vert_name();
    void show();
    void update_stadium(ILB::Stadium);
    ILB::Stadium& get_stadium(std::string);
    ILB::Stadium& get_stadium_admin(std::string);
    int* shortest_path(std::string, std::string);
    int* shortest_path(ILB::Stadium,ILB::Stadium); //returns distances then # of stadiums visited
    int* planned_path(std::string*,int);
    int find_index(std::string);
    bool vertice_exists(std::string);
    int find_index(ILB::Stadium);
    bool vertice_exists(ILB::Stadium);




};

#endif // BASEBALL_GRAPH_H
