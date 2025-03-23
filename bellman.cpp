#include "bellman.h"
#include <climits>
#include <vector>
#include <iostream>
using namespace std;

void BF(int graph[30][30], int num_v, char start_v, int value[30], int previous[30]) {
    int start_index = start_v - 'A';
    int* temp_val = new int[num_v];
    for (int i = 0; i < num_v; i++) {
        if (value[i] == 0) break;
        else if (i == num_v - 1) value[start_index] = 0;
    }
    for (int i = 0; i < num_v; i++) {
        temp_val[i] = value[i];
    }

    for (int u = 0; u < num_v; u++) {
        if (temp_val[u] == -1) continue;
        for (int v = 0; v < num_v; v++) {
            if (graph[u][v] != 0) {
                if (value[v] == -1 || temp_val[u] + graph[u][v] < value[v]) {
                    value[v] = temp_val[u] + graph[u][v];
                    previous[v] = u;
                }
            }
        }
    }

    delete[] temp_val;
}

string BF_Path(int graph[30][30], int num_v, char start_vertex, char goal_vertex) {
    int* value = new int[num_v];
    int* previous = new int[num_v];
    int start_index = start_vertex - 'A', end_index = goal_vertex - 'A';
    char vertex = goal_vertex;
    int vertex_index = end_index;
    string res = "";

    for (int i = 0; i < num_v; i++) {
        value[i] = -1;
        previous[i] = -1;
    }

    for (int i = 0; i < num_v - 1; i++) {
        BF(graph, num_v, start_vertex, value, previous);
    }

    do {
        res = vertex + res;
        vertex = previous[vertex_index] + 'A';
        vertex_index = previous[vertex_index];
        if (res[0] != start_vertex) res = ' ' + res;
    } while (res[0] != start_vertex);

    delete[] value;
    delete[] previous;

    return res;
}
