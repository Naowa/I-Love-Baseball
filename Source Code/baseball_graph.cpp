#include "baseball_graph.h"
#include "sstream"
#include "assert.h"
#include "iostream"
#include "fstream"
#include "cstdlib"

Baseball_Graph::Baseball_Graph():Graph(){}
Baseball_Graph::Baseball_Graph(int n):Graph(n){}

void Baseball_Graph::show(){
    for(int i=0; i<active_v; i++){
        for(int j=0; j<active_v; j++)
             std::cout<< "From vert: " << array[i]->vert << " to vert: " << array[j]->vert << " is weight " << array[i]->weights[j] << std::endl;
    }


}
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
        getline( file, line );
        getline( file, line );
        getline(file,line);
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
           getline(file,line,'-');
           getline(file,month,' ');
           for(int i=1; i<13; i++){
           if(month==all_months[i])
               date_opened="0"+std::to_string(i)+'/';
           }
           getline(file,line,',');
           date_opened=date_opened+line+'/';
           getline(file,line);
           date_opened=date_opened+line;
           getline(file,line, '-');
           getline(file,line,',');
           seating_cap=std::stoi(line)*1000;
           getline(file,line);
           seating_cap=seating_cap+stoi(line);
           ILB::Stadium temp(name,team_name,street_name,city_state_zip,box_office_num,date_opened,seating_cap,true,true);
           if(this->vertice_exists(name)){
               update_stadium(temp);
           }
           getline(file,line);



        }
        return true;

}else if(type==2){
    getline( file, line );
    getline( file, line );
    getline(file,line);
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
       getline(file,line,'-');
       getline(file,month,' ');
       for(int i=1; i<13; i++){
       if(month==all_months[i])
           date_opened="0"+std::to_string(i)+'/';
       }
       getline(file,line,',');
       date_opened=date_opened+line+'/';
       getline(file,line);
       date_opened=date_opened+line;
       getline(file,line, '-');
       getline(file,line,',');
       seating_cap=std::stoi(line)*1000;
       getline(file,line);
       seating_cap=seating_cap+stoi(line);
       ILB::Stadium temp(name,team_name,street_name,city_state_zip,box_office_num,date_opened,seating_cap,false,true);
       if(this->vertice_exists(name)){
           update_stadium(temp);
       }
       getline(file,line);



    }
    return true;

}

}



void Baseball_Graph::update_stadium(ILB::Stadium B){
    if(this->vertice_exists(B))
        this->array[this->find_index(B)]->vert=B;
}

ILB::Stadium& Baseball_Graph::get_stadium_admin(std::string name){
    for(int i=0; i<active_v; i++){
    if(this->array[i]->vert.get_name()==name)
        return array[i]->vert;
    }

}

ILB::Stadium& Baseball_Graph::get_stadium(std::string name){
    for(int i=0; i<active_v; i++){
    if(this->array[i]->vert.get_name()==name)
        return *(new ILB::Stadium(array[i]->vert));
    }

}

int* Baseball_Graph::shortest_path(ILB::Stadium A, ILB::Stadium B){
    void** temp=this->dijkstra(A);
    int* distances=(int*)temp[0];
    int* visits=(int*)temp[1];
    int* info= new int[2];
    info[0]=distances[this->find_index(B)];
    info[1]=visits[this->find_index(B)];

    return info;
}

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


int* Baseball_Graph::planned_path(std::string* planned_stadiums, int planned_visits){
   int* info= new int[2];
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

int Baseball_Graph::find_index(std::string src){

    for(int i=0; i<active_v; i++){
        if(src==array[i]->vert.get_name())
            return i;
  }
    return -1;
}
bool Baseball_Graph::vertice_exists(std::string src){
    for(int i=0; i<active_v; i++){
        if(src==array[i]->vert.get_name()){
            return true;
        }
  }

    return false;
}
int Baseball_Graph::find_index(ILB::Stadium src){

    for(int i=0; i<active_v; i++){
        if(src.get_name()==array[i]->vert.get_name())
            return i;
  }
    return -1;
}
bool Baseball_Graph::vertice_exists(ILB::Stadium src){
    for(int i=0; i<active_v; i++){
        if(src.get_name()==array[i]->vert.get_name()){
            return true;
        }
  }

    return false;
}
