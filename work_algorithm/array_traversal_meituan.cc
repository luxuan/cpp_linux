/* *
 * 给定一个二维数组( n * n)，写程序从右上角到右下角沿对角线方向打印
 * PS：实现了S型遍历和单向遍历
 *
 * */
#include <iostream>
using namespace std;

int* traversal(int *arr, int n) {
	int i, j, di, dj, idx;
	int *rs = new int[n * n];

	idx = 0;
	rs[idx] = *(arr + n - 1);
	i = 0;
	j = n - 2;
	di = 0;
	dj = -1;
	while(i != n - 1 || j != 0) {
		cout << i << " " << j << endl;
		rs[++idx] = *(arr + i * n + j);
		
		// left
		if(di == 0 && dj == -1) { // left
			if(i == 0) { 	// first line
				di = 1;
				dj = 1;
			} else { 	// last line
				di = -1;
				dj = -1;
			}
		} else if (di == 1 && dj == 1) {// right down
			if(i == n - 1) { 	// last line
				di = 0;
				dj = -1;
			} else if(j == n - 1) {
				di = 1;
				dj = 0;
			}
		} else if (di == 1 && dj == 0) { // down
			if(j == 0) {
				di = 1;
				dj = 1;
			} else {
				di = -1;
				dj = -1;
			}
		} else if (di == -1 && dj == -1) { // left up
			if(j == 0) {
				di = 1;
				dj = 0;
			} else if(i == 0) {
				di = 0;
				dj = -1;
			}
		}

		i += di;
		j += dj;
	}
	return rs;
}

int* traversal2(int *arr, int n) {
	int i, j, lasti, lastj, idx;
	int *rs = new int[n * n];

	idx = 0;
	i = 0;
	j = n - 1;
	lasti = 0;
	lastj = n - 1;
	rs[idx] = *(arr + n - 1);
	do {
		if(i == n - 1) {
			i = ++lasti;
			j = 0;
		} else if (j == n - 1) {
			i = 0;
			j = --lastj;
		} else {
			++i;
			++j;
		}
		cout << i << " " << j << endl;
		rs[++idx] = *(arr + i * n + j);
	} while(i != n - 1 || j != 0);
	return rs;
}

int main() {
	int arr[] = {
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16
	};
	int arr2[] = {
		1, 2, 3,
		4, 5, 6,
		7, 8, 9
	};
	//int *rs = traversal2((int*)arr, 4);
	int *rs = traversal2((int*)arr2, 3);
	for(int i = 0; i < 9; ++i) {
		cout << rs[i] << ", ";
	}	
	cout << endl;
	delete rs;
}
