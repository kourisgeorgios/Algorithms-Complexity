#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <functional>
#include <queue>
#include <map>
#include <stack>

using namespace std;

const int MY_INT_MAX = 1e9;

struct Node {
    int P;
    int S;
};

using AdjacencyList = vector<vector<int>>;
using Distances = vector<vector<long long>>;
using CustomNodeVector = vector<Node>;
using finalVector = vector<long long>;
using PathsMap = map<int, vector<int>>;

class Tree {
private:
    int nodes;
    AdjacencyList adjacency_list;
    Distances distances;
    CustomNodeVector Node;
    PathsMap Paths;

    void dfs_v2(int u, vector<int> &path, vector<bool> &is_visited);

public:
    explicit Tree(int v);

    void setEdge(int u, int v, int distance);

    void setNodeData(int u, int P, int S);

    void CalculateDistances();

    void SearchForPaths();

    void solution();

    finalVector final;
};

// Tree definition
Tree::Tree(int v) : nodes(v), adjacency_list(v + 1), distances(v + 1, vector<long long>(v + 1, MY_INT_MAX)),
                    Node(v + 1),
                    final(v + 1, LONG_MAX - 1) {
    for (int i = 1; i <= v; ++i) {
        distances[i][i] = 0;
    }
}

// Add edge on the Tree
void Tree::setEdge(int u, int v, int distance) {
    adjacency_list[u].push_back(v);
    adjacency_list[v].push_back(u);
    distances[u][v] = distance;
    distances[v][u] = distance;
}

// Set values for time P and S for each node
void Tree::setNodeData(int u, int P, int S) {
    Node[u].P = P;
    Node[u].S = S;
}

// Calculate distances between nodes in the tree using dfs
void Tree::CalculateDistances() {
    // Loop over nodes (excluding the Capital City node (number 1)
    for (int i = 2; i <= nodes; ++i) {
        // Initialize is_visited nodes and a stack for DFS
        vector<bool> is_visited(nodes + 1, false);
        stack<int> stack;
        stack.push(i); // Start DFS from node i
        is_visited[i] = true; // Mark node i as is_visited

        // Perform DFS
        while (!stack.empty()) {
            int v = stack.top(); // Get the top node from the stack
            stack.pop(); // Remove the top node from the stack

            // Explore adjacent nodes of node v
            for (int u: adjacency_list[v]) {
                if (!is_visited[u]) {
                    is_visited[u] = true; // Mark node u as is_visited

                    // Update distance from node i to node u based on node v
                    distances[i][u] = distances[i][v] + distances[v][u];

                    if (u != 1) {
                        stack.push(u);
                    }
                }
            }
        }
    }
}

void Tree::SearchForPaths() {
    vector<int> path; // Vector to store the current path being explored
    vector<bool> is_visited(nodes + 1, false); // Vector to track visited nodes

    // Iterate through all nodes to initiate DFS from each node
    for (int u = 1; u <= nodes; ++u) {
        // Perform dfs from node u
        dfs_v2(u, path, is_visited);
    }
}

void Tree::dfs_v2(int u, vector<int> &path, vector<bool> &is_visited) {
    // Mark the current node u as visited and add it to the path
    is_visited[u] = true;
    path.push_back(u);
    // If the current node is the destination node (node 1 - Capital), store the path
    if (u == 1) {
        int i = path[0]; // Get the starting node of the path
        Paths[i] = path; // Store the path in the Paths map
    } else {
        // Explore adjacent nodes of the current node u
        for (int next: adjacency_list[u]) {
            // Recursively traverse unvisited adjacent nodes
            if (!is_visited[next]) {
                dfs_v2(next, path, is_visited);
            }
        }
    }
    // Mark the current node 'u' as unvisited and remove it from the path
    is_visited[u] = false;
    path.pop_back();
}


void Tree::solution() {
    CalculateDistances();
    SearchForPaths();

    final[1] = 0;
    for (int i = 2; i <= nodes; ++i) {
        vector<int> new_node = Paths[i];

        if (new_node.size() == 2) {
            final[i] = distances[i][1] * Node[i].S + Node[i].P;
            continue;
        }
        // This is the recursive formula
        for (unsigned j = 1; j < new_node.size(); ++j) {
            long long distance = distances[i][new_node[j]];
            long long t = Node[i].P + Node[i].S * distance;
            long long new_t = final[new_node[j]];
            final[i] = min(final[i], t + new_t);
        }
    }
}

int main() {
    //freopen("lab02/relay/input3.txt", "r", stdin);
    int N;
    cin >> N;

    Tree tree(N);

    for (int i = 1; i < N; ++i) {
        int u, v, distance;
        cin >> u >> v >> distance;
        tree.setEdge(u, v, distance);
    }

    for (int i = 2; i <= N; ++i) {
        int P, S;
        cin >> P >> S;
        tree.setNodeData(i, P, S);
    }

    tree.solution();

    /*
    // FROM HERE
    freopen("lab02/relay/output3.txt", "r", stdin);

    vector<int> expectedOutput(N - 1);
    for (int i = 0; i < N - 1; ++i) {
        cin >> expectedOutput[i];
    }
    cout << "Expected Output: ";

    for (int i = 0; i < N - 1; ++i) {
        cout << expectedOutput[i] << " ";
    }
    cout << endl;

    cout << "Actual Output:   ";
    // UNTIL HERE
    */
    for (int i = 2; i < tree.final.size(); ++i) {
        cout << tree.final[i];
        if (i < tree.final.size() - 1)
            cout << " ";
    }

    cout << endl;
/*
    // FROM HERE
    bool correct = true;
    for (int i = 2; i < tree.final.size(); ++i) {
        if (expectedOutput[i - 2] != tree.final[i]) {
            correct = false;
            break;
        }
    }

    if (correct) {
        cout << "Correct!" << endl;
    } else {
        cout << "Wrong!" << endl;
    }
    // UNTIL HERE
*/
    return 0;
}