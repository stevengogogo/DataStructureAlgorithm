#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
using namespace std;

typedef unsigned long long ull;
typedef pair<ull, double> P;

int main(){
	ifstream ans("testdata/test.out", fstream::in);

	int query_id;
	double reward;
	ull digest;

	map<int, P> answers;

	while(ans >> query_id >> reward >> hex >> digest)
		answers[query_id] = P(digest, reward);
	
	double result = 0.0;
	int ans_cnt = 0;

	while(cin >> query_id >> hex >> digest){
		if(answers.find(query_id) == answers.end())
			continue;

		if(answers[query_id].first == digest)
			result += answers[query_id].second;
		else
			result -= answers[query_id].second * 0.5;
		
		answers[query_id] = P(0, 0);
		ans_cnt ++;
	}

	cout << "Answered " << ans_cnt << " times." << endl;
	cout << "Earned " << fixed << setprecision(2) << result << " Points." << endl;
	
	return 0;
}