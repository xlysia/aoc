#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <vector>
#include <algorithm>
#include <numeric>
#include <array>
#include <math.h>
#include <unordered_map>

using namespace std;


namespace aoc2023{
    namespace day24{

        std::string solvedayp1(std::string p,long long mini,long long maxi);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2023/day24/day24sample",7,27)=="2");
            std::cout << solvedayp1("./2023/day24/day24",200000000000000,400000000000000) << std::endl;

            std::cout << "Part 2" << std::endl;
            std::cout << solvedayp2("./2023/day24/day24") << std::endl;
        }

        using int3 = std::array<long long,3>;

        struct particle{
            int3 pos;
            int3 spd;
        };

        // overload operator - for int3
        int3 operator-(const int3& a, const int3& b){
            int3 c;
            for(int i = 0; i < 3; i++){
                c[i] = a[i] - b[i];
            }
            return c;
        }
        // operator *
        int3 operator*(const int3& a, const long long& b){
            int3 c;
            for(int i = 0; i < 3; i++){
                c[i] = a[i] * b;
            }
            return c;
        }
        
        using ll = long long;

        pair<double , double> intersect(particle p1, particle p2){
            // x = x0 + t * vx
            // y = y0 + t * vy
            
            /*
                intersect during path means there is a t1 and t2 such that
                (A) x0 + t1 * vx1 = x0 + t2 * vx2
                (B) y0 + t1 * vy1 = y0 + t2 * vy2

                solve the system of equations A et B to find t1 and t2
                (A)*vy1 - (B)*vx1 = 0 get t2
                (A)*vy2 - (B)*vx2 = 0 get t1

                t2 = (x0*vy1 - x0*vy2 + y0*vx1 - y0*vx2) / (vx1*vy2 - vx2*vy1)
                t1 = (x0*vy2 - x0*vy1 + y0*vx2 - y0*vx1) / (vx2*vy1 - vx1*vy2)
                            

            */
            double det = p2.spd[0]*p1.spd[1] - p1.spd[0]*p2.spd[1];
            if(det == 0) return {-1,-1};

            double t1 = (p2.spd[0]*p2.pos[1] + p2.spd[1]*p1.pos[0] - p2.pos[0]*p2.spd[1] - p2.spd[0]*p1.pos[1]) / det;
            double t2 = (p1.pos[0]*p1.spd[1] + p2.pos[1]*p1.spd[0] - p1.pos[1]*p1.spd[0] - p2.pos[0]*p1.spd[1]) / det;


            if(t1 < 0 || t2 < 0) return {-1,-1};

            return {t1,t2};

        }

        std::string solvedayp1(std::string p,long long mini,long long maxi){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            vector<particle> particles;

            while(getline(std::cin,line)){
                particle p;
                std::stringstream ss(line);
                char c;
                ss >> p.pos[0];
                ss >> c;
                ss >> p.pos[1];
                ss >> c;
                ss >> p.pos[2];
                ss >> c;
                ss >> p.spd[0];
                ss >> c;
                ss >> p.spd[1];
                ss >> c;
                ss >> p.spd[2];

                particles.push_back(p);
            }

            long long ans = 0;

            int K = particles.size();

            for(int i = 0; i < K; i++){
                for(int j = i+1; j < K; j++){
                    auto [t1,t2] = intersect(particles[i],particles[j]);
                    if(t1 < 0 || t2 < 0) continue;
                    double x1 = particles[i].pos[0] + t1 * particles[i].spd[0];
                    double y1 = particles[i].pos[1] + t1 * particles[i].spd[1];
                    double x2 = particles[j].pos[0] + t2 * particles[j].spd[0];
                    double y2 = particles[j].pos[1] + t2 * particles[j].spd[1];
                    if(x1 < mini || x1 > maxi || y1 < mini || y1 > maxi) continue;
                    if(x2 < mini || x2 > maxi || y2 < mini || y2 > maxi) continue;
                    ans++;
                }
            }

            return std::to_string(ans);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            vector<particle> particles;

            while(getline(std::cin,line)){
                particle p;
                std::stringstream ss(line);
                char c;
                ss >> p.pos[0];
                ss >> c;
                ss >> p.pos[1];
                ss >> c;
                ss >> p.pos[2];
                ss >> c;
                ss >> p.spd[0];
                ss >> c;
                ss >> p.spd[1];
                ss >> c;
                ss >> p.spd[2];

                particles.push_back(p);
            }
        
            // the rock will be thrown at the angle vx,vy,vz
            // the rock will be thrown from the point x,y,z

            int K = particles.size();

            int3 rock_spd;

            for(int d = 0; d < 3;d++){
                std::sort(particles.begin(),particles.end(),[&](const particle& a, const particle& b){
                    return a.spd[d] < b.spd[d];
                });
                int i = 0;
                int j = 1;
                unordered_map<long long , int> candidates;
                int maxi = 0;
                while(i < K){
                    while(j < K && particles[i].spd[d] == particles[j].spd[d]) j++;
                    // check for match
                    if(j-i < 3){
                        i = j;
                        continue;
                    }
                    // candidate v - vx will be gcd of xj - xi
                    vector<ll> diffs;
                    for(int k = i; k < j; k++){
                        for(int l = k+1; l < j; l++){
                            diffs.push_back(particles[l].pos[d] - particles[k].pos[d]);
                        }
                    }
                    ll v = std::accumulate(diffs.begin(),diffs.end(),diffs[0],[](ll a, ll b){
                        return std::__gcd(a,b);
                    });
                    // check if v is a candidate
                    candidates[v+particles[i].spd[d]] += j-i;
                    candidates[-v+particles[i].spd[d]] += j-i;
                    if(candidates[v+particles[i].spd[d]] > maxi){
                        maxi = candidates[v+particles[i].spd[d]];
                        rock_spd[d] = v+particles[i].spd[d];
                    }
                    if(candidates[-v+particles[i].spd[d]] > maxi){
                        maxi = candidates[-v+particles[i].spd[d]];
                        rock_spd[d] = -v+particles[i].spd[d];
                    }
                   // std::cout << "candidate v: " << v + particles[i].spd[d] << " " << -v + particles[i].spd[d] << std::endl;
                    i = j;
                }

            }

            cout << "rock spd: " << rock_spd[0] << " " << rock_spd[1] << " " << rock_spd[2] << endl;

            // find the first time the rock will be at the same position as a particle
            // consider the particle spd - rock spd
            // find the first time the particle will be at the same position as the rock

            // find intersection point between particle and rock
            particle p1 = particles[0];
            p1.spd = p1.spd - rock_spd;
            particle p2 = particles[1];
            p2.spd = p2.spd - rock_spd;

            auto t = intersect(p1,p2);

            int3 rock_pos = {0,0,0};
            rock_pos[0] = p1.pos[0] + t.first * p1.spd[0];
            rock_pos[1] = p1.pos[1] + t.first * p1.spd[1];
            rock_pos[2] = p1.pos[2] + t.first * p1.spd[2];

            cout << "starting point: " << rock_pos[0] << " " << rock_pos[1] << " " << rock_pos[2] << endl;

            return to_string(rock_pos[0]+rock_pos[1]+rock_pos[2]);
        }

        
    }
}

