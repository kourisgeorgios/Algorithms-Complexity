#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

int maxProfit(int N, int K, vector<int>& prices) {
    vector<int> dp(N, 0);

    for (int k = 1; k <= K; ++k) {
        int maxDiff = dp[0] - prices[0];
        for (int i = 1; i < N; ++i) {
            int prev_dp = dp[i];
            dp[i] = max(dp[i - 1], prices[i] + maxDiff);
            maxDiff = max(maxDiff, prev_dp - prices[i]);
        }
    }

    return dp[N - 1];
}

int main() {
    int N, K;
    //freopen("lab02/chocolate/input1.txt", "r", stdin);
    cin >> N >> K;
    vector<int> prices(N);

    for (int i = 0; i < N; ++i) {
        cin >> prices[i];
    }

    //auto start = high_resolution_clock::now();

    int ans = maxProfit(N, K, prices);
    cout << ans<<endl;

    /*
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Time taken: " << duration.count() << " milliseconds" << endl;

    freopen("lab02/chocolate/output1.txt", "r", stdin);
    int out;
    cin >> out;

    cout << "Expected " << out << endl;
    cout << ans << endl;

    if (out == ans) {
        cout << "Correct" << endl;
    } else {
        cout << "Wrong" << endl;
    }
*/
    return 0;
}
