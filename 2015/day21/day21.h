#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

namespace aoc2015{
    namespace day21{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);

        struct Object{
            std::string name =  "";
            int cost = 0;
            int damage = 0;
            int armor = 0;
        };

        struct Player{
            std::string name;
            int armor;
            int damage;
            int health;
        };

        void parseShop(map<std::string,std::vector<Object>>& shop);
        void parseBoss(std::string p, Player& enemy);
        void explore(Player& mine, Player& enemy,map<std::string,std::vector<Object>>& shop);
        int p1 = 999999;
        int p2 = -1;

        void run(){
            Player mine = {"me",0,0,100};
            Player enemy = {"Boss",0,0,100};
            std::map<std::string,std::vector<Object>> shop = {{"Weapons",{}},{"Armor",{{"none",0,0,0}}},{"Rings",{{"none1",0,0,0},{"none2",0,0,0}}}};
            
            parseShop(shop);
            parseBoss("./2015/day21/day21",enemy);
            explore(mine,enemy,shop);
            std::cout << "Part 1" << std::endl;
            std::cout << p1 << std::endl;

            std::cout << "Part 2" << std::endl;
            std::cout << p2 << std::endl;
        }



        void parseShop(map<std::string,std::vector<Object>>& shop){
            std::ifstream in("./2015/day21/shop");
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            std::getline(std::cin , line);

            for(std::string type : {"Weapons","Armor","Rings"}){
                while(std::getline(std::cin , line)){
                    if(line.size()<1){
                        std::getline(std::cin , line);
                        break;
                    }
                    size_t pos;
                    pos = line.find("  ");

                    Object o;
                    o.name = line.substr(0,pos);
                    line.erase(0, pos + 1);
                    std::stringstream ss(line);
                    ss >> o.cost >> o.damage >> o.armor;
                    shop[type].push_back(o);
                }
            }

        }
        
        void parseBoss(std::string p , Player& enemy){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            int x[3] = {0,0,0};
            for(int i = 0; i < 3;i++){
                std::string line;
                std::getline(std::cin , line);
                size_t pos = line.find(":");
                line.erase(0, pos + 1);
                std::stringstream ss(line);
                ss >> x[i];
            }
            enemy.health = x[0];
            enemy.damage = x[1];
            enemy.armor = x[2];           
        }

        bool doIwin(Player& mine, Player& enemy){
            int damage = std::max(1,mine.damage - enemy.armor);
            int takingdamage = std::max(1,enemy.damage - mine.armor);
            return damage >= takingdamage; 
        }

        void explore(Player& mine, Player& enemy,map<std::string,std::vector<Object>>& shop){
            for(Object w : shop["Weapons"]){
                for(Object a : shop["Armor"]){
                    for(Object r1 : shop["Rings"]){
                        for(Object r2 : shop["Rings"]){
                            mine.health = 100;
                            mine.armor = w.armor + a.armor + r1.armor + r2.armor;
                            mine.damage = w.damage + a.damage + r1.damage + r2.damage;
                            int cost = w.cost + a.cost + r1.cost + r2.cost;
                            
                            if(doIwin(mine,enemy)){
                                if(cost < p1) p1 = cost;
                            }else if(cost > p2){
                                p2 = cost;
                            }    
                        }
                    }
                }
            }
        }
    }
}

