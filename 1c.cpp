#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <numeric>

using ll = long long;
using ld = long double;

template <typename U>
void dfs(const U& pixels, U& used, std::pair<ll, ll> point, std::pair<ld, ld>& current_mean, ll& current_sum, ll n, ll m) {
    auto [x, y] = point;
    if (used[x][y]) {
        return;
    }

    current_mean.first += x * pixels[x][y];
    current_mean.second += y * pixels[x][y];
    current_sum += pixels[x][y];

    if (x > 0) {
        dfs(pixels, used, {x - 1, y}, current_mean, current_sum, n, m);
    }
    if (x < n - 1) {
        dfs(pixels, used, {x + 1, y}, current_mean, current_sum, n, m);
    }
    if (y > 0) {
        dfs(pixels, used, {x, y - 1}, current_mean, current_sum, n, m);
    }
    if (y < m - 1) {
        dfs(pixels, used, {x, y + 1}, current_mean, current_sum, n, m);
    }

}

int main() {
    std::fstream file;
    file.open(R"(C:\Users\zaits\Deskto\Python\circle.png)");
    char value;
    //////// TODO
    ll n; // длина
    ll m; // ширина
    std::vector<std::vector<ll>> pixels(n, std::vector<ll>(m)); // должен быть считан

    ll sum = 0;
    ld x_mean = 0, y_mean = 0;

    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < m; ++j) {
            x_mean += i * pixels[i][j];
            y_mean += j * pixels[i][j];
            sum += pixels[i][j];
        }
    }
    x_mean /= sum;
    y_mean /= sum;

    std::vector<std::pair<ld, ld>> means;
    std::vector<std::vector<ll>> used(n);
    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < m; ++j) {
            std::pair<ld, ld> current_mean = {0, 0};
            ll current_sum = 0;
            if (!used[i][j] && pixels[i][j]) {
                dfs(pixels, used, {i, j}, current_mean, current_sum, n, m);
            }
            auto[x, y] = current_mean;
            means.emplace_back(x / current_sum, y / current_sum);
        }
    }
    std::sort(std::begin(means), std::end(means),
              [x_mean, y_mean](const std::pair<ld, ld> &lhs, const std::pair<ld, ld> &rhs) {
                  // (lhs.second - y_mean) / (lhs.first - x_mean) < (rhs.second - y_mean) / (rhs.first - x_mean)
                  return (lhs.second - y_mean) * (rhs.first - x_mean) < (rhs.second - y_mean) * (lhs.first - x_mean);
              });
    std::vector<ld> distances;
    distances.reserve(means.size());
    for (auto point : means) {
        distances.push_back(std::sqrt(std::pow(point.first - x_mean, 2) + std::pow(point.second - y_mean, 2)));
    }
    ll amount_of_peaks = 0;
    for (int i = 1; i < distances.size() - 1; ++i) {
        if (distances[i - 1] < distances[i] && distances[i] < distances[i + 1]) {
            ++amount_of_peaks;
        }
    }
    if (distances.back() < distances.front() && distances.front() < distances[1]) {
        ++amount_of_peaks;
    }
    if (distances[distances.size() - 2] < distances.back() && distances.back() < distances.front()) {
        ++amount_of_peaks;
    }

    if (amount_of_peaks > 4) {
        std::cout << "circle" << std::accumulate(std::begin(distances), std::end(distances), 0) / distances.size();
    }
    // TODO
    // нужно перебрать остальные случаи, не успел...
    return 0;
}
