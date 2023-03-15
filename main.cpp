#include <bits/stdc++.h>
using namespace std;

vector<int> getSwaps(vector<vector<pair<float, int>>>& output, int i1, int i2) {
    float sum;
    for (auto a : output) sum += a[i1].first - a[i2].first;

    vector<pair<float, vector<int>>> swaps(4);
    swaps[0].first = abs(sum);
    swaps[1].second = vector<int>(1);

    float temp_sum = INT_MAX;
    int bestIndex = 0;
    for (int i = 0; i < 22; i++) {
        float temp = abs(sum - 2 * (output[i][i1].first - output[i][i2].first));
        if (temp_sum > temp) {
            temp_sum = temp;
            swaps[1].second[0] = i;
        };
    }

    swaps[1].first = temp_sum;
    if (temp_sum < swaps[bestIndex].first) bestIndex = 1;

    swaps[2].second = vector<int>(2);
    temp_sum = INT_MAX;
    for (int i = 0; i < 22; i++) {
        for (int j = i+1; j < 22; j++) {
            float temp =
                abs(sum - 2 * (output[i][i1].first - output[i][i2].first +
                               output[j][i1].first - output[j][i2].first));
            if (temp_sum > temp) {
                temp_sum = temp;
                swaps[2].second[0] = i;
                swaps[2].second[1] = j;
            };
        }
    }

    swaps[2].first = temp_sum;
    if (temp_sum < swaps[bestIndex].first) bestIndex = 2;

    swaps[3].second = vector<int>(3);
    temp_sum = INT_MAX;
    for (int i = 0; i < 22; i++) {
        for (int j = i+1; j < 22; j++) {
            for (int k = j+1; k < 22; k++) {
                float temp =
                    abs(sum - 2 * (output[i][i1].first - output[i][i2].first +
                                   output[j][i1].first - output[j][i2].first +
                                   output[k][i1].first - output[k][i2].first));
                if (temp_sum > temp) {
                    // cout << i << ' ' << j << ' ' << k << '\n';
                    temp_sum = temp;
                    swaps[3].second[0] = i;
                    swaps[3].second[1] = j;
                    swaps[3].second[2] = k;
                };
            }
        }
    }
    swaps[3].first = temp_sum;

    if (temp_sum < swaps[bestIndex].first) bestIndex = 3;
    return swaps[bestIndex].second;
}

auto getMatrix(vector<pair<float, int>> &a){
    auto output = vector<vector<pair<float, int>>>(22);
    for (int i = 0; i < 20; i++) {
        if (i % 2 == 0) {
            for (int j = 4 * i; j < 4 * i + 4; j++) {
                output[i].push_back(a[j]);
            }
        } else {
            for (int j = 4 * i + 3; j >= 4 * i; j--) {
                output[i].push_back(a[j]);
            }
        }
    }
    output[20].push_back(a[80]);
    output[20].push_back(a[81]);
    output[21].push_back(a[83]);
    output[21].push_back(a[82]);
    return output;
}

int main() {
    int n;
    cin >> n;
    auto vp = vector<pair<float, int>>();
    for (int i = 1; i <= n; i++) {
        float a;
        cin >> a;
        vp.push_back({a, i});
    }
    sort(vp.begin(), vp.end(), greater<pair<float, int>>());
    
    auto output = getMatrix(vp);;

    // for (auto a : output) {
    //     for (auto b : a) cout << b.first << "   ";
    //     cout << '\n';
    // }
    auto swaps = getSwaps(output, 0, 1);
    auto swaps2 = getSwaps(output, 2, 3);

    for(auto a: swaps) cout << a << ' ';
    cout << '\n';
    for(auto a: swaps2) cout << a << ' ';
    cout << '\n';

    for(auto a: swaps) swap(output[a][0], output[a][1]);
    for(auto a: swaps) swap(output[a][0], output[a][1]);

    for(auto &line: output) {
        for(auto number: line) cout << number.first << ' ';
        cout << '\n';
    }
    cout << '\n';
    for(auto &line: output) {
        for(auto number: line) cout << number.second << ' ';
        cout << '\n';
    }

    float sum = 0;
    for (auto a : output)
        sum += a[0].first - a[1].first;
    cout << sum << endl;

    sum = 0;
    for (auto a : output)
        sum += a[2].first - a[3].first;
    cout << sum;

    return 0;
}
