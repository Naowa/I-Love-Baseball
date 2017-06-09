#ifndef VERTEX_H
#define VERTEX_H

#include "iostream"
template <typename Vertex_Name_Type>
class Vertex
{
public:
    /**********************************************************
     *
     * Vertex()
     *_________________________________________________________
     * Constructs a Vertex
     *_________________________________________________________
     * PRE-CONDITIONS
     * None
     *
     *
     **********************************************************/

    //O(1)
    Vertex(){
        this->name="";
    }
    /**********************************************************
     *
     * Vertex(Vertex_Name_Type n)
     *_________________________________________________________
     * Constructs a Vertex with Vertex Name
     *_________________________________________________________
     * PRE-CONDITIONS
     * Any valid vertex name
     *
     *
     **********************************************************/

    //O(1)
    Vertex(Vertex_Name_Type n){
        name=n;
    }
    /**********************************************************
     *
     * operator <<
     *_________________________________________________________
     * returns a stream containing the name of the vertex
     *_________________________________________________________
     * PRE-CONDITIONS
     * None
     *
     *
     **********************************************************/

    //O(1)
    friend std::ostream& operator << (std::ostream& os, const Vertex<Vertex_Name_Type>& B){
        os<<B.get_name();
        return os;
    }
    /**********************************************************
     *
     * ==
     *_________________________________________________________
     * returns true if the names are the same
     *_________________________________________________________
     * PRE-CONDITIONS
     * two vertices
     *
     *
     **********************************************************/

    //O(1)
    virtual bool operator == (Vertex<Vertex_Name_Type> B){
        return(this->name == B.name);

    }
    /**********************************************************
     *
     * get_name()
     *_________________________________________________________
     * returns name of vertex
     *_________________________________________________________
     * PRE-CONDITIONS
     * none
     *
     *
     **********************************************************/

    //O(1)
    virtual Vertex_Name_Type get_name() const{
        return name;
    }
    /**********************************************************
     *
     * assignment operator
     *_________________________________________________________
     * set the name of a vertex to another
     *_________________________________________________________
     * PRE-CONDITIONS
     * None
     *
     *
     **********************************************************/

    //O(1)
    virtual Vertex& operator=(const Vertex& B){
        this->name=B.name;
        return *this;
    }

protected:

    Vertex_Name_Type name;
};


#endif // VERTEX_H
