#ifndef WARRIOR_H
#define WARRIOR_H

//#include <ctime>
//#include <stdlib.h>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>

#include "Weapon.h"



#define THE_DRAGON "dragon"
#define THE_NINJA "ninja"
#define THE_ICEMAN "iceman"
#define THE_LION "lion"
#define THE_WOLF "wolf"

using namespace std;

enum COLOR {RED,BLUE};


class WARRIOR{
public:
    size_t num;
    int life;
    int attack;
    COLOR color;
    string name;

    float morale;
    int loyalty;

    vector<WEAPON> weapons;
    vector<WEAPON> weapons_back;

    //int cur_weapon_index;


    void start_attack(WARRIOR* _enemy);

    void grab_weapons(WARRIOR* _enemy);
    void get_weapons(WARRIOR* _enemy,bool _get_all_weapon=true,bool _debugswitch=true);

    void report_weapons_status();

    bool all_weapons_is_sword(WARRIOR* _aa);


private:
    bool attack_action(WARRIOR* _enemy,WEAPON _weapon);
    pair<int,int> weapon_attack_value(WARRIOR* _enemy,WEAPON _weapon);

    //virtual ~WARRIOR(){}

};




class DRAGON:public WARRIOR{
public:
    DRAGON(size_t _num,COLOR _color,int _life,int _attack,float _morale){
        num=_num;
        color=_color;
        attack=_attack;
        life=_life;
        name=THE_DRAGON;

        morale=_morale;
        int tmp_weapon_type=num%3;
        weapons.push_back(WEAPON_TYPE(tmp_weapon_type));

        //cur_weapon_index=0;

        //cout<<"It has a arrow,and it's morale is ";
        //printf("%.2f \n",double(morale));
    }

    //virtual ~DRAGON(){}

public:
//    virtual void start_attack(WARRIOR*  _enemy);

};




class NINJA:public WARRIOR{
public:
    NINJA(size_t _num,COLOR _color,int _life,int _attack){
        num=_num;
        color=_color;
        attack=_attack;
        life=_life;
        name=THE_NINJA;

        int tmp_weapon_type=num%3;
        weapons.push_back(WEAPON_TYPE(tmp_weapon_type));
        tmp_weapon_type=(num+1)%3;
        weapons.push_back(WEAPON_TYPE(tmp_weapon_type));
        sort(weapons.begin(),weapons.end());

        //cur_weapon_index=0;

        //cout<<"It has a sword and a bomb"<<endl;
    }

    //virtual ~NINJA(){}

public:
    //virtual void start_attack(WARRIOR*  _enemy);
};





class ICEMAN:public WARRIOR{
public:
    ICEMAN(size_t _num,COLOR _color,int _life,int _attack){
        num=_num;
        color=_color;
        attack=_attack;
        life=_life;
        name=THE_ICEMAN;

        int tmp_weapon_type=num%3;
        weapons.push_back(WEAPON_TYPE(tmp_weapon_type));

        //cur_weapon_index=0;

        //cout<<"It has a sword"<<endl;
    }

    //virtual ~ICEMAN(){}

public:
    //virtual void start_attack(WARRIOR*  _enemy);


};



class LION:public WARRIOR{
public:
    LION(size_t _num,COLOR _color,int _life,int _attack,int _loyalty){
        num=_num;
        color=_color;
        attack=_attack;
        life=_life;
        name=THE_LION;

        loyalty=_loyalty;

        int tmp_weapon_type=num%3;
        weapons.push_back(WEAPON_TYPE(tmp_weapon_type));

        //cur_weapon_index=0;

        //cout<<"It's loyalty is "<<loyalty<<endl;
    }

    //virtual ~LION(){}

public:
    //virtual void start_attack(WARRIOR*  _enemy);
};



class WOLF:public WARRIOR{
public:
    WOLF(size_t _num,COLOR _color,int _life,int _attack){
        num=_num;
        color=_color;
        attack=_attack;
        life=_life;
        name=THE_WOLF;

        //cur_weapon_index=-1;
    }

    //virtual ~WOLF(){}

public:
    //virtual void start_attack(WARRIOR*  _enemy);
};




#endif // WARRIOR_H
