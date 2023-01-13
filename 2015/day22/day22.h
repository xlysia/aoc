#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <vector>

namespace aoc2015{
    namespace day22{
        

        const int NB_SPELLS = 5;
        struct spell{
            public:
            int cost;
            int damage;
            int armor;
            int mana;
            int heal;
            int turn;
        };

        spell spellbook[NB_SPELLS] = {
            {53,4,0,0,0,0},
            {73,2,0,0,2,0},
            {113,0,7,0,0,6},
            {173,3,0,0,0,6},
            {229,0,0,101,0,5}
        };

        struct player{
            public:
            int health;
            int damage;
            int mana;

            int spells[NB_SPELLS] = {0,0,0,0,0};

            int spent = 0;

            bool cast(int i){
                spells[i] = spellbook[i].turn;
                spent += spellbook[i].cost;
                mana -= spellbook[i].cost;
                return spellbook[i].turn <1;
            }

            void attack_magie(int i){
                health -= spellbook[i].damage;
            }
            void attack(int d){
                int armor = 0;
                for(int i = 0;i<NB_SPELLS;i++){
                    armor += spellbook[i].armor*(spells[i]>0);
                }
                health -= std::max(1,d-armor);
            }
            void heal(int i){
                health += spellbook[i].heal;
                mana += spellbook[i].mana;
            }
        };

        struct state{
            public:
            player me = {50,0,500};
            player boss = {0,0,0};
        };
        
        state game;

        void parse(){
            std::string line;
            std::vector<int> x;
            while(std::getline(std::cin,line)){
                size_t pos = line.find(":");
                line.erase(0,pos+1);
                x.push_back(std::atoi(line.c_str()));
            }
            game.boss.health = x[0];
            game.boss.damage = x[1];
        }
        
        int explore(state game,bool bhard){
            int res = 99999999;
            std::vector<state> queue =  {game};
            while(queue.size()>0){
                state turn = queue.back();
                queue.pop_back();
                if(res < turn.me.spent)continue;

                if(bhard){
                    turn.me.attack(1);
                    if(turn.me.health < 1){
                        continue;
                    }
                }
                for(int i = 0; i < NB_SPELLS;i++){
                    if(turn.me.spells[i]<1)continue;
                    turn.me.heal(i);
                    turn.boss.attack_magie(i);
                    turn.me.spells[i]--;

                }
                if(turn.boss.health < 1){
                    if(res > turn.me.spent){
                        res = turn.me.spent;
                    }
                    continue;
                }
                state sturn(turn);
                for(int i = 0; i < NB_SPELLS;i++){
                    if(sturn.me.spells[i]>0 || sturn.me.mana < spellbook[i].cost)continue;
                    turn = sturn;
                    if(turn.me.cast(i)){
                        turn.me.heal(i);
                        turn.boss.attack_magie(i);
                        if(turn.boss.health < 1){
                            if(res > turn.me.spent){
                                res = turn.me.spent;
                            }
                            continue;
                        }
                    }
                    
                    for(int i = 0; i < NB_SPELLS;i++){
                        if(turn.me.spells[i]<1)continue;
                        turn.me.heal(i);
                        turn.boss.attack_magie(i);
                        turn.me.spells[i]--;
                    }
                    if(turn.boss.health < 1){
                        if(res > turn.me.spent){
                            res = turn.me.spent;
                        }
                        continue;
                    }
                    turn.me.attack(turn.boss.damage);
                    if(turn.me.health < 1){
                        continue;
                    }
                    if(res < turn.me.spent)continue;
                    queue.push_back(turn);
                }
            }
            return res;
        }

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            std::cout << solvedayp1("./2015/day22/day22") << std::endl;

            std::cout << "Part 2" << std::endl;
            std::cout << solvedayp2("./2015/day22/day22") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            parse();
            int res = explore(game,false);
            return std::to_string(res);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            parse();
            int res = explore(game,true);
            return std::to_string(res);
        }
    }
}

