#ifndef GAME_H
#define GAME_H

#include "State.h"


class GAME{
public:
    GAME(bool _debug_flag){
        //*************************************  初始化  ************************************//
        //bool debug_flag=false;
        debug_flag=_debug_flag;
        case_cout=0;

        if(debug_flag){
            test_case_num=1;
        }
        else {
            cin >> test_case_num;
        }
        while(test_case_num){
            test_case_num--;
            if(debug_flag){
                M=6000;
                N=4;
                K=10;
                T=1000;

                warrior_life_map[THE_DRAGON]=120;
                warrior_life_map[THE_NINJA]=120;
                warrior_life_map[THE_ICEMAN]=30;
                warrior_life_map[THE_LION]=110;
                warrior_life_map[THE_WOLF]=20;

                warrior_attack_map[THE_DRAGON]=50;
                warrior_attack_map[THE_NINJA]=50;
                warrior_attack_map[THE_ICEMAN]=50;
                warrior_attack_map[THE_LION]=50;
                warrior_attack_map[THE_WOLF]=50;

                //6000 10 10 4000
                //120 20 130 10 20
                //50 50 50 50 150
            }
            else {
                cin >> M >>N >>K >>T;
                cin >> warrior_life_map[THE_DRAGON] >> warrior_life_map[THE_NINJA] >> warrior_life_map[THE_ICEMAN] >> warrior_life_map[THE_LION] >> warrior_life_map[THE_WOLF];
                cin >> warrior_attack_map[THE_DRAGON] >> warrior_attack_map[THE_NINJA] >> warrior_attack_map[THE_ICEMAN] >> warrior_attack_map[THE_LION] >> warrior_attack_map[THE_WOLF];
            }
            game_start();
        }

    }

    void game_start(){
        cout << "Case " << ++case_cout <<":"<< endl;
        hour=0;
        minute=0;

        STATE Red(RED,M,N,K,warrior_life_map,warrior_attack_map);
        STATE Blue(BLUE,M,N,K,warrior_life_map,warrior_attack_map);

        //int Time=100;
        while((hour*60+minute)<=T){
            Red.set_time(hour,minute);
            Blue.set_time(hour,minute);

            if(minute==0){   //在每个整点，即每个小时的第0分， 双方的司令部中各有一个武士降生。
                if(!Red.create_end_flag){
                    Red.create_warrior();
                }
                if(!Blue.create_end_flag){
                    Blue.create_warrior();
                }
            }
            else if (minute==5) {   //在每个小时的第5分，该逃跑的lion就在这一时刻逃跑了。
                Red.lion_run_away();
                Blue.lion_run_away();
            }
            else if (minute==10) {  //在每个小时的第10分：所有的武士朝敌人司令部方向前进一步。即从己方司令部走到相邻城市，或从一个城市走到下一个城市。或从和敌军司令部相邻的城市到达敌军司令部。
                Red.warrior_move();
                Blue.warrior_move();


                //------------------任何一方的司令部里若是出现了敌人，则认为该司令部已被敌人占领。
                bool end_flag=false;;

                if(state_win(Blue)){
                    print_current_time();
                    cout<<"blue "<<Blue.warriors.back()->name<<" "<<Blue.warriors.back()->num<<" ";
                    cout<<"reached red headquarter with "<<Blue.warriors.back()->life<<" elements and force "<<Blue.warriors.back()->attack<<endl;
                    print_current_time();
                    cout<<"red headquarter was taken"<<endl;
                    end_flag=true;
                }

                for (int ii=1;ii<int(Red.max_warrior_num)-1;ii++) {
                    int tmp_index=ii;
                    //int index_y=int(Red.max_warrior_num)-ii-1;
                    if(tmp_index > 0 && tmp_index<int(Red.warriors.size())){
                        WARRIOR* tmp_warror=Red.warriors[tmp_index];
                        if(tmp_warror && tmp_warror->life > 0){
                            print_current_time();
                            cout<<Red.state_name<<" "<<tmp_warror->name<<" "<<tmp_warror->num;
                            cout<<" marched to city "<<ii<<" with "<<tmp_warror->life<<" elements and force "<<tmp_warror->attack<<endl;
                        }
                    }
                    tmp_index=int(Red.max_warrior_num)-ii-1;
                    if(tmp_index > 0 && tmp_index<int(Blue.warriors.size())){
                        WARRIOR* tmp_warror=Blue.warriors[tmp_index];
                        if(tmp_warror && tmp_warror->life > 0){
                            print_current_time();
                            cout<<Blue.state_name<<" "<<tmp_warror->name<<" "<<tmp_warror->num;
                            cout<<" marched to city "<<ii<<" with "<<tmp_warror->life<<" elements and force "<<tmp_warror->attack<<endl;
                        }
                    }

                }

                if(state_win(Red)){
                    print_current_time();
                    cout<<"red "<<Red.warriors.back()->name<<" "<<Red.warriors.back()->num<<" ";
                    cout<<"reached blue headquarter with "<<Red.warriors.back()->life<<" elements and force "<<Red.warriors.back()->attack<<endl;

                    print_current_time();
                    cout<<"blue headquarter was taken"<<endl;
                    end_flag=true;

                    //输出样例：001:10 red iceman 1 reached blue headquarter with 20 elements and force 30
                    //（此时他生命值为20,攻击力为30）对于iceman,输出的生命值和攻击力应该是变化后的数值
                }



                if(end_flag) break;





            }
            else if (minute==35) {   //在每个小时的第35分：在有wolf及其敌人的城市，wolf要抢夺对方的武器。
                for(size_t ii=1;ii<(Red.max_warrior_num-1);ii++){
                    size_t jj=Red.max_warrior_num-ii-1;
                    if(ii>0 && ii<Red.warriors.size() && Red.warriors[ii] && jj>0 && jj<Blue.warriors.size() && Blue.warriors[jj]){
                        if((Red.warriors[ii]->name==THE_WOLF && Blue.warriors[jj]->name != THE_WOLF && Blue.warriors[jj]->weapons.size())
                                || (Red.warriors[ii]->name!=THE_WOLF && Blue.warriors[jj]->name == THE_WOLF && Red.warriors[ii]->weapons.size())){
                            if(Red.warriors[ii]->life > 0 && Blue.warriors[jj]->life > 0){
                                print_current_time();
                                Red.warriors[ii]->grab_weapons(Blue.warriors[jj]);
                                cout<<ii<<endl;
                            }
                        }
                    }
                }
            }
            else if (minute==40) {    //在每个小时的第40分：在有两个武士的城市，会发生战斗。
                for(int ii=1;ii<(int(Red.max_warrior_num)-1);ii++){
                    int jj=int(Red.max_warrior_num)-ii-1;
                    //if(Red.warriors[ii] && Blue.warriors[jj]){
                    if(ii>0 && ii<Red.warriors.size() && Red.warriors[ii]
                            && jj>0 && jj<Blue.warriors.size() && Blue.warriors[jj]
                            && Red.warriors[ii]->life > 0 && Blue.warriors[jj]->life > 0){

                        if(ii%2){
                            Red.warriors[ii]->start_attack(Blue.warriors[jj]);
                        }
                        else {
                            Blue.warriors[jj]->start_attack(Red.warriors[ii]);
                        }
                        //
                        print_current_time();
                        if(Red.warriors[ii]->life > 0 && Blue.warriors[jj]->life <= 0){
                            //Red.warriors[ii]->
                            cout<<"red "<<Red.warriors[ii]->name<<" "<<Red.warriors[ii]->num;
                            cout<<" killed ";
                            cout<<"blue "<<Blue.warriors[jj]->name<<" "<<Blue.warriors[jj]->num;
                            cout<<" in city "<<ii<<" remaining "<<Red.warriors[ii]->life<<" elements"<<endl;
                        }
                        else if (Red.warriors[ii]->life <= 0 && Blue.warriors[jj]->life > 0) {
                            cout<<"blue "<<Blue.warriors[jj]->name<<" "<<Blue.warriors[jj]->num;
                            cout<<" killed ";
                            cout<<"red "<<Red.warriors[ii]->name<<" "<<Red.warriors[ii]->num;
                            cout<<" in city "<<ii<<" remaining "<<Blue.warriors[jj]->life<<" elements"<<endl;
                        }
                        else if (Red.warriors[ii]->life > 0 && Blue.warriors[jj]->life > 0) {
                            cout<<"both ";
                            cout<<"red "<<Red.warriors[ii]->name<<" "<<Red.warriors[ii]->num;
                            cout<<" and ";
                            cout<<"blue "<<Blue.warriors[jj]->name<<" "<<Blue.warriors[jj]->num;
                            cout<<" were alive in city "<<ii<<endl;
                        }
                        else {
                            cout<<"both ";
                            cout<<"red "<<Red.warriors[ii]->name<<" "<<Red.warriors[ii]->num;
                            cout<<" and ";
                            cout<<"blue "<<Blue.warriors[jj]->name<<" "<<Blue.warriors[jj]->num;
                            cout<<" died in city "<<ii<<endl;
                        }

                        //000:40 red iceman 1 killed blue lion 12 in city 2 remaining 20 elements
                        //表示在0点40分，1号城市中，红魔1号武士iceman 杀死蓝魔12号武士lion后，剩下生命值20
                        //000:40 both red iceman 1 and blue lion 12 died in city 2
                        //注意，把红武士写前面
                        //000:40 both red iceman 1 and blue lion 12 were alive in city 2


                        // the  war is end, an begin to get weapon!
                        if(Red.warriors[ii]->life > 0 && Blue.warriors[jj]->life <= 0 ){
                            Red.warriors[ii]->get_weapons(Blue.warriors[jj],true,false);
                        }
                        else if(Red.warriors[ii]->life <= 0 && Blue.warriors[jj]->life > 0 ){
                            Blue.warriors[jj]->get_weapons(Red.warriors[ii],true,false);
                        }
                        // dragon在战斗结束后，如果还没有战死，就会欢呼
                        if(Red.warriors[ii]->name==THE_DRAGON && Red.warriors[ii]->life > 0){
                            print_current_time();
                            cout<<"red "<<Red.warriors[ii]->name<<" "<<Red.warriors[ii]->num;   // dragon在战斗结束后，如果还没有战死，就会欢呼--------
                            cout<<" yelled in city "<<ii<<endl;
                            //输出样例：003:40 blue dragon 2 yelled in city 4
                        }
                        if(Blue.warriors[jj]->name==THE_DRAGON && Blue.warriors[jj]->life > 0){
                            print_current_time();
                            cout<<"blue "<<Blue.warriors[jj]->name<<" "<<Blue.warriors[jj]->num;   // dragon在战斗结束后，如果还没有战死，就会欢呼--------
                            cout<<" yelled in city "<<ii<<endl;
                            // dragon在战斗结束后，如果还没有战死，就会欢呼-----------
                        }
                    }
                }
            }
            else if (minute==50) {   //在每个小时的第50分，司令部报告它拥有的生命元数量。---------
                print_current_time();
                cout<<Red.life<<" elements in red headquarter"<<endl;
                print_current_time();
                cout<<Blue.life<<" elements in blue headquarter"<<endl;
                //000:50 100 elements in red headquarter
                //000:50 120 elements in blue headquarter
                //表示在0点50分，红方司令部有100个生命元，蓝方有120个
            }
            else if (minute==55) {   //在每个小时的第55分，每个武士报告其拥有的武器情况。---------------------------------------
                for (int ii=1;ii<int(Red.max_warrior_num)-1;ii++) {
                    int tmp_index=ii;
                    if(tmp_index > 0 && tmp_index<int(Red.warriors.size())){
                        WARRIOR* tmp_warror=Red.warriors[tmp_index];
                        if(tmp_warror && tmp_warror->life > 0){
                            print_current_time();
                            tmp_warror->report_weapons_status();
                        }
                    }
                    tmp_index=int(Red.max_warrior_num)-ii-1;
                    if(tmp_index > 0 && tmp_index<int(Blue.warriors.size())){
                        WARRIOR* tmp_warror=Blue.warriors[tmp_index];
                        if(tmp_warror && tmp_warror->life > 0){
                            print_current_time();
                            tmp_warror->report_weapons_status();
                        }
                    }

                }
            }
            else {
                //cout<<"Wrong Time !!!!"<<endl;
            }
            time_forward();

            //cout<<"The hour :"<<hour<<",the minute : "<<minute<<endl;    //Shold be delete!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        }

    }


private:
    bool state_win(const STATE& _state){
        if(_state.warriors.size()==_state.max_warrior_num && _state.warriors.back() && _state.warriors.back()->life > 0){
            return true;
        }
        return false;
    }


    void time_forward(){
        minute+=5;
        hour+=minute/60;
        minute=minute%60;
    }

    void print_current_time(){
        printf("%03d:%02d ",hour,minute);
    }

private:
    bool debug_flag;
    int test_case_num,M,N,K,T;
    int case_cout;
    map<string,int> warrior_life_map;
    map<string,int> warrior_attack_map;

    int hour,minute;


};



#endif //GAME_H
