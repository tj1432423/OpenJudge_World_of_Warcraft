#ifndef STATE_H
#define STATE_H

#include "Warrior.h"

#include <vector>
#include <map>

using namespace std;

class STATE{
public:
    STATE(COLOR _color,float _life,const map<string,float>& _warrior_life_map){
       life=_life;
       color=_color;
       create_count=0;
       create_end_flag=false;
       warrior_num=0;

       warrior_life_map=_warrior_life_map;

//       warrior_life_map["iceman"]=5;
//       warrior_life_map["lion"]=6;
//       warrior_life_map["wolf"]=7;
//       warrior_life_map["ninja"]=4;
//       warrior_life_map["dragon"]=3;

       warrior_attack_map["iceman"]=10;
       warrior_attack_map["lion"]=10;
       warrior_attack_map["wolf"]=10;
       warrior_attack_map["ninja"]=10;
       warrior_attack_map["dragon"]=10;
    }



       void create_warrior(){
           if(create_end_flag) {
               if(color==RED) printf("red ");
               else printf("blue ");
               cout<<"headquarter stops making warriors"<<endl;
               return;
           }
            size_t count=0;
            bool born_error_flag=true;
            while(count<create_order[size_t(color)].size()){
                string tmp=create_order[size_t(color)][create_count];
                create_count=(create_count+1)%(create_order[size_t(color)].size());
                if(warrior_life_map[tmp]<=life){
                    warrior_born(tmp);
                    born_error_flag=false;
                    break;
                }
                count++;
            }
            if(born_error_flag) {
                if(color==RED) printf("red ");
                else printf("blue ");
                cout<<"headquarter stops making warriors"<<endl;
                create_end_flag=true;
            }
        }


       void warrior_born(string _warrior_name){
           WARRIOR* warrior;
           string tmp=_warrior_name;
           warrior_num++;
           if(tmp=="iceman"){
               ICEMAN *p=new ICEMAN(warrior_num,color,warrior_life_map[tmp],warrior_attack_map[tmp]);
               icemans.push_back(p);
               warrior=p;
           }
           else if (tmp=="lion") {
               LION* p=new LION(warrior_num,color,warrior_life_map[tmp],warrior_attack_map[tmp]);
               lions.push_back(p);
               warrior=p;
           }
           else if (tmp=="wolf") {
               WOLF* p=new WOLF(warrior_num,color,warrior_life_map[tmp],warrior_attack_map[tmp]);
               wolfs.push_back(p);
               warrior=p;
           }
           else if (tmp=="ninja") {
               NINJA* p=new NINJA(warrior_num,color,warrior_life_map[tmp],warrior_attack_map[tmp]);
               ninjas.push_back(p);
               warrior=p;
           }
           else if (tmp=="dragon") {
               DRAGON* p=new DRAGON(warrior_num,color,warrior_life_map[tmp],warrior_attack_map[tmp]);
               dragons.push_back(p);
               warrior=p;
           }
           else {
               cout<<"Fetal Wrong!!!!!!"<<endl;
           }
           warriors.push_back(warrior);
           warrior_count_map[tmp]++;
           life-=warrior_life_map[tmp];

           if(color==RED) printf("red ");
           else printf("blue ");
           cout<<tmp<<" "<<warrior_num<<" born with strength "<<warrior_life_map[tmp]<<","<<warrior_count_map[tmp]<<" "<<tmp<<" in ";
           if(color==RED) printf("red ");
           else printf("blue ");
           cout<<"headquarter"<<endl;
       }

       ~STATE(){
           for(size_t ii=0;ii<icemans.size();ii++){
               delete icemans[ii];
           }
           for(size_t ii=0;ii<lions.size();ii++){
               delete lions[ii];
           }
           for(size_t ii=0;ii<wolfs.size();ii++){
               delete wolfs[ii];
           }
           for(size_t ii=0;ii<ninjas.size();ii++){
               delete ninjas[ii];
           }
           for(size_t ii=0;ii<dragons.size();ii++){
               delete dragons[ii];
           }
       }

public:
    float life;
    COLOR color;
    size_t warrior_num;
    size_t create_count;
    bool create_end_flag;

    vector<WARRIOR*> warriors;


    map<string,float> warrior_life_map;
    map<string,float> warrior_attack_map;
    map<string,size_t> warrior_count_map;

    vector<ICEMAN*> icemans;
    vector<LION*> lions;
    vector<WOLF*> wolfs;
    vector<NINJA*> ninjas;
    vector<DRAGON*> dragons;

private:
   const vector<vector<string>> create_order={{"iceman","lion","wolf","ninja","dragon"},{"lion","dragon","ninja","iceman","wolf"}};
};



#endif // STATE_H
