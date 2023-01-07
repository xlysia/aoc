#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2015{
    namespace day11{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2015/day11/day11sample")=="abcdffaa");
            std::cout << solvedayp1("./2015/day11/day11") << std::endl;

            std::cout << "Part 2" << std::endl;
         //   assert (solvedayp2("./2015/day11/day11sample")=="-1");
            std::cout << solvedayp2("./2015/day11/day11") << std::endl;
        }

        bool ispassword(std::string s);
        std::string nextPassword(std::string psw);
        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string res;
            std::cin >> res;
            return nextPassword(res);
        }

        std::string solvedayp2(std::string p){
            return nextPassword(solvedayp1(p));
        }

        std::string nextPassword(std::string psw){
            bool b = true;
            while(!ispassword(psw)||b){
                b = false;
                int i = psw.size()-1;
                std::string n = "";
                while(1){
                    char c = psw[i];
                    if(c == 'z'){
                        c = 'a';
                        i--;
                        n = c + n;
                    }else{
                        c++;
                        n = c + n;
                        break;
                    }
                }
                psw = psw.substr(0,i)+n;
            }
            return psw;
        }

        bool ispassword(std::string s){
            bool cond1 = false;
            for(int i = 0; i < (int)s.size()-2;i++){
                cond1 |= (s[i]==s[i+1]-1)&&(s[i+1]==s[i+2]-1);
                if(cond1)break;
            }
            bool cond2 = true;
            for(char c : s){
                cond2 &= !(c=='o'||c=='l'||c=='i');
                if(!cond2)break;
            }
            std::string c3 = "";
            for(int i = 0; i < (int)s.size()-1;i++){
                if(c3.find(s[i])!= std::string::npos)continue;
                if(s[i]==s[i+1]){
                    c3.push_back(s[i]);
                    if(c3.size()>1)break;
                }
            }
            return cond1 && cond2 && (c3.size()>1);
        }
    }
}

