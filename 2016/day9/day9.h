#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2016{
    namespace day9{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        int explore(std::string s);
        long decompress(std::string s);
        void run(){
            std::cout << "Part 1" << std::endl;

            assert (explore("A(2x2)BCD(2x2)EFG")==11); 
            assert (explore("(6x1)(1x3)A")==6);
            assert (explore("X(8x2)(3x3)ABCY")==18);                      
            std::cout << solvedayp1("./2016/day9/day9") << std::endl;

            std::cout << "Part 2" << std::endl;
          //  assert (decompress("X(8x2)(3x3)ABCY")==20);
            assert (decompress("(25x3)(3x3)ABC(2x3)XY(5x2)PQRSTX(18x9)(3x2)TWO(5x7)SEVEN")==445);
            assert (decompress("(27x12)(20x12)(13x14)(7x10)(1x12)A")==241920);
            std::cout << solvedayp2("./2016/day9/day9") << std::endl;
        }

        struct repeat{
            int a = 0;
            int b = 0;
            std::string mem = "";
        };

        int explore(std::string s){
            int res = 0;
            bool open = false;
            repeat r;
            for(int i =0 ; i <(int)s.size();i++){
                char c = s[i];
                if(c == ' ')continue;
                if(c == '(')
                {
                    open = true;
                    r.a = 0;
                    r.b = 0;
                    r.mem = "";
                }else
                if(open){
                    if(c == 'x'){
                        r.a = std::atoi(r.mem.c_str());
                        r.mem = "";
                    }
                    else{
                        if(c == ')'){
                            r.b = std::atoi(r.mem.c_str());
                            r.mem = "";
                            res += r.a*r.b;
                            i += r.a;
                            open = false;
                            continue;
                        }else{
                            r.mem.push_back(c);
                        }
                    }
                }else{
                    res+=1;
                }
            }
            return res;
        }


        std::stringstream ss;
        long readsegment(int len , int i){
            long res = 0;
            bool open = false;
            repeat r;
            char c;

            for(;0<len;len--){
                ss >> c;
                while(c == ' ')ss >> c;
                if(c == '(')
                {
                    open = true;
                    r.a = 0;
                    r.b = 0;
                    r.mem = "";
                }else
                if(open){
                    if(c == 'x'){
                        r.a = std::atoi(r.mem.c_str());
                        r.mem = "";
                    }
                    else{
                        if(c == ')'){
                            r.b = std::atoi(r.mem.c_str());
                            r.mem = "";
                            res += readsegment(r.a, r.b)*i;
                            open = false;
                            len -= r.a;
                            continue;
                        }else{
                            r.mem.push_back(c);
                        }
                    }
                }else{
                    res+=i;
                }
            }
            return res;
        }

        long decompress(std::string s){
            ss = std::stringstream(s);
            bool open = false;
            repeat r;
            long res = 0;
            char c;
            while(ss >> c)
            {
               if(c == ' ')continue;
                if(c == '(')
                {
                    open = true;
                    r.a = 0;
                    r.b = 0;
                    r.mem = "";
                }else
                if(open){
                    if(c == 'x'){
                        r.a = std::atoi(r.mem.c_str());
                        r.mem = "";
                    }
                    else{
                        if(c == ')'){
                            r.b = std::atoi(r.mem.c_str());
                            r.mem = "";
                            res += readsegment(r.a, r.b);
                            open = false;
                            continue;
                        }else{
                            r.mem.push_back(c);
                        }
                    }
                }else{
                    res++;
                }
            
            }
 
            return res;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            std::getline(std::cin,line);

            return std::to_string(explore(line));
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            std::getline(std::cin,line);
            return std::to_string(decompress(line));
        }
    }
}

