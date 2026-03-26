# TPC-H Query 5 Implementation

## 📌 Problem
Implementation of TPC-H Query 5 to calculate nation-wise revenue for a given region and time period.

## 💻 Language
C++

## ⚙️ Approach
- Used hash-based joins with `unordered_map` for efficient lookup.
- Simulated relational joins across multiple tables.

## 🔄 Execution Flow
1. Filter Region → ASIA  
2. Join Nation with Region  
3. Join Supplier with Nation  
4. Join Customer with Nation  
5. Filter Orders by date (1994)  
6. Join LineItem with Orders  
7. Compute revenue = extendedprice × (1 - discount)  
8. Aggregate revenue nation-wise  
9. Sort results in descending order  

## 📊 Output
- Displays nation-wise revenue sorted in descending order.

## ▶️ How to Run
```bash
g++ query5.cpp -O2
./a.out
