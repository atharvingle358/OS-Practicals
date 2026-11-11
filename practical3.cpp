
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

void displayResult(vector<int> bt,
                   vector<int> wt,
                   vector<int> tat,
                   int n) {
    double totalWT = 0, totalTAT = 0;

    cout << "\nProcess\tBT\tWT\tTAT\n";

    for (int i = 0; i < n; i++) {
        cout << "P" << i + 1 << "\t"
             << bt[i] << "\t"
             << wt[i] << "\t"
             << tat[i] << "\n";

        totalWT += wt[i];
        totalTAT += tat[i];
    }

    cout << fixed << setprecision(2);

    cout << "\nAverage Waiting Time = "
         << totalWT / n;

    cout << "\nAverage Turnaround Time = "
         << totalTAT / n << "\n";
}

// FCFS Scheduling
void FCFS(vector<int> bt, int n) {
    vector<int> wt(n), tat(n);
    int time = 0;

    cout << "\n--- FCFS Scheduling ---\n";
    cout << "\nGantt Chart:\n0";

    for (int i = 0; i < n; i++) {
        wt[i] = time;
        time += bt[i];
        tat[i] = time;

        cout << " | P" << i + 1
             << " | " << time;
    }

    cout << "\n";

    displayResult(bt, wt, tat, n);
}

// SJF Scheduling (Non-preemptive)
void SJF(vector<int> bt, int n) {
    vector<int> order(n), wt(n), tat(n);

    for (int i = 0; i < n; i++)
        order[i] = i;

    sort(order.begin(), order.end(),
         [&](int a, int b) {
             return bt[a] < bt[b];
         });

    int time = 0;

    cout << "\n--- SJF Scheduling ---\n";
    cout << "\nGantt Chart:\n0";

    for (int p : order) {
        wt[p] = time;
        time += bt[p];
        tat[p] = time;

        cout << " | P" << p + 1
             << " | " << time;
    }

    cout << "\n";

    displayResult(bt, wt, tat, n);
}

// Priority Scheduling (Non-preemptive)
void PriorityScheduling(vector<int> bt,
                        vector<int> priority,
                        int n) {
    vector<int> order(n), wt(n), tat(n);

    for (int i = 0; i < n; i++)
        order[i] = i;

    sort(order.begin(), order.end(),
         [&](int a, int b) {
             return priority[a] < priority[b];
         });

    int time = 0;

    cout << "\n--- Priority Scheduling ---\n";
    cout << "(Smaller number = Higher priority)\n";
    cout << "\nGantt Chart:\n0";

    for (int p : order) {
        wt[p] = time;
        time += bt[p];
        tat[p] = time;

        cout << " | P" << p + 1
             << " | " << time;
    }

    cout << "\n";

    displayResult(bt, wt, tat, n);
}

// Round Robin Scheduling
void RoundRobin(vector<int> bt, int n, int quantum) {
    vector<int> rem = bt;
    vector<int> wt(n, 0), tat(n, 0);
    vector<int> completion(n, 0);

    int time = 0;
    bool done;

    cout << "\n--- Round Robin Scheduling ---\n";
    cout << "\nGantt Chart:\n";

    do {
        done = true;

        for (int i = 0; i < n; i++) {
            if (rem[i] > 0) {
                done = false;

                cout << time << " | P" << i + 1 << " | ";

                if (rem[i] > quantum) {
                    time += quantum;
                    rem[i] -= quantum;
                } else {
                    time += rem[i];
                    rem[i] = 0;
                    completion[i] = time;
                }

                cout << time << " ";
            }
        }
    } while (!done);

    cout << "\n";

    for (int i = 0; i < n; i++) {
        tat[i] = completion[i];
        wt[i] = tat[i] - bt[i];
    }

    displayResult(bt, wt, tat, n);
}

int main() {
    int n, choice, quantum;

    cout << "Enter number of processes: ";
    cin >> n;

    if (n <= 0 || n > 100) {
        cout << "Invalid number of processes.\n";
        return 1;
    }

    vector<int> bt(n), priority(n);

    for (int i = 0; i < n; i++) {
        cout << "Enter burst time of P"
             << i + 1 << ": ";
        cin >> bt[i];

        if (bt[i] <= 0) {
            cout << "Burst time must be positive.\n";
            return 1;
        }
    }

    cout << "\n1. FCFS";
    cout << "\n2. SJF";
    cout << "\n3. Priority Scheduling";
    cout << "\n4. Round Robin";

    cout << "\nEnter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            FCFS(bt, n);
            break;

        case 2:
            SJF(bt, n);
            break;

        case 3:
            for (int i = 0; i < n; i++) {
                cout << "Enter priority of P"
                     << i + 1 << ": ";
                cin >> priority[i];
            }
            PriorityScheduling(bt, priority, n);
            break;

        case 4:
            cout << "Enter time quantum: ";
            cin >> quantum;

            if (quantum <= 0) {
                cout << "Invalid time quantum.\n";
                return 1;
            }

            RoundRobin(bt, n, quantum);
            break;

        default:
            cout << "Invalid choice.\n";
    }

    return 0;
}
