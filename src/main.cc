#include "simple_fuse.h"
#include <cassert>
#include <chrono>
#include <fmt/base.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <iomanip>
#include <iostream>
#include <list>
#include <mutex>
#include <thread>
using namespace std;

int main(int argc, char *argv[]) {
  fmt::println("Hello");
  fmt::println("Hello {}", "World!");
  // return fuse_main(argc, argv, &demo_ops, NULL);
}
