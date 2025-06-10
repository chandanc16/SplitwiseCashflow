#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Structure to hold a person and their net balance
struct Person {
    int id;
    int amount;

    // For max-heap (creditors): max by amount
    bool operator<(const Person& other) const {
        return amount < other.amount;
    }
};

// Custom comparator for min-heap (debtors)
struct Compare {
    bool operator()(const Person& a, const Person& b) {
        return a.amount > b.amount; // min-heap
    }
};

int minCashFlow(const vector< vector<int> >& transactions, int numPeople) {
    vector<int> netAmount(numPeople, 0);

    // Step 1: Compute net amount for each person
    for (size_t i = 0; i < transactions.size(); ++i) {
        int payer = transactions[i][0];
        int payee = transactions[i][1];
        int amount = transactions[i][2];
        netAmount[payer] -= amount;
        netAmount[payee] += amount;
    }

    // Step 2: Create two heaps
    priority_queue<Person> creditors; // max-heap
    priority_queue<Person, vector<Person>, Compare> debtors; // min-heap

    for (int i = 0; i < numPeople; ++i) {
        if (netAmount[i] > 0) {
            Person p; p.id = i; p.amount = netAmount[i];
            creditors.push(p);
        }
        else if (netAmount[i] < 0) {
            Person p; p.id = i; p.amount = netAmount[i];
            debtors.push(p);
        }
    }

    int transactionCount = 0;

    // Step 3: Settle transactions using greedy heap method
    while (!creditors.empty() && !debtors.empty()) {
        Person creditor = creditors.top(); creditors.pop();
        Person debtor = debtors.top(); debtors.pop();

        int settledAmount = min(creditor.amount, -debtor.amount);

        // Output transaction
        cout << "Person " << debtor.id << " pays " << settledAmount
             << " to Person " << creditor.id << endl;

        transactionCount++;

        int remainingCred = creditor.amount - settledAmount;
        int remainingDebt = debtor.amount + settledAmount;

        if (remainingCred > 0) {
            Person p; p.id = creditor.id; p.amount = remainingCred;
            creditors.push(p);
        }
        if (remainingDebt < 0) {
            Person p; p.id = debtor.id; p.amount = remainingDebt;
            debtors.push(p);
        }
    }

    return transactionCount;
}

int main() {
    vector< vector<int> > transactions;
    vector<int> t1; t1.push_back(0); t1.push_back(1); t1.push_back(100);
    vector<int> t2; t2.push_back(1); t2.push_back(2); t2.push_back(50);
    vector<int> t3; t3.push_back(2); t3.push_back(0); t3.push_back(30);
    transactions.push_back(t1);
    transactions.push_back(t2);
    transactions.push_back(t3);

    int numPeople = 3;

    int minTransactions = minCashFlow(transactions, numPeople);

    cout << "Minimum transactions required: " << minTransactions << endl;

    return 0;
}
