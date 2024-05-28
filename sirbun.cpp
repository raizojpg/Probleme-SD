#include <iostream>
#include <vector>
#include <set>
using namespace std;

//ifstream cin("sirbun.in");
//ofstream cout("sirbun.out");

int n, x;
vector<int> sir;
vector<int> pos;
set<int> distinct;

int main()
{
	sir.push_back(0);
	pos.push_back(0);
    int left = 1;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x;
        sir.push_back(x);

		if (distinct.empty() || distinct.find(x) == distinct.end()) {
			distinct.insert(x);
			pos.push_back(left);
		}
		else {
			int x_original = x;
			while (distinct.find(x) != distinct.end() && x > 0) {x--;}
			if (x > 0) {
				// nu merge asa, setul nu poate avea duplicate
				distinct.insert(x_original);
				pos.push_back(left);
			}
			else {
				x = x_original;
				while (sir[left] > x && !distinct.empty()) {
					distinct.erase(sir[left]);
					left++;
				}
				distinct.erase(sir[left]);
				left++;
				distinct.insert(x);
				pos.push_back(left);
			}
		}
    }

	left = 1;
	long long ct = 0;
	
	for (int i = 1; i <= n; i++) {
		cout<<pos[i]<<" ";
	}
	cout << endl;

	for (int i = 1; i <= n; i++) {
		ct += i - pos[i] + 1;
	}
	cout << ct;
   

}
