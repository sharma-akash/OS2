#include <iostream>

using namespace std;

void think();
void get_forks();
void eat();
void put_forks();

struct philospher {
    bool hasFork = false;
};

int main() {

  philospher Aristotle;
  philospher ImmanuelKant;
  philospher ReneDescrates;
  philospher KarlMarx;
  philospher JohnLocke;

  while (true) {
    think();
    get_forks();
    eat();
    put_forks();
    }
}

void think() {
  return;
}

void get_forks() {
  return;
}

void eat() {
  return;
}

void put_forks() {
  return;
}
