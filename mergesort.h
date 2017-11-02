#include <iostream>
#include <cmath>

using namespace std;

void mergesort (int*a, int start, int end) {
	if(end-start==1)
		return;
	else {
		mergesort(a, start, end/2);
	}
}

int main() {
	return 0;
}