/* *
 * N只熊分一堆苹果，
 * 第一只熊把这堆苹果分为N份，多了一个，他把多的一个扔掉了，拿走一份；
 * 第二只熊把剩下的苹果分为N份，又多了一个，他同样把多的一个扔掉了，拿走一份；
 * 第三、第四直到第N只都这样做。
 * 问：这堆苹果最少有多少个？
 *
 * */

#include <iostream>
using namespace std;

int main() {

	int i, j, begin, mid, k;
	for(i = 2; i < 9; ++i) {
	//while(cin >> i) {
		k = 1;
		mid = k * (i - 1);
		begin = mid;
		for(j = 0; j < i; ++j) {
			if(mid * i % (i -1) != 0) {
				do {
					++k;
					mid = k * (i - 1);
				} while(mid % i != 0);
				begin = mid;
				j = 0;
				//printf("1.i=%d, j=%d, k=%d, begin=%d\n", i, j, k, mid);
			}
			mid = mid * i / (i - 1) + 1;
			//cout << "mid=" << mid << endl;
			//printf("2.i=%d, r=%d\n", i, mid);
		}
		cout << "i=" << i << " mid=" << mid << endl;
	}	
	return 0;
}
