#include <fstream>
#include <vector>
#include <queue>
using namespace std;

ifstream cin("timbre.in");
ofstream cout("timbre.out");

struct compareFuncPairMax {
    bool operator()(pair<int, int> a, pair<int, int> b) const {
        return a.first < b.first;
    }
};

struct compareFuncPairMin {
    bool operator()(pair<int, int> a, pair<int, int> b) const {
        return a.second > b.second; 
    }
};

priority_queue<pair<int, int>, vector<pair<int, int>>, compareFuncPairMax> intervale;
priority_queue<pair<int, int>, vector<pair<int, int>>, compareFuncPairMin> costuri;

int n, m, k, r, c, smin;

int main()
{
    cin >> n >> m >> k;

    for (int i = 0; i < m; i++) {
        cin >> r >> c;
        intervale.push({ r,c });
    }
    while (n > 0) {
        while (!intervale.empty() && intervale.top().first >= n) {
            costuri.push(intervale.top());
            intervale.pop();
        }

        n -= k;
        smin += costuri.top().second;
        costuri.pop();
    }    
    cout << smin;

}

