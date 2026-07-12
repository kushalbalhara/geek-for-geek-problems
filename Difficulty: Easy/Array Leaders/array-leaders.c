#include <stdlib.h>

int* leaders(int* arr, int n, int* returnSize) {
    int *ans = (int*)malloc(n * sizeof(int));
    int count = 0;

    int maxRight = arr[n - 1];

    ans[count++] = maxRight;

    for (int i = n - 2; i >= 0; i--) {
        if (arr[i] >= maxRight) {
            maxRight = arr[i];
            ans[count++] = arr[i];
        }
    }

    // Reverse the array
    for (int i = 0; i < count / 2; i++) {
        int temp = ans[i];
        ans[i] = ans[count - 1 - i];
        ans[count - 1 - i] = temp;
    }

    *returnSize = count;
    return ans;
}