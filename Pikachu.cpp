#include <fstream>
#include <vector>
#include <climits>
#include <math.h>
using namespace std;

ifstream cin("pikachu.in");
ofstream cout("pikachu.out");

int n, k, x;
int mini, maxi;
vector<int> vec;
long long int result = LLONG_MAX;

long long int check(int h) {
	long long int result_for_h;
	long long int re = 0;
	for (int i = 1; i <= k; i++) {
		re += abs(vec[i] - h);
	}
	result_for_h = re;
	for (int i = k + 1; i <= n; i++) {
		re = re - abs(vec[i - k] - h) + abs(vec[i] - h);
		result_for_h = min(result_for_h, re);
	}
	result = min(result_for_h, result);
	return result_for_h;
}

int main()
{
	vec.push_back(0);
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		cin >> x;
		vec.push_back(x);
		maxi = max(maxi, x);
	}
	mini = 0;
	while (maxi > mini) {
		int mid = mini + (maxi - mini) / 2;
		if (check(mid) < check(mid + 1)) {
			maxi = mid;
		}
		else {
			mini = mid + 1;
		}
	}
	cout << result;

}

