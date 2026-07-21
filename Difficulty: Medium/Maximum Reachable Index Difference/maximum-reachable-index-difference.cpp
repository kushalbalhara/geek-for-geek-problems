class Solution {
public:
    int maxIndexDifference(string &s) {
        int n = s.size();

        vector<int> dp(n);
        vector<int> best(26, -1);

        bool hasA = false;
        int ans = -1;

        for (int i = n - 1; i >= 0; i--) {
            int c = s[i] - 'a';

            dp[i] = i;

            if (c < 25 && best[c + 1] != -1)
                dp[i] = best[c + 1];

            best[c] = max(best[c], dp[i]);

            if (c == 0) {
                hasA = true;
                ans = max(ans, dp[i] - i);
            }
        }

        return hasA ? ans : -1;
    }
};