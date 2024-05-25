#include <iostream>
#include <vector>
using namespace std;

int MOD = 1e9 + 7;
vector<vector<int>> rmq;
int n, x, y, q;

long long pow(long long e) {
    if (e == 0) { return 1; }
    if (e % 2 == 0) { return (pow(e / 2) * pow(e / 2)) % MOD; }
    else { return (2 * pow(e - 1)) % MOD; }
}

int largestPowerOfTwo(int n) {
    int msb = 0;
    while (n > 1) {
        n >>= 1;
        msb++;
    }
    return msb;
}

void compute_rmq() {
    int k = 0;
    while ((1 << k) <= n) {
        vector<int> v;
        v.push_back(0);
        for (int i = 1; i + (1 << k) < rmq[k].size(); i++) {
            int m = max(rmq[k][i], rmq[k][i + (1 << k)]);
            v.push_back(m);
        }
        rmq.push_back(v);
        k++;
    }
}

int response_rmq(int l,int r) {
    int k = largestPowerOfTwo(r - l + 1);
    return max(rmq[k][l], rmq[k][r - (1 << k) + 1]);
}

void print_rmq() {
    for (int i = 0; i < rmq.size(); i++) {
        for (int j = 1; j < rmq[i].size(); j++) {
            cout << rmq[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}


int main()
{
    vector<int> v;
    v.push_back(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x;
        v.push_back(x);
    }
    rmq.push_back(v);
    compute_rmq();
    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> x >> y;
        long long rez = (response_rmq(x, y) * pow(y - x)) % MOD;
        cout << rez << endl;
    }
}

