#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define endl "\n";

struct custom_hash {
	static uint64_t splitmix64(uint64_t x) {
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}

	size_t operator()(uint64_t x) const {
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x + FIXED_RANDOM);
	}

	size_t operator()(pair<uint64_t,uint64_t> x) const {
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x.first + FIXED_RANDOM)^(splitmix64(x.second + FIXED_RANDOM) >> 1);
	}
};

void generate_primes(void)
{
	int N = 200005;
	vector<bool> p(N, true);

	p[0] = false;
	p[1] = false;
	for (int i = 2; i * i <= N; ++i)
	{
		if (p[i])
		{
			for (int j = i * i; j < N; j += i)
			{
				p[j] = false;
			}
		}
	}

	vector<ll> primes;

	primes.push_back(2);

	for (int i = 3; i < N; i+=2)
	{
		if (p[i])
		{
			primes.push_back(i);
		}
	}
}

// p is the result of sieve of erat. (p[i] == true if i is prime, else false), primes is list of primes
void get_prime_divisors (ll n, unordered_set<ll,custom_hash> & div, vector<ll> & primes, vector<bool> & p)
{
	for (int j = 0; j < (int)primes.size() && primes[j] * primes[j] <= n; ++j)
	{
		if (n % primes[j] == 0)
		{
			div.insert(primes[j]);
			while (n % primes[j] == 0)
			{
				n /= primes[j];
			}
			if (p[n])
			{
				div.insert(n);
			}
		}
	}
}

// better than the above function if we don't have the list of primes and sieve result, but it is slower than the above function if we have the list of primes and sieve result
void get_prime_divisors (ll n, unordered_set<ll,custom_hash> & div)
{
	for (int j = 2; j * j <= n; ++j)
	{
		while (n % j == 0)
		{
			div.insert(j);
			n /= j;
		}
	}
	if (n > 1)
	{
		div.insert(n);
	}
}
