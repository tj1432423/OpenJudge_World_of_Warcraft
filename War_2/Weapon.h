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
    }
    WEAPON_TYPE type;
    string name;
};



#endif //WEAPON_H
