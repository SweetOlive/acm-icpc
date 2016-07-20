#include <stdio.h>
const int maxn = 16, ans[maxn][maxn] = {
{1, 1, 1, 1, 1, 1, 1, 1},
{1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597},
{3, 11, 41, 153, 571, 2131, 7953, 29681},
{1, 5, 11, 36, 95, 281, 781, 2245, 6336, 18061, 51205, 145601, 413351, 1174500, 3335651, 9475901},
{8, 95, 1183, 14824, 185921, 2332097, 29253160, 366944287},
{1, 13, 41, 281, 1183, 6728, 31529, 167089, 817991, 4213133, 21001799, 106912793, 536948224, 720246619, 704300462, 289288426},
{21, 781, 31529, 1292697, 53175517, 188978103, 124166811, 708175999},
{1, 34, 153, 2245, 14824, 167089, 1292697, 12988816, 108435745, 31151234, 940739768, 741005255, 164248716, 498190405, 200052235, 282756494},
{55, 6336, 817991, 108435745, 479521663, 528655152, 764896039, 416579196},
{1, 89, 571, 18061, 185921, 4213133, 53175517, 31151234, 479521663, 584044562, 472546535, 732130620, 186229290, 274787842, 732073997, 320338127},
{144, 51205, 21001799, 940739768, 472546535, 177126748, 513673802, 881924366},
{1, 233, 2131, 145601, 2332097, 106912793, 188978103, 741005255, 528655152, 732130620, 177126748, 150536661, 389322891, 371114062, 65334618, 119004311},
{377, 413351, 536948224, 164248716, 186229290, 389322891, 351258337, 144590622},
{1, 610, 7953, 1174500, 29253160, 720246619, 124166811, 498190405, 764896039, 274787842, 513673802, 371114062, 351258337, 722065660, 236847118, 451896972},
{987, 3335651, 704300462, 200052235, 732073997, 65334618, 236847118, 974417347},
{1, 1597, 29681, 9475901, 366944287, 289288426, 708175999, 282756494, 416579196, 320338127, 881924366, 119004311, 144590622, 451896972, 974417347, 378503901}};
typedef long long LL;
const int mod = 1000000007;
int sz[1 << maxn], lbit[1 << maxn];
int f[maxn + 1][maxn + 1], g[maxn + 1], h[maxn + 1];
int solve(int n, int m)
{
	int ret = 0;
	if(n > m)
	{
		n = n + m;
		m = n - m;
		n = n - m;
	}
	for(int msk = 0; msk < 1 << n - 1; ++msk)
	{
		for(int i = 1; i <= m; ++i)
		{
			g[i] = 1;
			int s = msk, pre = -1, cur = lbit[s];
			for( ; s > 0; pre = cur, s ^= 1 << cur, cur = lbit[s])
				g[i] = (LL)g[i] * f[i][cur - pre] % mod;
			h[i] = g[i] = (LL)g[i] * f[i][n - 1 - pre] % mod;
			for(int j = 1; j < i; ++j)
				h[i] = (h[i] - (LL)h[j] * g[i - j]) % mod;
			if(h[i] < 0)
				h[i] += mod;
		}
		if(sz[msk] & 1)
		{
			if((ret -= h[m]) < 0)
				ret += mod;
		}
		else
		{
			if((ret += h[m]) >= mod)
				ret -= mod;
		}
	}
	return ret;
}
int main()
{
	for(int i = 1; i < 1 << maxn; ++i)
	{
		sz[i] = sz[i >> 1] + (i & 1);
		lbit[i] = i & 1 ? 0 : lbit[i >> 1] + 1;
	}
	f[0][0] = 1;
	for(int i = 1; i <= maxn; ++i)
		f[i][0] = f[0][i] = 1;
	for(int i = 1; i <= maxn; i += 2)
		for(int j = 2; j <= maxn; j += 2)
			f[i][j] = ans[i - 1][j - 2 >> 1];
	for(int i = 2; i <= maxn; i += 2)
		for(int j = 1; j <= maxn; ++j)
			f[i][j] = ans[i - 1][j - 1];
	int n, m;
	while(scanf("%d%d", &n, &m) == 2)
    	printf("%d\n", solve(n, m));
	return 0;
}