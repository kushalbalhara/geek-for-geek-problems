class Solution {
public:
    int find(vector<int>& arr) {
        int need = 0;

        for (int i = arr.size() - 1; i >= 0; i--) {
            need = (need + arr[i] + 1) / 2;   // ceil((need + arr[i]) / 2)
        }

        return max(1, need);
    }
};