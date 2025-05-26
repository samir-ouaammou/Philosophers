# 🏛️ Philosophers - 1337 School Project (With Bonus)

## 🔹 Introduction

Philosophers is a concurrency problem that explores process/thread synchronization using mutexes and semaphores. This project is an exercise in avoiding race conditions, deadlocks, and resource starvation while adhering to The Dining Philosophers Problem rules.

The project helps develop a deep understanding of threading, mutexes, and synchronization mechanisms in C. The bonus part introduces an alternative approach using semaphores for better synchronization and performance.

---

## 📌 The Dining Philosophers Problem

The problem involves `N` philosophers sitting at a round table, with `N` forks placed between them. Philosophers follow these rules:

1. A philosopher must pick up two forks (left and right) to eat.
2. A philosopher must release both forks after eating and return to thinking.
3. A philosopher must not starve (if one is unable to eat indefinitely, the implementation fails).
4. A void deadlocks where all philosophers hold one fork and wait indefinitely.

---

## 🏗️ Implementation Details

### 🔹 Program Execution

The program takes the following arguments:

```shell
./philosophers [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [optional: number_of_meals]
```

- `number_of_philosophers` → Total number of philosophers.
- `time_to_die` → Time (in ms) after which a philosopher dies if they do not eat.
- `time_to_eat` → Time (in ms) taken for a philosopher to eat.
- `time_to_sleep` → Time (in ms) taken for a philosopher to sleep.
- `number_of_meals` (optional) → If provided, the simulation stops when all philosophers eat this many meals.

### 🔹 Threads & Synchronization

- Each philosopher is represented by a thread.
- Forks are protected using mutexes to prevent race conditions.
- Time tracking ensures philosophers do not exceed `time_to_die`.
- Mutex locking/unlocking ensures controlled fork access.

---

## ⚡ Key Features

✅ Multi-threaded execution.                    
✅ Uses mutexes for safe fork access.            
✅ Prevents deadlocks.               
✅ Supports an optional meal limit.          
✅ Prints philosopher actions (thinking, eating, sleeping, died).          
✅ Bonus: Implements semaphores for better synchronization.              

---

## 🏗️ Project Structure

```
philo/                 # Core part of the project
├── Makefile           # Build script
├── Philo_header.h     # Main header file
├── Philo_parsing.c    # Parsing-related code
├── malloc             # Memory allocation related functions
├── Philo_main.c       # Entry point for the main part
├── Philo_routine.c    # Philosopher behavior (eating, thinking, etc.)

philo_bonus/           # Bonus part (semaphore-based synchronization)
├── Makefile           # Build script for bonus
├── Philo_header.h     # Header file for bonus part
├── Philo_parsing.c    # Parsing-related code for bonus
├── malloc             # Memory allocation for bonus
├── Philo_main.c       # Entry point for the bonus part
├── Philo_routine.c    # Philosopher behavior with semaphores    
```

---

## 🛠️ Installation & Compilation

1. Clone the repository to your local machine:
   ```bash
   git clone https://github.com/samir-ouaammou/1337-Philosophers 
   ```
2. Navigate to the project directory:
   ```bash
   cd 1337-Philosophers/Project/philo
   ```
3. Compile the source files using `make`:
   ```bash
   make 
   ```
4. Clean up compiled files:
   ```bash
   make clean
   ```
5. To remove all object files and the executable:
   ```bash
   make fclean
   ```
6. To recompile the project from scratch:
   ```bash
   make re
   ```
7. Run the program:
   ```bash
   ./philo 5 800 200 200
   ```

For the bonus part:           

1. Navigate to the philo_bonus directory:
   ```bash
   cd ..
   cd philo_bonus
   ```
2. Compile the bonus version using:
   ```bash
   make 
   ```
3. Run the bonus program:
   ```bash
   ./philo_bonus 5 800 200 200 
   ```
---

## 🚀 Expected Output

The output should display philosophers' actions:

```
0   Philosopher 1 is thinking
5   Philosopher 2 is thinking
10  Philosopher 3 has taken a fork
15  Philosopher 3 has taken another fork
20  Philosopher 3 is eating
...
1000 Philosopher 2 has died
```

If no philosopher starves, the program runs successfully.

---

## 🎯 Bonus Part: Semaphore-Based Implementation

The bonus part replaces mutexes with semaphores:

- Uses a global semaphore for forks instead of individual mutexes.
- Prevents deadlocks using an alternative synchronization strategy.
- More efficient for large numbers of philosophers.

---

## 🏆 Achievements

✅ Gained deep understanding of threading and synchronization.            
✅ Implemented mutexes to avoid race conditions.          
✅ Successfully prevented deadlocks.           
✅ Optimized time management to avoid unnecessary delays.          
✅ Learned how to manage thread execution effectively.         
✅ Implemented a semaphore-based solution for better scalability.   

---

## 🎯 Next Steps

✅ Enhance performance for large numbers of philosophers.               
✅ Implement additional optimizations for the mutex-based version.              
✅ Explore alternative synchronization mechanisms.           
✅ Apply lessons learned to future concurrency projects.        
✅ Compare mutex and semaphore-based implementations.         

---

## 💡 Reflection

This project was a challenging yet rewarding experience in concurrent programming. It deepened my understanding of threads, mutexes, and process scheduling. Learning to avoid race conditions, deadlocks, and starvation was crucial. 

The bonus part, implementing semaphores, allowed me to explore different synchronization techniques. Understanding when to use mutexes versus semaphores was an essential takeaway. This project has significantly improved my problem-solving skills in low-level programming and concurrency control. 🚀

---

Thank you for checking out my Philosophers project! Stay tuned for more exciting challenges. 🔥

