#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <tuple>
#include <vector>
#include <string>
#include <complex>
#include <utils/cvutils.h>
#include <queue>

using namespace std;

namespace aoc2018{
    namespace day13{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2018/day13/day13sample")=="7,3");
            std::cout << solvedayp1("./2018/day13/day13") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2018/day13/day13sample2")=="6,4");
            std::cout << solvedayp2("./2018/day13/day13") << std::endl;
        }

        using coord = std::complex<int>;

        struct Cart{
            coord pos;
            coord dir;
            int turn;
            bool crashed;
        };

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            std::vector<std::string> grid;
            
            vector<Cart> carts;

            while(std::getline(std::cin, line)){
                
                for(int i = 0; i < (int)line.size(); i++){
                    if(line[i]=='<'){
                        line[i]='-';
                        carts.push_back({{i, (int)grid.size()}, {-1, 0}, 0,0});
                    }else if(line[i]=='>'){
                        line[i]='-';
                        carts.push_back({{i, (int)grid.size()}, {1, 0}, 0,0});
                    }else if(line[i]=='^'){
                        line[i]='|';
                        carts.push_back({{i, (int)grid.size()}, {0, -1}, 0,0});
                    }else if(line[i]=='v'){
                        line[i]='|';
                        carts.push_back({{i, (int)grid.size()}, {0, 1}, 0,0});
                    }
                }
                grid.push_back(line);
            }

            int m = grid.size();
            int n = grid[0].size();

            newFrame(cv::Size(n,m),cv::Scalar(0,0,0));

            vector<vector<bool>> occupied(m, vector<bool>(n, 0));
            for(Cart c : carts){
                occupied[c.pos.imag()][c.pos.real()] = 1;
            }

            while(1){
                sort(carts.begin(), carts.end(), [](Cart a, Cart b){
                    return a.pos.imag() < b.pos.imag() || (a.pos.imag() == b.pos.imag() && a.pos.real() < b.pos.real());
                });
                for(Cart& c : carts){
                    occupied[c.pos.imag()][c.pos.real()] = 0;
                    c.pos += c.dir;
                    if(occupied[c.pos.imag()][c.pos.real()]){
                        return std::to_string(c.pos.real()) + "," + std::to_string(c.pos.imag());
                    }
                    occupied[c.pos.imag()][c.pos.real()] = 1;
                    if(grid[c.pos.imag()][c.pos.real()] == '+'){
                        if(c.turn == 0){
                            c.dir *= coord(0, -1);
                        }else if(c.turn == 2){
                            c.dir *= coord(0, 1);
                        }
                        c.turn = (c.turn + 1) % 3;
                    }else if(grid[c.pos.imag()][c.pos.real()] == '/'){
                        if(c.dir.real() == 0){
                            c.dir *= coord(0, 1);
                        }else{
                            c.dir *= coord(0, -1);
                        }
                    }else if(grid[c.pos.imag()][c.pos.real()] == '\\'){
                        if(c.dir.real() == 0){
                            c.dir *= coord(0, -1);
                        }else{
                            c.dir *= coord(0, 1);
                        }
                    }

                    setPixel(c.pos.real(), c.pos.imag(), cv::Vec3b(255,255,255));
                    setPixel(c.pos.real()+c.dir.real(), c.pos.imag()+c.dir.imag(), cv::Vec3b(120,120,120));
                    resize(4);
                    showResize("Day 13", 1);
                }
            }
            return "ERROR";
        }

        std::string solvedayp2(std::string p){
           std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            std::vector<std::string> grid;
            
            vector<Cart> carts;

            while(std::getline(std::cin, line)){
                
                for(int i = 0; i < (int)line.size(); i++){
                    if(line[i]=='<'){
                        line[i]='-';
                        carts.push_back({{i, (int)grid.size()}, {-1, 0}, 0,0});
                    }else if(line[i]=='>'){
                        line[i]='-';
                        carts.push_back({{i, (int)grid.size()}, {1, 0}, 0,0});
                    }else if(line[i]=='^'){
                        line[i]='|';
                        carts.push_back({{i, (int)grid.size()}, {0, -1}, 0,0});
                    }else if(line[i]=='v'){
                        line[i]='|';
                        carts.push_back({{i, (int)grid.size()}, {0, 1}, 0,0});
                    }
                }
                grid.push_back(line);
            }

            int m = grid.size();
            int n = grid[0].size();

            newFrame(cv::Size(n,m),cv::Scalar(0,0,0));

            vector<vector<int>> occupied(m, vector<int>(n, -1));
            for(size_t i = 0; i < carts.size();i++){
                Cart& c = carts[i];
                occupied[c.pos.imag()][c.pos.real()] = i;
            }
            int N = carts.size();
            while(N >1){
                priority_queue<tuple<int, int, int>,vector<tuple<int,int,int>>,greater<tuple<int,int,int>>> q;
                for(size_t i = 0; i < carts.size();i++){
                    Cart& c = carts[i];
                    if(c.crashed)continue;
                    q.push({c.pos.imag(), c.pos.real(), i});
                }
                while(!q.empty()){
                    int i = get<2>(q.top());
                    q.pop();
                    Cart& c = carts[i];
                    if(c.crashed)continue;
                    occupied[c.pos.imag()][c.pos.real()] = -1;
                    c.pos += c.dir;
                    if(occupied[c.pos.imag()][c.pos.real()] != -1){
                        c.crashed = 1;
                        carts[occupied[c.pos.imag()][c.pos.real()]].crashed = 1;
                        occupied[c.pos.imag()][c.pos.real()] = -1;
                        N-=2;
                        continue;
                    }
                    occupied[c.pos.imag()][c.pos.real()] = i;
                    if(grid[c.pos.imag()][c.pos.real()] == '+'){
                        if(c.turn == 0){
                            c.dir *= coord(0, -1);
                        }else if(c.turn == 2){
                            c.dir *= coord(0, 1);
                        }
                        c.turn = (c.turn + 1) % 3;
                    }else if(grid[c.pos.imag()][c.pos.real()] == '/'){
                        if(c.dir.real() == 0){
                            c.dir *= coord(0, 1);
                        }else{
                            c.dir *= coord(0, -1);
                        }
                    }else if(grid[c.pos.imag()][c.pos.real()] == '\\'){
                        if(c.dir.real() == 0){
                            c.dir *= coord(0, -1);
                        }else{
                            c.dir *= coord(0, 1);
                        }
                    }

                    setPixel(c.pos.real(), c.pos.imag(), cv::Vec3b(255,255,255));
                    setPixel(c.pos.real()+c.dir.real(), c.pos.imag()+c.dir.imag(), cv::Vec3b(120,120,120));
                    resize(4);
                    showResize("Day 13", 1);
                }
                // delete crashed carts
            }
            carts.erase(std::remove_if(carts.begin(), carts.end(), [](Cart c){return c.crashed;}), carts.end());
            return std::to_string(carts[0].pos.real()) + "," + std::to_string(carts[0].pos.imag());
        }
    }
}

