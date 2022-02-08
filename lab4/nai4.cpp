#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <time.h>
using namespace std;
//generowanie liczb pseudolosowych
random_device device;
mt19937 rng(time(nullptr));
//sequence container that encapsulates dynamic size arrays
vector<int> generateGen(int n){
    vector<int> gen;
    uniform_int_distribution<> distrib(0, 1);
    for(int i=0; i<n; i++){
        gen.push_back(distrib(rng));
    }
    return gen;
}
//convert to pair
pair<unsigned long long int,unsigned long long int> genotypToFenotyp(vector<int> binary){
    unsigned long long int x = 0;
    unsigned long long int y = 0;
    unsigned long long int j=0;
    for(int i=63; i>=0; i--){
        x += binary.at(i)*(unsigned long long int)(1ULL<<j);
        y += binary.at(i+64)*(unsigned long long int)(1ULL<<j);
        j++;
    } 
    return {x,y};
}

vector<int> fenotypToGenotyp(unsigned long long int x,unsigned long long int y){
    vector<int> gen(128);
    for(int i=63; i>=0; i--){
        gen[i] = x%2;
        x = x/2;
        gen[i+64] = y%2;
        y = y/2;
    }
    return gen;
}

double bukin (double x, double y){
    return 100*sqrt(abs(y-(0.01*pow(x,2))))+0.01*abs(x+10);
};

double long_to_double(unsigned long long int num) {
    return num / 1.8446744e+18;
}

double fitness(vector<int> gen){
    auto feno = genotypToFenotyp(gen);
    double x = long_to_double(feno.first);
    double y = long_to_double(feno.second);
    return 1/(bukin(x,y)+1);
}

int main(){
    vector<int> geno = generateGen(128);
    for(int i=0;i<64;i++){
        cout << geno[i];
    }
    cout << endl;
    for(int i=64;i<128;i++){
        cout << geno[i];
    }
    cout << endl;
    auto feno = genotypToFenotyp(geno);
    cout << feno.first << endl << feno.second << endl;

    vector<int> geno1 = fenotypToGenotyp(feno.first, feno.second);
    for(int i=0;i<64;i++){
        cout << geno1[i];
    }
    cout << endl;
    for(int i=64;i<128;i++){
        cout << geno1[i];
    }
    cout << endl;

    double result = fitness(geno);
    cout << result;
    return 0;
}