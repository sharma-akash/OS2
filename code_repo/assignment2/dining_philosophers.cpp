#include <iostream>

using namespace std;

struct philospher {
    bool hasFork = false;
} Aristotle, ImmanuelKant, ReneDescrates, KarlMarx, JohnLocke;

void think(philospher);
int get_forks(int*);
void eat(philospher);
void put_forks();

int main() {

  philospher philosphers[5];

  philosphers[0] = Aristotle;
  philosphers[1] = ImmanuelKant;
  philosphers[2] = ReneDescrates;
  philosphers[3] = KarlMarx;
  philosphers[4] = JohnLocke;

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
