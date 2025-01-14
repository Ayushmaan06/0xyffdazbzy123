#include <iostream>
#include <fstream>
#include <unordered_set>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;

void generateTicketsRand(int n) {
    const int MIN_TICKET = 100;
    const int MAX_TICKET = 9999;

    unordered_set<int> tickets;
    srand(time(0)); // Seed the random number generator

    auto start = chrono::high_resolution_clock::now();
    while (tickets.size() < n) {
        tickets.insert(MIN_TICKET + rand() % (MAX_TICKET - MIN_TICKET + 1));
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    // Write to file
    ofstream outFile("tickets_rand.txt");
    if (outFile.is_open()) {
        for (int ticket : tickets) {
            outFile << ticket << endl;
        }
        outFile.close();
    } else {
        cout << "Error opening file!" << endl;
    }

    cout << "Time taken using std::rand(): " << duration.count() << " seconds." << endl;
}
int main() {
    int n;
    cout << "Enter the number of ticket numbers to generate: ";
    cin >> n;

    generateTicketsRand(n);

    return 0;
}
