#include <iostream>
#include <vector>
#include <set>
using namespace std;

struct info {
    int mini;
    set<int> pos;
};

vector<vector<info>> rmq;
int n,x;

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
        vector<info> v;
        v.push_back({ 0,{} });
        for (int i = 1; i + (1 << k) < rmq[k].size(); i++) {
            info inf;
            if (rmq[k][i].mini == rmq[k][i + (1 << k)].mini) {
                inf.mini = rmq[k][i].mini;
                inf.pos = rmq[k][i].pos;
                for (int j : rmq[k][i + (1 << k)].pos) {
                    inf.pos.insert(j);
                }
            }
            else if (rmq[k][i].mini < rmq[k][i + (1 << k)].mini) {
                inf.mini = rmq[k][i].mini;
                inf.pos = rmq[k][i].pos;
            }
            else {
                inf.mini = rmq[k][i + (1 << k)].mini;
                inf.pos = rmq[k][i + (1 << k)].pos;
            }
            v.push_back(inf);
        }
        rmq.push_back(v);
        k++;
    }
}

info response_rmq(int l, int r) {
    int k = largestPowerOfTwo(r - l + 1);
    info inf;
    if (rmq[k][l].mini == rmq[k][r - (1 << k) + 1].mini) {
        inf.mini = rmq[k][l].mini;
        inf.pos = rmq[k][l].pos;
        for (int j : rmq[k][r - (1 << k) + 1].pos) {
            inf.pos.insert(j);
        }
    }
    else if (rmq[k][l].mini < rmq[k][r - (1 << k) + 1].mini) {
        inf.mini = rmq[k][l].mini;
        inf.pos = rmq[k][l].pos;
    }
    else {
        inf.mini = rmq[k][r - (1 << k) + 1].mini;
        inf.pos = rmq[k][r - (1 << k) + 1].pos;
    }
    return inf;
}

void print_rmq() {
    for (int i = 0; i < rmq.size(); i++) {
        for (int j = 1; j < rmq[i].size(); j++) {
            cout << rmq[i][j].pos.size() << " ";
        }
        cout << endl;
    }
    cout << endl;
}

unsigned long long int subseq(int l, int r) {
    unsigned long long int ss = 0;
    if (r > l) {
        info inf = response_rmq(l, r);
        
        vector<int> positions;
        positions.push_back(l-1);
        for (int i : inf.pos) {
            int prev = positions[positions.size() - 1];
            ss += subseq(prev+1, i - 1);
            positions.push_back(i);
        }
        int prev = positions[positions.size() - 1];
        ss += subseq(prev + 1, r);

        for (int i = 1; i < positions.size(); i++) {
            long long int ii = positions[i] - l + 1;
            long long int rr = r - positions[i];
            if (ii - 2 <= rr) {
                long long int prod1 = (ii - 1) * ii / 2;
                ss += prod1;
            }
            else {
                long long int dif = ii - 2 - rr;
                long long int prod1 = (ii - 1) * ii / 2;
                long long int prod2 = dif * (dif + 1) / 2;
                ss += prod1 - prod2;
            }
        }
    }
    return ss;
}



int main()
{
    vector<info> v;
    v.push_back({ 0,{} });
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x;
        v.push_back({ x,{i} });
    }
    rmq.push_back(v);
    compute_rmq();

    unsigned long long int ss = subseq(1,n);
    cout << ss;

}

