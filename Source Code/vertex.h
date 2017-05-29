#ifndef VERTEX_H
#define VERTEX_H

#include "iostream"
template <typename Vertex_Name_Type>
class Vertex
{
public:
    Vertex(){
        this->name="";
    }

    Vertex(Vertex_Name_Type n){
        name=n;
    }

    friend std::ostream& operator << (std::ostream& os, const Vertex<Vertex_Name_Type>& B){
        os<<B.get_name();
        return os;
    }
    virtual bool operator == (Vertex<Vertex_Name_Type> B){
        return(this->name == B.name);

    }
    virtual Vertex_Name_Type get_name() const{
        return name;
    }

    virtual Vertex& operator=(const Vertex& B){
        this->name=B.name;
        return *this;
    }

protected:

    Vertex_Name_Type name;
};


#endif // VERTEX_H
