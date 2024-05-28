#include <iostream>
#include <vector>
using namespace std;

struct str {
	unsigned int maxi;
	unsigned int second_max;
	unsigned int mini;
	unsigned int maxi_pos;
};

vector<vector<str>> rmq;
vector<unsigned int> vec;
int n;
unsigned int x;
unsigned long long expr,maxi;

unsigned int largestPowerOfTwo(unsigned int n) {
	unsigned int msb = 0;
	while (n > 1) {
		n >>= 1;
		msb++;
	}
	return msb;
}

void compute_rmq() {
	unsigned int k = 0;
	vector<str> v;
	v.push_back({ 0,0,0,0 });
	for (unsigned int i = 1; i + (1 << k) < rmq[k].size(); i++) {
		str s;
		if (rmq[k][i].maxi > rmq[k][i + (1 << k)].maxi) {
			s.maxi = rmq[k][i].maxi;
			s.maxi_pos = rmq[k][i].maxi_pos;
		}
		else {
			s.maxi = rmq[k][i + (1 << k)].maxi;
			s.maxi_pos = rmq[k][i + (1 << k)].maxi_pos;
		}
		s.second_max = min(rmq[k][i].maxi, rmq[k][i + (1 << k)].maxi);
		s.mini = s.second_max;
		v.push_back(s);
	}
	rmq.push_back(v);

	k = 1;
	while ((1 << k) <= n) {
		vector<str> v;
		v.push_back({ 0,0,0,0 });
		for (unsigned int i = 1; i + (1<<k) < rmq[k].size();i++) {
			str s;
			s.maxi = max(rmq[k][i].maxi, rmq[k][i + (1 << k)].maxi);
			s.second_max = max(max(rmq[k][i].second_max, rmq[k][i + (1 << k)].second_max),
							min(rmq[k][i].maxi, rmq[k][i + (1 << k)].maxi));
			s.mini = min(rmq[k][i].mini, rmq[k][i + (1 << k)].mini);
			v.push_back(s);
		}
		rmq.push_back(v);
		k++;
	}
}

unsigned long long response_rmq_sum(unsigned int left) {
	unsigned int k = largestPowerOfTwo(n - left + 1);
	str s;
	s.maxi = max(rmq[k][left].maxi, rmq[k][n - (1 << k) +1 ].maxi);
	if (rmq[k][left].maxi == rmq[k][n - (1 << k) + 1].maxi){
		if (rmq[k][left].maxi_pos == rmq[k][n - (1 << k) + 1].maxi_pos) {
			s.second_max = max(rmq[k][left].second_max, rmq[k][n - (1 << k) + 1].second_max);
		}
		else {
			s.second_max = s.maxi;
		}
	}
	else {
		s.second_max = max(max(rmq[k][left].second_max, rmq[k][n - (1 << k) + 1].second_max),
							min(rmq[k][left].maxi, rmq[k][n - (1 << k) + 1].maxi));
	}
	unsigned long long sum = s.maxi + s.second_max;
	return sum;
}

unsigned int response_rmq_xor(unsigned int right) {
	unsigned int k = largestPowerOfTwo(right);
	str s;
	s.mini = min(rmq[k][1].mini, rmq[k][right - (1 << k) + 1].mini);
	s.maxi = max(rmq[k][1].maxi, rmq[k][right - (1 << k) + 1].maxi);
	return (s.mini^s.maxi);
}

void print() {
	for (unsigned int i = 0; i < rmq.size(); i++) {
		for (unsigned int j = 1; j < rmq[i].size(); j++) {
			cout << rmq[i][j].mini << " ";
		}
		cout << endl;
	}
	cout << endl;
	
}

unsigned int calculate_max_xor(unsigned int right,unsigned int& p1,unsigned int& p2) {
	unsigned int max_rez = 0;
	for (unsigned int i = 1; i <= right - 1; i++) {
		for (unsigned int j = i + 1; j <= right; j++) {
			unsigned int rez = (vec[i] ^ vec[j]);
			if (max_rez < rez) {
				max_rez = rez;
				p1 = vec[i];
				p2 = vec[j];
			}
		}
	}
	return max_rez;
}


int main()
{
	vector<str> v;
	v.push_back({ 0,0,0,0 });
	vec.push_back(0);
	cin >> n;
	for (unsigned int i = 1; i <= n; i++) {
		cin >> x;
		vec.push_back(x);
		v.push_back({ x,0,x,i });
	}
	rmq.push_back(v);
	compute_rmq();


	for (unsigned int i = 1; i <= n - 3; i++) {
		for (unsigned int j = i + 1; j <= n - 2; j++) {
			expr = (vec[i] ^ vec[j]) * response_rmq_sum(j + 1);
			maxi = max(maxi, expr);
		}
	}
	cout << maxi;

}

