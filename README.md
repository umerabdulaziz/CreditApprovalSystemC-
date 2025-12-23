# Credit Approval System (C++ & Qt)

A rule-based Credit Approval System developed using **C++** for backend logic and **Qt (C++)** for the graphical user interface.

This project evaluates loan applications based on financial, personal, and risk-related factors and produces a loan decision:
- APPROVED
- REVIEW
- REJECTED

---

## 🧠 Project Overview

- **Frontend:** Qt GUI (C++)
- **Backend:** Rule-based C++ program
- **Storage:** CSV file (`applicants.csv`)
- **Decision Method:** Weighted scoring system

The GUI collects applicant data and stores it in a CSV file.  
The backend program reads this CSV file, calculates a credit score, and outputs a loan decision.

---

## 📁 Project Structure

CreditApproval/
│
├── backend/
│ ├── backend.cpp
│ ├── applicants_sample.csv
│
├── Headers/
│ └── mainwindow.h
│
├── Sources/
│ ├── main.cpp
│ └── mainwindow.cpp
│
├── CreditApproval.pro
├── README.md
└── .gitignore

yaml
Copy code

---

## 🖥️ GUI (Qt)

The Qt interface allows users to enter:
- Personal details (age, marital status)
- Financial information (salary, savings, spending)
- Assets (houses, cars)
- Risk indicators (credit score, criminal record, late payments)

The GUI:
- Saves data to `backend/applicants.csv`
- Displays entries in a table
- Runs the backend program to get loan decisions

---

## ⚙️ Backend Logic

The backend uses a **rule-based scoring system**.

Each factor adds or subtracts points:

| Factor | Max Score |
|------|----------|
| Credit Score | +25 |
| Salary vs Loan | +20 |
| Age | +10 |
| Employment | +15 |
| Assets | +10 |
| Savings | +10 |
| Spending Ratio | +10 |
| Criminal Record | -30 |

### Final Decision Rules:
- **Score ≥ 70** → APPROVED
- **Score 50–69** → REVIEW
- **Score < 50** → REJECTED

---

## 🧪 Sample Test Case

**Approved Example**
Age: 30
Salary: 150000
Loan: 500000
Credit Score: 750
Savings: 300000
Spending: 40000
Criminal Record: No

markdown
Copy code
➡️ Result: **APPROVED**

**Rejected Example**
Age: 22
Salary: 30000
Loan: 1000000
Credit Score: 550
Savings: 5000
Spending: 25000
Criminal Record: Yes

yaml
Copy code
➡️ Result: **REJECTED**

---

## 🛠️ How to Compile Backend

Using Dev-C++ or MinGW:

```bash
g++ backend.cpp -o backend.exe
Place backend.exe inside the backend/ folder.
