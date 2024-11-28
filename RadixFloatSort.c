#include <stdio.h>

void radix_sort(unsigned int A[], unsigned int n) {
    unsigned int bucket0[100], bucket1[100];
    unsigned int mask, count0, count1;
    for (int d = 0; d < 32; d++) {
        mask = 1 << d;
        count0 = count1 = 0;
        for (int i = 0; i < n; i++) {
            if ((A[i] & mask) == 0) {
                bucket0[count0++] = A[i];
            } else {
                bucket1[count1++] = A[i];
            }
        }
        for (int i = 0; i < count0; i++) {
            A[i] = bucket0[i];
        }
        for (int i = 0; i < count1; i++) {
            A[count0 + i] = bucket1[i];
        }
    }
}

void real_radix_sort(float A[], unsigned int n) {
    unsigned int positive[100], negative[100];
    unsigned int pCount = 0, nCount = 0;
    for (unsigned int i = 0; i < n; i++) {
        unsigned int *p = (unsigned int *)&A[i];
        if (A[i] >= 0) {
            positive[pCount++] = *p;
        } else {
            unsigned int neg = *p ^ 0xFFFFFFFF;
            negative[nCount++] = neg;
        }
    }
    radix_sort(positive, pCount);
    radix_sort(negative, nCount);

    for (int i = 0; i < nCount; i++) {
        unsigned int neg = negative[i] ^ 0xFFFFFFFF;
        float *f = (float *)&neg;
        A[i] = *f;
    }
    for (unsigned int i = 0; i < pCount; i++) {
        float *f = (float *)&positive[i];
        A[nCount + i] = *f;
    }
}

int main() {
    unsigned int arrayAmount, x, i = 0;
    printf("How many values will you use?: ");
    if (scanf("%u", &arrayAmount) != 1 || arrayAmount > 100 || arrayAmount <= 0) {
        printf("Invalid input, must be between 1 and 100 \n");
        return 1;
    }
    float arr[arrayAmount];
    while (i < arrayAmount){
    	printf("Enter your number: ");
        if (scanf("%f", &arr[i]) != 1) {
            printf("Invalid input\n");
            return 1;
        }
        i++;
    }

    printf("Before:\n");
    for (unsigned int i = 0; i < arrayAmount; i++) {
        printf("%f\n", arr[i]);
    }

    printf("After:\n");
    real_radix_sort(arr, arrayAmount);
    for (unsigned int i = 0; i < arrayAmount; i++) {
        printf("%f\n", arr[i]);
    }
    
    return 0;
}

