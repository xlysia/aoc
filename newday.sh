cd ./$1
N=$(ls -l ./ | grep -c ^d)
N=$((N+1))
cp -rf ../template ./day$N;
cd ./day$N;
mv ./day1 ./day$N
mv ./day1sample ./day${N}sample
mv ./day1.h ./day$N.h
sed -i "s/day1/day$N/g" ./day$N.h
sed -i "s/2015/$1/g" ./day$N.h
cd ..
cd ..
sed -i "18 i \ \ {\"$1_$N\",aoc$1::day$N::run}," main.cpp
bash setup.sh