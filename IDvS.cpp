#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

queue<pair<int, int>> q;
vector<pair<int, int>> vec;
vector<int> visited;
int n, d, s, ct, result = INT_MAX;
bool max_visits,complete;

void optimize() {
    int max_dif = q.back().first - q.front().first;
    result = min(result, max_dif);
    visited[q.front().second]++;
    if (visited[q.front().second] == 2) { ct--; complete = false; }
    else if (visited[q.front().second] == 4) { ct--; complete = false; max_visits = true; }
    q.pop();
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> d >> s;
        vec.push_back({ d,i });
        vec.push_back({ s,i });
        visited.push_back(0);
    }
    sort(vec.begin(), vec.end());
    for (int i = 0; i < 2 * n; i++) {
        q.push(vec[i]);
        visited[vec[i].second]++;
        if (visited[vec[i].second] == 1 || visited[vec[i].second] == 3) {
            ct++;
            if (ct == n) { complete = true; }
        }        
        while (complete) {
            optimize();
        }
        if (max_visits) { break; }
    }
    cout << result;

}

