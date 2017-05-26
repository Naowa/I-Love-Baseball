#include "baseball_graph.h"
#include "sstream"
#include "assert.h"
#include "iostream"
#include "fstream"
#include "cstdlib"

Baseball_Graph::Baseball_Graph()
{
}
void Baseball_Graph::show(){
    for(int i=0; i<active_v; i++){
        for(int j=0; j<active_v; j++)
             std::cout<< "From vert: " << array[i]->vert.get_stadium_name() << " to vert: " << array[j]->vert.get_stadium_name() << " is weight " << array[i]->weights[j] << std::endl;
    }


}
bool Baseball_Graph::initialize_from_file(std::string file_name){
       std::ifstream file;
       file.open(file_name.c_str());
       assert(file.is_open());

       std::string line;

       std::string cell_value;
           int isEOF = 0;
getline( file, line );
           for(int i=0;isEOF != EOF && std::getline( file, line); i++){
               std::stringstream line_stream(line);
               std::getline(line_stream,cell_value, ',');
               array[i]=new AdjList<ILB::Stadium,int>(30);
//               std::cout<<cell_value << " ";
                       array[i]->vert.set_stadium_name(cell_value);

                    for(int j=0;getline(line_stream, cell_value, ',' );j++){
                        std::stringstream cell_stream;
                        cell_stream << cell_value;
                        int temp_int;
                        cell_stream >> temp_int;
//                        std::cout<<temp_int << " ";
                        this->array[i]->weights[j]=temp_int;
                    }
//                    std::cout << std::endl;
                    this->active_v++;
        isEOF = file.peek();
           }


           return true;

}

std::string* Baseball_Graph::get_vert_name(){

             std::string* temp=new std::string[active_v];
             ILB::Stadium* temp2=get_vert();
             for(int i=0; i<active_v; i++)
                 temp[i]=temp2[i].get_stadium_name();

             return temp;

}
