class Solution {
public:
    static const int MOD = 1000000007;

    int countSubsets(vector<int> &arr) {
        vector<int> primes = {2,3,5,7,11,13,17,19,23,29};

        int ones = 0;
        vector<int> masks;

        for (int x : arr) {
            if (x == 1) {
                ones++;
                continue;
            }

            int t = x;
            int mask = 0;
            bool ok = true;

            for (int i = 0; i < 10; i++) {
                int p = primes[i];
                int cnt = 0;

                while (t % p == 0) {
                    t /= p;
                    cnt++;
                }

                if (cnt > 1) {
                    ok = false;
                    break;
                }

                if (cnt == 1)
                    mask |= (1 << i);
            }

            if (t > 1) ok = false;

            if (ok)
                masks.push_back(mask);
        }

        vector<long long> dp(1 << 10, 0);
        dp[0] = 1;

        for (int m : masks) {
            vector<long long> ndp = dp;

            for (int mask = 0; mask < (1 << 10); mask++) {
                if ((mask & m) == 0) {
                    ndp[mask | m] = (ndp[mask | m] + dp[mask]) % MOD;
                }
            }

            dp.swap(ndp);
        }

        long long ans = 0;
        for (long long x : dp)
            ans = (ans + x) % MOD;

        ans = (ans - 1 + MOD) % MOD;   // remove empty subset

        long long mul = 1;
        while (ones--) {
            mul = (mul * 2) % MOD;
        }

        ans = (ans * mul) % MOD;

        return (int)ans;
    }
};