#include <iostream>
#include <vector>

using namespace std;

int n, op, x;
vector<int> vec;

int binary_search(int l, int r, int value) {
    if (l <= r) {
        int mid = (l + r)/2;
        if (mid == vec.size() - 1) { return vec.size() - 1; }
        else if (vec[mid] <= value && vec[mid + 1] >= value) { return mid; }
        else if (vec[mid] < value) { return binary_search(mid + 1, r, value); }
        else { return binary_search(l, mid - 1, value); }
    }
}

int main()
{
    vec.push_back(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> op >> x;
        if (op == 1) {
            int poz = binary_search(0, vec.size()-1, x);
            if (poz == vec.size() - 1) { vec.push_back(x); }
            else { vec.insert(vec.begin() + poz+1, x); }
        }
        else {
            long long int sum = 0;
            for (int i = 1; i <= x; i++) {
                sum += vec[i];
            }
            cout << sum << endl;
        }
    }
    
}
