#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

int min(int a, int b, int c) {
    int min = a;
    if (b < min) {
        min = b;
    }
    if (c < min) {
        min = c;
    }
    return min;
}

int editDistance(char str1[], char str2[], int len1, int len2) {
    int dp[MAX_LEN][MAX_LEN];
    int i, j;
    
    for (i = 0; i <= len1; i++) {
        for (j = 0; j <= len2; j++) {
            if (i == 0) {
                dp[i][j] = j;
            } else if (j == 0) {
                dp[i][j] = i;
            } else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + min(dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]);
            }
        }
    }
    
    // print the steps to convert str1 to str2
    i = len1;
    j = len2;
    while (i > 0 && j > 0) {
        if (str1[i - 1] == str2[j - 1]) {
            i--;
            j--;
        } else if (dp[i][j] == dp[i - 1][j - 1] + 1) {
            printf("Replace %c with %c\n", str1[i - 1], str2[j - 1]);
            str1[i - 1] = str2[j - 1];
            i--;
            j--;
        } else if (dp[i][j] == dp[i - 1][j] + 1) {
            printf("Delete %c\n", str1[i - 1]);
            i--;
            // delete character from str1
            memmove(&str1[i], &str1[i + 1], len1 - i);
            len1--;
        } else if (dp[i][j] == dp[i][j - 1] + 1) {
            printf("Insert %c\n", str2[j - 1]);
            // insert character into str1
            memmove(&str1[i], &str1[i - 1], len1 - i + 1);
            str1[i - 1] = str2[j - 1];
            len1++;
            j--;
        }
        printf("Updated string 1: %s\n", str1);
        printf("Updated string 2: %s\n", str2);
    }
    while (i > 0) {
        printf("Delete %c\n", str1[i - 1]);
        i--;
        // delete character from str1
        memmove(&str1[i], &str1[i + 1], len1 - i);
        len1--;
        printf("Updated string 1: %s\n", str1);
        printf("Updated string 2: %s\n", str2);
    }
    while (j > 0) {
        printf("Insert %c\n", str2[j - 1]);
        // insert character into str1
        memmove(&str1[i], &str1[i - 1], len1 - i);
        str1[i - 1] = str2[j - 1];
        len1++;
        j--;
        printf("Updated string 1: %s\n", str1);
        printf("Updated string 2: %s\n", str2);
    }
    
    return dp[len1][len2];
}

int main() {
    char str1[MAX_LEN], str2[MAX_LEN];
    int len1, len2, distance;
    
    printf("Enter string 1: ");
    scanf("%s", str1);
    printf("Enter string 2: ");
    scanf("%s", str2);
    
    len1 = strlen(str1);
    len2 = strlen(str2);
    
    distance = editDistance(str1, str2, len1, len2);
    
    printf("Minimum edit distance: %d\n", distance);
    
    return 0;
}
