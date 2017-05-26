#include <iostream>
#include <baseball_graph.h>
using namespace std;

int main()
{
    Baseball_Graph g;

    if(g.initialize_from_file("ILB Weights - Sheet1.csv"))
    {
        g.show();
    }
    else
        cout << "failed";

    cout << "finished";
    return 0;
}

