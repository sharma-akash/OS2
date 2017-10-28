#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;

struct philospher {
    string name;
    int status = 0;
    int forks[2] = {-1, -1};
};

void think(philospher *);
void get_forks(philospher*, int*);
void eat(philospher *);
void put_forks(philospher*, int*);
void start_philospher(philospher *, int *);
void print_status(philospher *, int *);

mutex mtx;
int lastForkTaken = -1;

int main() {

  philospher philosphers[5];
  int forks[5] = {1, 1, 1, 1, 1};
  srand (time(NULL));

  philosphers[0].name = "Aristotle";
  philosphers[1].name = "Immanuel Kant";
  philosphers[2].name = "Rene Descrates";
  philosphers[3].name = "Karl Marx";
  philosphers[4].name = "John Locke";

  thread p1 (start_philospher, &philosphers[0], forks);
  this_thread::sleep_for(chrono::seconds(1));
  thread p2 (start_philospher, &philosphers[1], forks);
  this_thread::sleep_for(chrono::seconds(1));
  thread p3 (start_philospher, &philosphers[2], forks);
  this_thread::sleep_for(chrono::seconds(1));
  thread p4 (start_philospher, &philosphers[3], forks);
  this_thread::sleep_for(chrono::seconds(1));
  thread p5 (start_philospher, &philosphers[4], forks);

  print_status(philosphers, forks);

  auto startTime = chrono::steady_clock::now();
  auto endTime = chrono::steady_clock::now();

  while(true) {
    if(chrono::duration_cast<chrono::seconds>(endTime - startTime).count() > 3) {
      print_status(philosphers, forks);
      startTime = chrono::steady_clock::now();
    }
    endTime = chrono::steady_clock::now();
  }

  p1.join();
  p2.join();
  p3.join();
  p4.join();
  p5.join();
}



void start_philospher(philospher * philo, int forks[5]) {

  while (true) {
    think(philo);
    get_forks(philo, forks);
    eat(philo);
    put_forks(philo, forks);
  }

}

void think(philospher * philo) {
  int thinkingTime = rand() % 20 + 1;
  cout << "\n" << philo->name << " is thinking for " << thinkingTime << " seconds\n";
  philo->status = 2;
  this_thread::sleep_for(chrono::seconds(thinkingTime));
  return;
}

void get_forks(philospher * philo, int forks[5]) {

  while(true) {
    mtx.lock();
    int forkOne = -1, forkTwo = -1;

    for(int i = 0; i < 5; i++) {

      if(lastForkTaken == i) {
        continue;
      }

      if(lastForkTaken == 3 && forks[4] == 1) {
        forkOne = 4;
        lastForkTaken = 4;
      }

      if(forks[i]) {
        if(forkOne == -1) {
          forkOne = i;
        } else {
          forkTwo = i;
          break;
        }
      }
    }

    if(forkTwo != -1) {
      philo->forks[0] = forkOne;
      philo->forks[1] = forkTwo;
      lastForkTaken = forkTwo;
      forks[forkOne] = 0;
      forks[forkTwo] = 0;
      mtx.unlock();
      return;
    }

    mtx.unlock();
  }
}

void eat(philospher * philo) {
  int eatingTime = rand() % 8 + 2;
  cout << "\n" << philo->name << " is eating for " << eatingTime << " seconds.\n";
  philo->status = 1;
  this_thread::sleep_for(chrono::seconds(eatingTime));
  return;
}

void put_forks(philospher * philo, int forks[5]) {

  mtx.lock();
  forks[philo->forks[0]] = 1;
  forks[philo->forks[1]] = 1;
  philo->forks[0] = -1;
  philo->forks[1] = -1;
  mtx.unlock();
  philo->status = 0;
  cout << "\n" << philo->name << " put back his forks..\n";

}

void print_status(philospher philo[5], int forks[5])
{
  int x;

  cout << "\n------------------\n\n";

  for(x = 0; x < 5; x++)
  {
    switch (philo[x].status)
    {
    case 0:
      cout << philo[x].name << " is currently waiting.\n";
      break;
    case 1:
      cout << philo[x].name << " is currently eating. YUM!\n";
      break;
    case 2:
      cout << philo[x].name << " is currently thinking. Hmmm...\n";
      break;
    default:
      cout << philo[x].name << " broke my code!\n";
    }
  }

  cout << "\n";

  for (x = 0; x < 5; x++)
  {
    if (!forks[x])
    {
      cout << "Fork " << x << " is not available" << "\n";
    }
    else
    {
      cout << "Fork " << x << " is currently available\n";
    }
  }

  cout << "\n------------------\n\n";
}
