/* *
 * 给你一个6x6的数组，给你一个6x6的数组，
 * 每次可以水平走一步，或者向下走一步，
 * 求遍历过的元素和最大值
 * PS: 实现了递归和非递归的方法
 *
 * */

#include <iostream>
using namespace std;

#define SQ 6

int max(int *arr, int x, int y) {
	if(x < 0 || y < 0 || *(arr + SQ * x + y) < 0) return -1;
	if(x == 0 && y == 0) return *arr;

	int up = max(arr, x, y - 1);
	int left = max(arr, x - 1, y);
	if(up < 0 && left < 0) return -1;

	return *(arr + SQ * x + y) + (up > left ? up : left);
}

int linemax(int *arr) {
	int rs[SQ * SQ], up, left, i, j, jstart;
	rs[0] = *arr;
	j = 1;
	for(i = 0; i < SQ; ++i) {
		for(; j < SQ; ++j) {
			if(i == 0) up = -1;
			else up = *(arr + SQ * (i - 1) + j);
			
			if(j == 0) left = -1;
			else left = *(arr + SQ * i +j - 1);
			
			if(up < 0 && left < 0)  *(arr + SQ * i + j) = -1;
			else  if(*(arr + SQ * i + j) >= 0) *(arr + SQ * i + j) +=  (up > left ? up : left);
		}
		j = 0;
	}
	return *(arr + SQ * SQ - 1);
}


int main() {
	/*
	int arr[SQ * SQ] {
		1, 2, 3, 4, 5, 6,
		2, 9, 3, 4, 5, 6,
		3, 2, 3, 4, 3, -1,
		4, 0, 3, 4, -1, 6,
		5, 2, 3, 4, 5, 6,
		6, 9, 3, 4, -1, 6
	};
	//*/
	int arr[SQ * SQ] {
		1, 2, 3, 4, 5, 6,
		-1, -1, 3, -1, 5, 6,
		3, -1, 3, 4, 3, -1,
		4, 0, -1, 4, -1, 6,
		5, 2, 3, 4, 5, 6,
		6, 9, 3, 4, -1, 6
	};
	cout << "max=" << max(arr, SQ - 1, SQ - 1) << endl;
	cout << "linemax=" << linemax(arr) << endl;
}
