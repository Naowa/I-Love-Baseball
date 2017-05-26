#ifndef BASEBALL_GRAPH_H
#define BASEBALL_GRAPH_H
#include <Graph.h>
#include <stadium.h>
class Baseball_Graph : public Graph<ILB::Stadium,int>
{
public:
    Baseball_Graph();
    bool initialize_from_file(std::string file_name);
    std::string* get_vert_name();
    void show();



};

#endif // BASEBALL_GRAPH_H
