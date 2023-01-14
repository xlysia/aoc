#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <vector>

namespace aoc2015{
    namespace day24{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2015/day24/day24sample")=="99");
            std::cout << solvedayp1("./2015/day24/day24") << std::endl;

            std::cout << "Part 2" << std::endl;
            std::cout << solvedayp2("./2015/day24/day24") << std::endl;
        }

        std::vector<int> weights;
        int W;
        int NB_GROUPS = 3;
        void parse(){
            int c;
            W = 0;
            weights.clear();
            while(std::cin >> c){
                weights.push_back(c);
                W+=c;
            }
        }

        struct group{
            public:
            int w = 0;
            long QE = 1;
            std::vector<int> list = {};

            bool add(int i){
                if(w+i > W/NB_GROUPS)return false;
                w+=i;
                QE*=i;
                list.push_back(i);
                return true;
            }
        };
        struct state{
            public:
            group groups[2]={{0,1,{}},{0,1,{}}};
            int idx=0;
            long QE = 1;
            int W = 0;
            bool add(int gid){
                bool b = groups[gid].add(weights[idx]);
                W+=weights[idx];
                QE = groups[0].QE;
                idx++;
                return b||gid>0;
            }
            int size0(){
                if(QE==1)return 99999999;
                return groups[0].list.size();
            }
        };

        long explore(){
            state board;

            state best;
            std::vector<state> queue = {board};
            
            int count = 1;
            while(queue.size()>0){
                count++;
                if(count%10000==0)std::cout << best.QE << " " << queue.size() << std::endl;
                state s = queue.back();
                queue.pop_back();
                state ns(s);
                for(int i = 0;i < 2;i++){
                    s = ns;
                    if(s.add(i)){
                        if(s.groups[0].w == W/NB_GROUPS){
                            if((best.size0() > s.size0())
                                 || (( best.size0()==s.size0()) && best.QE > s.QE)){
                                best = s;
                            }
                        }else if(W-s.W >= W/NB_GROUPS - s.groups[0].w){
                            queue.push_back(s);
                        }
                    }
                }
            }
            return best.QE;

        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            parse();
            return std::to_string(explore());
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            parse();
            NB_GROUPS = 4;
            return std::to_string(explore());
        }
    }
}

