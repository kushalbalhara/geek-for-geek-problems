class Solution {
  public:
    int longestSubarray(vector<int>& arr, int k) {
        unordered_map<long long, int> mp;
        
        long long sum = 0;
        int ans = 0;
        
        for (int i = 0; i < arr.size(); i++) {
            sum += arr[i];
            
            // If prefix sum itself equals k
            if (sum == k)
                ans = i + 1;
            
            // If (sum-k) exists, subarray found
            if (mp.find(sum - k) != mp.end()) {
                ans = max(ans, i - mp[sum - k]);
            }
            
            // Store first occurrence of prefix sum
            if (mp.find(sum) == mp.end()) {
                mp[sum] = i;
            }
        }
        
        return ans;
    }
};