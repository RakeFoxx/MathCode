/**
	Computes determinants in O(n^3).

	@author Rishabh Ranjan

	input format:
	T
	(T testcases)
	N
	(N rows) (N scalars)

	eg.
	2

	3
	-3 0 0
	6 4 0
	-1 2 5

	4
	2 0 -4 6
	4 5 1 0
	0 2 6 -1
	-3 8 9 1
*/

#include <iostream>
#include <vector>
using namespace std;

// for ease of change to user-defined datatypes
typedef double scalar;

typedef vector<scalar> vs;
typedef vector<vector<scalar>> vvs;

// returns det of a
// modifies a
// using row reduction to upper triangular form
scalar det(vvs &a)
{
	int n = a.size();
	bool sb = false; // tracks sign changes of det as a is modified

	// o -> row/column offset for reduction work
	for(int o = 0; o < n; ++o)
	{
		// pivoting
		if(a[o][o] == 0)
		{
			int i;
			for(i = o+1; i < n; ++i)
			{
				if(a[i][o] != 0)
				{
					swap(a[o], a[i]);
					sb ^= 1;
					break;
				}
			}

			if(i == n) // det is 0 if pivoting fails
				return 0;
		}

		for(int i = o+1; i < n; ++i)
		{
			scalar m = a[i][o] / a[o][o];
			for(int j = o+1; j < n; ++j)
				a[i][j] = a[i][j] - m*a[o][j]; // reduction of jth row
		}
	}

	scalar d = 1; // stores det
	// det = product of diagonal entries in upper triangular form
	for(int i = 0; i < n; ++i)
		d *= a[i][i];
	if(sb) d = -d; // accounts for sign change

	return d;
}

int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		int n;
		cin >> n;

		vvs a(n, vs(n));
		for(int i = 0; i < n; ++i)
		{
			for(int j = 0; j < n; ++j)
				cin >> a[i][j];
		}

		cout << det(a) << '\n';
	}
}