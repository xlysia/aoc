#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <map> 

namespace aoc2015{
    namespace day13{
        const int table_size = 10;
        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2015/day13/day13sample")=="330");
            std::cout << solvedayp1("./2015/day13/day13") << std::endl;

            std::cout << "Part 2" << std::endl;
         //   assert (solvedayp2("./2015/day13/day13sample")=="-1");
            std::cout << solvedayp2("./2015/day13/day13") << std::endl;
        }

        int table[table_size][table_size];
        std::map<std::string,int> people;

        class state{
            public:
            int val = 1; 
            int res = -99999;
            std::vector<int> path = {};
            bool bfull(){
                return val == (1 << people.size())-1;
            }

            int value(){
                if(path.size()<2)return -999999;
                res = 0;
                for(int i = 0; i < (int)path.size();i++){
                    res += table[path[i]][path[(i+1)%path.size()]];
                    res += table[path[(i+1)%path.size()]][path[i]];
                }
                return res;
            }
        };

        int explore();
        void parse();
        
        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            parse();

            int res =  explore();
            return std::to_string(res);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            parse();
            people["Me"] = people.size();
            int res =  explore();
            return std::to_string(res);
        }

        void parse(){
            for(int i = 0; i < table_size;i++){
                for(int j = 0; j < table_size;j++){
                    table[i][j] = 0;
                }
            }
            people.clear();
            std::string line;
            while(std::getline(std::cin,line)){
                size_t pos;
                std::vector<std::string> x;
                while((pos = line.find(' ')) != std::string::npos){
                    x.push_back(line.substr(0, pos).c_str());
                    line.erase(0, pos + 1);
                }
                line.pop_back();
                x.push_back(line);
                if(people.find(x[0]) == people.end())people[x[0]] = people.size();
                if(people.find(x.back()) == people.end())people[x.back()] = people.size();
                int val = (x[2]=="lose"?-1:1)*std::atoi(x[3].c_str());
                table[people[x[0]]][people[x.back()]] = val;
            }
        }

        int explore(){
            state s;
            state best;
            best.val = -1;
            s.path.push_back(0);
            std::vector<state> queue = {s};
            while(queue.size() > 0){
                s = queue.back();
                queue.pop_back();
                if(s.bfull() && s.value() >= best.value()){
                    best = s;         
                }
                for(int i = 0 ; i < (int) people.size() ; i++ ){
                    if((s.val & (1 << i)) == 0){
                        state ns(s);
                        ns.val |= (1<<i);
                        ns.path.push_back(i);
                        queue.push_back(ns);
                    }
                }
            }
            return best.value();
        }
    }
}

