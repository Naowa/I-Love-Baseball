#ifndef NATIONAL_STADIUM_H
#define NATIONAL_STADIUM_H
#include <stadium.h>

class National_Stadium : public ILB::Stadium
{
public:
    National_Stadium() : Stadium(){stadium_type="National";}
    National_Stadium(std::string a) : ILB::Stadium(a){}
    bool operator ==(Stadium& B){
        return(this->stadium_name==B.get_stadium_name() && this->stadium_type==B.get_type());
    }
};

#endif // NATIONAL_STADIUM_H
