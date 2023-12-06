#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2023{
    namespace day6{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2023/day6/day6sample")=="288");
            std::cout << solvedayp1("./2023/day6/day6") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2023/day6/day6sample")=="71503");
            std::cout << solvedayp2("./2023/day6/day6") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            int ans =  1;
            string token;
            int duration;
            int record;

            getline(cin, line);
            stringstream ss1(line);
            getline(cin, line);
            stringstream ss2(line);
            ss1 >> token;
            ss2 >> token;
            while(ss1.peek() != EOF){

                ss1 >> duration;
                ss2 >> record;

                double t1 = max(0.,(duration - sqrt(duration*duration - 4*record))/2);
                if(t1 == ceil(t1))t1+=1;
                double t2 = (duration + sqrt(duration*duration - 4*record))/2;
                if(t2 == ceil(t2))t2-=1;
                ans *= floor(t2)-ceil(t1)+1;
            } 

            return std::to_string(ans);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            long long ans =  1;
            string token,part;
            long long duration = 0;
            long long record = 0;

            getline(cin, line);
            stringstream ss1(line);

            ss1 >> part;
            while(ss1.peek() != EOF){
                ss1 >> part;
                token.append(part);
            }
            duration = stoi(token);

            getline(cin, line);
            stringstream ss2(line); 
            ss2 >> part;
            token = "";
            while(ss2.peek() != EOF){
                ss2 >> part;
                token.append(part);
            }
            record = stoll(token);

            double t1 = max(0.,(duration - sqrt(duration*duration - 4*record))/2);
            if(t1 == ceil(t1))t1+=1;
            double t2 = (duration + sqrt(duration*duration - 4*record))/2;
            if(t2 == ceil(t2))t2-=1;
            ans *= floor(t2)-ceil(t1)+1;

            return std::to_string(ans);
        }
    }
}

