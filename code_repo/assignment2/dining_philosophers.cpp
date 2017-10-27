#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct philospher {
    string name;
    bool hasFork = false;
    bool isEating = false;
    bool isThinking = false;
};

void think(philospher);
int get_forks(int*);
void eat(philospher);
void put_forks();

int main() {

  philospher philosphers[5];
  srand (time(NULL));

  philosphers[0].name = "Aristotle";
  philosphers[1].name = "ImmanuelKant";
  philosphers[2].name = "ReneDescrates";
  philosphers[3].name = "KarlMarx";
  philosphers[4].name = "JohnLocke";

  int forks[5] = {1, 1, 1, 1, 1};

  while (true) {
    for(int i = 0; i < 5; i++) {
      think(philosphers[i]);
      get_forks(forks);
      eat(philosphers[i]);
      put_forks();
      }
  }
}

void think(philospher philo) {
  int thinkingTime = rand() % 20 + 1;

  return;
}

int get_forks(int forks[5]) {
  return 0;
}

void eat(philospher philo) {
  return;
}

void put_forks() {
  return;
}
