#ifndef WARRIOR_H
#define WARRIOR_H

//#include <ctime>
//#include <stdlib.h>
#include <iostream>


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
    DRAGON(size_t _num,COLOR _color,float _life,float _attack){
        num=_num;
        color=_color;
        attack=_attack;
        life=_life;
    }
};

class NINJA:public WARRIOR{
public:
    NINJA(size_t _num,COLOR _color,float _life,float _attack){
        num=_num;
        color=_color;
        attack=_attack;
        life=_life;
    }
};


class ICEMAN:public WARRIOR{
public:
    ICEMAN(size_t _num,COLOR _color,float _life,float _attack){
        num=_num;
        color=_color;
        attack=_attack;
        life=_life;
    }
};

class LION:public WARRIOR{
public:
    LION(size_t _num,COLOR _color,float _life,float _attack){
        num=_num;
        color=_color;
        attack=_attack;
        life=_life;
    }
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
