#include "Warrior.h"

#define THE_SWORD "sword"
#define THE_BOMB "bomb"
#define THE_ARROW "arrow"

bool WARRIOR::attack_action(WARRIOR* _enemy,WEAPON _weapon){
    if(this->life<=0) return false;
    if(_enemy->life<=0) return false;
    if(_weapon.rest_use_time<=0) return false;
    pair<int,int> tmp=weapon_attack_value(_enemy,_weapon);
    _enemy->life -=tmp.first;
    this->life -=tmp.second;
    if(tmp==make_pair(0,0)) return false;
    return true;
}

pair<int,int> WARRIOR::weapon_attack_value(WARRIOR* _enemy,WEAPON _weapon){
    if(_weapon.name==THE_SWORD){
        return make_pair(this->attack*2/10,0);
    }
    else if(_weapon.name==THE_BOMB){
        if(this->name != THE_NINJA){
            return make_pair(this->attack*4/10,this->attack*4/10/2);
        }
        return make_pair(this->attack*4/10,0);

    }
    else if (_weapon.name==THE_ARROW) {
        return make_pair(this->attack*3/10,0);
    }
    else {
        cout<<"fetal wrong !!!  unknow weapon name !!!"<<endl;
        cout<<"fetal wrong !!!  unknow weapon name !!!"<<endl;
        cout<<"fetal wrong !!!  unknow weapon name !!!"<<endl;
        return make_pair(0,0);
    }
}



void WARRIOR::start_attack(WARRIOR*  _enemy){
    WARRIOR* aa=this;
    WARRIOR* bb=_enemy;
    int attack_valid_num=0;
    bool sword_war_flag=false;
    while(aa->life > 0 && bb->life > 0){
        if(aa->weapons.empty() && !bb->weapons.empty()){
            swap(aa,bb);
            continue;
        }
        else if(aa->weapons.empty() && bb->weapons.empty()){
            break;
        }

        bool tmp_attack_valid=aa->attack_action(bb,aa->weapons.back());

        if(aa->weapons.back().name != THE_SWORD){
            aa->weapons.back().rest_use_time--;
        }
        if(aa->weapons.back().rest_use_time>0){
            aa->weapons_back.push_back(aa->weapons.back());
        }
        aa->weapons.pop_back();
        if(aa->weapons.empty()){
            aa->weapons=aa->weapons_back;
            sort(aa->weapons.begin(),aa->weapons.end());
            aa->weapons_back.clear();
        }

        if(  all_weapons_is_sword(aa) && all_weapons_is_sword(bb)   ){
            sword_war_flag=true;
        }

        if(sword_war_flag && !tmp_attack_valid){
            attack_valid_num++;
        }
        else {
            attack_valid_num=0;
        }

        if(attack_valid_num==4) break;

        swap(aa,bb);
    //dragon在战斗结束后，如果还没有战死，就会欢呼
    }
    aa->weapons.insert(aa->weapons.end(),aa->weapons_back.begin(),aa->weapons_back.end());
    sort(aa->weapons.begin(),aa->weapons.end());
    bb->weapons.insert(bb->weapons.end(),bb->weapons_back.begin(),bb->weapons_back.end());
    sort(bb->weapons.begin(),bb->weapons.end());
    aa->weapons_back.clear();
    bb->weapons_back.clear();
}

bool WARRIOR::all_weapons_is_sword(WARRIOR* _aa){
    for (size_t ii=0;ii<_aa->weapons.size();ii++) {
        if(_aa->weapons[ii].name!=THE_SWORD) return false;
    }
    for (size_t ii=0;ii<_aa->weapons_back.size();ii++) {
        if(_aa->weapons_back[ii].name!=THE_SWORD) return false;
    }
    return true;
}

void WARRIOR::grab_weapons(WARRIOR* _enemy){
    WARRIOR* aa=this;
    WARRIOR* bb=_enemy;
    if(aa->name==THE_WOLF && bb->name==THE_WOLF) return;
    if(aa->name!=THE_WOLF && bb->name!=THE_WOLF) return;
    if(bb->name==THE_WOLF) swap(aa,bb);
    aa->get_weapons(bb,false);
}


void WARRIOR::get_weapons(WARRIOR* _enemy,bool _get_all_weapon,bool _debugswitch){
    WARRIOR* aa=this;
    WARRIOR* bb=_enemy;

    if(bb->weapons.size()==0) return;
    vector<vector<WEAPON>> tmp={{bb->weapons[0]}};
    for(size_t ii=1;ii<bb->weapons.size();ii++){
        if(bb->weapons[ii].name!=tmp.back().back().name){
            tmp.push_back({});
        }
        tmp.back().push_back(bb->weapons[ii]);
    }

    for (size_t ii=0;ii<tmp.size();ii++) {
        reverse(tmp[ii].begin(),tmp[ii].end());
    }

    string grab_weapons_name;
    int get_weapons_num=0;

    while(aa->weapons.size()<10 && tmp.size()){
        aa->weapons.push_back(tmp.back().back());
        get_weapons_num++;
        grab_weapons_name=tmp.back().back().name;
        tmp.back().pop_back();
        if(tmp.back().size()==0){
            tmp.pop_back();
            if(!_get_all_weapon) break;
        }
    }

    if(get_weapons_num) {
        string tmp_aa_color=aa->color==RED ? "red" : "blue";
        string tmp_bb_color=bb->color==RED ? "red" : "blue";
      if(_debugswitch) {
          cout<<tmp_aa_color<<" "<<aa->name<<" "<<aa->num<<" took "<< get_weapons_num<<" "<<grab_weapons_name<<" from "<<tmp_bb_color<<" "<<bb->name<<" "<<bb->num<<" in city ";
      }
    }


    bb->weapons.clear();
    for(size_t ii=0;ii<tmp.size();ii++){
        for(size_t jj=0;jj<tmp[ii].size();jj++){
            bb->weapons.push_back(tmp[ii][jj]);
        }
    }

    sort(aa->weapons.begin(),aa->weapons.end());
    sort(bb->weapons.begin(),bb->weapons.end());
}

void WARRIOR::report_weapons_status(){
    if(life<=0) return;
    map<string,int> mp;
    for(size_t ii=0;ii<weapons.size();ii++){
        mp[weapons[ii].name]++;
    }

    string tmp_color_name= color==RED ? "red" : "blue";

    int tmp_sword_num=mp.count(THE_SWORD) ? mp[THE_SWORD] : 0 ;
    int tmp_bomb_num=mp.count(THE_BOMB) ? mp[THE_BOMB] : 0 ;
    int tmp_arrow_num=mp.count(THE_ARROW) ? mp[THE_ARROW] : 0 ;

    cout<<tmp_color_name<<" "<<name<<" "<<num<<" has "<<tmp_sword_num<<" "<<THE_SWORD<<" ";
    cout<<tmp_bomb_num<<" "<<THE_BOMB<<" ";
    cout<<tmp_arrow_num<<" "<<THE_ARROW<<" ";
    cout<<"and "<<life<<" elements"<<endl;


    //000:55 blue wolf 2 has 2 sword 3 bomb 0 arrow and 7 elements
    //为简单起见，武器都不写复数形式。elements一律写复数，哪怕只有1个
    //交代武器情况时，次序依次是：sword,bomb, arrow。
}







