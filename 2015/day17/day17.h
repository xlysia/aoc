#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2015{
    namespace day17{
        
        int liters = 25;
        struct container{
            int capacity;
        };
        std::vector<container> containers;
        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            liters = 25;
            assert (solvedayp1("./2015/day17/day17sample")=="4");
            liters = 150;
            std::cout << solvedayp1("./2015/day17/day17") << std::endl;
            liters = 25;
            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2015/day17/day17sample")=="3");
            liters = 150;
            std::cout << solvedayp2("./2015/day17/day17") << std::endl;
        }

        void parse(){
            int val;
            containers.clear();
            while(std::cin >> val){
                container c;
                c.capacity = val;
                containers.push_back(c);
            }
        }

        int eval(std::vector<bool> combi){
            int val = 0;
            for(int i = 0; i < (int)combi.size();i++){
                val += combi[i];
            }
            return val;
        }

        int find(std::vector<bool> combi, int n){
            if(combi.size() == containers.size()){
                return n==0;
            }
            int res = 0;
            std::vector<bool> sval(combi);
            if(containers[combi.size()].capacity <= n){
                combi.push_back(true);
                res += find(combi, n - containers[combi.size()-1].capacity);
            }
            combi = sval;
            combi.push_back(false);
            res += find(combi, n);

            return res;
        }

        void find2(std::vector<bool> combi, int n, std::map<int,int>& vals,int& ref){
            if(combi.size() == containers.size()){
                if(n == 0){
                    int val = eval(combi);
                    if(val < ref)ref=val;
                    if(vals.find(val) == vals.end())vals[val]=0;
                    vals[val]+=1;
                }
                return;
            }
            std::vector<bool> sval(combi);
            if(containers[combi.size()].capacity <= n){
                combi.push_back(true);
                find2(combi, n - containers[combi.size()-1].capacity,vals,ref);
            }
            combi = sval;
            combi.push_back(false);
            find2(combi, n,vals,ref);

            return;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            parse();
            int res =  find({},liters);
            return std::to_string(res);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            parse();
            std::map<int,int> vals;
            int idx = 99999999;
            find2({},liters,vals,idx);
            return std::to_string(vals[idx]);
        }
    }
}

