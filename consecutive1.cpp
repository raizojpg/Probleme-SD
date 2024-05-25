#include <iostream>
#include <vector>
#include <set>
using namespace std;

vector<vector<pair<int,int>>> rmq; // first is min second is max
vector<int> pos;
set<int> distinct; 
int n, x, y, q;

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
	while (1 << (k + 1) <= n) {
		vector<pair<int, int>> v;
		v.push_back({ 0,0 });
		for (int i = 1; i + (1 << k) < rmq[k].size(); i++) {
			pair<int, int> p;
			p.first = min(rmq[k][i].first, rmq[k][i + (1 << k)].first);
			p.second = max(rmq[k][i].second, rmq[k][i + (1 << k)].second);
			v.push_back(p);
		}
		rmq.push_back(v);
		k++;
	}
}

pair<int,int> response_rmq(int x,int y) {
	int k = largestPowerOfTwo(y - x + 1);
	pair<int, int> p;
	p.first = min(rmq[k][x].first, rmq[k][y - (1 << k) + 1].first);
	p.second = max(rmq[k][x].second, rmq[k][y - (1 << k) + 1].second);
	return p;
}

void print_rmq() {
	for (int i = 0; i < rmq.size(); i++) {
		for (int j = 1; j < rmq[i].size(); j++) {
			cout << rmq[i][j].first << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < rmq.size(); i++) {
		for (int j = 1; j < rmq[i].size(); j++) {
			cout << rmq[i][j].second << " ";
		}
		cout << endl;
	}
	cout << endl;
}

bool check(int x, int y,int min) {
	vector<int> f(y - x + 1, 0);
	for (int i = x; i <= y; i++) {
		f[rmq[0][i].first-min] += 1;
	}
	for (int i = 0; i < y - x + 1; i++) {
		if (f[i] != 1) { return false; }
	}
	return true;
}


int main()
{
	vector<pair<int, int>> v;
	v.push_back({ 0,0 });
	pos.push_back(0);
	int left = 1;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> x;
		v.push_back({ x,x });
		if (distinct.empty() || distinct.find(x) == distinct.end()) {
			distinct.insert(x);
			pos.push_back(left);
		}
		else {
			while (distinct.find(x) != distinct.end()) {
				distinct.erase(v[left].first);
				left++;
			}
			distinct.insert(x);
			pos.push_back(left);
		}
	}
	rmq.push_back(v);
	compute_rmq();

	cin >> q;
	for (int i = 0; i < q; i++) {
		cin >> x >> y;
		pair<int, int> p = response_rmq(x, y);
		if (p.second - p.first + 1 != y - x + 1) {
			cout << "0";
		}
		else {
			if (pos[y]<=x) {
				cout << "1";
			}
			else {
				cout << "0";
			}
		}
	}

}

