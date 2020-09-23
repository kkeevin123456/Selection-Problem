#include<bits/stdc++.h>

using namespace std;

struct timespec diff(struct timespec start, struct timespec end) {
    struct timespec temp;
    if ((end.tv_nsec-start.tv_nsec)<0) {
        temp.tv_sec = end.tv_sec-start.tv_sec-1;
        temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    } else {
        temp.tv_sec = end.tv_sec-start.tv_sec;
        temp.tv_nsec = end.tv_nsec-start.tv_nsec;
    }
    return temp;
}

int Partition(vector<int>& vec, int front, int end) {
    int pivot = vec[end];
    int i = front - 1;
    for (int j=front; j<end; j++) {
        if (vec[j] < vec[end]) {
            i++;
            std::swap(vec[i], vec[j]);
        }
    }
    i++;
    std::swap(vec[i], vec[end]);
    return i;
}

void Quicksort(vector<int>& vec, int front, int end) {
    if (front < end) {
        int pivot = Partition(vec, front, end);
        Quicksort(vec, front, pivot-1);
        Quicksort(vec, pivot+1, end);
    }
}

void PruneAndSearch(vector<int> vec, int k, int& result) {
    int size = vec.size();
    //cout << "size: " << size << endl;
    if (size <= 10) {
        Quicksort(vec, 0, size-1);
        result = vec[k-1];
        return;
    }
    int idx = 0;
    vector<vector<int>> matrix;
    vector<int> temp;
    while (size >= 5) {
        size -= 5;
        for (int i=0; i<5; i++) {
            temp.push_back(vec[idx]);
            idx++;
        }
        Quicksort(temp, 0, 4);
        matrix.push_back(temp);
        temp.clear();
    }
    // if (n mod 5) != 0
    if ((vec.size() % 5) != 0) {
        int count = 0;
        while (size > 0) {
            size--;
            count++;
            temp.push_back(vec[idx]);
            idx++;
        }
        for (; count<5; count++) {
            temp.push_back(INT_MAX);
        }
        Quicksort(temp, 0, 4);
        matrix.push_back(temp);
        temp.clear();
    }

    // debug
    /*for (int i=0; i<matrix.size(); i++) {
        for (int j=0; j<5; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }*/

    // find p
    int p = matrix[matrix.size()/2][2];

    // partition S into three subsets
    vector<int> S1;
    vector<int> S2;
    vector<int> S3;

    for (int i: vec) {
        if (i == INT_MAX)
            continue;
        else if (i < p)
            S1.push_back(i);
        else if (i == p)
            S2.push_back(i);
        else
            S3.push_back(i);
    }

    int s1_size = S1.size(), s2_size = S2.size();
    if (s1_size >= k)
        PruneAndSearch(S1, k, result);
    else if (s1_size + s2_size >= k){
        result = p;
        return;
    }
    else 
        PruneAndSearch(S3, k - s1_size - s2_size, result);
}

int main() {
    struct timespec start, end;
    double time_used;

    vector<int> v;
    ifstream input("input.txt");
    ofstream outputQS("QS.txt");
    ofstream outputPS("PS.txt");
    int n, k_th, temp;

    input >> n >> k_th;

    for (int i=0; i<n; i++) {
        input >> temp;
        v.push_back(temp);
    }

    vector<int> QS_result = v;

    // QS
    // 計算開始時間
    clock_gettime(CLOCK_MONOTONIC, &start);

    Quicksort(QS_result, 0, n-1);
    //cout << QS_result[k_th-1] << endl;

    // 計算結束時間
    clock_gettime(CLOCK_MONOTONIC, &end);
    // 計算實際花費時間
    struct timespec temp1 = diff(start, end);
    time_used = temp1.tv_sec + (double) temp1.tv_nsec / 1000000000.0;

    outputQS << QS_result[k_th-1] << endl;
    outputQS << time_used;

    /*for (int i: QS_result)
        cout << i << " ";*/

    // PS
    int result = -1;
    // 計算開始時間
    clock_gettime(CLOCK_MONOTONIC, &start);

    PruneAndSearch(v, k_th, result);

    // 計算結束時間
    clock_gettime(CLOCK_MONOTONIC, &end);
    // 計算實際花費時間
    temp1 = diff(start, end);
    time_used = temp1.tv_sec + (double) temp1.tv_nsec / 1000000000.0;

    outputPS << result << endl;
    outputPS << time_used;
    //cout << "PS: " << result << endl;
}