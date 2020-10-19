#ifndef WARRIOR_H
#define WARRIOR_H

//#include <ctime>
//#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>

#include "Weapon.h"


using namespace std;

enum COLOR {RED,BLUE};


class WARRIOR{
public:
    size_t num;
    float life;
    float attack;
    COLOR color;

};



class DRAGON:public WARRIOR{
public:
    DRAGON(size_t _num,COLOR _color,float _life,float _attack,float _morale){
        num=_num;
        color=_color;
        attack=_attack;
        life=_life;
        morale=_morale;
        weapons.push_back(WEAPON_TYPE(num%3));
        cout<<"It has a "<<weapons[0].name<<",and it's morale is ";
        printf("%.2f \n",morale);
    }

    vector<WEAPON> weapons;
    float morale;
};

class NINJA:public WARRIOR{
public:
    NINJA(size_t _num,COLOR _color,float _life,float _attack){
        num=_num;
        color=_color;
        attack=_attack;
        life=_life;
        weapons.push_back(WEAPON_TYPE(num%3));
        weapons.push_back(WEAPON_TYPE((num+1)%3));

        cout<<"It has a "<<weapons[0].name<<" and a "<<weapons[1].name<<endl;
    }

    vector<WEAPON> weapons;
};


class ICEMAN:public WARRIOR{
public:
    ICEMAN(size_t _num,COLOR _color,float _life,float _attack){
        num=_num;
        color=_color;
        attack=_attack;
        life=_life;
        weapons.push_back(WEAPON_TYPE(num%3));
        cout<<"It has a "<<weapons[0].name<<endl;
    }

    vector<WEAPON> weapons;
};

class LION:public WARRIOR{
public:
    LION(size_t _num,COLOR _color,float _life,float _attack,float _loyalty){
        num=_num;
        color=_color;
        attack=_attack;
        life=_life;
        loyalty=_loyalty;

        cout<<"It's loyalty is "<<loyalty<<endl;
    }

    float loyalty;
};

class WOLF:public WARRIOR{
public:
    WOLF(size_t _num,COLOR _color,float _life,float _attack){
        num=_num;
        color=_color;
        attack=_attack;
        life=_life;
    }
};




#endif // WARRIOR_H
