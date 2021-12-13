/* https://adventofcode.com/2021/day/3 */
#include <iostream>
#include <bitset>
#include <cmath>
#include <vector>

using ll = long long;
using b32 = std::bitset<32>;

std::vector<b32> test(const std::vector<b32>& input, const int pos, const bool keepMoreCommon){
    const int n = input.size();
    ll countOnes = 0;
    for (int i = 0; i < n; ++i){
        if(input[i][pos])
            countOnes++;
    }

    bool keepValue;

    if(keepMoreCommon){
        if(2*countOnes >= n)
            keepValue = true;
        else
            keepValue = false;
    }
    else{
        const ll countZeroes = n - countOnes;
        if(2*countOnes >= n)
            keepValue = false;
        else
            keepValue = true;
    }

    std::vector<b32> answer;

    for(const auto& v: input){
        if(v[pos] == keepValue)
            answer.push_back(v);
    }
    return answer;
}

template<typename T>
void printVec(std::vector<T> &v){
    if(v.empty())
        std::cerr << "{empty}";
    for(const auto& value: v)
        std::cerr << value << std::endl;
}

int main(){
    int n;
    ll ans1 = 0, ans2 = 0;
    ll msb = 0;
    std::cin >> n;
    std::vector<b32> input(n);

    ll max = 0;
    for(auto& v: input){
        std::cin >> v;
        max = (v.to_ullong() > max ? v.to_ullong() : max);
    }

    std::cerr << "max: " << max << std::endl;

    while(max){
        max /= 2;
        msb++;
    }

    std::cerr << "msb: " << msb << std::endl;

    auto vec = input;
    for (int j = msb - 1; vec.size() > 1 && j >= 0; --j){
        printVec(vec); std::cerr<<std::endl;
        vec = test(vec, j, true);
    }

    ans1 = vec[0].to_ullong();

    vec = input;
    for (int j = msb - 1; vec.size() > 1 && j >= 0; --j){
        printVec(vec); std::cerr<<std::endl;
        vec = test(vec, j, false);
    }

    ans2 = vec[0].to_ullong();

    std::cerr << ans1 << ' ' << ans2 << std::endl;

    std::cout << ans1 * ans2 << std::endl;
}