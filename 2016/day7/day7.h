#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2016{
    namespace day7{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);


        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2016/day7/day7sample")=="2");
            std::cout << solvedayp1("./2016/day7/day7") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2016/day7/day7sample")=="3");
            std::cout << solvedayp2("./2016/day7/day7") << std::endl;
        }

        bool doesTLS(std::string s){
            std::string w = "";
            bool shouldFind = true;
            bool found = false;
            for(char c:s){
                if(c == '['){shouldFind = false;w="";continue;}
                else if(c == ']'){shouldFind = true;w="";continue;}
                
                w.push_back(c);
                if((int)w.size()<4)continue;
                if((int)w.size()>4)w = w.substr(1,4);
                
                if(w[0] == w[3] && w[1]==w[2] && w[0]!=w[1]){
                    if(!shouldFind){
                        return false;
                    }
                    found = true;
                }
            }
            return found;
        }

        std::string mirror(std::string s){
            s.pop_back();
            return std::string(1,s[1])+s;
        }

        bool doesSSL(std::string s){
            std::string w = "";
            bool inB = false;
            std::vector<std::string> out;
            std::vector<std::string> in;
            for(char c:s){
                if(c == '['){inB = true;w="";continue;}
                else if(c == ']'){inB = false;w="";continue;}
                
                w.push_back(c);
                if((int)w.size()<3)continue;
                if((int)w.size()>3)w = w.substr(1,3);
                
                if(w[0] == w[2] && w[0]!=w[1]){
                    if(!inB){
                        if(std::find(in.begin(),in.end(),mirror(w)) != in.end()){
                            return true;
                        }
                        if(std::find(out.begin(),out.end(),w) == out.end()){
                            out.push_back(w);    
                        }
                    }else{
                        if(std::find(out.begin(),out.end(),mirror(w)) != out.end()){
                            return true;
                        }
                        if(std::find(in.begin(),in.end(),w) == in.end()){
                            in.push_back(w);    
                        } 
                    }
                }
            }
            return false;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            int res =  0;
            while(std::getline(std::cin,line)){
                res +=doesTLS(line);
            }
            return std::to_string(res);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            int res =  0;
            while(std::getline(std::cin,line)){
                res +=doesSSL(line);
            }
            return std::to_string(res);
        }
    }
}

