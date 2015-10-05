// Implements map operations for keys known in construction
// Undefined behavior when key doesn't exist
#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;

template<typename keyT, typename valueT>
struct FastMap {
	vector<keyT> keys;
	vector<valueT> values;
	
	FastMap(const vector<keyT>&ks) : keys(ks), values(ks.size()) {
		sort(keys.begin(), keys.end());
	}
	
	valueT& operator[](keyT key) {
		auto it=lower_bound(keys.begin(), keys.end(), key);
		return values[it-keys.begin()];
	}
};