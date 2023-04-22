#include <iostream>
#include <stack>

using stack = std::stack<int>;

void move(stack& from, stack& to) {
	to.push(from.top());
	from.pop();
}

void hanoi(int n, stack& from, stack& to, stack& aux) {
	if(n == 1) move(from, to);
	else {
		hanoi(n-1, from, aux, to);
      move(from, to);
		hanoi(n-1, aux, to, from);
   }
}

void hanoi2(int n, char from, char to, char aux) {
	if(n == 1) std::cout << "Sposto da " << from << " a " << to << "(" << n << ")\n";
	else {
		hanoi2(n-1, from, aux, to);
     	std::cout << "Sposto da " << from << " a " << to << "(" << n << ")\n";
		hanoi2(n-1, aux, to, from);
   }
}

int main(int argc, char* argv[]) {
	//h1
	stack A, B, C;
	int n = atoi(argv[1]);
	for(int i = n; i >= 0; --i)
		A.push(n);
	//hanoi(n, A, C, B);
	//h2
	hanoi2(n, 'A', 'C', 'B');
}
