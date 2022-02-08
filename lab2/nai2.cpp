#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <functional>
#include <string>

using namespace std;

random_device rd;
mt19937 generator(rd());

auto eggholder = [](vector<double> v){
    double x = v.at(0), y = v.at(1);
    return (-1)*(y+47)*sin(sqrt(abs(x/2 + y + 47))) - x*sin(sqrt(abs(x - y - 47)));
};

auto eggholder_domain = [](vector<double> v) {
    return (abs(v[0]) <= 512) && (abs(v[1]) <= 512);
};

uniform_real_distribution<> distrib_xy(-512, 512);
vector<double> eggholder_p0 = {
        distrib_xy(generator),
        distrib_xy(generator),
};

auto bukin = [](vector<double> v){
    double x = v.at(0), y = v.at(1);
    return 100*sqrt(abs(y-(0.01*pow(x,2))))+0.01*abs(x+10);
};

auto bukin_domain = [](vector<double> v) {
    return (v[0] >= -15) && (v[0] <= -5) && (abs(v[1]) <= 3);
};

uniform_real_distribution<> distrib_x(-15, -5);
uniform_real_distribution<> distrib_y(-3, 3);
vector<double> ackley_p0 = {
        distrib_x(generator),
        distrib_y(generator),
};

ostream& operator<<(ostream& o, vector<double> v)
{
    for (auto e : v) {
        o << std::fixed << std::setprecision(5) << "\t" << e;
    }
    return o;
}


vector<double> hill_climbing(function<double(vector<double>)> func, function<bool(vector<double>)> func_domain, vector<double> p0, int iterations)
{
    auto p1 = p0;
    uniform_int_distribution<> distrib(0, p1.size() - 1);
    uniform_real_distribution<> distrib_r(-0.1, 0.1);

    if (!func_domain(p1)) throw std::invalid_argument("The p0 point must be in domain");
    for (int i = 0; i < iterations; i++) {
        auto p2 = p1;

        p2[distrib(generator)] += distrib_r(generator);
        if (func_domain(p2)) {
            double val2 = func(p2);
            double val1 = func(p1);
            if (val2 < val1) {
                p1 = p2;
            }
        }
    }
    return p1;
}

int main() {
    bool active = true;
    while(active == true){
        string func_chosen;
        cout << "Podaj nazwe funkcji: " << endl;
        cin >> func_chosen;
        int wybor;
        cout << "Podaj wartosc iteracji" << endl;
        cin >> wybor;
        if(func_chosen == "bukin"){
            
            auto result = hill_climbing(bukin, bukin_domain, ackley_p0, wybor);
            cout << result << " -> " << bukin(result) << endl;
            active = false;
        }else if(func_chosen == "eggholder"){
            auto result = hill_climbing(eggholder, eggholder_domain, eggholder_p0, wybor);
            cout << result << " -> " << eggholder(result) << endl;
            active = false;
        }else{
            cout << "Invalid argument" << endl;
        }
    }


    return 0;
}