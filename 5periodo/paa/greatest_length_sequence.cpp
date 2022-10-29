#include <bits/stdc++.h>
using namespace std;
 
int lis(int arr[], int n) {
	int lis[n];

	lis[0] = 1;

	for (int i = 1; i < n; i++) {
		lis[i] = 1;
		for (int j = 0; j < i; j++)
			if (arr[i] > arr[j] && lis[i] < lis[j] + 1)
				lis[i] = lis[j] + 1;
	}

	return *max_element(lis, lis + n);
}

int main() {
	int arr[] = { 11, 17, 5, 8, 6, 4, 7, 12, 3 };
	int n = sizeof(arr) / sizeof(arr[0]);


	auto start = chrono::steady_clock::now();

	cout <<"Length of longest increasing subsequence is "<< lis(arr, n) << endl;

	auto end = chrono::steady_clock::now();

	cout << "time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;


	return 0;
}
