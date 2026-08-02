# Philosophers 🍝

A 42 School project that dives into the world of **concurrent programming**. Based on the classic *Dining Philosophers* problem, this project is all about threads, mutexes, and avoiding the two nightmares of concurrency: **deadlocks** and **data races**.

## 📖 About

A number of philosophers sit around a table, alternating between three states: eating, thinking, and sleeping. Between each philosopher lies a single fork, meaning each philosopher needs **both** the fork on their left and the fork on their right to eat.

The challenge is to simulate this scenario while respecting strict rules:
- No philosopher should starve to death.
- No data race should occur on shared resources (the forks).
- No philosopher should be able to eat without holding two forks.
- Philosophers should not lift a fork before actually needing it.

This project forces you to think about timing, synchronization, and how to model a real-world resource contention problem using threads and mutexes in C.

## ⚙️ Features

- Simulation of `N` philosophers with individual threads
- Fork management using mutexes to prevent race conditions
- Death detection (a philosopher who hasn't eaten in `time_to_die` ms dies, and the simulation stops)
- Optional meal count limit (simulation stops once every philosopher has eaten enough times)
- Clean thread synchronization with no deadlocks

## 🚀 Usage

```bash
make
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

**Example:**
```bash
./philo 5 800 200 200
```

## 🎨 Debug Mode — Colored Output

Following the simulation live in the terminal can get messy fast, especially with a lot of philosophers logging at once. To make debugging easier, this project includes a simple **color toggle**.

In `main.c`, there's a variable called `color`:

```c
vars.color = false; // set to 'false' to disable colors, true to enable
```

When `color` is set to `true`, each philosopher's actions (`is thinking`, `is eating`, `is sleeping`, `has taken a fork`, `died`) are printed in a **unique color**, making it instantly clear who is doing what without having to trace philosopher IDs through a wall of text.

Set it to `false` for standard, uncolored output (useful when piping logs to a file or running automated tests).

Piping the output (e.g. `xclip --selection clipboard`) carries the ANSI color codes with it. This matters because of [philosophers-visualizer](https://nafuka11.github.io/philosophers-visualizer/), a tool that takes the raw, uncolored output of your simulation and turns it into a visual timeline of each philosopher's state. Feed it colored output and it won't parse correctly — so keeping the plain mode around isn't just for logs, it's what makes this visualizer actually usable.

This small addition made debugging race conditions and timing issues significantly easier during development — being able to visually track a single philosopher's state changes across the terminal saved a lot of head-scratching.

## 🧠 What I Learned

- Thread creation and synchronization (`pthread_create`, `pthread_join`)
- Mutex locking strategies to prevent deadlocks
- Precise timing management in C
- Debugging concurrent programs (a skill that transfers directly to systems and security work)

## 🛠️ Built With

- C
- pthread / mutex

---
*Part of the 42 School common core curriculum.*
