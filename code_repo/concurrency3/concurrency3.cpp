#include <iostream>
#include <stdlib.h>
#include <thread>
#include <mutex>

using namespace std;

void start();

mutex mtx_num;
mutex mtx_res;
int sharedResource = 0;
int numProcesses = 0;
bool wait = false;

int main() {
  thread process1 (start);
  thread process2 (start);
  thread process3 (start);
  thread process4 (start);

  process1.join();
  process2.join();
  process3.join();
  process4.join();
}

void start() {
  while(1) {
    while(1) {
      mtx_num.lock();

      if (numProcesses == 3) {
        wait = true;
      } else if (numProcesses == 0) {
        wait = false;
        numProcesses++;
        printf("Number using resource: %d\n", numProcesses);
        mtx_num.unlock();
        break;
      } else if (wait == false) {
        numProcesses++;
        printf("Number using resource: %d\n", numProcesses);
        mtx_num.unlock();
        break;
      }
      mtx_num.unlock();
      this_thread::sleep_for(chrono::seconds(1));
    }

    mtx_res.lock();
    sharedResource++;
    mtx_res.unlock();
    this_thread::sleep_for(chrono::seconds(3));
    mtx_num.lock();
    numProcesses--;
    printf("Number using resource: %d\n", numProcesses);
    mtx_num.unlock();
  }
}
