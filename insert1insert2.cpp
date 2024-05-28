#include <iostream>
#include <vector>
using namespace std;

std::vector<int> sum;
int n, op, pos, val;
int red, black;
long long re;

void update(int pos, int val) {
    sum.insert(sum.begin() + pos, 0);
    for (int i = pos; i < sum.size(); i+= i&(-i)) {
        sum[i] += val;
        sum[i] %= 666013;
    }
}

int query() {
    int l = min(red, black);
    int r = max(red, black);
    int sr = 0;
    for (int i = r; i > 0; i -=( i & (-i))) {
        sr += sum[i];
        sr %= 666013;
    }
    int sl = 0;
    for (int i = l-1; i > 0; i -=(i & (-i))) {
        sl += sum[i];
        sl %= 666013;
    }

    return sr-sl;

}




int main()
{
    sum.push_back(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> op;
        if (op == 1) {
            cin >> pos >> val;
            pos++;
            red = pos;
            if (black >= red) {
                black++;
            }
            update(pos, val);
        }
        else if (op == 2) {
            cin >> pos >> val;
            pos++;
            black = pos;
            if (red >= black) {
                red++;
            }
            update(pos,val);
        }
        else {
            re += query();
            re %= 666013;
        }
    }
    cout << re << endl;

}