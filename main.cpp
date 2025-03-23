#include "bellman.h" // Import các hàm Bellman-Ford
#include "tsm.h"     // Import các hàm TSP

#include <iostream>
#include <fstream>
#include <sstream>
#include <climits> // Thêm thư viện để sử dụng INT_MAX
using namespace std;

const int INF = INT_MAX / 2; // Định nghĩa hằng số INF

// Hàm hiển thị đồ thị
void displayGraph(int graph[30][30], int num_v) {
    cout << "Ma trận trọng số của đồ thị (" << num_v << " đỉnh):" << endl;
    for (int i = 0; i < num_v; i++) {
        for (int j = 0; j < num_v; j++) {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
}

// Hàm đọc đồ thị từ file
void readGraphFromFile(const string& filename, int graph[30][30], int& num_v) {
    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Không thể mở file: " << filename << endl;
        exit(1);
    }

    num_v = 0; // Khởi tạo số đỉnh

    string line;
    while (getline(inputFile, line) && num_v < 30) {
        istringstream iss(line);
        int col = 0;

        // Đọc từng giá trị trong dòng
        while (iss >> graph[num_v][col] && col < 30) {
            col++;
        }

        num_v++; // Đếm số dòng (cũng là số đỉnh vì đồ thị vuông)
    }

    inputFile.close();

    // Debug: Hiển thị số lượng đỉnh đã đọc
    cout << "Số đỉnh đã đọc từ file: " << num_v << endl;
}

void testBellmanFordStatic(int graph[30][30], int num_v) {
    cout << "\n=== Test Case Bellman-Ford ===" << endl;

    char start = 'A';
    char goal = 'E';

    int value[30], previous[30];
    for (int i = 0; i < 30; i++) {
        value[i] = -1;
        previous[i] = -1;
    }

    // Tính Bellman-Ford từ đỉnh bắt đầu
    BF(graph, num_v, start, value, previous);

    // Kết quả khoảng cách
    cout << "\nKết quả Bellman-Ford từ đỉnh " << start << ":\n";
    for (int i = 0; i < num_v; i++) {
        cout << "Đỉnh " << (char)(i + 'A') << ": Khoảng cách = " << value[i] << endl;
    }

    // Hiển thị đường đi ngắn nhất từ A đến E
    cout << "\nĐường đi từ " << start << " đến " << goal << ": ";
    cout << BF_Path(graph, num_v, start, goal) << endl;
}


// Hàm test Traveling Salesman Problem (TSP)
void testTSP(int graph[30][30], int num_v) {
    cout << "\n=== Test Case Traveling Salesman ===" << endl;

    char start = 'A';

    // Tính và hiển thị kết quả
    string path = Traveling(graph, num_v, start);
    cout << "\nĐường đi ngắn nhất qua tất cả các đỉnh (bắt đầu tại " << start << "):\n";
    cout << path << endl;
}

// Hàm chính
int main() {
    int graph[30][30] = {0};
    int num_v = 0;

    // Nhập tên file input
    string filename;
    cout << "Nhập tên file input (ví dụ: Trave_in12.txt): ";
    cin >> filename;

    // Đọc đồ thị từ file
    readGraphFromFile(filename, graph, num_v);

    // Hiển thị đồ thị
    displayGraph(graph, num_v);

    // Chạy test case Bellman-Ford
    testBellmanFordStatic(graph, num_v);

    // Chạy test case Traveling Salesman
    testTSP(graph, num_v);

    return 0;
}
