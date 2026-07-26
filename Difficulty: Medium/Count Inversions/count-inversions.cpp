class Solution {
private:
    int mergeAndCount(vector<int>& arr, int left, int mid, int right) {
        int i = left;
        int j = mid + 1;
        int k = 0;
        int inv_count = 0;
        
        // Temporary array for merged elements
        vector<int> temp(right - left + 1);

        // Merge the two halves while counting inversions
        while (i <= mid && j <= right) {
            if (arr[i] <= arr[j]) {
                temp[k++] = arr[i++];
            } else {
                // Inversion found
                temp[k++] = arr[j++];
                inv_count += (mid - i + 1);
            }
        }

        // Copy remaining elements of left half (if any)
        while (i <= mid) {
            temp[k++] = arr[i++];
        }

        // Copy remaining elements of right half (if any)
        while (j <= right) {
            temp[k++] = arr[j++];
        }

        // Copy sorted elements back into original array
        for (int p = 0; p < temp.size(); p++) {
            arr[left + p] = temp[p];
        }

        return inv_count;
    }

    int mergeSortAndCount(vector<int>& arr, int left, int right) {
        int inv_count = 0;
        if (left < right) {
            int mid = left + (right - left) / 2;

            // Count inversions in the left half
            inv_count += mergeSortAndCount(arr, left, mid);
            
            // Count inversions in the right half
            inv_count += mergeSortAndCount(arr, mid + 1, right);
            
            // Count inversions across the split
            inv_count += mergeAndCount(arr, left, mid, right);
        }
        return inv_count;
    }

public:
    int inversionCount(vector<int>& arr) {
        return mergeSortAndCount(arr, 0, arr.size() - 1);
    }
};