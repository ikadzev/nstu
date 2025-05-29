#include <iostream>
#include <vector>

int count_knight_paths(int N, int M) {
    std::vector<std::vector<int>> dp(N, std::vector<int>(M, 0));
    dp[0][0] = 1;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (i - 2 >= 0 && j - 1 >= 0)
                dp[i][j] += dp[i - 2][j - 1];
            if (i - 1 >= 0 && j - 2 >= 0)
                dp[i][j] += dp[i - 1][j - 2];
        }
    }
    return dp[N - 1][M - 1];
}

int main() {
    int N, M;
    std::cin >> N >> M;
    std::cout << count_knight_paths(N, M) << std::endl;
    return 0;
}