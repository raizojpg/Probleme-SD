#include <fstream>
#include <vector>
using namespace std;

ifstream cin("plantatie.in");
ofstream cout("plantatie.out");

int n, m, x;
vector<vector<int>> mat;
vector<vector<vector<int>>> rmq;

int largestPowerOfTwo(int n) {
    int msb = 0;
    while (n > 1) {
        n >>= 1;
        msb++;
    }
    return msb;
}

void compute_rmq() {
    rmq.push_back(mat);
    int k = 0;
    while ((1 << (k + 1)) <= n) {
        vector<vector<int>>vec;
        vector<int> v;
        v.push_back(0);
        vec.push_back(v);
        for (int i = 1; i + (1 << k) < rmq[k].size(); i++) {
            vector<int> v;
            v.push_back(0);
            for (int j = 1; j + (1 << k) < rmq[k][i].size(); j++) {
                int maxi1 = max(rmq[k][i][j], rmq[k][i + (1 << k)][j]);
                int maxi2 = max(rmq[k][i][j + (1 << k)], rmq[k][i + (1 << k)][j + (1 << k)]);
                int maxi = max(maxi1, maxi2);
                v.push_back(maxi);
            }
            vec.push_back(v);
        }
        rmq.push_back(vec);
        k++;
    }
}

int response_rmq(int x, int y, int l) {
    int k = largestPowerOfTwo(l);
    int maxi1 = max(rmq[k][x][y], rmq[k][x + l - (1 << k)][y]);
    int maxi2 = max(rmq[k][x][y + l - (1 << k)], rmq[k][x + l - (1 << k)][y + l - (1 << k)]);
    int maxi = max(maxi1, maxi2);
    return maxi;
}

void print_rmq(int k) {
    for (int i = 0; i < rmq[k].size(); i++) {
        for (int j = 1; j < rmq[k][i].size(); j++) {
            cout << rmq[k][i][j] << " ";
        }
        cout << endl;
    }
}


int main()
{
    cin >> n >> m;
    vector<int> v;
    v.push_back(0);
    mat.push_back(v);

    for (int i = 1; i <= n; i++) {
        vector<int> v;
        v.push_back(0);
        for (int j = 1; j <= n; j++) {
            cin >> x;
            v.push_back(x);
        }
        mat.push_back(v);
    }

    compute_rmq();

    int x, y, l;
    for (int i = 0; i < m; i++) {
        cin >> x >> y >> l;
        cout << response_rmq(x, y, l) << endl;
    }

}
