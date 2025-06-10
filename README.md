# SplitwiseCashflow
# 💰 Splitwise Cash Flow Optimizer in C++

This project implements an efficient algorithm to minimize the number of transactions required to settle debts among a group of people, similar to how the Splitwise app works.

It uses **priority queues (heaps)** to optimize settlement between creditors and debtors.

---

## 🚀 Features

- Computes net balances from multiple transactions.
- Uses **max-heap** for creditors and **min-heap** for debtors.
- Minimizes the total number of transactions.
- Supports dynamic number of people and transactions.
- Compatible with **older C++ compilers (C++98)**.

---

## 🧠 Problem Statement

Given a list of transactions, such as:

