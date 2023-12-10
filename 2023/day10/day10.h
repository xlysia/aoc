#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <utils/cvutils.h>

using namespace std;

namespace aoc2023{
    namespace day10{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2023/day10/day10sample")=="8");
            std::cout << solvedayp1("./2023/day10/day10") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2023/day10/day10p2sample")=="10");
            std::cout << solvedayp2("./2023/day10/day10") << std::endl;
        }


        void drawTile(int x ,int y,vector<vector<int>>&tile,cv::Vec3b c){
            for(int i = 0; i <3;i++){
                for(int j = 0; j < 3;j++){
                    if(tile[i][j])setPixel(3*x+i,3*y+j,c);
                }
            }
        }
        pair<int,int> dir[4]{{-1,0},{0,1},{1,0},{0,-1}};
        map<char,vector<int>> book{{'.',{0,0,0,0}},{'|',{1,0,1,0}},{'-',{0,1,0,1}},{'7',{0,0,1,1}},{'L',{1,1,0,0}},{'J',{1,0,0,1}},{'F',{0,1,1,0}}};
        // draw pipes
        map<char,vector<vector<int>>> tiles{{'|',{{0,1,0},{0,1,0},{0,1,0}}},
                                            {'-',{{0,0,0},{1,1,1},{0,0,0}}},
                                            {'7',{{0,0,0},{1,1,0},{0,1,0}}},
                                            {'L',{{0,1,0},{0,1,1},{0,0,0}}},
                                            {'F',{{0,0,0},{0,1,1},{0,1,0}}},
                                            {'J',{{0,1,0},{1,1,0},{0,0,0}}},
                                            {'.',{{0,0,0},{0,0,0},{0,0,0}}}
                                            };
        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            vector<string> grid;
            tuple<int,int,char> curr;
            while(cin.peek() != EOF){
                getline(cin,line);
                grid.push_back(line);

                auto it = line.find('S');
                if(it != string::npos)curr = {grid.size()-1,it,'S'};
            }

            int m = grid.size();
            int n = grid[0].size();

            // find pipe of S
                // N E S W

            for(auto [k,v] : book){
                if(k=='.')continue;
                bool found = true;
                int i = get<0>(curr);
                int j = get<1>(curr);
                
                for(int d = 0; d < 4;d++){
                    if(!v[d])continue;
                    
                    auto [x,y] = dir[d];
                    x+=i,y+=j;
                    if(x<0 || y<0 || x>m-1 ||y>n-1){found = false;break;}
                    if(!book[grid[x][y]][(d+2)%4]){found = false;break;}
                }
                if(found){
                    grid[i][j] = k;
                    curr = {i,j,k};
                    break;
                }
            }

            int ans =  0;
            
            int H = 3*n;
            int W = 3*m;
            newFrame(cv::Size(H,W),cv::Scalar(0,0,0));
            


            for(int i = 0; i < m;i++){
                for(int j = 0; j < n;j++){
                    char c = grid[i][j];
                    auto tile = tiles[c];
                    drawTile(i,j,tile,cv::Vec3b(255,255,255));
                }
            }


            queue<tuple<int,int,char>> queue;
            queue.push(curr);
            grid[get<0>(curr)][get<1>(curr)] = '.';


            while(!queue.empty()){
                
                int s = queue.size();
                while(s--){
                    auto [i,j,c] = queue.front();
                
                    drawTile(i,j,tiles[c],cv::Vec3b(255, 215, 0));
                    queue.pop();
                    
                    for(int d = 0; d < 4;d++){
                        if(!book[c][d])continue;
                        
                        auto [x,y] = dir[d];
                        x+=i,y+=j;
                        if(grid[x][y]=='.')continue;
                        queue.push({x,y,grid[x][y]});
                        grid[x][y] = '.';
                    }            
                }
                resize(2);
                showResize("2023day10",1);
                ans++;
            }
            resize(2);
            showResize("2023day10",0);
            return std::to_string(ans-1);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            vector<string> grid;
            tuple<int,int,char> curr;
            while(cin.peek() != EOF){
                getline(cin,line);
                grid.push_back(line);

                auto it = line.find('S');
                if(it != string::npos)curr = {grid.size()-1,it,'S'};
            }

            int m = grid.size();
            int n = grid[0].size();

            // find pipe of S
                // N E S W

            for(auto [k,v] : book){
                if(k=='.')continue;
                bool found = true;
                int i = get<0>(curr);
                int j = get<1>(curr);
                
                for(int d = 0; d < 4;d++){
                    if(!v[d])continue;
                    
                    auto [x,y] = dir[d];
                    x+=i,y+=j;
                    if(x<0 || y<0 || x>m-1 ||y>n-1){found = false;break;}
                    if(!book[grid[x][y]][(d+2)%4]){found = false;break;}
                }
                if(found){
                    grid[i][j] = k;
                    curr = {i,j,k};
                    break;
                }
            }

            int ans =  0;
            int perim = 0;
            int H = 3*n;
            int W = 3*m;
            newFrame(cv::Size(H,W),cv::Scalar(0,0,0));

            for(int i = 0; i < m;i++){
                for(int j = 0; j < n;j++){
                    char c = grid[i][j];
                    auto tile = tiles[c];
                    drawTile(i,j,tile,cv::Vec3b(255,255,255));
                }
            }

            grid[get<0>(curr)][get<1>(curr)] = '.';
            int xprev = -1,yprev = -1;
            int x = get<0>(curr);
            int y = get<1>(curr);
            int xstart = x,ystart = y;
            char c = get<2>(curr);
            while(1){
                
                
                drawTile(x,y,tiles[c],cv::Vec3b(255, 215, 0));
                
                for(int d = 0; d < 4;d++){
                    if(!book[c][d])continue;
                    
                    auto [i,j] = dir[d];
                    i+=x,j+=y;
                    if(i == xprev && j == yprev)continue;
                    c = grid[i][j];
                    
                    xprev = x;
                    yprev = y;
                    x = i;
                    y = j;

                    break;
                }
                perim++;

                ans += (x+xprev)*(y-yprev);

                if(x == xstart && y == ystart)break;
                resize(2);
                showResize("2023day10",1);
            }
            resize(2);
            showResize("2023day10",1);
            ans = (abs(ans) - perim)/2+1;
            return std::to_string(ans);
        }
    }
}

