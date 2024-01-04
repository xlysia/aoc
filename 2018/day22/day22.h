#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <string>
#include <vector>
#include <complex>
#include <queue>
#include <tuple>

using namespace std;

namespace aoc2018{
    namespace day22{

        std::string solveday(std::string p);
        void run(){
            std::cout << "Part 1 & 2" << std::endl;
            assert (solveday("./2018/day22/day22sample")=="114 45");
            std::cout << solveday("./2018/day22/day22") << std::endl;

        }

        using coord = std::complex<int>;

        int getErosion(int x, int y, vector<vector<int>>& gi_memo, int depth, coord target){
            if(gi_memo[x][y] != -1){
                return gi_memo[x][y];
            }
            int gi;
            if(x == 0 && y == 0){
                gi = 0;
            }else if(x == target.real() && y == target.imag()){
                gi = 0;
            }else if(y == 0){
                gi = x * 16807;
            }else if(x == 0){
                gi = y * 48271;
            }else{
                gi = getErosion(x-1, y, gi_memo, depth, target)* getErosion(x, y-1, gi_memo, depth, target);
            }
            gi = (gi + depth) % 20183;
            gi_memo[x][y] = gi;
            return gi;
        }

        std::string solveday(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            int depth;
            int tx, ty;
            coord target;

            std::getline(std::cin, line);
            sscanf(line.c_str(), "depth: %d", &depth);
            std::getline(std::cin, line);
            sscanf(line.c_str(), "target: %d,%d", &tx, &ty);
            target = coord(tx, ty);

            int p1 =  0;

            vector<vector<int>> gi_memo(1000, vector<int>(1000, -1));
            for(int i = 0 ; i < tx+1; i++){
                for(int j = 0 ; j < ty+1; j++){
                    int gi = getErosion(i, j, gi_memo, depth, target);
                    p1 += gi % 3;
                }
            }

            int p2 = 0;

            const int ROCKY = 0;
            const int WET = 1;
            const int NARROW = 2;

            const int NEITHER = 0;
            const int TORCH = 1;
            const int CLIMBING = 2;

            priority_queue<tuple<int,int,int,int>,vector<tuple<int,int,int,int>>,greater<tuple<int,int,int,int>>> pq;
            pq.push({0, TORCH, 0,0});

            bool visited[1000][1000][3];
            memset(visited, 0, sizeof(visited));

            while(!pq.empty()){
                auto [time, tool, x,y] = pq.top();
                pq.pop();

                if(visited[x][y][tool]){
                    continue;
                }
                visited[x][y][tool] = true;

                if(x == tx && y == ty && tool == TORCH){
                    p2 = time;
                    break;
                }

                int gi = getErosion(x, y, gi_memo, depth, target);
                int type = gi % 3;

                if(type == ROCKY){
                    if(tool == CLIMBING){
                        pq.push({time+7, TORCH, x,y});
                    }else if(tool == TORCH){
                        pq.push({time+7, CLIMBING, x,y});
                    }
                }else if(type == WET){
                    if(tool == CLIMBING){
                        pq.push({time+7, NEITHER, x,y});
                    }else if(tool == NEITHER){
                        pq.push({time+7, CLIMBING, x,y});
                    }
                }else if(type == NARROW){
                    if(tool == TORCH){
                        pq.push({time+7, NEITHER, x,y});
                    }else if(tool == NEITHER){
                        pq.push({time+7, TORCH, x,y});
                    }
                }

                for(int i = 0 ; i < 4; i++){
                    int dx = 0;
                    int dy = 0;
                    if(i == 0){
                        dx = 1;
                    }else if(i == 1){
                        dx = -1;
                    }else if(i == 2){
                        dy = 1;
                    }else if(i == 3){
                        dy = -1;
                    }
                    int newx = x + dx;
                    int newy = y + dy;
                    if(newx < 0 || newy < 0){
                        continue;
                    }
                    int newgi = getErosion(newx, newy, gi_memo, depth, target);
                    int newtype = newgi % 3;
                    if(newtype == ROCKY){
                        if(tool != NEITHER){
                            pq.push({time+1, tool, newx,newy});
                        }
                    }else if(newtype == WET){
                        if(tool != TORCH){
                            pq.push({time+1, tool, newx,newy});
                        }
                    }else if(newtype == NARROW){
                        if(tool != CLIMBING){
                            pq.push({time+1, tool, newx,newy});
                        }
                    }
                }
            }

            return std::to_string(p1) + " " + std::to_string(p2);
        }
    }
}

