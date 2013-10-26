#include <iostream>
#include <algorithm>
using namespace std;

class node {
public:
	double start, end;
	bool operator < (const node &other) const {
		return start < other.start;
	}
	
	friend ostream& operator << (ostream &, node &);
};
ostream& operator << (ostream &output, node &a) {
	output << a.start << " " << a.end;
	return output;	
}
/* return length of seg*/
int merge(node *segs, int n) {
	sort(segs, segs + n);
	int last_index = 0;
	for(int i = 1; i < n; ++i) {
		if(segs[i].start <= segs[last_index].end) {  // TODO double equel 
			if(segs[last_index].end < segs[i].end)
				segs[last_index].end = segs[i].end;  // merge the seg
		} else if(++last_index < i) {  // else should do "++last_index"
			segs[last_index] = segs[i];
		}
	}
	return last_index + 1; // length of merged segs;
}

int main() {
	node segs[] = {{-10.3, -5},{-3, -1}, {-1, 2}, {4, 5.5}, {3.2, 5}, {8, 9}, {7.3, 10}, {20, 23}, {22, 26}, {30, 40}, {35, 36}, {6.2, 7.6}, {26, 28}, {29.5, 41.5}};
	int n = merge(segs, 14);
	for(int i = 0; i < n; ++i) {
		cout << i << " " << segs[i] << endl;
	}
	return 0;
}
