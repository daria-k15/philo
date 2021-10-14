# Dining philosophers problem
This project has a goal to get knowledge about multhithreding and multiprocessing and related problems with data manipulation.

* Philo - multithreading and mutex
* Philo_bonus - multiprocessing and semaphore

# Parameters
1. number_of_philosophers: is the number of philosophers and also the number of forks
2. time_to_die: is in milliseconds, if a philosopher doesn’t start eating ’time_to_die’ milliseconds after starting his last meal or the beginning of the simulation, it dies
3. time_to_eat: is in milliseconds and is the time it takes for a philosopher to eat. During that time he will need to keep the two forks
4. time_to_sleep: is in milliseconds and is the time the philosopher will spend sleeping
5. number_of_times_each_philosopher_must_eat: argument is optional, if all philosophers eat at least ’number_of_times_each_philosopher_must_eat’ the simulation will stop. If not specified, the simulation will stop only at the death of a philosopher.

# Examples 
* 5 800 200 200 - no one should die
* 5 800 200 200 7 - no one should die and the simulation should stop when all the philosopher haseaten at least 7 times each
* 4 310 200 100 - a philosopher should die
