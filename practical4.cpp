#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter number of resources: ";
    cin >> m;

    if (n <= 0 || m <= 0) {
        cout << "Invalid input.\n";
        return 1;
    }

    vector<vector<int>> allocation(n, vector<int>(m));
    vector<vector<int>> maximum(n, vector<int>(m));
    vector<vector<int>> need(n, vector<int>(m));

    vector<int> available(m);
    vector<int> work(m);
    vector<bool> finish(n, false);
    vector<int> safeSequence;

    // Input Allocation Matrix
    cout << "\nEnter Allocation Matrix:\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> allocation[i][j];
        }
    }

    // Input Maximum Matrix
    cout << "\nEnter Maximum Matrix:\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> maximum[i][j];
        }
    }

    // Input Available Resources
    cout << "\nEnter Available Resources:\n";

    for (int j = 0; j < m; j++) {
        cin >> available[j];
    }

    // Calculate Need Matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (maximum[i][j] < allocation[i][j]) {
                cout << "Invalid resource allocation.\n";
                return 1;
            }

            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    work = available;

    // Banker's Safety Algorithm
    while (true) {
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canExecute = true;

                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canExecute = false;
                        break;
                    }
                }

                if (canExecute) {
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }

                    safeSequence.push_back(i);
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            break;
        }
    }

    // Display Need Matrix
    cout << "\nNeed Matrix:\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << need[i][j] << " ";
        }
        cout << endl;
    }

    // Check Safe State
    if (safeSequence.size() == n) {
        cout << "\nSystem is in SAFE state.\n";

        cout << "Safe Sequence: ";

        for (int i = 0; i < n; i++) {
            cout << "P" << safeSequence[i];

            if (i != n - 1) {
                cout << " -> ";
            }
        }

        cout << endl;
    } else {
        cout << "\nSystem is in UNSAFE state.\n";
        cout << "No safe sequence exists.\n";
    }

    return 0;
}

