#include <cassert>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <list>
#include <mutex>
#include <thread>
#include <fiu.h>
using namespace std;
static auto get_current_timestamp() {
    auto now = std::chrono::system_clock::now();
    auto timestamp =
        std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
    return timestamp;
  }
int main(int argc, char *argv[]) {
    cout << get_current_timestamp() << endl;

}
