#include <iostream>
#include <fstream>
#include <random>
#include <unordered_set>
#include <chrono>
using namespace std;

void generateTicketsNormal(int n) {
    const int MIN_TICKET = 100;
    const int MAX_TICKET = 9999;

    random_device rd;
    mt19937 gen(rd());
    normal_distribution<> dist((MIN_TICKET + MAX_TICKET) / 2.0, (MAX_TICKET - MIN_TICKET) / 6.0);
    unordered_set<int> tickets;

    auto start = chrono::high_resolution_clock::now();
    while (tickets.size() < n) {
        int ticket = round(dist(gen));
        if (ticket >= MIN_TICKET && ticket <= MAX_TICKET) {
            tickets.insert(ticket);
        }
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    // Write to file
    ofstream outFile("tickets_normal.txt");
    if (outFile.is_open()) {
        for (int ticket : tickets) {
            outFile << ticket << endl;
        }
        outFile.close();
    } else {
        cout << "Error opening file!" << endl;
    }

    cout << "Time taken using std::normal_distribution: " << duration.count() << " seconds." << endl;
}
int main() {
    int n;
    cout << "Enter the number of ticket numbers to generate: ";
    cin >> n;

    
    generateTicketsNormal(n);
    

    return 0;
}
