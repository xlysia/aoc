#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <string>
#include <vector>  
#include <set>
#include <map>
#include <climits> 
#include <cmath>
#include <algorithm>
#include <unordered_map>

using namespace std;
namespace aoc2017{
    namespace day20{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2017/day20/day20sample")=="0");
            std::cout << solvedayp1("./2017/day20/day20") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2017/day20/day20sample2")=="1");
            std::cout << solvedayp2("./2017/day20/day20") << std::endl;
        }
        struct particle{
            int pos[3];
            int spd[3];
            int acc[3];
        };
        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            std::vector<particle> particles;
            
            while(std::getline(std::cin, line)){
                particle p;
                std::stringstream ss(line);
                std::string token;
                int i = 0;

                while(getline(ss, token, '>')){
                    token = token.substr(token.find('<')+1);
                    std::stringstream ss2(token);
                    std::string token2;
                    int j = 0;
                    while(getline(ss2, token2, ',')){
                        if (i == 0){
                            p.pos[j] = std::stoi(token2);
                        } else if (i == 1){
                            p.spd[j] = std::stoi(token2);
                        } else if (i == 2){
                            p.acc[j] = std::stoi(token2);
                        }
                        j++;
                    }
                    i++;
                }
                particles.push_back(p);
            }

            int K = particles.size();
            // there are no nullvalues in the input
            // the one with the lowest acceleration will stay closer to <0,0,0>
            // in the long term
            int minacc = INT_MAX;
            int ans = -1;
            for (int i = 0; i < K; i++){
                int acc = 0;
                for (int j = 0; j < 3; j++){
                    acc += std::abs(particles[i].acc[j]);
                }
                if (acc < minacc){
                    minacc = acc;
                    ans = i;
                }
            }
            return std::to_string(ans);
        }

        int sim(std::vector<particle>& particles, int N){
            int K = particles.size();
            int ans = K;
            while(N--){
                for(int j = 0; j < K; j++){
                    if(particles[j].pos[0] == INT_MAX){
                        continue;
                    }
                    for(int k = 0; k < 3; k++){
                        
                        particles[j].spd[k] += particles[j].acc[k];
                        particles[j].pos[k] += particles[j].spd[k];
                    }
                }

                // lets check for possible collisions
                std::set<int> todelete;
                for(int a = 0; a < K ; a++){
                    if(particles[a].pos[0] == INT_MAX){
                        continue;
                    }
                    for(int b = a+1; b < K;b++){
                        if(particles[b].pos[0] == INT_MAX){
                            continue;
                        }
                        bool col = true;
                        for(int k = 0; k < 3; k++){
                            if(particles[a].pos[k] != particles[b].pos[k]){
                                col = false;
                                break;
                            }
                        }
                        if(col){
                            todelete.insert(a);
                            todelete.insert(b);

                        }
                    }
                }
                for(auto it = todelete.begin(); it != todelete.end(); it++){
                    particles[*it].pos[0] = INT_MAX;
                    ans--;
                }
            }
            return ans;
        }

        int physics(std::vector<particle>& particles){
            /*
                x(t) = x_0 + t*v_0 + t*(t+1)/2*a
                x(t) = x_0 + (v_0 + a/2)*t + (a/2)*t^2

                xA(t) = xA_0 + (vA_0 + aA/2)*t + (aA/2)*t^2
                xB(t) = xB_0 + (vB_0 + aB/2)*t + (aB/2)*t^2

                xA(t) = xB(t)
                xA_0 + (vA_0 + aA/2)*t + (aA/2)*t^2 = xB_0 + (vB_0 + aB/2)*t + (aB/2)*t^2
                (aA/2 - aB/2)*t^2 + (vA_0 + aA/2 - vB_0 - aB/2)*t + (xA_0 - xB_0) = 0

                a = (aA - aB)/2
                b = (vA_0 - vB_0) + (aA - aB)/2
                c = xA_0 - xB_0

                t = (-b +- sqrt(b^2 - 4*a*c))/(2*a)


                // resoudre l'equation quadratique a*t*t + b*t + c = 0

                // si a = 0
                // b*t + c = 0
                // t = -c/b

                // si a != 0
                // t = (-b +- sqrt(b^2 - 4*a*c))/(2*a)

            */
            int K = particles.size();
            std::vector<std::tuple<double,int,int>> collisions;

            for(int i = 0; i < K ; i++){
                for(int j = i+1; j < K;j++){
                    // check if the roots are real
                    // chek collision in 3d

                    std::map<double,int> roots;
                    int dim = 3;
                    for(int k = 0; k < 3; k++){

                /*      
                        a = (aA - aB)/2
                        b = vA_0 - vB_0 + (aA - aB)/2
                        c = xA_0 - xB_0
                */
                        double a = (particles[i].acc[k] - particles[j].acc[k])/2.0;

                        if( a == 0){
                            // linear
                            // if the speed is the same they will never collide
                            if(particles[i].spd[k] == particles[j].spd[k]){
                                if(particles[i].pos[k] == particles[j].pos[k]){
                                    // they are in the same position
                                    // they will collide at time 0
                                    dim--;
                                }
                                continue;
                            }
                            // b*t + c = 0
                            double b = particles[i].spd[k] - particles[j].spd[k];
                            double c = particles[i].pos[k] - particles[j].pos[k];

                            double root = -c/b;
                            if(root >= 0){
                                roots[root]++;
                            }
                            continue; 
                        }

                        double b = particles[i].spd[k] - particles[j].spd[k] + (particles[i].acc[k] - particles[j].acc[k])/2.0;
                        double c = particles[i].pos[k] - particles[j].pos[k];
                        double tmp = b*b - 4*a*c;

                        if(tmp >=0){
                            double root = (-b- sqrt(tmp))/(2*a);
                            if(root >= 0){
                                roots[root]++;
                            }
                            root = (-b + sqrt(tmp))/(2*a);
                            if(root >= 0){
                                roots[root]++;
                            }
                        }
                    }

                    for(auto it = roots.begin(); it != roots.end(); it++){
                        if(it->second == dim){
                            collisions.push_back({it->first,i,j});
                        }
                    }
                }
            }
            std::sort(collisions.begin(),collisions.end(),[](std::tuple<double,int,int> a, std::tuple<double,int,int> b){
                return std::get<0>(a) > std::get<0>(b);
            });

            unordered_map<int,double> collided;
            
            while(!collisions.empty()){
                tuple<double,int,int> t = collisions.back();
                collisions.pop_back();
                int i = get<1>(t);
                int j = get<2>(t);
                double coltime = get<0>(t);
                if(     (collided.find(i) != collided.end() && collided[i]< coltime)
                    ||  (collided.find(j) != collided.end() && collided[j]< coltime))
                {
                    continue;
                }
                collided[i] = coltime;
                collided[j] = coltime;
            }
            

            return K - collided.size();

        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;



            std::vector<particle> particles;
            
            while(std::getline(std::cin, line)){
                particle p;
                std::stringstream ss(line);
                std::string token;
                int i = 0;

                while(getline(ss, token, '>')){
                    token = token.substr(token.find('<')+1);
                    std::stringstream ss2(token);
                    std::string token2;
                    int j = 0;
                    while(getline(ss2, token2, ',')){
                        if (i == 0){
                            p.pos[j] = std::stoi(token2);
                        } else if (i == 1){
                            p.spd[j] = std::stoi(token2);
                        } else if (i == 2){
                            p.acc[j] = std::stoi(token2);
                        }
                        j++;
                    }
                    i++;
                }
                particles.push_back(p);
            }


            int ans = physics(particles);
//            int ans  = sim(particles,1000); 
            
            return std::to_string(ans);
        }
    }
}

