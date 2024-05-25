#include <fstream>
#include <queue>
#include <vector>
using namespace std;

ifstream cin("proc2.in");
ofstream cout("proc2.out");

struct compareFuncMin {
    bool operator()(int a, int b) const {
        return a > b;
    }
};

struct compareFuncPairMin {
    bool operator()(pair<int, int> a, pair<int, int> b) const {
        return a.first > b.first;
    }
};

int n, m, s, d, p;
priority_queue<int,vector<int>,compareFuncMin> procesoare_libere;
priority_queue<pair<int, int>, vector<pair<int, int>>, compareFuncPairMin> procesoare_in_functiune;

int main(){
    
	cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        procesoare_libere.push(i);
    }

	for (int i = 0; i < m; i++) {
		cin >> s >> d;
        while (!procesoare_in_functiune.empty() && procesoare_in_functiune.top().first <= s) {
            procesoare_libere.push(procesoare_in_functiune.top().second);
            procesoare_in_functiune.pop();
        }
        p = procesoare_libere.top();
        procesoare_libere.pop();
        procesoare_in_functiune.push({ s + d,p });
        cout << p << std::endl;
	}
    

}