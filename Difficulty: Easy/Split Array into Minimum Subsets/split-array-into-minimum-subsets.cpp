class Solution {
public:
    int minSubsets(vector<int>& arr) {
        sort(arr.begin(), arr.end());

        int subsets = 1;

        for (int i = 1; i < arr.size(); i++) {
            if (arr[i] != arr[i - 1] + 1)
                subsets++;
        }

        return subsets;
    }
};