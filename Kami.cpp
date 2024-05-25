#include <fstream>
#include <vector>
using namespace std;

ifstream cin("kami.in");
ofstream cout("kami.out");

vector<int> val;
int n, x, m, q, v, p;

int query(int poz) {
    int sum = val[poz];
    while (poz > 0) {
        if (sum > val[poz - 1]) {
            sum += val[poz - 1];
            if (sum > 1000000000) { poz = 0; break; }
            poz--;
        }
        else {
            poz--;
            break;
        }
    }
    return poz;
}

int main()
{
    val.push_back(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x;
        val.push_back(x);
    }

    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> q;
        if (q == 0) {
            cin >> p >> v;
            val[p] = v;
        }
        else {
            cin >> p;
            cout << query(p)<<endl;
        }
    }
}

