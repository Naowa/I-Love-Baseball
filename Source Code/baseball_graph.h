#ifndef BASEBALL_GRAPH_H
#define BASEBALL_GRAPH_H
#include <Graph.h>
#include <stadium.h>

class Baseball_Graph : public Graph<ILB::Stadium,int>
{
public:
    Baseball_Graph();
    Baseball_Graph(int);
    bool initialize_from_file(std::string file_name);
    std::string* get_vert_name();
    void show();
    void update_stadium(ILB::Stadium);
    ILB::Stadium& get_stadium(std::string);
    ILB::Stadium& get_stadium_admin(std::string);
    int* shortest_path(std::string, std::string);
    int* shortest_path(ILB::Stadium,ILB::Stadium); //returns distances then # of stadiums visited
    int* planned_path(std::string*,int);




};

#endif // BASEBALL_GRAPH_H
