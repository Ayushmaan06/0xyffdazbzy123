#include <iostream>
#include <fstream>
#include <random>
#include <unordered_set>
#include <chrono>
using namespace std;

void generateTicketsUniformInt(int n) {
    const int MIN_TICKET = 100;
    const int MAX_TICKET = 9999;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(MIN_TICKET, MAX_TICKET);
    unordered_set<int> tickets;

    auto start = chrono::high_resolution_clock::now();
    while (tickets.size() < n) {
        tickets.insert(dist(gen));
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    // Write to file
    ofstream outFile("tickets_uniform_int.txt");
    if (outFile.is_open()) {
        for (int ticket : tickets) {
            outFile << ticket << endl;
        }
        outFile.close();
    } else {
        cout << "Error opening file!" << endl;
    }

    cout << "Time taken using std::uniform_int_distribution: " << duration.count() << " seconds." << endl;
}
int main() {
    int n;
    cout << "Enter the number of ticket numbers to generate: ";
    cin >> n;

    
    generateTicketsUniformInt(n);
    

    return 0;
}
