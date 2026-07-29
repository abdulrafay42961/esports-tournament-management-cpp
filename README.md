# 🏆 E-Sports Tournament Management System

A secure, module-driven C++ application designed to automate e-sports tournament operations, manage team rosters, enforce anti-cheat rules, and run multi-tiered match fixtures. Built with core Object-Oriented Programming (OOP) principles and low-level memory safety.

---

## 📌 Project Overview
Managing e-sports tournaments manually leads to administrative errors, incorrect point allocation, and data tampering. This system provides a consolidated platform with separated Admin and Player/Team privileges, automated tie-breaker logic, dynamic point distribution, and persistent file storage.

* **Dual Operational Workflows:** Dedicated interfaces for Admin control and credentialed Player dashboards.
* **Automated Tournament Lifecycle:** Interactive match execution, 3-tiered tie-breaker logic, and automated standings.
* **Anti-Cheat Penalization Subsystem:** Dynamic point deduction or opponent compensation based on infraction severity levels.
* **Data Persistence & Memory Safety:** Automated load/save routines via file streams (`ifstream`/`ofstream`) and custom destructors to prevent heap memory leaks.

---

## 🛠️ Tech Stack & Tools

| Category | Technology / Specification |
| :--- | :--- |
| **Language** | C++ |
| **Paradigm** | Object-Oriented Programming (OOP) |
| **Persistence** | File Streams (`fstream`) |
| **Data Structures** | Arrays, Dynamic Pointers, Abstract Classes |
| **Coursework** | Department of Cyber Security, Air University Multan |

---

## 🧱 Architecture & OOP Concepts Implemented

```text
                  +-------------------+
                  |    Participant    | (Abstract Base)
                  +-------------------+
                    ^               ^
                    |               |
         +----------+               +----------+
         |                                     |
+-----------------+                   +-----------------+
|   PlayerClass   |                   |      Coach      |
+-----------------+                   +-----------------+
         ^ 1:5                                 ^ 1:1
         | (Composition)                       | (Aggregation)
         +-----------------+-------------------+
                           |
                   +---------------+
                   |     Team      |
                   +---------------+
