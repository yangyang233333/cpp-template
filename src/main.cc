#include <iostream>
#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/os.h>
#include <fmt/ranges.h>
#include <spdlog/spdlog.h>

using namespace std;

int main() {
    cout << "Hello World!" << endl;
    fmt::print("{}\n", "Hello World!");
    spdlog::info("1+1={}", 2);
}