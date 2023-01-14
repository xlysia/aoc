#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <utils/md5.h>

namespace aoc2016{
    namespace day5{

        std::string solvedayp1(std::string p);
        std::string solveday(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
           // assert (solvedayp1("./2016/day5/day5sample")=="18f47a30");
            assert (solveday("./2016/day5/day5sample")=="05ace8e3");
            solveday("./2016/day5/day5");
        }

        std::string solveday(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string roomid;
            std::cin >> roomid;
            std::string res = "";
            std::string res2 = "________"; 
            int i = 0;
            while(1){
                std::string s = md5(roomid+std::to_string(i));
                if(s.substr(0,5) == "00000"){
                    if(res.size() < 8){
                        res.push_back(s[5]);
                        if(res.size()==8)std::cout << "P1: " << res << std::endl;
                    }
                    if(s[5]>='0' && s[5]<'8'){
                        if(res2[s[5]-'0'] == '_')res2.replace(s[5]-'0',1,std::string(1,s[6]));
                    }
                    if(res2.find('_')==std::string::npos){
                        std::cout << "P2: " << res2 << std::endl;
                        break;
                    }
                    std::cout << i << " " << s[5] << " "<< s[6] << " " << res << " " << res2 << std::endl;
                }
                i++;
            }

            return res2;
        }


        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string roomid;
            std::cin >> roomid;
            std::string res = "";
            int i = 0;
            while(1){
                std::string s = md5(roomid+std::to_string(i));
                if(s.substr(0,5) == "00000"){
                    res.push_back(s[5]);
                    if(res.size()==8)break;
                }
                i++;
            }

            return res;
        }
    }
}

