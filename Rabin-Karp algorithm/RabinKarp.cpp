#include <iostream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;

typedef long long ll;
vector<ll> t;
const ll mod = 13;
bool match = true;

static ll horner_hash(string s)
{
	ll p = 0LL;
	for (int i = 0; i < s.length(); i++) {
		p += (ll)pow(10, s.length() - 1 - i)*(s[i] - '0');
	}
	return p % mod;
}

static ll modulo(ll a, ll b)
{
	ll r = a % b;
	return r < 0 ? r + b : r;
}

int main(void)
{
	string T = "212412412412412412424124359023141526732313231231231231231231231231231231231231231231239921";
	string P = "31415";

	ll p = horner_hash(P);
	t.push_back(horner_hash(T.substr(0, P.length())));

	ll h = (ll)pow(10, P.length() - 1) % mod;
	for (int i = 1; i <= T.length() - P.length(); i++)
		t.push_back(((10 * modulo(t[i - 1] - (T[i - 1] - '0')*h, mod)) + (T[i - 1 + P.length()] - '0')) % mod);

	for (int i = 0; i < t.size(); i++) {
		if (p == t[i]) {
			for (int j = 0; j < P.length(); j++) {
				if (P[j] != T[i + j]) {
					match = false;
					break;
				}
			}
			if (match) cout << "Pattern occurs with shift " << i << '\n';
			match = true;
		}
	}


	
	return 0;
}