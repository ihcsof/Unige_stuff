#include <iostream>
#include <vector>

void swap(int& x, int& y) {
	int tmp = x;
	x = y;
	y = tmp;
}

int partition(std::vector<int>& v, int fst, int lst) {
	int pivot = v[fst];
	int i = fst + 1;
	
	for(int j=i; j<=lst; ++j)
		if(v[j] < pivot)
			swap(v[j], v[i++]);

	swap(v[i-1], v[fst]);
	return (i-1);
}

int random(std::vector<int>& v, int fst, int lst) {
	srand(time(NULL));
	int r = rand()%(lst-fst) + fst;
	swap(v[r], v[fst]);
	return partition(v, fst, lst);
}

void qs(std::vector<int>& v, int fst, int lst) {
	if(fst < lst) {
		int i_pivot = random(v, fst, lst);
		qs(v, fst, i_pivot-1);
		qs(v, i_pivot+1, lst);
	}
}

void quickSort(std::vector<int>& v) {
	if(v.size() <= 1)
		return;
	qs(v, 0, v.size()-1);
}

int main() {
	std::vector<int> v{3,6,8,1,2,6,6,8,9,0,7,4,8,5};
	quickSort(v);
	for(int i=0; i<v.size(); ++i)
		std::cout << v[i] << " ";
	std::cout << "\n";
}
