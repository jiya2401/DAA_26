//  TIME & SPACE COMPLEXITY SUMMARY
//  Method       Time             Space          Notes
//  Greedy       O(n log n)       O(1)           Picks largest coin first
//                                                (not always optimal)
//  DP           O(n * amount)    O(n * amount)  Builds full table,
//                                                always optimal 

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <chrono>
#include <iomanip>

using namespace std;

// GREEDY METHOD
int greedyChange(vector<int> coins, int amount) {
    sort(coins.rbegin(), coins.rend());   // largest coin first
    int count = 0;

    cout << "\nGreedy Coins Used : ";
    for (int coin : coins) {
        while (amount >= coin) {
            cout << coin << " ";
            amount -= coin;
            count++;
        }
    }
    cout << endl;
    return count;
}

// DYNAMIC PROGRAMMING METHOD
int dpChange(vector<int> coins, int amount) {
    int n = coins.size();
    const int INF = 9999;

    // dp[i][j] = minimum coins needed to make amount j
    // using the first i coin denominations
    vector<vector<int>> dp(n + 1, vector<int>(amount + 1));

    for (int i = 0; i <= n; i++) dp[i][0] = 0;          // amount 0 -> 0 coins
    for (int j = 1; j <= amount; j++) dp[0][j] = INF;   // no coins -> impossible

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= amount; j++) {
            dp[i][j] = dp[i - 1][j];                    // skip this coin
            if (coins[i - 1] <= j) {
                dp[i][j] = min(dp[i][j],
                                dp[i][j - coins[i - 1]] + 1);   // take this coin
            }
        }
    }

    // Print DP table (aligned columns)
    cout << "\n========== DP TABLE (min coins for each amount) ==========\n";

    cout << setw(10) << "Coin\\Amt";
    for (int j = 0; j <= amount; j++) cout << setw(5) << j;
    cout << "\n" << string(10 + 5 * (amount + 1), '-') << "\n";

    for (int i = 1; i <= n; i++) {
        cout << setw(10) << coins[i - 1];
        for (int j = 0; j <= amount; j++) {
            if (dp[i][j] == INF) cout << setw(5) << "-";
            else                 cout << setw(5) << dp[i][j];
        }
        cout << "\n";
    }
    cout << string(10 + 5 * (amount + 1), '-') << "\n";

    return dp[n][amount];
}

// MAIN
int main() {
    vector<int> coins = {1, 5, 6, 9};
    int amount;

    cout << "Coins available: 1, 5, 6, 9\n";
    cout << "Enter amount: ";
    cin >> amount;

    if (amount < 0) {
        cout << "Amount cannot be negative.\n";
        return 1;
    }

    //  Greedy
    auto startGreedy = chrono::high_resolution_clock::now();
    int greedyResult = greedyChange(coins, amount);
    auto endGreedy = chrono::high_resolution_clock::now();
    chrono::duration<double, std::nano> durationGreedy = endGreedy - startGreedy;

    // DP 
    auto startDP = chrono::high_resolution_clock::now();
    int dpResult = dpChange(coins, amount);
    auto endDP = chrono::high_resolution_clock::now();
    chrono::duration<double, std::nano> durationDP = endDP - startDP;

    // Results
    cout << "\n========== RESULTS ==========\n";
    cout << "Amount              : " << amount << endl;
    cout << "Greedy Result       : " << greedyResult << " coins" << endl;
    cout << "Greedy Time         : " << durationGreedy.count() << " ns" << endl;
    cout << "-------------------------------\n";
    cout << "DP Result           : " << dpResult << " coins" << endl;
    cout << "DP Time             : " << durationDP.count() << " ns" << endl;
    cout << "-------------------------------\n";

    // Comparison Table
    cout << "\n========== COMPARISON ==========\n";
    cout << left  << setw(12) << "Method"
         << setw(12) << "Coins"
         << setw(10) << "Optimal?" << endl;

    cout << left << setw(12) << "Greedy"
         << setw(12) << greedyResult
         << setw(10) << (greedyResult == dpResult ? "Yes" : "No") << endl;

    cout << left << setw(12) << "DP"
         << setw(12) << dpResult
         << setw(10) << "Yes" << endl;

    return 0;
}
