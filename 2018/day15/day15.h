#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <complex>
#include <algorithm>
#include <tuple>
#include <utils/cvutils.h>

using namespace std;

namespace aoc2018{
    namespace day15{
        using coord = std::complex<int>;

        auto comp = [](const coord& lhs, const coord& rhs){
                        return lhs.imag() < rhs.imag() || (lhs.imag() == rhs.imag() && lhs.real() < rhs.real());};

        int dist(coord a, coord b){
            return abs(a.real()-b.real()) + abs(a.imag()-b.imag());
        }   

        const int MAX_HEALTH = 200;
        const int MAX_AP = 3;

        struct unit{
            coord pos;
            int hp;
            int ap;
            char type;
            int target = -1;
            bool operator<(const unit& rhs) const{
                return pos.real() < rhs.pos.real() || (pos.real() == rhs.pos.real() && pos.imag() < rhs.pos.imag());
            }
        };

        coord dirs[4] = {{0,-1},{-1,0},{1,0},{0,1}};

        coord dfs(coord pos, vector<vector<int>>& visited, vector<string>& grid){
            int d = visited[pos.imag()][pos.real()];
            if(d == 1)  return pos;
            bool found = false;
            coord ans = {9999,9999};
            for(coord dir : dirs){
                dir += pos;
                if (visited[dir.imag()][dir.real()] == d-1 && grid[dir.imag()][dir.real()] == '.'){
                    ans = min(ans,dfs(dir, visited,grid),comp);
                    found = true;
                }
            }
            if(!found)return {9999,9999};
            return ans;
        }

        void domove(unit& _unit, vector<string>& grid, vector<vector<int>>& occupied, vector<unit>& units,int& nb_elves, int& nb_goblins){
            // bfs to find closest target
            int m = grid.size();
            int n = grid[0].size();
            
            _unit.target = -1;
            queue<coord> q;
            q.push(_unit.pos);
            vector<vector<int>> visited(m, vector<int>(n, -1));
            visited[_unit.pos.imag()][_unit.pos.real()] = 0;
            vector<coord> targets;

            int d = 0;
            while(targets.empty() && !q.empty()){
                int s = q.size();
                d++;
                while(s--){
                    coord pos = q.front();
                    q.pop();
                    for(coord dir : dirs){  
                        dir += pos;
                        if (dir.real() < 0 || dir.real() >= n || dir.imag() < 0 || dir.imag() >= m) continue;
                        if (visited[dir.imag()][dir.real()] !=-1) continue;
                        if (grid[dir.imag()][dir.real()] == '#') continue;

                        visited[dir.imag()][dir.real()] = d;
                        if(occupied[dir.imag()][dir.real()] != -1){
                            unit& u = units[occupied[dir.imag()][dir.real()]];
                            if (u.type != _unit.type){
                                targets.push_back(dir);
                            }
                        }else{
                            q.push(dir);
                        }
                    }
                }
            }
            sort(targets.begin(), targets.end(),comp);
            if (targets.size() > 0){

                coord pos = dfs(targets[0], visited,grid);
                _unit.target = occupied[targets[0].imag()][targets[0].real()];
                if (pos != _unit.pos && pos != targets[0]){
                    grid[_unit.pos.imag()][_unit.pos.real()] = '.';
                    setPixel(_unit.pos.real(), _unit.pos.imag(), cv::Vec3b(255,255,255));
                    grid[pos.imag()][pos.real()] = _unit.type;
                    setPixel(pos.real(), pos.imag(), _unit.type == 'E'?cv::Vec3b(0,0,255):cv::Vec3b(0,255,0));
                    occupied[pos.imag()][pos.real()] = occupied[_unit.pos.imag()][_unit.pos.real()];
                    occupied[_unit.pos.imag()][_unit.pos.real()] = -1;

                    _unit.pos = pos;
                }
                int health = MAX_HEALTH+1;
                _unit.target = -1;
                for(auto dir : dirs){
                    dir+= _unit.pos;
                    if (dir.real() < 0 || dir.real() >= n || dir.imag() < 0 || dir.imag() >= m) continue;
                    if (grid[dir.imag()][dir.real()] == '#') continue;
                    if( grid[dir.imag()][dir.real()] == '.') continue;
                    if( grid[dir.imag()][dir.real()] == _unit.type) continue;

                    if(health > units[occupied[dir.imag()][dir.real()]].hp){
                        health = units[occupied[dir.imag()][dir.real()]].hp;
                        _unit.target = occupied[dir.imag()][dir.real()];
                    }
                }

                if(_unit.target != -1){
                    unit& u = units[_unit.target];
                    u.hp -= _unit.ap;
                    if (u.hp <= 0){
                        occupied[u.pos.imag()][u.pos.real()] = -1;
                        grid[u.pos.imag()][u.pos.real()] = '.';
                        setPixel(u.pos.real(), u.pos.imag(), cv::Vec3b(255,255,255));
                        if (u.type == 'E') nb_elves--;
                        else nb_goblins--;
                    }
                }

            }
        }

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2018/day15/day15sample")=="27730");
            assert (solvedayp1("./2018/day15/day15sample2")=="36334");
            assert (solvedayp1("./2018/day15/day15sample3")=="39514");
            assert (solvedayp1("./2018/day15/day15sample4")=="27755");
            assert (solvedayp1("./2018/day15/day15sample5")=="28944");
            assert (solvedayp1("./2018/day15/day15sample6")=="18740");

            std::cout << solvedayp1("./2018/day15/day15") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2018/day15/day15sample")=="4988");
            std::cout << solvedayp2("./2018/day15/day15") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            vector<string> grid;
            vector<unit> units;
            vector<vector<int>> occupied;
            int nb_rounds = 0;
            int nb_elves = 0;
            int nb_goblins = 0;
            while (getline(cin, line)){
                grid.push_back(line);
                occupied.push_back(vector<int>(line.size(), -1));
                for(size_t i = 0; i < line.size(); i++){
                    if (line[i] == 'E' || line[i] == 'G'){
                        unit u;
                        u.pos = {(int)i, (int)grid.size()-1};
                        u.hp = MAX_HEALTH;
                        u.ap = MAX_AP;
                        u.type = line[i];
                        if (line[i] == 'E') nb_elves++;
                        else nb_goblins++;
                        occupied[u.pos.imag()][u.pos.real()] = units.size();
                        units.push_back(u);
                    }
                }
            }

            int m = grid.size();
            int n = grid[0].size();

            newBackgroundFrame({2*n, 2*m}, cv::Scalar(0,0,0));

            for(int i = 0; i < m; i++){
                for(int j = 0; j < n; j++){
                    if (grid[i][j] == '#')continue;
                    setBackgroundPixel(j,i, cv::Vec3b(255,255,255));
                }
            }

            newFrame({2*n, 2*m}, cv::Scalar(0,0,0));
            for(unit& u : units){
                if (u.hp <= 0) continue;
                setPixel(u.pos.real(), u.pos.imag(), cv::Vec3b(0,0,0));
                if (u.type == 'E') setPixel(u.pos.real(), u.pos.imag(), cv::Vec3b(0,0,255));
                else setPixel(u.pos.real(), u.pos.imag(), cv::Vec3b(0,255,0));
            }

            resize(10);
            showResize("Day 15", 1);

            while(nb_elves && nb_goblins){

                

                priority_queue<tuple<int,int,int>,vector<tuple<int,int,int>>,greater<tuple<int,int,int>>> q;
                for(size_t i = 0; i < units.size();i++){
                    if (units[i].hp <= 0)continue; 
                    q.push({units[i].pos.imag(), units[i].pos.real(), i});
                }
                bool fullturn = true;
                while(!q.empty()){
                    unit& u = units[get<2>(q.top())];
                    q.pop();
                    if (u.hp <= 0) continue;
                    if(!nb_elves || !nb_goblins){fullturn = false;break;}
                    domove(u,grid, occupied, units, nb_elves, nb_goblins);
                    resize(10);

                    showResize("Day 15", 1);
                }
                nb_rounds+=fullturn;
            }
            int ans = 0;
            for(unit& u : units){
                if (u.hp <= 0) continue;
                ans += u.hp;
            }
            ans *= nb_rounds;
            return std::to_string(ans);
        }

        int IsElfPerfWin(vector<string> grid, vector<unit> units, vector<vector<int>> occupied, int nb_elves, int nb_goblins){
            int nb_rounds = 0;
            while(nb_elves && nb_goblins){
                
                priority_queue<tuple<int,int,int>,vector<tuple<int,int,int>>,greater<tuple<int,int,int>>> q;
                for(size_t i = 0; i < units.size();i++){
                    if (units[i].hp <= 0)continue; 
                    q.push({units[i].pos.imag(), units[i].pos.real(), i});
                }
                int oldnb_elves = nb_elves;
                bool fullturn = true;
                while(!q.empty()){
                    unit& u = units[get<2>(q.top())];
                    q.pop();
                    if (u.hp <= 0) continue;
                    if(!nb_elves || !nb_goblins){fullturn = false;break;}

                    domove(u,grid, occupied, units, nb_elves, nb_goblins);
                }
                if(oldnb_elves != nb_elves) return false;
                nb_rounds+=fullturn;
            }

            int ans = 0;
            for(unit& u : units){
                if (u.hp <= 0) continue;
                ans += u.hp;
            }
            ans *= nb_rounds;
            return ans;
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            vector<string> grid;
            vector<unit> units;
            vector<vector<int>> occupied;

            int nb_elves = 0;
            int nb_goblins = 0;
            while (getline(cin, line)){
                grid.push_back(line);
                occupied.push_back(vector<int>(line.size(), -1));
                for(size_t i = 0; i < line.size(); i++){
                    if (line[i] == 'E' || line[i] == 'G'){
                        unit u;
                        u.pos = {(int)i, (int)grid.size()-1};
                        u.hp = MAX_HEALTH;
                        u.ap = MAX_AP;
                        u.type = line[i];
                        if (line[i] == 'E') nb_elves++;
                        else nb_goblins++;
                        occupied[u.pos.imag()][u.pos.real()] = units.size();
                        units.push_back(u);
                    }
                }
            }
            newFrame({2*(int)grid[0].size(), 2*(int)grid.size()}, cv::Scalar(0,0,0));
            int L = 3,R = 200;
            int ans = 0;
            while(L <= R){
                int M = (L+R)/2;
                for(unit& u : units){
                    if (u.hp <= 0) continue;
                    if(u.type == 'E') u.ap = M;
                }
                ans = IsElfPerfWin(grid, units, occupied, nb_elves, nb_goblins);
                if(ans > 0){
                    R = M-1;
                }else{
                    L = M+1;
                }
            };
            return std::to_string(ans);
        }
    }
}

