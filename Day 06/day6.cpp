/* https://adventofcode.com/2021/day/6 */
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

int main(){
    int n; cin >> n;
    vector<ll> stages(9);
    for (int i = 0; i < n; ++i){
        int x; cin >> x;
        stages[x]++;
    }

    const int max_days = 256;

    for (int k = 0; k <= max_days; ++k){
        ll new_fish = stages[0];
        for (int i = 0; i < 8; ++i)
            stages[i] = stages[i + 1];
        stages[8] = new_fish;
        stages[6] += new_fish;
    }

    ll ans = 0;
    for (int i = 0; i < 8; ++i){
        ans += stages[i];
    }
    cout << ans << endl;
}