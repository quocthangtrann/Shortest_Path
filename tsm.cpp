#include <vector>
#include <climits>
#include <string>
using namespace std;

const int INF = INT_MAX / 2;  // Đại diện giá trị vô cùng lớn

// Hàm tính toán chính (Dynamic Programming với Bitmask)
int calculate(int graph[30][30], int visited, int curr, int n, int start, vector<vector<int>>& dp, vector<vector<int>>& parent) {
    if (visited == (1 << n) - 1) {
        return (graph[curr][start] > 0) ? graph[curr][start] : INF;
    }

    if (dp[curr][visited] != -1) {
        return dp[curr][visited];
    }

    int minCost = INF;
    for (int next = 0; next < n; next++) {
        if (!(visited & (1 << next)) && graph[curr][next] > 0) {
            int cost = calculate(graph, visited | (1 << next), next, n, start, dp, parent) + graph[curr][next];
            if (cost < minCost) {
                minCost = cost;
                parent[curr][visited] = next;
            }
        }
    }

    dp[curr][visited] = minCost;
    return minCost;
}

// Hàm dựng đường đi từ bảng parent
string buildPath(vector<vector<int>>& parent, int start, int n) {
    int visited = 1 << start;
    int curr = start;
    string path(1, start + 'A');

    while (true) {
        int next = parent[curr][visited];
        if (next == -1) break;
        path += " " + string(1, next + 'A');
        visited |= (1 << next);
        curr = next;
    }

    path += " " + string(1, start + 'A'); // Quay lại điểm bắt đầu
    return path;
}

// Hàm giải quyết Traveling Salesman Problem
string Traveling(int graph[30][30], int n, char start_v) {
    vector<vector<int>> dp(n, vector<int>(1 << n, -1));
    vector<vector<int>> parent(n, vector<int>(1 << n, -1));
    int start = start_v - 'A';

    calculate(graph, 1 << start, start, n, start, dp, parent);

    return buildPath(parent, start, n);
}
