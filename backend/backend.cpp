#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

/* ---------- CSV SPLIT FUNCTION ---------- */
vector<string> splitCSV(const string &line)
{
    vector<string> result;
    string token;
    bool inQuotes = false;

    for (size_t i = 0; i < line.length(); i++)
    {
        char ch = line[i];

        if (ch == '"')
        {
            inQuotes = !inQuotes;
        }
        else if (ch == ',' && !inQuotes)
        {
            result.push_back(token);
            token.clear();
        }
        else
        {
            token += ch;
        }
    }
    result.push_back(token);
    return result;
}

/* ---------- SAFE CONVERSIONS ---------- */
int safeInt(const string &s)
{
    stringstream ss(s);
    int x = 0;
    ss >> x;
    return x;
}

double safeDouble(const string &s)
{
    stringstream ss(s);
    double x = 0.0;
    ss >> x;
    return x;
}

/* ---------- SCORING FUNCTIONS ---------- */

int scoreAge(int age)
{
    if (age >= 25 && age <= 55) return 10;
    if (age >= 18 && age < 25) return 5;
    if (age > 55 && age <= 65) return 5;
    return -10;
}

int scoreCredit(int credit)
{
    if (credit >= 750) return 25;
    if (credit >= 700) return 20;
    if (credit >= 650) return 10;
    if (credit >= 600) return 5;
    return -20;
}

int scoreSalaryLoan(double salary, double loan)
{
    if (loan <= 0) return 0;

    double ratio = (salary * 12) / loan;

    if (ratio >= 5) return 20;
    if (ratio >= 3) return 15;
    if (ratio >= 2) return 5;
    return -15;
}

int scoreEmployment(const string &type)
{
    if (type == "Permanent") return 15;
    if (type == "Contract") return 8;
    if (type == "Self") return 5;
    return -10;
}

int scoreDependents(int d)
{
    if (d <= 1) return 5;
    if (d <= 3) return 2;
    return -5;
}

int scoreEducation(const string &e)
{
    if (e == "Masters") return 8;
    if (e == "Bachelors") return 6;
    if (e == "Intermediate") return 3;
    return 0;
}

int scoreAssets(int houses, double avgSize)
{
    if (houses <= 0) return 0;

    double totalSize = houses * avgSize;

    if (totalSize >= 3000) return 10;
    if (totalSize >= 1500) return 5;
    return 2;
}

int scoreCars(int cars, double worth)
{
    if (cars == 0) return 0;
    if (worth >= 5000000) return 8;
    if (worth >= 2000000) return 5;
    return 2;
}

int scoreMarital(const string &m)
{
    if (m == "Married") return 5;
    if (m == "Single") return 7;
    return 0;
}

int scoreActiveLoans(int loans)
{
    if (loans == 0) return 10;
    if (loans <= 2) return 3;
    return -10;
}

int scoreLatePayments(int late)
{
    if (late == 0) return 10;
    if (late <= 2) return 5;
    if (late <= 5) return -5;
    return -15;
}

int scoreCriminal(const string &c)
{
    if (c == "Yes") return -30;
    return 10;
}

int scoreSavings(double savings, double loan)
{
    if (loan <= 0) return 0;

    double ratio = savings / loan;

    if (ratio >= 0.5) return 10;
    if (ratio >= 0.25) return 5;
    return 0;
}

int scoreSpending(double salary, double spending)
{
    if (salary <= 0) return 0;

    double ratio = spending / salary;

    if (ratio <= 0.4) return 10;
    if (ratio <= 0.6) return 5;
    return -10;
}

string finalDecision(int score)
{
    if (score >= 70) return "APPROVED";
    if (score >= 50) return "REVIEW";
    return "REJECTED";
}

/* ---------- MAIN PROGRAM ---------- */

int main()
{
    ifstream file("applicants.csv");

    if (!file.is_open())
    {
        cout << "Error: applicants.csv not found." << endl;
        return 1;
    }

    string line;
    getline(file, line); // Skip header

    while (getline(file, line))
    {
        vector<string> c = splitCSV(line);
        if (c.size() < 18) continue;

        string name = c[0];
        int age = safeInt(c[1]);
        double salary = safeDouble(c[2]);
        int credit = safeInt(c[3]);
        double loan = safeDouble(c[4]);
        string employment = c[5];
        int dependents = safeInt(c[6]);
        string education = c[7];
        int houses = safeInt(c[8]);
        double houseSize = safeDouble(c[9]);
        int cars = safeInt(c[10]);
        double carWorth = safeDouble(c[11]);
        string marital = c[12];
        int activeLoans = safeInt(c[13]);
        int latePayments = safeInt(c[14]);
        string criminal = c[15];
        double savings = safeDouble(c[16]);
        double spending = safeDouble(c[17]);

        int score = 0;

        score += scoreAge(age);
        score += scoreCredit(credit);
        score += scoreSalaryLoan(salary, loan);
        score += scoreEmployment(employment);
        score += scoreDependents(dependents);
        score += scoreEducation(education);
        score += scoreAssets(houses, houseSize);
        score += scoreCars(cars, carWorth);
        score += scoreMarital(marital);
        score += scoreActiveLoans(activeLoans);
        score += scoreLatePayments(latePayments);
        score += scoreCriminal(criminal);
        score += scoreSavings(savings, loan);
        score += scoreSpending(salary, spending);

        cout << name << " -> " << finalDecision(score) << endl;
    }

    file.close();
    return 0;
}
