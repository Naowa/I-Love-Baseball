#ifndef AMERICAN_STADIUM_H
#define AMERICAN_STADIUM_H
#include <stadium.h>

class American_Stadium : public ILB::Stadium
{
public:
    American_Stadium(): Stadium(){stadium_type="American";}
    American_Stadium(std::string a) : ILB::Stadium(a){}
    bool operator ==(Stadium& B){
        return(this->stadium_name==B.get_stadium_name() && this->stadium_type==B.get_type());
    }

};

#endif // AMERICAN_STADIUM_H
