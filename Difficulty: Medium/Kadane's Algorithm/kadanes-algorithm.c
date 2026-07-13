int maxSubarraySum(int arr[], int n) {
    int curr = arr[0];
    int ans = arr[0];

    for (int i = 1; i < n; i++) {
        curr = (curr + arr[i] > arr[i]) ? curr + arr[i] : arr[i];
        ans = (ans > curr) ? ans : curr;
    }

    return ans;
}