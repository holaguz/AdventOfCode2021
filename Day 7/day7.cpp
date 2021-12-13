#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
int main(){
    int n;
    cin >> n;
    vector<long long> pos(n);
    for(auto& p: pos)
        cin >> p;

    sort(pos.begin(), pos.end());
    auto median = pos[(n + 1) / 2];
    long long mean = 0.0;
    long long ans = 0;

    for(const auto& p: pos){
        ans += abs(p - median);
        mean += p;
    }
    mean /= (double)n;
    cout << "Part 1: " << ans << endl;

    auto cost = [](long long n) -> long long {
        if(n < 0)
            n = -n;
        return (n*(n+1)) / 2;
    };

    ans = 0;
    for (int i = 0; i < pos.size(); ++i){
        ans += cost(
                abs(pos[i] - mean));
    }

    // 100220525 --> OK!
    // 100220548 is too high
    // 100748249 is too high
    cout << "Part 2: " << ans << endl;


}