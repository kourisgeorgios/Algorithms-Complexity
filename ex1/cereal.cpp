#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool check(int array[], int &N, int &K, int &median) {
    int pre[N];
    for (int i = 0; i < N; i++) {
        if (array[i] >= median) {
            pre[i] = 1;
        } else {
            pre[i] = -1;
        }

        if (i > 0) {
            pre[i] += pre[i - 1];
        }

    }
    int submax = pre[K - 1];
    int submin = 0;
    for (int i = K; i < N; i++) {
        submin = min(submin, pre[i - K]);
        submax = max(submax, pre[i] - submin);
    }

    if (submax > 0) {
        return true;
    }

    return false;
}

int searchMedian(int array[], int N, int K) {
    int left = 1;
    int right = N + 1;
    int submax_median = -1;

    while (left <= right) {
        int centre = (left + right) / 2;
        if (check(array, N, K, centre)) {
            submax_median = centre;
            left = centre + 1;
        } else {
            right = centre - 1;
        }

    }
    return submax_median;
}

int main() {

    //freopen("testcases/cereal/input20.txt", "r", stdin);

    int N, K, ans, searchMedian_ans;
    cin >> N >> K;

    int availability[N];
    for (int i = 0; i < N; ++i) {
        cin >> availability[i];
    }
    /*
    freopen("testcases/cereal/output20.txt", "r", stdin);
    cin >> ans;
    */
    searchMedian_ans = searchMedian(availability, N, K);

    cout << searchMedian_ans << endl;
    /*
    if (ans == searchMedian_ans) {
        cout << "Correct" << endl;
    } else {
        cout << "Wrong" << endl;
    }*/

    return 0;
}