#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <vector>
#include <regex>
#include "utils/cvutils.h"

using namespace std;


namespace aoc2018{
    namespace day10{

        void solvedayp1(std::string p);

        void run(){
            std::cout << "Part 1 & 2" << std::endl;
          //  solvedayp1("./2018/day10/day10sample");
            solvedayp1("./2018/day10/day10");

        }

        struct point{
            int x;
            int y;
            int vx;
            int vy;
        };

        void update(vector<point>& points){
            for(auto& p : points){
                p.x += p.vx;
                p.y += p.vy;
            }
        }

        void draw(vector<vector<bool>>&grid , vector<point> points){

            newFrame(cv::Size(1000, 1000),cv::Scalar(0,0,0));
            
            int minx = INT_MAX;
            int maxx = INT_MIN;
            for(auto& p : points){
                minx = min(minx, p.x);
                maxx = max(maxx, p.x);
                if(p.x < 0 || p.x >= 1000 || p.y < 0 || p.y >= 1000)continue;
                setPixel(p.x, p.y, cv::Vec3b(255,255,255));
            }
            if(minx > -1000 && maxx  < 1000)show("points", 0);
        }

        void solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            // parse line into points
            //position=<-40328,  10248> velocity=< 4, -1>
            // we wanna extart pair point and velocty -40328,  10248 and 4, -1
            // we can use regex to extract the numbers
            // we can use a stringstream to parse the string
            
            vector<point> points;

            while(std::getline(std::cin, line)){
                std::stringstream ss(line);
                // use regex to extract the numbers
                regex r("position=<\\s*(-?\\d+),\\s*(-?\\d+)> velocity=<\\s*(-?\\d+),\\s*(-?\\d+)>");
                smatch m;
                regex_search(line, m, r);
                points.push_back(point{stoi(m[1]), stoi(m[2]), stoi(m[3]), stoi(m[4])});
            }

            // now we have all the points
            vector<vector<bool>> grid = vector<vector<bool>>(1000, vector<bool>(1000, 0));

            newBackgroundFrame(cv::Size(1000, 1000),cv::Scalar(0,0,0));

            int N = 0;
            while(1){
                cout << ++N << endl;
                update(points);
                draw(grid, points);

            }
             
        }
    }
}

