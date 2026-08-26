*This project has been created as part of the 42 curriculum by rcamps-v.*

# Codexion 👨‍💻
## Description
Codexion is a concurrency and multithreading simulation project developed in C. It simulates a coworking space in which several programmers must share a limited number of USB drives to compile their code. The main objective of the project is to manage shared resources efficiently by coordinating multiple POSIX threads and mutexes to prevent deadlocks, avoid resource shortages, and ensure that no programmer runs out of resources before reaching the required number of compiles.

## Instructions

**Compilation:**
The project includes a Makefile to compile the source code cleanly. Run the following command at the root of the repository:
```bash
make
```
**Execution:**
Run the executable with the following 8 mandatory arguments:
```bash
./codexion <number_of_coders> <time_to_burnout> <time_to_compile> <time_to_debug> <time_to_refactor> <number_of_compiles_required> <dongle_cooldown> <scheduler>
```
scheduler: Must be either fifo (First In, First Out) or edf (Earliest Deadline First).

Example:
```bash
./codexion 2 1000 200 200 200 1 100 fifo
```
## Resources
- Documentation: POSIX Threads Programming (LLNL)

- Documentation: Mutexes and Condition Variables (Oracle)

- AI Usage: Artificial Intelligence tools were utilized during the development of this project as a peer-review assistant. Specifically, AI was used to help debug specific edge cases related to the usleep timing precision, and refine the logic of the priority queue used for the EDF and FIFO schedulers. The core architecture and thread synchronization mechanisms were manually implemented and fully understood.

### Blocking cases handled
Deadlock Prevention & Coffman Conditions: A potential deadlock (circular wait) is actively prevented by establishing a strict resource hierarchy. When a coder attempts to acquire their two assigned dongles, they will always lock the dongle with the lower index first (left_idx < right_idx evaluation). This breaks the circular wait condition.

Starvation Prevention: Resource starvation is avoided through the implementation of a dynamic priority queue (scheduler). Depending on the execution argument, the queue processes requests either strictly by arrival time (fifo) or by the most urgent burnout deadline (edf), ensuring fair access.

Cooldown Management: The dongle_cooldown is managed by recording the last_release_ms. Before assigning a dongle, the system checks if the current time has surpassed the release time plus the cooldown. If not, the thread sleeps via pthread_cond_timedwait to avoid CPU busy-looping.

Precise Burnout Detection: A dedicated monitor thread continuously iterates over all coders. By isolating the burnout checks in a separate monitor thread, the system guarantees that burnouts are detected and logged within the strict 10ms tolerance window.

Log Serialization: A global log_lock mutex surrounds every printf call. This prevents interleaved or scrambled output lines when multiple threads attempt to write their state changes simultaneously.

### Thread synchronization mechanisms
pthread_mutex_t: Used to enforce mutual exclusion on shared resources.

Dongles: Each dongle struct contains its own mutex (dongle->lock). When a coder acquires a dongle, they lock this mutex so no other thread can claim it or modify its available boolean state.

Logging: The log_lock mutex guarantees thread-safe communication to the standard output.

pthread_cond_t: Condition variables (dongle->cond) are used for efficient thread waiting. Instead of aggressively polling to check if a dongle is available (which consumes massive CPU resources), a coder thread will call pthread_cond_timedwait.

Thread-Safe Communication: When a coder finishes compiling, it calls release_dongle. This function locks the dongle's mutex, updates the availability state, unlocks it, and immediately signals all sleeping threads via pthread_cond_broadcast. This awakes the threads waiting in the queue, allowing the monitor and other coders to proceed without race conditions.