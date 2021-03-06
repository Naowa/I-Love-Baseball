#include "baseball_graph.h"
#include "sstream"
#include "assert.h"
#include "iostream"
#include "fstream"
#include "cstdlib"
/**********************************************************
 *
 * Baseball_Graph()
 *_________________________________________________________
 * Constructor
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 *
 *
 **********************************************************/

//O(n)
Baseball_Graph::Baseball_Graph():Graph(){}
/**********************************************************
 *
 * See Graph(int)
 *_________________________________________________________
 * Constructor
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 *
 *
 **********************************************************/

//O(n)
Baseball_Graph::Baseball_Graph(int n):Graph(n){}
/**********************************************************
 *
 * initialize_from_file
 *_________________________________________________________
 * initialize graph with file
 *_________________________________________________________
 * PRE-CONDITIONS
 * a valid filename to a file that is formatted according
 * to pdf from canvas
 *
 **********************************************************/

//O(n)
bool Baseball_Graph::initialize_from_file(std::string file_name, int type=0){ //0=initialize edge values, 1=initialize stadiums(american), 2=initialize stadiums(national)
       std::ifstream file;
       file.open(file_name.c_str());
       assert(file.is_open());
       std::string line;

       std::string cell_value;
           int isEOF = 0;

if(type==0){
           getline( file, line );
           for(int i=0;isEOF != EOF && std::getline( file, line); i++){
               std::stringstream line_stream(line);
               std::getline(line_stream,cell_value, ',');
               array[i]=new AdjList<ILB::Stadium,int>(30);
                       array[i]->vert.set_stadium_name(cell_value);

                    for(int j=0;getline(line_stream, cell_value, ',' );j++){
                        std::stringstream cell_stream;
                        cell_stream << cell_value;
                        int temp_int;
                        cell_stream >> temp_int;
                        this->array[i]->weights[j]=temp_int;
                    }
                this->active_v++;
                isEOF = file.peek();
           }
           return true;
}
else if(type==1){
//        getline( file, line );
//        getline( file, line );
//        getline(file,line);
        while(getline(file,line)){
            std::string name,team_name,street_name,city_state_zip,box_office_num, date_opened;
            std::string month;
            std::string all_months[13]={"","January", "Feburary", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
            int seating_cap;

           name=line;

           getline(file,team_name);

           getline(file,street_name);
           getline(file,city_state_zip);
           getline(file,box_office_num);
           file.ignore(9);
           getline(file,month, ' ');

           for(int i=1; i<13; i++){
           if(month==all_months[i])
               date_opened="0"+std::to_string(i)+'/';
           }

           getline(file,line,',');
           if(isdigit(line[0])){
           int day=std::stoi(line);
           if(day<10)
               line='0'+line;
           }
           date_opened=date_opened+line+'/';
           file.ignore(1);
           getline(file,line);
           date_opened=date_opened+line;


           file.ignore(11);

           getline(file,line,',');
           seating_cap=std::stoi(line)*1000;

           getline(file,line);
           seating_cap=seating_cap+stoi(line);

           ILB::Stadium temp(name,team_name,street_name,city_state_zip,box_office_num,date_opened,seating_cap,true,true);

           if(vertice_exists(name)){
               update_stadium(temp);

           }


                getline(file,line);
                if(file.peek()=='\n')
                    getline(file,line);




        }
        return true;

}else if(type==2){

    while(isEOF != EOF&&getline(file,line)){
        std::string name,team_name,street_name,city_state_zip,box_office_num, date_opened;
        std::string month;
        std::string all_months[13]={"","January", "Feburary", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
        int seating_cap;

       name=line;
       getline(file,team_name);
       getline(file,street_name);
       getline(file,city_state_zip);
       getline(file,box_office_num);
       file.ignore(9);
       getline(file,month, ' ');

       for(int i=1; i<13; i++){
       if(month==all_months[i])
           date_opened="0"+std::to_string(i)+'/';
       }

       getline(file,line,',');
       if(isdigit(line[0])){
        int day=std::stoi(line);
       if(day<10)
           line='0'+line;
       }
       date_opened=date_opened+line+'/';
       file.ignore(1);
       getline(file,line);
       date_opened=date_opened+line;


       file.ignore(11);

       getline(file,line,',');
       if(isdigit(line[0]))
       seating_cap=std::stoi(line)*1000;

       getline(file,line);
       if(isdigit(line[0]))
       seating_cap=seating_cap+stoi(line);

       ILB::Stadium temp(name,team_name,street_name,city_state_zip,box_office_num,date_opened,seating_cap,false,true);

       if(this->vertice_exists(name)){
           update_stadium(temp);
       }
       getline(file,line);

       if(file.peek()=='\n')
           getline(file,line);



    }
    return true;

}

}


/**********************************************************
 *
 * update_stadium
 *_________________________________________________________
 * updates existing stadium with the same name
 *_________________________________________________________
 * PRE-CONDITIONS
 * a valid stadium
 *
 *
 **********************************************************/

//O(1)
void Baseball_Graph::update_stadium(ILB::Stadium B){
    if(this->vertice_exists(B))
        this->array[this->find_index(B)]->vert=B;
}
/**********************************************************
 *
 * get_stadium_admin
 *_________________________________________________________
 * returns the address of a stadium in the graph
 *_________________________________________________________
 * PRE-CONDITIONS
 * A valid string must be entered
 *
 *
 **********************************************************/

//O(n)
ILB::Stadium& Baseball_Graph::get_stadium_admin(std::string name){
    for(int i=0; i<active_v; i++){
    if(this->array[i]->vert.get_name()==name)
        return array[i]->vert;
    }

}
/**********************************************************
 *
 * get_stadium
 *_________________________________________________________
 * returns a copy of a stadium in the graph
 *_________________________________________________________
 * PRE-CONDITIONS
 * A valid string must be entered
 *
 *
 **********************************************************/

//O(n)
ILB::Stadium& Baseball_Graph::get_stadium(std::string name){
    for(int i=0; i<active_v; i++){
    if(this->array[i]->vert.get_name()==name)
        return *(new ILB::Stadium(array[i]->vert));
    }

}
/**********************************************************
 *
 * shortest_path
 *_________________________________________________________
 * returns distance and numbers of stadiums visited
 *_________________________________________________________
 * PRE-CONDITIONS
 * 2 unique and valid stadiums
 *
 *
 **********************************************************/

//O(1)
int* Baseball_Graph::shortest_path(ILB::Stadium A, ILB::Stadium B){
    void** temp=this->dijkstra(A);
    int* distances=(int*)temp[0];
    int* visits=(int*)temp[1];
    int* info= new int[2];
    info[0]=distances[this->find_index(B)];
    info[1]=visits[this->find_index(B)];

    return info;
}
/**********************************************************
 *
 * shortest_path
 *_________________________________________________________
 * returns distance and numbers of stadiums visited
 *_________________________________________________________
 * PRE-CONDITIONS
 * 2 unique and valid stadium names
 *
 *
 **********************************************************/

//O(1)
int* Baseball_Graph::shortest_path(std::string a, std::string b){
    ILB::Stadium A(a);
    ILB::Stadium B(b);
    void** temp=this->dijkstra(A);
    int* distances=(int*)temp[0];
    int* visits=(int*)temp[1];
    int* info= new int[2];
    info[0]=distances[this->find_index(B)];
    info[1]=visits[this->find_index(B)];

    return info;
}

/**********************************************************
 *
 * planned path
 *_________________________________________________________
 * returns distance and stadiums visited for an array of valid stadiums
 *_________________________________________________________
 * PRE-CONDITIONS
 * an array of valid and existing stadiums
 *
 *
 **********************************************************/

//O(n)
int* Baseball_Graph::planned_path(std::string* planned_stadiums, int planned_visits){
   int* info= new int[2];
   info[0]=0;
   info[1]=0;
   ILB::Stadium current(planned_stadiums[0]);
   for(int i=1; i<planned_visits; i++){
       ILB::Stadium next(planned_stadiums[i]);
       int* segment_value=this->shortest_path(current,next);
       info[0]+=segment_value[0];
       info[1]+=segment_value[1];
       current=next;
   }
   return info;

}
/**********************************************************
 *
 * find_index
 *_________________________________________________________
 * returns index of stadium by name
 *_________________________________________________________
 * PRE-CONDITIONS
 * valid stadium name
 *
 *
 **********************************************************/

//O(n)
int Baseball_Graph::find_index(std::string src){

    for(int i=0; i<active_v; i++){
        if(src==array[i]->vert.get_name())
            return i;
  }
    return -1;
}
/**********************************************************
 *
 * vertice_exists
 *_________________________________________________________
 * returns if a vertex exists by name
 *_________________________________________________________
 * PRE-CONDITIONS
 * a string containing the name of a vertex
 *
 *
 **********************************************************/

//O(n)
bool Baseball_Graph::vertice_exists(std::string src){
    for(int i=0; i<active_v; i++){
        if(src==array[i]->vert.get_stadium_name()){
            return true;
        }
  }

    return false;
}
/**********************************************************
 *
 * find_index
 *_________________________________________________________
 * returns index of stadium by name
 *_________________________________________________________
 * PRE-CONDITIONS
 * valid stadium name
 *
 *
 **********************************************************/

//O(n)
int Baseball_Graph::find_index(ILB::Stadium src){

    for(int i=0; i<active_v; i++){
        if(src.get_name()==array[i]->vert.get_name())
            return i;
  }
    return -1;
}
/**********************************************************
 *
 * vertice_exists
 *_________________________________________________________
 * returns if a vertex exists by name
 *_________________________________________________________
 * PRE-CONDITIONS
 * a string containing the name of a vertex
 *
 *
 **********************************************************/

//O(n)
bool Baseball_Graph::vertice_exists(ILB::Stadium src){
    for(int i=0; i<active_v; i++){
        if(src.get_name()==array[i]->vert.get_name()){
            return true;
        }
  }

    return false;
}
/**********************************************************
 *
 * shortest_ham_path
 *_________________________________________________________
 * returns distance of the shortest hamitonian path
 *_________________________________________________________
 * PRE-CONDITIONS
 * None
 *
 *
 **********************************************************/

//O(2^n)
int Baseball_Graph::shortest_ham_path(int path){
//   int p[active_v];
//   int key[active_v];
//   bool set[active_v];

//   for(int i=0; i<active_v; i++)
//       p[i]=0,key[i]=INT_MAX, set[i]=false;

//   key[0]=0;
//   p[0]=-1;
//if(path==2){
//   for(int i=0; i<active_v-1; i++){
//       int min=INT_MAX,min_i=0;

//       for(int j=0; j<active_v; j++)
//           if(set[j]==false && key[j]<min && array[j]->vert.if_national_leauge())
//               min=key[j],min_i=j;
//       int k=min_i;
//       set[k]=true;

//       for(int l=0; l<active_v; l++){
//           if(array[l]->weights[k]&& set[k] == false && array[l]->weights[k] <key[l] && array[l]->weights[k] >=0 && !array[l]->vert.if_american_league())
//               p[l]=k,key[l]=array[l]->weights[k];
//       }
//   }
//   int sum=0;
//   for(int i=1; i<15; i++){
//       if(array[i]->weights[p[i]]>=0){
//       sum+=array[i]->weights[p[i]];
//       }
//   }

//   return sum;
//}
//else if(path==1){
//    for(int i=0; i<active_v-1; i++){
//        int min=INT_MAX,min_i=0;

//        for(int j=0; j<active_v; j++)
//            if(set[j]==false && key[j]<min && array[j]->vert.if_american_league())
//                min=key[j],min_i=j;
//        int k=min_i;
//        set[k]=true;

//        for(int l=0; l<active_v; l++){
//            if(array[k]->weights[l]&& set[k] == false && array[k]->weights[l] <key[l] && array[k]->weights[l] >=0 && array[l]->vert.if_american_league())
//                p[l]=k,key[l]=array[k]->weights[l];
//        }
//    }
//    int sum=0;
//    for(int i=1; i<15; i++){
//        if(array[i]->weights[p[i]]>=0){
//        sum+=array[i]->weights[p[i]];
//        }
//    }

//    return sum;
// }
//else if(path==0){
//    for(int i=0; i<active_v-1; i++){
//        int min=INT_MAX,min_i=0;

//        for(int j=0; j<active_v; j++)
//            if(set[j]==false && key[j]<min)
//                min=key[j],min_i=j;
//        int k=min_i;
//        set[k]=true;

//        for(int l=0; l<active_v; l++){
//            if(array[l]->weights[k]&& set[k] == false && array[l]->weights[k] <key[l] && array[l]->weights[k] >=0)
//                p[l]=k,key[l]=array[l]->weights[k];
//        }
//    }
// }

//   int sum=0;
//   for(int i=1; i<active_v; i++){
//       if(array[i]->weights[p[i]]>=0){
//       sum+=array[i]->weights[p[i]];
//       }
//   }

//   return sum;
    int temp2[15];
    int* temp=temp2;
    for(int i=0; i<active_v; i++){
        if(array[i]->vert.if_american_league()){
            *temp=i;
            temp++;
        }
    }
    int n=0;
    int sum=0;
    if(path==0)
         n=active_v;
    else
         n=active_v;

    int key[n];
        bool in_mst[n];
        int parent[n];


        for (int v = 0; v < n; v++) {

            key[v] = INT_MAX;


            in_mst[v] = false;
        }

        key[0] = 0;
        parent[0] = -1;

        for (int i = 0; i < n - 1; i++) {

            int v;

                int min = INT_MAX;
                int min_index;
                for (v = 0; v < n; v++)
                    if (in_mst[v] == false && key[v] < min) {
                        min = key[v];
                        min_index = v;
                    }
                v= min_index;



            in_mst[v] = true;

if(path==0){
            for (int u = 0; u < n; u++) {
                if (array[v]->weights[u] && in_mst[u] == false && array[v]->weights[u] < key[u] && array[v]->weights[u]>=0) {

                    parent[u] = v;

                    key[u] = array[v]->weights[u];
                }
            }
}
else if(path==1){
            for (int u = 0; u < n; u++) {
                if (array[v]->weights[u] && in_mst[u] == false && array[v]->weights[u] < key[u] && array[v]->weights[u]>=0 && array[u]->vert.if_american_league()) {

                    parent[u] = v;

                    key[u] = array[v]->weights[u];
                }
            }
}
else if(path==2){
    for (int u = 0; u < n; u++) {
        if (array[v]->weights[u] && in_mst[u] == false && array[v]->weights[u] < key[u] && array[v]->weights[u]>=0 && !array[u]->vert.if_american_league()) {

            parent[u] = v;

            key[u] = array[v]->weights[u];
        }
    }
}



}

for(int i=0; i<active_v; i++){
    if(key[i]>=0 && key[i]<3000){
        sum=key[i]+sum;
    }
}
return sum;
}

/**********************************************************
 *
 * get_american_count
 *_________________________________________________________
 * returns number of american stadiums
 *_________________________________________________________
 * PRE-CONDITIONS
 * None
 *
 *
 **********************************************************/

//O(n)
int Baseball_Graph::get_american_count(){
    int count=0;
    for(int i=0; i<active_v; i++)
        if(array[i]->vert.get_american_league())
            count++;

    return count;
}
/**********************************************************
 *
 * get_national_count
 *_________________________________________________________
 * returns number of national stadiums
 *_________________________________________________________
 * PRE-CONDITIONS
 * None
 *
 **********************************************************/

//O(n)
int Baseball_Graph::get_national_count(){
    int count=0;
    for(int i=0; i<active_v; i++)
        if(!array[i]->vert.get_american_league())
            count++;

    return count;
}

//void Baseball_Graph::addEdge(std::string src, ILB::Stadium dest, int dist){
//    ILB::Stadium temp(src);
//    this->Graph::addEdge(temp,dest,dist);
//}
