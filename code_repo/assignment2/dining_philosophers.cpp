#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <thread>

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
void startPhilospher(int*,  philospher*);


int main() {

  philospher philosphers[5];
  int forks[5] = {1, 1, 1, 1, 1};
  srand (time(NULL));

  philosphers[0].name = "Aristotle";
  philosphers[1].name = "ImmanuelKant";
  philosphers[2].name = "ReneDescrates";
  philosphers[3].name = "KarlMarx";
  philosphers[4].name = "JohnLocke";

    for(int i = 0; i < 5; i++) {
      thread t (test, forks, philosphers);
    }

}



void startPhilospher(int forks[5], philospher philosphers[5]) {

  for(int i = 0; i < 5; i++) {
    cout << philosphers[i].name << "\n";
  }
}

/*
  while (true) {
    think(philosphers[i]);
    get_forks(forks);
    eat(philosphers[i]);
    put_forks();
  }
  */
}

void think(philospher philo) {
  int thinkingTime = rand() % 20 + 1;

  return;
}

int get_forks(int forks[5]) {
  return 0;
}

void eat(philospher philo) {

  int eatingTime = rand() % 8 + 2;

  return;
}

void put_forks() {
  return;
}

void print_status(philospher philo, int [])
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

  for (x = 0; x++, x < 5)
  {
    if (philo[x].hasFork == 1)
    {
      cout << "Fork number" << x << "is in the hands of" << philo[x].name << "\n";
    }
    else
    {
      cout << "Fork number" << x << "is currently available\n";
    }
  }
}
