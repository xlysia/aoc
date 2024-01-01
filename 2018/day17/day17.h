#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <vector>
#include <string>
#include <complex>
#include <utils/cvutils.h>

using namespace std;

namespace aoc2018{
    namespace day17{

        std::string solveday(std::string p);
        void run(){
            
            std::cout << "Part 1" << std::endl;
            assert (solveday("./2018/day17/day17sample")=="57 29");
            std::cout << solveday("./2018/day17/day17") << std::endl;
        }
        using coord = complex<int>;
        using int2 = pair<int,int>;
        int2 operator+=(int2& a, const int2& b){
            a.first += b.first;
            a.second += b.second;
            return a;
        }
        pair<int,int> dfs(coord start ,vector<string>& grid, const int maxy){
            int2 ans = {0,0};
            int& count_running = ans.first;
            int& count_still = ans.second;
            if(grid[start.imag()][start.real()] == '#' || grid[start.imag()][start.real()] == '~'){
                return {0,0};
            }
            
            if(grid[start.imag()][start.real()] == '|'){
                return {0,0};
            }
            
            if(grid[start.imag()][start.real()] == '.'){
                count_running++;
                grid[start.imag()][start.real()] = '|';
                setPixel(start.real(),start.imag(),cv::Vec3b(255,0,0));
                showROI(start.real(),start.imag(),200,"",1);
            }

            if(start.imag()+1 <= maxy && grid[start.imag()+1][start.real()] == '.'){
                ans += dfs(start+coord(0,1),grid,maxy);
            }
            
            if(start.imag() == maxy) return ans; 

            if(grid[start.imag()+1][start.real()] == '#' || grid[start.imag()+1][start.real()] == '~'){
                // spread L and R
                coord left = start;
                while(grid[left.imag()][left.real()-1] != '#' && (grid[left.imag()+1][left.real()-1] == '#' || grid[left.imag()+1][left.real()-1] == '~')){
                    left += coord(-1,0);
                    if(grid[left.imag()][left.real()] == '.')count_running++;
                    grid[left.imag()][left.real()] = '|';
                    setPixel(left.real(),left.imag(),cv::Vec3b(255,0,0));
                    showROI(left.real(),left.imag(),200,"",1);
                }
                coord right = start;
                while(grid[right.imag()][right.real()+1] != '#'&& (grid[right.imag()+1][right.real()+1] == '#' || grid[right.imag()+1][right.real()+1] == '~')){
                    right += coord(1,0);
                    if(grid[right.imag()][right.real()] == '.')count_running++;
                    grid[right.imag()][right.real()] = '|';
                    setPixel(right.real(),right.imag(),cv::Vec3b(255,0,0));
                    showROI(right.real(),right.imag(),200,"",1);
                }
                
                if(grid[left.imag()][left.real()-1] == '#'&& grid[right.imag()][right.real()+1] == '#'){
                    for(int i = left.real(); i <= right.real(); i++){
                        grid[left.imag()][i] = '~';
                        count_running--;
                        count_still++;
                        setPixel(i,left.imag(),cv::Vec3b(120,0,0));
                    }
                    showROI(start.real(),start.imag(),200,"",1);
                    return ans;
                }
                ans += dfs(right+coord(1,0),grid,maxy);
                ans += dfs(left-coord(1,0),grid,maxy);
            }
            return ans;
        }

        std::string solveday(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            vector<string> grid = vector<string>(2000, string(2000, '.'));
            int minx = 2000;
            int maxx = 0;
            int miny = 2000;
            int maxy = 0;
            
            newFrame({2000,2000},cv::Scalar(255,255,255));

            while(getline(std::cin, line)){
                std::istringstream iss(line);
                char key1,key2,c;
                int val, min_, max_;
                iss >> key1 >> c >> val >> c >> c >> key2 >> min_ >> c >> c >> max_;
                if(key1 == 'x'){
                    miny = min(miny,min_);
                    maxy = max(maxy,max_);
                    maxx = max(maxx,val);
                    minx = min(minx,val);
                }
                else{
                    maxx = max(maxx,max_);
                    maxy = max(maxy,val);
                    minx = min(minx,min_);
                    miny = min(miny,val);
                }
                for(int i = min_; i <= max_; i++){
                    if(key1 == 'x'){
                        grid[i][val] = '#';
                        setPixel(val,i,cv::Vec3b(0,0,0));

                    }else{
                        grid[val][i] = '#';
                        setPixel(i,val,cv::Vec3b(0,0,0));

                    }
                }

            }


            setPixel(500,0,cv::Vec3b(0,0,0));
            for(int i = 1; i < miny;i++){
                setPixel(500,i,cv::Vec3b(255,0,0));
                grid[i][500] = '|';
            }
            coord sink = {500,0};
            int2 ans =  dfs(sink+coord(0,miny),grid,maxy);
            showROI({minx,0,maxx-minx+1,maxy+1},"",0);
            saveFrame(p);
            return std::to_string(ans.first+ans.second) + " " + std::to_string(ans.second);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
 	        std::string line;
            int ans = 0;
            return std::to_string(ans);
        }
    }
}

