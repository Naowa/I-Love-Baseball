#include <iostream>
#include <vertex.h>
template <typename v,typename w>
struct AdjList
{

    AdjList(v V, int n){

    vert=V;
    weights=new w[n];
    for(int i=0; i<n; i++){
        weights[i]=-1;
       }

    }
    AdjList(int n){
    weights=new w[n];
    for(int i=0; i<n; i++){
        weights[i]=-1;
       }

    }

     v vert;
     w* weights;
};

template <typename v, typename w>
class Graph
{
    protected:
        int vertices; //MAX
        AdjList<v,w>** array=NULL;
        int active_v;




    public:
        /**********************************************************
         *
         * Graph()
         *_________________________________________________________
         * Constructor
         *_________________________________________________________
         * PRE-CONDITIONS
         * None
         *
         *
         **********************************************************/

        //O(1)
        Graph(){
            this->vertices = 20;
            this->active_v=0;
            this->array=new AdjList<v,w>*[vertices];
            for(int i=0; i<vertices; i++)
                this->array[i]=NULL;
        }
        /**********************************************************
         *
         * Graph(int)
         *_________________________________________________________
         * Constructor that initialize the Graph with int V number of arrays
         *_________________________________________________________
         * PRE-CONDITIONS
         * None
         *
         *
         **********************************************************/

        //O(1)
        Graph(int V)
        {
            this->vertices = V;
            this->active_v=0;
            this->array=new AdjList<v,w>*[vertices];
            for(int i=0; i<vertices; i++)
                this->array[i]=NULL;

            }
        /**********************************************************
         *
         * return_weight
         *_________________________________________________________
         * returns the weight of an edge
         *_________________________________________________________
         * PRE-CONDITIONS
         * 2 valid and unique vertices
         *
         *
         **********************************************************/

        //O(1)
        w return_weight(v A,v B){
            if(vertice_exists(A)&&vertice_exists(B))
                return(array[find_index(A)]->weights[find_index(B)]);
        }
        /**********************************************************
         *
         * get_vcount
         *_________________________________________________________
         * returns number of active vertices
         *_________________________________________________________
         * PRE-CONDITIONS
         *
         *
         *
         **********************************************************/

        //O(1)
        int get_vcount()const{
            return active_v;
        }
        /**********************************************************
         *
         * find_index
         *_________________________________________________________
         * returns index of vertex
         *_________________________________________________________
         * PRE-CONDITIONS
         * A valid vertex
         *
         *
         **********************************************************/

        //O(n)
        virtual int find_index(v src){

            for(int i=0; i<active_v; i++){
                if(src==array[i]->vert)
                    return i;
          }
            return -1;
        }
        /**********************************************************
         *
         * vertice_exists(v)
         *_________________________________________________________
         * returns if a Vertex exists in the graph
         *_________________________________________________________
         * PRE-CONDITIONS
         * any vertex
         *
         *
         **********************************************************/

        //O(n)
        virtual bool vertice_exists(v src){
            for(int i=0; i<active_v; i++){
                if(src==array[i]->vert){
                    return true;
                }
          }

            return false;
        }


        /**********************************************************
         *
         * addVertex(v src);
         *_________________________________________________________
         * adds a Vertex to the Graph
         *_________________________________________________________
         * PRE-CONDITIONS
         * Any vertex
         *
         *
         **********************************************************/

        //O(1)

        void addVertex(v src){
            if(vertice_exists(src)){
                return;
            }
            array[active_v]=new AdjList<v,w>(src, vertices);
            active_v++;
            return;
        }


        /**********************************************************
         *
         * addEdge
         *_________________________________________________________
         * Adds an edge between 2 different vertices
         *_________________________________________________________
         * PRE-CONDITIONS
         * at least 1 valid and existing vertex and 1 vertex
         * a valid weight
         *
         **********************************************************/

        //O(n)
        void addEdge(v src, v dest, w weight)
        {

        int src_index=active_v;

        if(vertice_exists(src)){

            src_index=find_index(src);
        }
        else{
            array[src_index]=new AdjList<v,w>(src, vertices);
            active_v++;

        }

        int dest_index=active_v;

        if(vertice_exists(dest)){
            dest_index=find_index(dest);
        }
        else{

            array[dest_index]=new AdjList<v,w>(dest,vertices);

            active_v++;
        }

        array[src_index]->weights[src_index]=0;
        array[dest_index]->weights[dest_index]=0;
        array[src_index]->weights[dest_index]=weight;
        array[dest_index]->weights[src_index]=weight;


        }





          /**********************************************************
           *
           * dijkstra
           *_________________________________________________________
           * find shortest path to every vertex from a source vertex
           *_________________________________________________________
           * PRE-CONDITIONS
           * A valid vertex
           *
           *
           **********************************************************/

          //O(n^2)
        void** dijkstra(v src){

          w* dist=new w[active_v];
          int* v_visit=new int[active_v];
          bool spt[active_v];

          for(int i=0;i<active_v; i++){
            dist[i]=INT_MAX;
            spt[i]=false;
            v_visit[i]=0;
          }
          dist[find_index(src)]=0;

          for(int i=0; i<active_v; i++){
              int n=INT_MAX;
              int candidate;
              for(int j=0; j<active_v; j++){

                  if (spt[j]==false && dist[j] <=n && dist[j] >= 0){
                      n=dist[j];
                      candidate=j;

                  }

              }
              int index=candidate;

              spt[index]=true;

         for(int j=0; j<active_v; j++){

             if(!spt[j] && array[index]->weights[j] && (dist[index]+array[index]->weights[j])<dist[j] && array[index]->weights[j]>=0){
                 v_visit[j]=v_visit[candidate];
                 v_visit[j]++;
                 dist[j]=dist[index]+array[index]->weights[j];

             }


           }

         }

          void** return_this=new void*[2];
          return_this[0]=dist;
          return_this[1]=v_visit;


          return return_this; //Extract with     int* distances=(int*)temp2[0];
                              //                 int* visits=(int*)temp2[1];
                              //For Graph<int,Vertex>

     }
        /**********************************************************
         *
         * get_vert()
         *_________________________________________________________
         * returns an array of all the vertex (copy)
         *_________________________________________________________
         * PRE-CONDITIONS
         * None
         *
         *
         **********************************************************/

        //O(n)

       v* get_vert(){

                     v* temp=new v[active_v];
                     for(int i=0; i<active_v; i++)
                         temp[i]=this->array[i]->vert;

                     return temp;

        }
       /**********************************************************
        *
        * Graph(Graph &B)
        *_________________________________________________________
        * Copy constructor
        *_________________________________________________________
        * PRE-CONDITIONS
        * Another graph
        *
        *
        **********************************************************/

       //O(n^2)
       Graph(Graph& B){
           this->vertices = B.vertices*2;
           this->active_v=0;
           this->array=new AdjList<v,w>*[vertices];
           for(int i=0; i<vertices; i++){
               this->array[i]->vert=B.array[i]->vert;
                for(int j=0; j<active_v; j++){
                    this->array[i]->weights[j]=B.array[i]->weights[j];
                }
           }
       }



};
