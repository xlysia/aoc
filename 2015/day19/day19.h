#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2015{
    namespace day19{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        struct molecule{
            public:
            std::vector<std::string> comp = {};
            std::string getstr(){
                std::string res = "";
                for(std::string c : comp){
                    res += c;
                }
                return res;
            }
            void chop(std::string line){
                comp.clear();
                for(char c : line){
                    if(c < 'a'){
                        comp.push_back(std::string(1, c));
                    }else{
                        comp.back().push_back(c);
                    }
                }
            }
        };

        molecule mol;
        std::map<std::string,std::vector<std::string>> swaps;
        std::map<std::string,std::vector<std::string>> rswaps;
        std::vector<std::string> rs; 
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2015/day19/day19sample")=="7");
            std::cout << solvedayp1("./2015/day19/day19") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2015/day19/day19sample")=="6");
            std::cout << solvedayp2("./2015/day19/day19") << std::endl;
        }

        bool myCmp(std::string s1, std::string s2)
        {
            if (s1.size() == s2.size()) {
                return s1 > s2;
            }
            else {
                return s1.size() > s2.size();
            }
        }
        void parse(){
            std::string line;
            swaps.clear();
            rswaps.clear();
            while(getline(std::cin, line)){
                if(line.size()<1){
                    getline(std::cin, line);
                    mol.chop(line);
                    break;
                }
                size_t pos;
                std::vector<std::string> x;
                while((pos = line.find(' ')) != std::string::npos){
                    x.push_back(line.substr(0, pos).c_str());
                    line.erase(0, pos + 1);
                }
                x.push_back(line);
                if(swaps.find(x[0])== swaps.end())swaps[x[0]] = {};
                if(rswaps.find(x[2])== rswaps.end()){
                    rswaps[x[2]] = {};
                    rs.push_back(x[2]);
                }
                swaps[x[0]].push_back(x[2]);
                rswaps[x[2]].push_back(x[0]);
            }

            std::sort(rs.begin(),rs.end(),myCmp);
        }

        int explore(){
            molecule smol(mol);
            std::vector<std::string> reached = {};

            for(int i = 0; i < (int)mol.comp.size();i++){
                if(swaps.find(mol.comp[i]) == swaps.end())continue;
                for(std::string s : swaps[mol.comp[i]]){
                    mol = smol;
                    mol.comp[i] = s;
                    std::string c = mol.getstr();
                    if(std::find(reached.begin(),reached.end(),c) == reached.end()){
                        reached.push_back(c);
                    }
                }
            }
            return reached.size();
        }


        int explore2(){
            std::string goal = mol.getstr();
            std::map<std::string,int> explored = {{ goal,0}};
            std::vector<std::string> queue = {goal};
            int i = 0;
            int T = goal.length(); 

            while(queue.size()>0){
                i++;
                std::string s = queue.back();
                queue.pop_back();
                std::string ns(s);
                bool b = false;
                for(std::string str : rs){
                    
                    int index = 0;
                    while ((index = s.find(str, index)) != (int)std::string::npos) {
                        for(std::string p : rswaps[str]){
                            s = ns;
                            s = s.substr(0,index)+ p +s.substr(index+str.length(),s.size());
                            if(p == "e" && s != "e")continue;
                            if(explored[ns]+1 > T) continue;
                            if(explored.find(s)==explored.end()){
                                explored[s]=explored[ns]+1;
                                queue.push_back(s);
                            }
                            else{
                                if(explored[s]>explored[ns]+1){
                                    explored[s]=explored[ns]+1;
                                    queue.push_back(s);  
                                }
                            }                 
                        }
                        s = ns;
                        index += str.length();
                        b = true;
                        break;
                    }
                    if(b)break;
                }
            }
            if(explored.find("e")==explored.end())return -999;
            else return explored["e"];
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            parse();
            int res = explore();
            return std::to_string(res);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            parse();
            int res = explore2();
            return std::to_string(res);
        }
    }
}

