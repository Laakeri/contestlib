// TCR
// Sample code on how to use g++ ordered set
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace std;
using namespace __gnu_pbds;
//using namespace pb_ds;
typedef tree<int, null_type, less<int>, rb_tree_tag, 
tree_order_statistics_node_update> ordered_set;
int main() {
	ordered_set X;
	X.insert(1);X.insert(4);
	cout<<*X.find_by_order(1)<<endl; // 4
	cout<<X.order_of_key(3)<<endl;   // 1
}