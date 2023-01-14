#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2016{
    namespace day1{
 
        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);

        Point O[4] = {Point(0,-1),Point(1,0),Point(0,1),Point(-1,0)};

        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2016/day1/day1sample")=="12");
            std::cout << solvedayp1("./2016/day1/day1") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2016/day1/day1sample2")=="4");
            std::cout << solvedayp2("./2016/day1/day1") << std::endl;
        }

        int explore(){
            std::string token = "";
            Point p(0,0);
            int idx = 0;
            while(std::cin >> token){
                int o = token[0]=='L'?-1:1;
                int s = std::atoi(token.substr(1,token.size()).c_str());
                idx= (idx+o+4)%4;
                p += O[idx]*s;
            }
            return p.norm_1();
        }

        int explore2(){
            std::string token = "";
            Point p(0,0);
            std::vector<Point> visited = {p};
            int idx = 0;
            newFrame(cv::Size(300,100),cv::Scalar(0,0,0));
            setPixel(p.x+30,p.y+50,cv::Vec3b(255,255,255));
            while(std::cin >> token){
                int o = token[0]=='L'?-1:1;
                int s = std::atoi(token.substr(1,token.size()).c_str());
                idx= (idx+o+4)%4;
                for(int i = 0;i<s;i++){
                    p += O[idx];
                    setPixel(p.x+30,p.y+50,cv::Vec3b(255,255,255));
                    resize(5);
                    showResize("2016 day1",1);
                    if(std::find(visited.begin(),visited.end(),p)!=visited.end())return p.norm_1();
                    visited.push_back(p);
                }
            }
            return p.norm_1();
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            return std::to_string(explore());
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            return std::to_string(explore2());
        }
    }
}

