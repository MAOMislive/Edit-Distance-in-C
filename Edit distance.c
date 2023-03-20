#include <stdio.h>
#include <string.h>

// Helper function to return the minimum of three integers
int min(int a, int b, int c) {
    if (a < b && a < c) {
        return a;
    } else if (b < c) {
        return b;
    } else {
        return c;
    }
}

// Function to calculate the edit distance between two strings
int edit_distance(char s1[], char s2[], int m, int n) {
    // Initialize a matrix to store the edit distance between all pairs of substrings
    int dp[m+1][n+1];

    // Fill in the first row and column of the matrix with the edit distance between the empty string and each substring
    for (int i = 0; i <= m; i++) {
        dp[i][0] = i;
    }
    for (int j = 0; j <= n; j++) {
        dp[0][j] = j;
    }

    // Fill in the rest of the matrix using dynamic programming
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1]; // If the current characters are the same, no edit is needed
            } else {
                dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]); // Otherwise, take the minimum of the three possible edits
            }
        }
    }

    // Return the edit distance between the two strings
    return dp[m][n];
}

int main() {
    // Example usage
    char s1[] = "kitten";
    char s2[] = "sitting";
    int m = strlen(s1);
    int n = strlen(s2);
    int distance = edit_distance(s1, s2, m, n);
    printf("The edit distance between %s and %s is %d.\n", s1, s2, distance);
    return 0;
}
