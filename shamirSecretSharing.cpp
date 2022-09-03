#include<bits/stdc++.h>
using namespace std;

// modulos for the field
#define mod 253

typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x<<" "; _print(x); cerr << endl;
#else
#define debug(x);
#endif

void _print(ll t) {cerr << t;}
void _print(int t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(lld t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(ull t) {cerr << t;}

template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T, class V> void _print(map <T, V> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(pair <T, V> p) {cerr << "{"; _print(p.first); cerr << ","; _print(p.second); cerr << "}";}
template <class T> void _print(vector <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(set <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(multiset <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}

void extendedEuclid(int a, int b, int& x, int& y, int& d) {
	assert(a > 0);
	assert(b > 0);

	int q, r;
	int x1, x2, y1, y2;

	if (b == 0) {
		d = a;
		x = 1;
		y = 0;
	}
	else {
		x1 = 0;
		x2 = 1;
		y1 = 1;
		y2 = 0;

		while (b > 0) {
			q = a / b;
			r = a % b;
			a = b;
			b = r;
			x = x2 - q * x1;
			y = y2 - q * y1;
			x2 = x1;
			x1 = x;
			y2 = y1;
			y1 = y;
		}
		d = a;
		x = x2;
		y = y2;
	}
}

// Implementation of arithmetic operations for galois field
int inverseModular(int a) {
	int d, x, y;

	// Compute modular multiplicative inverse of b (exists if d = 1)
	extendedEuclid(a, mod, x, y, d);

	// If a and m are not relatively prime, there is no inverse.
	if (d != 1) {
		cout << "Error! No inverse!!";
		return -1;
	}

	return ( (x > 0) ? x : (mod + x) );
}

int galoisFieldAdd(int a, int b) {
	return (a + b) % mod;
}

int galoisFieldSubtract(int a, int b) {
	return (a + (mod - b)) % mod;
}

int galoisFieldMultiply(int a, int b) {
	return (a * b) % mod;
}

int galoisFieldDivide(int a, int b) {
	if (b == 0) {
		cout << "Error! Divide by zero!!";
		return -1;
	}
	return (a * inverseModular(b)) % mod;
}

// Display the shares after creations along with shareNo
void displayShares(vector<int> share, int shareNo) {
	cout << "Share " << shareNo << " is: " << endl;
	for (int i = 0; i < 32; i++) {
		cout << share[i] << " ";
	}
	cout << endl;
	return;
}

void validate(vector<int>& secret, vector<int>& secretFound) {
	for (int i = 0; i < 32; i++) {
		string isMatching = (secret[i] == secretFound[i]) ? "Matching" : "Not Matching";
		cout << secret[i] << "		" << secretFound[i] << "		" << isMatching << endl;
	}
	return;
}

// Using lagrange function, simplified it for using 2 secrets only.
int lagrange(int x1, int x2, int y1, int y2) {
	int a = galoisFieldMultiply(y2, x1);
	int b = galoisFieldMultiply(y1, x2);
	int c = galoisFieldSubtract(x1, x2);
	return galoisFieldDivide(galoisFieldSubtract(a, b), c);
}

// Find the secret and stores it in secretFound
void decrypt(vector<vector<int>>& shares, vector<int>& secretFound) {
	cout << "Enter any two shares which can be used for finding the secret \n(enter no. between 1 and 4) " << endl;
	int shareNo1, shareNo2;
	cin >> shareNo1 >> shareNo2;
	cout << "Secret found after using " << shareNo1 << " and " << shareNo2 << " is: " << endl;
	for (int i = 0; i < 32; i++) {
		secretFound[i] = lagrange(shareNo1, shareNo2, shares[shareNo1 - 1][i], shares[shareNo2 - 1][i]);
	}
	return;
}

// Generate the shares
void generateShares(vector<vector<int>>& shares, vector<int>& secret) {
	int randNo = rand() % 256;
	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 4; j++) {
			shares[j][i] = galoisFieldAdd(secret[i], galoisFieldMultiply(randNo, (j + 1)));
		}
	}
	return;
}

// Shamir Secret Sharing Algorithm
void shamirSecretSharingAlgorithm() {
	cout << "Enter your secret! Enter 32 numbers which make up your secret. Keep the values between 1 - 255" << endl;
	vector<int> secret(32);
	for (int i = 0; i < 32; i++) {
		cin >> secret[i];
	}

	vector<vector<int>> shares(4, vector<int>(32));
	generateShares(shares, secret);

	for (int i = 0; i < 4; i++) {
		displayShares(shares[i], i + 1);
	}

	vector<int> secretFound(32);
	decrypt(shares, secretFound);

	validate(secret, secretFound);
	return;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	freopen("error.txt", "w", stderr);
#endif
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	shamirSecretSharingAlgorithm();
	return 0;
}