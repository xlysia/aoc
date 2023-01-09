#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2015{
    namespace day15{
        int teaspoons = 100;
        bool bOnly500cal = false;
        const int nb_properties = 5;
        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2015/day15/day15sample")=="62842880");
            std::cout << solvedayp1("./2015/day15/day15") << std::endl;
            
            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2015/day15/day15sample")=="57600000");
            std::cout << solvedayp2("./2015/day15/day15") << std::endl;
        }
        struct ingredient{
            int properties[5] = {0,0,0,0,0};
        };
        void parse();
        long explore();
        std::vector<ingredient> ingredients;
        std::string solvedayp1(std::string p){
            bOnly500cal = false;
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            parse();
            long res =  explore();
            return std::to_string(res);
        }

        std::string solvedayp2(std::string p){
            bOnly500cal = true;
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            parse();
            long res =  explore();
            return std::to_string(res);
        }

        void parse(){
            ingredients.clear();
            std::string line;
            while(std::getline(std::cin , line)){
                size_t pos;
                std::vector<std::string> x;
                while((pos = line.find(' ')) != std::string::npos){
                    x.push_back(line.substr(0, pos).c_str());
                    line.erase(0, pos + 1);
                }
                x.push_back(line);
                ingredient I;
                for(int i = 0;i < nb_properties;i++){
                    I.properties[i] = std::atoi(x[(i+1)*2].c_str());
                }
                ingredients.push_back(I);
            }
            
        }

        long eval(std::vector<int> combi){
            int val[nb_properties];
            long res = 1;
            if(bOnly500cal){
                val[nb_properties-1] = 0; 
                for(int j=0; j < (int)ingredients.size();j++){
                    val[nb_properties-1] += ingredients[j].properties[nb_properties-1]*combi[j];
                }
                if(val[nb_properties-1]!=500)return 0;
            }

            for(int i=0 ; i<nb_properties -1;i++){
                val[i] = 0;
                for(int j=0; j < (int)ingredients.size();j++){
                    val[i] += ingredients[j].properties[i]*combi[j];
                }
                if(val[i]<=0)return 0;
                res*=val[i];
            }
            return res;
        }

        long find(std::vector<int> combi, int n){
            if(combi.size() == ingredients.size()-1){
                combi.push_back(n);
                return eval(combi);
            }
            long res = 0;
            std::vector<int> sval(combi);
            for(int i = 0; i < n+1;i++){
                combi = sval;
                combi.push_back(i);
                res = std::max(res,find(combi, n-i));
            }
            return res;
        }

        long explore(){
            return find({},teaspoons);
        }
    }
}

