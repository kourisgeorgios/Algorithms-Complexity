#include<bits/stdc++.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// Creating shortcut for an integer pair
typedef pair<int, int> iPair;
typedef pair<iPair, iPair> EdgePair;

bool customSort(const EdgePair& a, const EdgePair& b, double c) {
    int gain_a = a.first.first;
    int weight_a = a.first.second;
    int gain_b = b.first.first;
    int weight_b = b.first.second;

    return (gain_a - c * weight_a) > (gain_b - c * weight_b);
}

struct Graph {
    int V, E;
    vector<pair<iPair, iPair> > edges;

    // Constructor
    Graph(int V, int E) {
        this->V = V;
        this->E = E;
    }

    void addEdge(int u, int v, int p, int w) {
        edges.push_back({{p, w},
                         {u, v}});
    }

    // Function to find MST using Kruskal's
    // MST algorithm
    iPair kruskalMST(double c);

    pair<double, iPair> kruskalMaxGainPerWeight();

};

// To represent Disjoint Sets
struct DisjointSets {
    int *parent, *rnk;
    int n;

    // Constructor.
    DisjointSets(int n) {
        // Allocate memory
        this->n = n;
        parent = new int[n + 1];
        rnk = new int[n + 1];

        // Initially, all vertices are in
        // different sets and have rank 0.
        for (int i = 0; i <= n; i++) {
            rnk[i] = 0;

            //every element is parent of itself
            parent[i] = i;
        }
    }

    // Find the parent of a node 'u'
    // Path Compression
    int find(int u) {
        /* Make the parent of the nodes in the path
        from u--> parent[u] point to parent[u] */
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }

    // Union by rank
    void merge(int x, int y) {
        x = find(x), y = find(y);

        /* Make tree with smaller height
        a subtree of the other tree */
        if (rnk[x] > rnk[y])
            parent[y] = x;
        else // If rnk[x] <= rnk[y]
            parent[x] = y;

        if (rnk[x] == rnk[y])
            rnk[y]++;
    }
};

iPair Graph::kruskalMST(double c) {
    int mst_gain = 0;
    int mst_weight = 0;

    // Sort edges in increasing order on basis of cost
    sort(edges.begin(), edges.end(), [&](const EdgePair& a, const EdgePair& b) {
        return customSort(a, b, c);
    });

    // Create disjoint sets
    DisjointSets ds(V);

    // Iterate through all sorted edges
    vector<EdgePair>::iterator it;
    for (it = edges.begin(); it != edges.end(); it++) {
        int u = it->second.first;
        int v = it->second.second;

        int set_u = ds.find(u);
        int set_v = ds.find(v);

        if (set_u != set_v) {

            // Update MST weight
            mst_gain += it->first.first;
            mst_weight += it->first.second;

            // Merge two sets
            ds.merge(set_u, set_v);
        }
    }

    return {mst_gain, mst_weight};
}

pair<double, iPair> Graph::kruskalMaxGainPerWeight() {
    double low = 0.0, high = 200;
    pair<double, iPair> ans = {0.0, {0, 0}}; // {maxRatio, {sumGains, sumWeights}}
    const double eps = 1e-8; // Set precision for binary search

    // Perform binary search for the optimal value of 'c' to construct MST
    while (high - low > eps) {
        double mid = (low + high) / 2.0;
        iPair total;
        total = kruskalMST(mid);
        double currentRatio = total.first / static_cast<double>(total.second);

        if (total.first - mid * total.second >= 0) {
            if (currentRatio > ans.first) {
                ans = {currentRatio, total};
            }
            low = mid;
        } else {
            high = mid;
        }
    }

    return ans;
}


int gcd(int a, int b) {
    /* GCD(0, b) == b; GCD(a, 0) == a,
       GCD(0, 0) == 0 */
    if (a == 0)
        return b;
    if (b == 0)
        return a;

    /*Finding K, where K is the
      greatest power of 2
      that divides both a and b. */
    int k;
    for (k = 0; ((a | b) & 1) == 0; ++k) {
        a >>= 1;
        b >>= 1;
    }

    /* Dividing a by 2 until a becomes odd */
    while ((a & 1) == 0)
        a >>= 1;

    /* From here on, 'a' is always odd. */
    do {
        /* If b is even, remove all factor of 2 in b */
        while ((b & 1) == 0)
            b >>= 1;

        /* Now a and b are both odd.
           Swap if necessary so a <= b,
           then set b = b - a (which is even).*/
        if (a > b)
            swap(a, b); // Swap u and v.

        b = (b - a);
    } while (b != 0);

    /* restore common factors of 2 */
    return a << k;
}

int main() {
    int ans1,ans2, out1, out2;
    int V, E;
    freopen("testcases/bicriteriamst/input27.txt", "r", stdin);

    cin >> V >> E;

    Graph g(V, E);

    for (int i = 0; i < E; i++) {
        int u, v, p, w;
        cin >> u >> v >> p >> w;
        g.addEdge(u, v, p, w);
    }

    pair<double, iPair> answer = g.kruskalMaxGainPerWeight();
    double maxGainPerEdge = answer.first;


    ans1 = answer.second.first / gcd(answer.second.first, answer.second.second);
    ans2 = answer.second.second / gcd(answer.second.first, answer.second.second);

    cout << ans1 << " " << ans2<<endl;


    freopen("testcases/bicriteriamst/output27.txt", "r", stdin);
    cin >> out1 >> out2;
    cout << out1 << " " << out2<<endl;
    if(out1 == ans1 && out2 == ans2) {
        cout << "Correct"<<endl;
    }
    else {
        cout << "Wrong" <<endl;
    }
    return 0;
}
