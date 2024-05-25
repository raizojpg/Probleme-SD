#include <fstream>
#include <vector>
using namespace std;

ifstream cin("stramosi.in");
ofstream cout("stramosi.out");

vector<int> v;
vector<vector<int>> vec;
int n, m, p, q, x;


int largestPowerOfTwo(int n) {
    int msb = 0;
    while (n > 1) {
        n >>= 1;
        msb++;
    }
    return msb;
}

int stramosi(int q, int p) {
    int sizeq = vec[q].size()-1;
    if ( (1<<sizeq) > p ) { 
        int msb = largestPowerOfTwo(p);
        int stramos_indepartat = vec[q][msb+1];
        int ramasi = p - (1 << (msb));
        if (ramasi <= 0) { return stramos_indepartat; }
        else { return stramosi(stramos_indepartat, ramasi); }
    }
    else {
        int cel_mai_indepartat_stramos = vec[q][sizeq];
        int ramasi = p - (1 << (sizeq-1));
        if (cel_mai_indepartat_stramos == 0) {
            return 0;
        }
        else {
            int rez = stramosi(cel_mai_indepartat_stramos, ramasi);
            int stramos = cel_mai_indepartat_stramos;
            int size_stramos = vec[stramos].size()-1;
            while (size_stramos >= sizeq) {
                int stramos_indepartat = vec[stramos][sizeq];
                vec[q].push_back(stramos_indepartat);
                sizeq++;
                stramos = stramos_indepartat;
                size_stramos = vec[stramos].size() - 1;
            }
            return rez;
        }
    }

}

int main()
{
    cin >> n >> m;
    vector<int> v;
    v.push_back(0);
    vec.push_back(v);
    for (int i = 0; i < n; i++) {
        vector<int> v;
        v.push_back(0);
        cin >> x;
        v.push_back(x);
        vec.push_back(v);
    }
    for (int i = 0; i < m; i++) {
        cin >> q >> p;
        cout << stramosi(q, p) << "\n";
    }

}