#include <iostream>
#include <baseball_graph.h>
#include <american_stadium.h>
void printstadium(ILB::Stadium&);
using namespace std;

int main()
{
//    Graph<string,int> g(20);

//    g.addEdge("6","7",1);
//    g.addEdge("6","5",2);
//    g.addEdge("2","8",2);
//    g.addEdge("5","2",4);
//    g.addEdge("0","1",4);
//    g.addEdge("8","6",6);
//    g.addEdge("2","3",7);
//    g.addEdge("8","7",7);
//    g.addEdge("0","7",8);
//    g.addEdge("1","2",8);
//    g.addEdge("3","4",9);
//    g.addEdge("4","5",10);
//    g.addEdge("1","7",11);
//    g.addEdge("3","5",14);



//    g.show();
//    cout << "\n";
//    cout << "Test 2: \n";
//   cout << "Vertex   Distance from Source\n";
//    void** temp2=g.dijkstra("0");
//    int* distances=(int*)temp2[1];
//    int* visits=(int*)temp2[2];

//    for(int i=0; i<g.get_vcount(); i++){
//        cout << distances[i] << endl;
//        cout << visits[i] << endl;
//    }
//        ILB::Stadium s("asdf");
//        Vertex<string> v("asdf");

    //    cout << v;
//    Baseball_Graph g(50);
//    g.addVertex(*(new ILB::Stadium("Yankee")));

    int* temp=new int[10];
    for(int i=0; i<10; i++)
        temp[i]=i;



//    if(g.initialize_from_file("ILB Weights - Sheet1.csv"))
//    {
//        g.show();
//    }
//    else
//        cout << "failed";


//ILB::Stadium temp("Yankee");
//int* temp2=g.dijkstra(temp);
//if(g.vertice_exists(temp))
//    cout << "yes";
//for(int i=0; i<g.get_vcount(); i++)
//    cout << temp2[i] << endl;

//    American_Stadium asdf;
//    asdf.set_stadium_name("Kenny");
//    ILB::Stadium b("Kenny");
//    if(b==asdf){
//        cout << "yes";
//    }
    return 0;
}
void printstadium(ILB::Stadium& b){
    cout << b.get_type() << endl;

}
