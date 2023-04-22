#include <iostream>
#include <random>
#include <chrono>

// Distribuzione uniforme (meglio del rand)
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator(seed);

// Dimensione matrice
constexpr int n = 100;
// Numero run
constexpr int run = 100;
// Numero k
constexpr int nk = 3;

// Controllo eq. (se trova un valore diverso da 0 non sono uguali)
bool checkEqualiy(int u[], int t[]) {
	for(int i = 0; i < n; ++i)
		if(t[i] - u[i]) return false;
	return true;
}

bool mcmult(int A[][n], int B[][n], int C[][n]) {
	// Init di r, s, u
	bool r[n];
	int s[n]{0};
	int t[n]{0};
	int u[n]{0};
	// Distribuzione uniforme valori
	std::uniform_int_distribution<int> bern(0, 1);
	
	// Creazione vettore r
	for(int i = 0; i < n; ++i) r[i] = bern(generator);
	
	// s <-- B * r
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			s[i] += B[i][j] * r[j];

	// t <-- A * s
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			t[i] += A[i][j] * s[j];

	// u <-- C * r
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			u[i] += C[i][j] * r[j];

	// Controllo sull'uguaglianza
	return checkEqualiy(u, t);
}

bool repeat(int A[][n], int B[][n], int C[][n], int k) {
	for(int i = 0; i < k; ++i)
			if(!mcmult(A, B, C)) return false;
	return true;
}

int main() {
	// Distribuzione uniforme valori
	std::uniform_int_distribution<int> distribution(-2, 2);

	int A[n][n];
	int B[n][n];

	// Array freq
	double fq[nk]{0};

	// Creazione di A
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			A[i][j] = distribution(generator);

	// Ripetizione per 100 volte
	for(int r = 0; r < run; ++r) {
		int C[n][n]{0};
	
		// Creazione di B
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				B[i][j] = distribution(generator);

		// Creazione di C
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				for(int k = 0; k < n; ++k)
					C[i][j] += A[i][k] * B[k][j];
		// Perturbo C
		++C[2][2];
		--C[2][8];

		// Conto i fallimenti (ed è corretto fallisca (AB non è uguale a C))
		if(!repeat(A, B, C, 2)) fq[0]++; // 1/4 di fallire
		if(!repeat(A, B, C, 5)) fq[1]++; // 1/32 di fallire
		if(!repeat(A, B, C, 10)) fq[2]++; // 1/1024 di fallire

		/* Per debug
		std::cout << std::boolalpha << repeat(A, B, C, 2) << ' ';
		std::cout << std::boolalpha << repeat(A, B, C, 5) << ' ';
		std::cout << std::boolalpha << repeat(A, B, C, 10) << '\n';*/
	}

	std::cout << std::boolalpha;
	// Stampo i fallimenti (ed è corretto fallisca (AB non è uguale a C))
	// ES: 0.73 (k = 2), 0.96 (k = 5), 0.99 (k = 10)
	for(int i = 0; i < nk; ++i)
		std::cout << (double) fq[i] / (double) run << ' ';
	std::cout << '\n';
}
