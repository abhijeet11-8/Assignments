#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

pair<vector<vector<int>>, int> LCS(string X, string Y) {
    int m = X.length();
    int n = Y.length();

    // Create a 2D table to store lengths of LCS
    vector<vector<int>> c(m + 1, vector<int>(n + 1, 0));

    // Fill the table in bottom-up manner
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1])
                c[i][j] = c[i - 1][j - 1] + 1;
            else
                c[i][j] = max(c[i - 1][j], c[i][j - 1]);
        }
    }

    return {c, c[m][n]};
}

string getLCS(string X, string Y, vector<vector<int>>& c) {
    int i = X.length();
    int j = Y.length();
    string lcs = "";

    // Backtracking to find the LCS string
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs += X[i - 1];
            i--; j--;
        } else if (c[i - 1][j] >= c[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    reverse(lcs.begin(), lcs.end());
    return lcs;
}

int main() {
    string X = "ABCBDAB";
    string Y = "BDCABA";

    auto [table, length] = LCS(X, Y);
    cout << "Length of LCS: " << length << endl;

    string lcs = getLCS(X, Y, table);
    cout << "LCS: " << lcs << endl;

    return 0;
}