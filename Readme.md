# Linux & OS Systems Programming Tasks

A collection of practical implementations and exercises exploring operating system internals and system programming concepts.

---

## Table of Contents

- [Chapter 45: Introduction to System V IPC](#chapter-45-introduction-to-system-v-ipc)

---

## Chapter 45: Introduction to System V IPC

### Exercise 45.1: Verification of the ftok() Algorithm

- **Objective:** Verify that `ftok()` uses the file's i-node number, minor device number, and project identifier when generating a System V IPC key.
- **Requirements:**
  1. Accept the path to an existing file and a single-character project identifier as command-line arguments.
  2. Use `stat()` to retrieve the file metadata, including the i-node number (`st_ino`) and device number (`st_dev`).
  3. Extract the minor device number from `st_dev` using the `minor()` macro.
  4. Call `ftok()` with the supplied path and project identifier, handling invalid arguments and system-call errors.
  5. Print the project identifier, minor device number, i-node number, and value returned by `ftok()` in hexadecimal.
- **Verification:** Run the program with several existing files and project identifiers, then inspect the printed values to verify the relationship between the inputs and the key returned by `ftok()`.
- **Usage:** `./ftok_verify <pathname> <single-character-proj_id>`
- **Source File:** [`45.1_ftok_verify.c`](45.1_ftok_verify.c)
