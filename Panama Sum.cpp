#include <iostream>
#include <vector>
using namespace std;

vector<int> vec;
int n, q, op, l, r, a,b;

long long int func(int l, int r) {
	long long int maxi = 0;
	for (int i = l; i <= r; i++) {
		long long int sum = 0;
		for (int j = i; j <= r; j++) {
			if ((j - i) % 2 == 0) {
				sum += vec[j];
			}
			else {
				sum -= vec[j];
			}
			if (sum > maxi) { maxi = sum; }
		}
	}
	return maxi;
}


int main()
{
	vec.push_back(0);
	cin >> n >> q;
	for (int i = 0; i < n; i++) {
		cin >> b;
		vec.push_back(b);
	}
	for (int i = 0; i < q; i++) {
		cin >> op;
		if (op == 1) {
			cin >> a >> b;
			vec[a] = b;
		}
		else {
			cin >> l >> r;
			cout << func(l, r) << endl;
		}
	}
}

