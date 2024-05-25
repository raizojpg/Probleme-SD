#include <fstream>
#include <vector>
using namespace std;

ifstream cin("euclid.in");
ofstream cout("euclid.out");

vector<vector<vector<int>>> rmq;
int t, n, m, h, w, x;

int gcd(int a, int b) {
    while (b) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int largestPowerOfTwo(int n) {
    int msb = 0;
    while (n > 1) {
        n >>= 1;
        msb++;
    }
    return msb;
}

void compute(vector<vector<vector<int>>>& rmq, int limit) {
    int k = 0;
    while ((1 << k) <= m && k <= limit) {
        vector<vector<int>> vec;
        vector<int> v;
        v.push_back(0);
        vec.push_back(v);
        for (int i = 1; i + (1 << k) < rmq[k].size(); i++) {
            vector<int> v;
            v.push_back(0);
            for (int j = 1; j + (1 << k) < rmq[k][i].size(); j++) {
                int gcd1 = gcd(rmq[k][i][j], rmq[k][i][j + (1 << k)]);
                int gcd2 = gcd(rmq[k][i + (1 << k)][j], rmq[k][i + (1 << k)][j + (1 << k)]);
                int gcd3 = gcd(gcd1, gcd2);
                v.push_back(gcd3);
            }
            vec.push_back(v);
        }
        rmq.push_back(vec);
        k++;
    }
}

int get_rectangle(vector<vector<vector<int>>>& rmq, int i, int j, int k, int h, int w) {
    int gcd0 = rmq[k][i][j];
    int ii = i;
    for (; ii + (1 << k) <= i + h; ii += (1 << k)) {
        int jj = j;
        for (; jj + (1 << k) <= j + w; jj += (1 << k)) {
            gcd0 = gcd(gcd0, rmq[k][ii][jj]);
        }
        if (jj != j + w) {
            gcd0 = gcd(gcd0, rmq[k][ii][j + w - (1 << k)]);
        }
    }
    if (ii != i + h) {
        int jj = j;
        for (; jj + (1 << k) <= j + w; jj += (1 << k)) {
            gcd0 = gcd(gcd0, rmq[k][i + h - (1 << k)][jj]);
        }
        if (jj != j + w) {
            gcd0 = gcd(gcd0, rmq[k][i + h - (1 << k)][j + w - (1 << k)]);
        }
    }
    return gcd0;
}

int result(vector<vector<vector<int>>>& rmq, int k, int h, int w) {
    int maxi = 0;
    for (int i = 1; i < rmq[k].size(); i++) {
        for (int j = 1; j < rmq[k][i].size(); j++) {
            if (i + h - 1 < rmq[0].size() && j + w - 1 < rmq[0][i].size()) {
                int gcd0 = get_rectangle(rmq, i, j, k, h, w);
                maxi = max(gcd0, maxi);
            }
        }
    }
    return maxi;
}

void print(vector<vector<vector<int>>>& rmq,int k) {
    cout << endl;
    for (int i = 1; i < rmq[k].size(); i++) {
        for (int j = 1; j < rmq[k][i].size(); j++) {
            cout << rmq[k][i][j] << " ";
        }
        cout << endl;
    }
}


int main()
{
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        vector<vector<vector<int>>> rmq;
        vector<vector<int>> vec;
        vector<int> v;
        v.push_back(0);
        vec.push_back(v);
        cin >> m >> n >> h >> w;
        for (int i = 0; i < m; i++) {
            vector<int> v;
            v.push_back(0);
            for (int j = 0; j < n; j++) {
                cin >> x;
                v.push_back(x);
            }
            vec.push_back(v);
        }
        rmq.push_back(vec); // mat on rmq[0]
        int limit = largestPowerOfTwo(min(h, w)) + 1 ;
        compute(rmq,limit);
        cout << "Case #" << tt << ": " << result(rmq, limit - 1, h, w) << endl;
    }
}

