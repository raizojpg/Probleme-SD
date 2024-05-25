#include <fstream>
#include <cmath>
#include <queue>

using namespace std;

ifstream cin("bleach.in");
ofstream cout("bleach.out");

int n, k, x;
priority_queue<int> puteri;


int main()
{
    long long int current, sum = 0, dif, start=0;
    cin >> n >> k;
    for (int i = 0; i < min(k+1,n); i++) {
        cin >> x;
        puteri.push((-1) * x);
    }
    for (int i = k+1; i < n; i++) {
        current = (-1) * puteri.top();
        puteri.pop();
        
        if (sum - current < 0) { 
            dif = current - sum; 
            if (dif > start) { start = dif; }
        }
        sum += current;
        
        cin >> x;
        puteri.push((-1) * x);
    }
    while (!puteri.empty()) {
        current = (-1) * puteri.top();
        puteri.pop();

        if (sum - current < 0) {
            dif = current - sum;
            if (dif > start) { start = dif; }
        }
        sum += current;
    }
    cout << start;

}

