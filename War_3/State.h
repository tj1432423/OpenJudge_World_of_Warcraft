#ifndef STATE_H
#define STATE_H

#define THE_BLUE "blue"
#define THE_RED "red"


#include "Warrior.h"


#include <map>

using namespace std;

class STATE{
public:
    STATE(COLOR _color,int _life,int _city_num,int _loyalty_loss,const map<string,int>& _warrior_life_map,const map<string,int>& _warrior_attack_map){
       life=_life;
       color=_color;
       create_count=0;
       create_end_flag=false;
       warrior_num=0;
       loyalty_loss=_loyalty_loss;
       city_num=_city_num;
       max_warrior_num=size_t(city_num)+2;

       warrior_life_map=_warrior_life_map;
       warrior_attack_map=_warrior_attack_map;

       if(color==RED) state_name=THE_RED;
       else if(color==BLUE) state_name=THE_BLUE;
       else cout<<"fetal wrong !!! unknow color"<<endl;

    }



       void create_warrior(){
           if(create_end_flag) {
               //cout<<state_name<<"headquarter stops making warriors"<<endl;
               return;
           }
            size_t count=0;
            bool born_error_flag=true;
            while(count<create_order[size_t(color)].size()){
                string tmp=create_order[size_t(color)][create_count];
                create_count=(create_count+1)%(create_order[size_t(color)].size());
                if(life>0 && warrior_life_map[tmp]<=life){
                    print_current_time();
                    warrior_born(tmp);
                    born_error_flag=false;
                    break;
                }
                else {
                    create_end_flag=true;
                    return;
                }
                count++;
            }
            if(born_error_flag) {
                //cout<<state_name<<"headquarter stops making warriors"<<endl;
                create_end_flag=true;
            }
        }


       void warrior_born(string _warrior_name){
           WARRIOR* warrior=nullptr;
           string tmp=_warrior_name;
           warrior_num++;


           cout<<state_name<<" "<<tmp<<" "<<warrior_num<<" born"<<endl;


           if(tmp==THE_ICEMAN){
               ICEMAN *p=new ICEMAN(warrior_num,color,warrior_life_map[tmp],warrior_attack_map[tmp]);
               icemans.push_back(p);
               warrior=p;
           }
           else if (tmp==THE_LION) {
               int loyalty=life-warrior_life_map[tmp];
               LION* p=new LION(warrior_num,color,warrior_life_map[tmp],warrior_attack_map[tmp],loyalty);
               lions.push_back(p);
               warrior=p;
               cout<<"Its loyalty is "<<loyalty<<endl;
           }
           else if (tmp==THE_WOLF) {
               WOLF* p=new WOLF(warrior_num,color,warrior_life_map[tmp],warrior_attack_map[tmp]);
               wolfs.push_back(p);
               warrior=p;
           }
           else if (tmp==THE_NINJA) {
               NINJA* p=new NINJA(warrior_num,color,warrior_life_map[tmp],warrior_attack_map[tmp]);
               ninjas.push_back(p);
               warrior=p;
           }
           else if (tmp==THE_DRAGON) {
               float morale=float(life-warrior_life_map[tmp])/float(warrior_life_map[tmp]);
               DRAGON* p=new DRAGON(warrior_num,color,warrior_life_map[tmp],warrior_attack_map[tmp],morale);
               dragons.push_back(p);
               warrior=p;
           }
           else {
               cout<<"Fetal Wrong!!!!!!"<<endl;
           }

           if(warriors.empty()) {
               warriors.push_back(warrior);
           }
           else {
               warriors[0]=warrior;
           }

           warrior_count_map[tmp]++;
           life-=warrior_life_map[tmp];
       }


        void warrior_move(){
            warriors.insert(warriors.begin(),nullptr);
            if(warriors.size()>max_warrior_num) warriors.pop_back();
                for(size_t ii=1;ii<warriors.size();ii++){
                    if(warriors[ii] && warriors[ii]->name==THE_ICEMAN){
                        warriors[ii]->life=warriors[ii]->life-int(warriors[ii]->life*1/10);
                    }
                    if(warriors[ii] && warriors[ii]->name==THE_LION){
                        warriors[ii]->loyalty=warriors[ii]->loyalty-loyalty_loss;
                    }
                }
        }

        void lion_run_away(){
            for (size_t ii=0;ii<warriors.size();ii++) {
                if(warriors[ii] && warriors[ii]->name==THE_LION && ii != (this->max_warrior_num-1) && warriors[ii]->loyalty<=0 && warriors[ii]->life > 0){
                    warriors[ii]->life=0;
                    print_current_time();
                    cout<<state_name<<" lion "<<warriors[ii]->num<<" ran away"<<endl;
                }
            }
        }

        void set_time(int _hour,int _minute){
            hour=_hour;
            minute=_minute;
        }

        void print_current_time(){
            printf("%03d:%02d ",hour,minute);
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
    int life;
    COLOR color;
    size_t warrior_num;
    size_t create_count;
    bool create_end_flag;

    string state_name;

    vector<WARRIOR*> warriors;


    map<string,int> warrior_life_map;
    map<string,int> warrior_attack_map;
    map<string,size_t> warrior_count_map;



    size_t max_warrior_num;

    int loyalty_loss;
    int city_num;

private:
   const vector<vector<string>> create_order={{THE_ICEMAN,THE_LION,THE_WOLF,THE_NINJA,THE_DRAGON},{THE_LION,THE_DRAGON,THE_NINJA,THE_ICEMAN,THE_WOLF}};

   vector<ICEMAN*> icemans;
   vector<LION*> lions;
   vector<WOLF*> wolfs;
   vector<NINJA*> ninjas;
   vector<DRAGON*> dragons;

   int hour,minute;
};



#endif // STATE_H
