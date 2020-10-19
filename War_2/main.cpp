#include "State.h"



int main(){
//*************************************  初始化  ************************************//
    bool debug_flag=false;
    //bool debug_flag=true;
    int test_case_num,M;
    int case_cout=0;
    map<string,float> warrior_life_map;
    if(debug_flag){
        test_case_num=1;
    }
    else {
        cin >> test_case_num;
    }
    while(test_case_num){
        test_case_num--;
        if(debug_flag){
            M=20;
            warrior_life_map["dragon"]=3;
            warrior_life_map["ninja"]=4;
            warrior_life_map["iceman"]=5;
            warrior_life_map["lion"]=6;
            warrior_life_map["wolf"]=7;  
        }
        else {
            cin >> M;
            cin >> warrior_life_map["dragon"] >> warrior_life_map["ninja"] >> warrior_life_map["iceman"] >> warrior_life_map["lion"] >> warrior_life_map["wolf"];
        }

        //*************************************************************************//

        cout << "Case:" << ++case_cout << endl;
        int count=0;
        STATE Red(RED,M,warrior_life_map);
        STATE Blue(BLUE,M,warrior_life_map);
        while(!Red.create_end_flag || !Blue.create_end_flag){
            if(!Red.create_end_flag){
                printf("%03d ",count);
                Red.create_warrior();
            }
            if(!Blue.create_end_flag){
                printf("%03d ",count);
                Blue.create_warrior();
            }
            count++;
        }
    }
    return 0;
}
