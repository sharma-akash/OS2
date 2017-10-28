#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct philospher {
    string name;
    int hasFork = 0;
    int isEating = 0;
    int isThinking = 0;
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
  int thinkingTime = rand() % 8 + 2;

  return;
}

void put_forks() {
  return;
}

void print_status(philospher philo[])
{
  int x;
  for(x = 0; x++; x < 5)
  {
    switch (philo[x].isThinking)
    {
    case 0:
      cout << "Philosopher" << x << "," << philo[x].name << ", is currently eating\n";
    case 1:
      cout << "Philosopher" << x << "," << philo[x].name << ", is currently thinking\n";
    default:
      cout << "Philosopher" << x << "," << philo[x].name << ", is currently waiting\n";
    }
  } 

  int y;
  for (y = 0; y++; y < 5)
  {
    if (philo[y].hasFork == 1)
    {
      cout << "Fork number" << y << "is in the hands of" << philo[y].name << "\n";
    }
    else
    {
      cout << "Fork number" << y << "is currently available\n";
    }
  }
}