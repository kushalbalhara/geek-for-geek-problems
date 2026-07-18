class Solution {
public:
    int findWays(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        int m = matrix[0].size();
        int MOD = 1e9 + 7;

        // Base case: If k == 1, just check if the matrix has at least one '1'
        if (k == 1) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (matrix[i][j] == 1) return 1;
                }
            }
            return 0;
        }

        // 1. Build the 2D Suffix Sum Array
        vector<vector<int>> suf(n + 1, vector<int>(m + 1, 0));
        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                suf[i][j] = matrix[i][j] 
                          + suf[i + 1][j] 
                          + suf[i][j + 1] 
                          - suf[i + 1][j + 1];
            }
        }

        // Quick fail: If the total '1's in the matrix is less than k, it's impossible.
        if (suf[0][0] < k) return 0;

        // 2. Precompute the immediate next valid cut index to avoid looping later
        vector<vector<int>> next_r(n, vector<int>(m, n));
        vector<vector<int>> next_c(n, vector<int>(m, m));

        for (int r = n - 1; r >= 0; r--) {
            for (int c = m - 1; c >= 0; c--) {
                // Next row that leaves at least one '1' in the top piece
                if (r + 1 < n) {
                    next_r[r][c] = (suf[r][c] > suf[r + 1][c]) ? (r + 1) : next_r[r + 1][c];
                }
                // Next column that leaves at least one '1' in the left piece
                if (c + 1 < m) {
                    next_c[r][c] = (suf[r][c] > suf[r][c + 1]) ? (c + 1) : next_c[r][c + 1];
                }
            }
        }

        // 3. Initialize DP for 0 cuts remaining (Base State)
        vector<vector<int>> prev_dp(n, vector<int>(m, 0));
        vector<vector<int>> curr_dp(n, vector<int>(m, 0));

        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                if (suf[r][c] > 0) prev_dp[r][c] = 1;
            }
        }

        vector<vector<int>> col_sum(n + 1, vector<int>(m + 1, 0));
        vector<vector<int>> row_sum(n + 1, vector<int>(m + 1, 0));

        // 4. Bottom-Up DP for 1 to k-1 cuts
        for (int cut = 1; cut < k; cut++) {
            
            // Generate cumulative sums of the previous DP state for O(1) lookups
            for (int r = n - 1; r >= 0; r--) {
                for (int c = m - 1; c >= 0; c--) {
                    col_sum[r][c] = (prev_dp[r][c] + col_sum[r + 1][c]) % MOD;
                    row_sum[r][c] = (prev_dp[r][c] + row_sum[r][c + 1]) % MOD;
                }
            }

            for (int r = n - 1; r >= 0; r--) {
                for (int c = m - 1; c >= 0; c--) {
                    // Invalid submatrix (no 1s left)
                    if (suf[r][c] == 0) {
                        curr_dp[r][c] = 0;
                        continue;
                    }

                    long long ways = 0;

                    // Fetch all valid horizontal cuts in O(1)
                    int nr = next_r[r][c];
                    if (nr < n) {
                        ways = (ways + col_sum[nr][c]) % MOD;
                    }

                    // Fetch all valid vertical cuts in O(1)
                    int nc = next_c[r][c];
                    if (nc < m) {
                        ways = (ways + row_sum[r][nc]) % MOD;
                    }

                    curr_dp[r][c] = ways;
                }
            }
            // Overwrite previous state
            prev_dp = curr_dp;
        }

        return prev_dp[0][0];
    }
};