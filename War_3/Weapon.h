#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <iostream>

using namespace std;


enum WEAPON_TYPE{SWORD,BOMB,ARROW};


class WEAPON{
public:

public:
    WEAPON(int _num){
        type=WEAPON_TYPE(_num);
        if(type==SWORD) name="sword";
        else if (type==BOMB) name="bomb";
        else if (type==ARROW) name="arrow";
        else cout<<"Fetal wrong !!! unknow swepon type !!!"<<endl;

        if(type==SWORD) rest_use_time=1;
        else if (type==BOMB) rest_use_time=1;
        else if (type==ARROW) rest_use_time=2;
        else cout<<"Fetal wrong !!! unknow swepon type !!!"<<endl;

    }

    bool operator<(const WEAPON& _x)const{
        bool res;
        if (int(this->type)<int(_x.type)) res=true;
        else {
            res = this->rest_use_time<_x.rest_use_time;
        }
        return !res;    // reverse sort!!!
    }

    WEAPON_TYPE type;
    int rest_use_time;
    string name;
};



#endif //WEAPON_H
