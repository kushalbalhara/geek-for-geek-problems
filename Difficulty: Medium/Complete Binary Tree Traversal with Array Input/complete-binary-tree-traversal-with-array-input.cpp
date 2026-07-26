#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> levelSort(vector<int>& arr) {
        vector<vector<int>> result;
        int n = arr.size();
        int index = 0;
        int level_size = 1;
        
        while (index < n) {
            vector<int> current_level;
            
            // Push elements of the current level into a temporary vector
            for (int i = 0; i < level_size && index < n; ++i, ++index) {
                current_level.push_back(arr[index]);
            }
            
            // Sort the extracted level
            sort(current_level.begin(), current_level.end());
            
            // Add it to the final result
            result.push_back(current_level);
            
            // Double the expected nodes for the next level
            level_size *= 2;
        }
        
        return result;
    }
};