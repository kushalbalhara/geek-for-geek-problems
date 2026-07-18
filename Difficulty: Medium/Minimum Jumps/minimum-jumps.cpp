class Solution {
  public:
    int minJumps(vector<int>& arr) {
        int n = arr.size();
        
        // Edge cases
        if (n <= 1) return 0; // Already at the last index
        if (arr[0] == 0) return -1; // Cannot even make the first jump

        int jumps = 0;
        int current_end = 0;
        int farthest = 0;

        // We only iterate up to n - 2 because if we reach the last element, 
        // we don't need to jump from it.
        for (int i = 0; i < n - 1; i++) {
            // Update the farthest index we can reach from our current position
            farthest = max(farthest, i + arr[i]);
            
            // If the farthest we can reach is our current index, we are stuck.
            if (i == farthest) return -1;
            
            // If we have reached the end of the range for the current jump
            if (i == current_end) {
                jumps++;
                current_end = farthest;
                
                // If the new range already reaches or exceeds the last index, we can stop
                if (current_end >= n - 1) break;
            }
        }
        
        return (current_end >= n - 1) ? jumps : -1;
    }
};