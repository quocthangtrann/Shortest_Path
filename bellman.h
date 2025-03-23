#ifndef BELLMAN_H
#define BELLMAN_H

#include <string>
using namespace std;

// Hàm Bellman-Ford để tính đường đi ngắn nhất
void BF(int graph[30][30], int num_v, char start_v, int value[30], int previous[30]);

// Hàm hiển thị đường đi ngắn nhất giữa 2 đỉnh
string BF_Path(int graph[30][30], int num_v, char start_v, char goal_v);

#endif
