#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <vector>

using namespace std;

namespace aoc2018{
    namespace day6{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p,int max_dist);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2018/day6/day6sample")=="17");
            std::cout << solvedayp1("./2018/day6/day6") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2018/day6/day6sample",32)=="16");
            std::cout << solvedayp2("./2018/day6/day6",10000) << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            using point = pair<int,int>;

            std::vector<point> points;

            int max_x = 0;
            int max_y = 0;

            while (std::getline(std::cin, line)){
                std::istringstream iss(line);
                int x,y;
                char c;
                iss >> x >> c >> y;
                points.push_back(point(x,y));
                max_x = std::max(max_x, x);
                max_y = std::max(max_y, y);
            }

            int n = points.size();
            vector<int> area(n, 0);
            vector<bool> infinite(n,false);

            for(int x = 0; x < max_x; x++){
                for(int y = 0; y < max_y; y++){
                    int min_dist = max_x + max_y;
                    int min_dist_idx = -1;
                    bool tie = false;
                    for(int i = 0; i < n; i++){
                        int dist = abs(x - points[i].first) + abs(y - points[i].second);
                        if (dist < min_dist){
                            min_dist = dist;
                            min_dist_idx = i;
                            tie = false;
                        } else if (dist == min_dist){
                            tie = true;
                        }
                    }
                    if (!tie){
                        area[min_dist_idx]++;
                    }

                    if (x == 0 || x == max_x || y == 0 || y == max_y){
                        infinite[min_dist_idx] = true;
                    }
                }
            }


            int ans =  0;

            for(int i = 0; i < n; i++){
                if (!infinite[i]){
                    ans = std::max(ans, area[i]);
                }
            }

            return std::to_string(ans);
        }

        std::string solvedayp2(std::string p, int max_dist){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
 	        std::string line;

            using point = pair<int,int>;

            std::vector<point> points;

            int max_x = 0;
            int max_y = 0;

            while (std::getline(std::cin, line)){
                std::istringstream iss(line);
                int x,y;
                char c;
                iss >> x >> c >> y;
                points.push_back(point(x,y));
                max_x = std::max(max_x, x);
                max_y = std::max(max_y, y);
            }

            int n = points.size();

            // we wanna find the size of the region where the sum of the distances to all points is less than max_dist
            // start with a bounding box around all points
            int min_x = max_x;
            int min_y = max_y;
            int max_x2 = 0;
            int max_y2 = 0;

            for(int i = 0; i < n; i++){
                min_x = std::min(min_x, points[i].first);
                min_y = std::min(min_y, points[i].second);
                max_x2 = std::max(max_x2, points[i].first);
                max_y2 = std::max(max_y2, points[i].second);
            }

            auto dist = [&](int x, int y){
                int ans = 0;
                for(int i = 0; i < n; i++){
                    ans += abs(x - points[i].first) + abs(y - points[i].second);
                }
                return ans;
            };

            int ans = 0;

            for(int x = 0; x <= max_x; x++){
                for(int y = 0; y <= max_y; y++){
                    if (dist(x,y) < max_dist){
                        ans++;
                    }
                }
            }

            return std::to_string(ans);
        }
    }
}

