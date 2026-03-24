cc
#include <iostream>
#include <string>
#include <limits>
#include <cctype>

using namespace std;

int main() {
    while(true){
        int x;
        cout << "\n--------------------------------\n";
        cout << "Enter 0 to exit \n";
        cout << "Enter 1 to Encrypt a message \n";
        cout << "Enter 2 to Decrypt a message \n";
        cout << "Choice: ";
        if (!(cin >> x)) {
            cout << "Invalid input! Please enter a number.\n";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the bad input
            continue; 
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if(x == 0){
            cout << "Exiting program.\n";
            break;
        }
        else if(x == 1){
            string message;
            cout << "Enter the message to encrypt: ";
            getline(cin, message);
            
            int k;
            cout << "Enter shift value (integer): ";
            if(!(cin >> k)){
                 cout << "Invalid shift value! Aborting.\n";
                 cin.clear();
                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
                 continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            string encrypted_message = "";
            int shift = k % 26;
            if(shift < 0) shift += 26;

            for(char c : message){
                unsigned char uc = static_cast<unsigned char>(c);
                if(isalpha(uc)){
                    char base = isupper(uc) ? 'A' : 'a';
                    char e = base + ( (uc - base + shift) % 26 );
                    encrypted_message += e;
                }
                else encrypted_message += c;
            }
            cout << "Encrypted message: " << encrypted_message << "\n";
        }
        else if(x == 2){
            string message;
            cout << "Enter the message to decrypt: ";
            getline(cin, message);

            int k;
            cout << "Enter shift value (integer): ";
             if(!(cin >> k)){
                 cout << "Invalid shift value! Aborting.\n";
                 cin.clear();
                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
                 continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            string decrypted_message = "";
            int shift = k % 26;
            if(shift < 0) shift += 26;

            for(char c : message){
                unsigned char uc = static_cast<unsigned char>(c);
                if(isalpha(uc)){
                    char base = isupper(uc) ? 'A' : 'a';
                    char d = base + ( (uc - base - shift + 26) % 26 );
                    decrypted_message += d;
                }
                else decrypted_message += c;
            }
            cout << "Decrypted message: " << decrypted_message << "\n";
        }
        else{
            cout << "Invalid option (Choose 0, 1, or 2).\n";
        }
    }
    return 0;
}



------------------------------------------------

pf

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <cctype>

using namespace std;

class PlayfairCipher {
    char matrix[5][5];
    map<char, pair<int, int>> pos;

public:
    void generateMatrix(string key) {
        string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; // No J
        string combined = "";
        vector<bool> used(26, false);
        used['J' - 'A'] = true; // Mark J as used (mapped to I)

        for (char c : key) {
            if (!isalpha(c)) continue;
            c = toupper(c);
            if (c == 'J') c = 'I';
            if (!used[c - 'A']) {
                combined += c;
                used[c - 'A'] = true;
            }
        }

        for (char c : alphabet) {
            if (!used[c - 'A']) {
                combined += c;
                used[c - 'A'] = true;
            }
        }

        int k = 0;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                matrix[i][j] = combined[k++];
                pos[matrix[i][j]] = {i, j};
            }
        }
    }

    void displayMatrix() {
        cout << "\n--- 5x5 Key Matrix ---\n";
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << "----------------------\n";
    }

    string formatPlaintext(string text) {
        string filtered = "";
        for (char c : text) {
            if (isalpha(c)) {
                c = toupper(c);
                if (c == 'J') c = 'I';
                filtered += c;
            }
        }

        string formatted = "";
        for (size_t i = 0; i < filtered.length(); i++) {
            formatted += filtered[i];
            if (i + 1 < filtered.length()) {
                if (filtered[i] == filtered[i + 1]) {
                    formatted += 'X'; // Inject filler if letters are same
                } else {
                    formatted += filtered[++i];
                }
            } else {
                formatted += 'X'; // Pad if odd length
            }
        }
        return formatted;
    }

    string process(string text, int dir) {
        string output = "";
        for (size_t i = 0; i < text.length(); i += 2) {
            char a = text[i];
            char b = text[i + 1];
            int r1 = pos[a].first, c1 = pos[a].second;
            int r2 = pos[b].first, c2 = pos[b].second;

            if (r1 == r2) {
                // Same Row
                output += matrix[r1][(c1 + dir + 5) % 5];
                output += matrix[r2][(c2 + dir + 5) % 5];
            } else if (c1 == c2) {
                // Same Column
                output += matrix[(r1 + dir + 5) % 5][c1];
                output += matrix[(r2 + dir + 5) % 5][c2];
            } else {
                // Rectangle
                output += matrix[r1][c2];
                output += matrix[r2][c1];
            }
        }
        return output;
    }

    string encrypt(string text) {
        string formatted = formatPlaintext(text);
        return process(formatted, 1);
    }

    string decrypt(string text) {
        // Ciphertext should already be uppercase and handle I/J
        return process(text, -1);
    }
};

int main() {
    PlayfairCipher pc;
    string key, text;
    int choice;

    cout << "========================================\n";
    cout << "       PLAYFAIR CIPHER SIMULATION       \n";
    cout << "========================================\n";

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Encrypt a message\n";
        cout << "2. Decrypt a message\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (choice == 3) {
            cout << "Exiting simulation...\n";
            break;
        }

        cout << "Enter keyword: ";
        cin >> ws; // clear whitespace
        getline(cin, key);
        pc.generateMatrix(key);
        pc.displayMatrix();

        if (choice == 1) {
            cout << "Enter plaintext: ";
            getline(cin, text);
            string formatted = pc.formatPlaintext(text);
            string encrypted = pc.encrypt(text);
            cout << "\nResults:\n";
            cout << "Original Text:  " << text << endl;
            cout << "Formatted Text: " << formatted << " (Digraphs formed)\n";
            cout << "Encrypted Text: " << encrypted << endl;
        } else if (choice == 2) {
            cout << "Enter ciphertext: ";
            getline(cin, text);
            // Pre-process ciphertext (remove spaces, etc)
            string cleanCipher = "";
            for(char c : text) if(isalpha(c)) cleanCipher += toupper(c == 'J' ? 'I' : c);
            
            if (cleanCipher.length() % 2 != 0) {
                cout << "Error: Ciphertext must have an even length.\n";
            } else {
                string decrypted = pc.decrypt(cleanCipher);
                cout << "\nResults:\n";
                cout << "Encrypted Text: " << cleanCipher << endl;
                cout << "Decrypted Text: " << decrypted << endl;
                cout << "(Note: 'X' may be present as filler or padding)\n";
            }
        } else {
            cout << "Invalid choice! Please select 1, 2, or 3.\n";
        }
    }

    return 0;
}

-----------------------------------------------------------------------
  affine
  #include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
int gcd(int a, int b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}

string encrypt(string text, int a, int b) {
    string res = "";
    for (char &c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            int p = c - base;
            int C = (a * p + b) % 26;
            if (C < 0) C += 26;
            res += (char)(C + base);
        } else {
            res += c;
        }
    }
    return res;
}

string decrypt(string cipher, int a, int b) {
    string res = "";
    int a_inv = modInverse(a, 26);
    if (a_inv == -1) return "Error: 'a' must be coprime to 26.";

    for (char &c : cipher) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            int C = c - base;
            int P = (a_inv * (C - b)) % 26;
            if (P < 0) P += 26;
            res += (char)(P + base);
        } else {
            res += c;
        }
    }
    return res;
}

void bruteForce(string cipher, ofstream &out) {
    out << "--- Brute Force Attack Results ---\n";
    for (int a = 1; a < 26; a++) {
        if (gcd(a, 26) == 1) {
            for (int b = 0; b < 26; b++) {
                out << "a=" << a << ", b=" << b << ": " << decrypt(cipher, a, b) << "\n";
            }
        }
    }
    out << "----------------------------------\n";
}

int main() {
    ifstream in("in.txt");
    ofstream out("out.txt");

    if (!in.is_open()) {
        cerr << "Error: Could not open in.txt" << endl;
        return 1;
    }

    int choice;
    while (true) {
        out << "\nAffine Cipher Simulation\n";
        out << "1. Encrypt\n";
        out << "2. Decrypt\n";
        out << "3. Brute Force Search\n";
        out << "4. Exit\n";
        out << "Choice: ";

        if (!(in >> choice)) break; // Stop when input stream ends
        out << choice << endl;

        if (choice == 4) break;

        string text;
        int a, b;

        if (choice == 1) {
            out << "Enter text to encrypt: ";
            in >> text;
            out << text << endl;
            out << "Enter key a: ";
            in >> a;
            out << a << endl;
            out << "Enter key b: ";
            in >> b;
            out << b << endl;

            if (gcd(a, 26) != 1) {
                out << "Error: 'a' (" << a << ") is not coprime with 26. Choosing a valid key is required.\n";
            } else {
                string encrypted = encrypt(text, a, b);
                out << "Encrypted Text: " << encrypted << endl;
            }
        } else if (choice == 2) {
            out << "Enter text to decrypt: ";
            in >> text;
            out << text << endl;
            out << "Enter key a: ";
            in >> a;
            out << a << endl;
            out << "Enter key b: ";
            in >> b;
            out << b << endl;

            if (gcd(a, 26) != 1) {
                out << "Error: 'a' (" << a << ") is not coprime with 26.\n";
            } else {
                string decrypted = decrypt(text, a, b);
                out << "Decrypted Text: " << decrypted << endl;
            }
        } else if (choice == 3) {
            out << "Enter text to brute force: ";
            in >> text;
            out << text << endl;
            bruteForce(text, out);
        } else {
            out << "Invalid choice.\n";
        }
    }

    in.close();
    out.close();

    cout << "Simulation completed. Check out.txt for results." << endl;
    return 0;
}
----------------------------------------------------------------------------------------
hill

  #include <iostream>
#include <vector>
#include <string>

using namespace std;
int gcd(int a, int b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int modInverse(int n, int m) {
    n = n % m;
    if (n < 0) n += m;
    for (int x = 1; x < m; x++) {
        if ((n * x) % m == 1)
            return x;
    }
    return -1;
}

int determinant2x2(const vector<vector<int>>& mat) {
    return (mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0]) % 26;
}

int determinant3x3(const vector<vector<int>>& mat) {
    int det = mat[0][0] * (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1]) -
              mat[0][1] * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0]) +
              mat[0][2] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]);
    return det % 26;
}

vector<vector<int>> inverse2x2(const vector<vector<int>>& mat) {
    int det = determinant2x2(mat);
    if (det < 0) det += 26;
    int invDet = modInverse(det, 26);
    
    vector<vector<int>> inv(2, vector<int>(2));
    inv[0][0] = (mat[1][1] * invDet) % 26;
    inv[0][1] = (-mat[0][1] * invDet) % 26;
    inv[1][0] = (-mat[1][0] * invDet) % 26;
    inv[1][1] = (mat[0][0] * invDet) % 26;
    
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            if (inv[i][j] < 0) inv[i][j] += 26;
            
    return inv;
}

vector<vector<int>> inverse3x3(const vector<vector<int>>& mat) {
    int det = determinant3x3(mat);
    if (det < 0) det += 26;
    int invDet = modInverse(det, 26);
    
    vector<vector<int>> inv(3, vector<int>(3));
    inv[0][0] = (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1]) * invDet % 26;
    inv[0][1] = -(mat[0][1] * mat[2][2] - mat[0][2] * mat[2][1]) * invDet % 26;
    inv[0][2] = (mat[0][1] * mat[1][2] - mat[0][2] * mat[1][1]) * invDet % 26;
    inv[1][0] = -(mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0]) * invDet % 26;
    inv[1][1] = (mat[0][0] * mat[2][2] - mat[0][2] * mat[2][0]) * invDet % 26;
    inv[1][2] = -(mat[0][0] * mat[1][2] - mat[0][2] * mat[1][0]) * invDet % 26;
    inv[2][0] = (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]) * invDet % 26;
    inv[2][1] = -(mat[0][0] * mat[2][1] - mat[0][1] * mat[2][0]) * invDet % 26;
    inv[2][2] = (mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0]) * invDet % 26;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (inv[i][j] < 0) inv[i][j] += 26;

    return inv;
}

string process(string text, const vector<vector<int>>& key, int n) {
    while (text.length() % n != 0) text += 'X';
    string res = "";
    for (size_t i = 0; i < text.length(); i += n) {
        vector<int> block(n);
        for (int j = 0; j < n; j++) block[j] = toupper(text[i + j]) - 'A';
        
        for (int row = 0; row < n; row++) {
            int sum = 0;
            for (int col = 0; col < n; col++) {
                sum += key[row][col] * block[col];
            }
            res += (char)((sum % 26 + 26) % 26 + 'A');
        }
    }
    return res;
}

int main() {
    int choice, n;
    while (true) {
        cout << "\n--- Hill Cipher Simulation ---\n";
        cout << "1. Encrypt\n";
        cout << "2. Decrypt\n";
        cout << "3. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        if (choice == 3) break;

        cout << "Enter matrix size (2 for 2x2, 3 for 3x3): ";
        cin >> n;
        if (n != 2 && n != 3) {
            cout << "Only 2 or 3 is supported.\n";
            continue;
        }

        vector<vector<int>> key(n, vector<int>(n));
        cout << "Enter key matrix elements (row-wise):\n";
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> key[i][j];

        int det = (n == 2) ? determinant2x2(key) : determinant3x3(key);
        if (det < 0) det += 26;
        if (det == 0 || gcd(det, 26) != 1) {
            cout << "Error: Key matrix is not invertible mod 26 (det=" << det << ").\n";
            continue;
        }

        string text;
        cout << "Enter text: ";
        cin >> text;

        if (choice == 1) {
            cout << "Encrypted Text: " << process(text, key, n) << endl;
        } else {
            vector<vector<int>> invKey = (n == 2) ? inverse2x2(key) : inverse3x3(key);
            cout << "Decrypted Text: " << process(text, invKey, n) << endl;
        }
    }
    return 0;
}


--------------------------------

  #include<bits/stdc++.h>
using namespace std;

// Initial Permutation Table
const int IP[] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

// Final Permutation Table ( IP^-1 )
const int FP[] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};

// Expansion Table ( Expands 32 bits to 48 bits )
const int E[] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
};

// Permutation Function (P) - 32 bits
const int P[] = {
    16, 7, 20, 21,
    29, 12, 28, 17,
    1, 15, 23, 26,
    5, 18, 31, 10,
    2, 8, 24, 14,
    32, 27, 3, 9,
    19, 13, 30, 6,
    22, 11, 4, 25
};

// Permutation Choice 1 ( PC-1 ) - 64 bits to 56 bits (Key Permutation) basically removes every 8th bit (parity bits)
//How it does this? It takes the 64-bit key and permutes it according to the PC-1 table, which selects 56 bits from the original key. The bits are rearranged based on the positions specified in the PC-1 table, effectively discarding the parity bits (every 8th bit) and creating a 56-bit key that will be used for further processing in the DES algorithm.
const int PC1[] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
};

// Permutation Choice 2 ( PC-2 ) - 56 bits to 48 bits (Key Compression) basically selects 48 bits from the 56-bit key generated after PC-1
//How it does this? It takes the 56-bit key generated after the PC-1 permutation and permutes it according to the PC-2 table, which selects 48 bits from the original 56-bit key. The bits are rearranged based on the positions specified in the PC-2 table, effectively compressing the key to 48 bits that will be used in each round of the DES algorithm.
const int PC2[] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

// Number of left shifts for each round
const int SHIFTS[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

// S-Boxes (S1 to S8)
const int S_BOX[8][4][16] = {
    // S1
    { {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
      {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
      {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
      {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13} },
    // S2
    { {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
      {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
      {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
      {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9} },
    // S3
    { {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
      {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
      {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
      {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12} },
    // S4
    { {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
      {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
      {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
      {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14} },
    // S5
    { {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
      {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
      {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
      {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3} },
    // S6
    { {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
      {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
      {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
      {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13} },
    // S7
    { {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
      {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
      {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
      {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12} },
    // S8
    { {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
      {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
      {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
      {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11} }
};

string hexCharToBin(char c) {
    switch(toupper(c)) {
        case '0': return "0000"; case '1': return "0001"; case '2': return "0010"; case '3': return "0011";
        case '4': return "0100"; case '5': return "0101"; case '6': return "0110"; case '7': return "0111";
        case '8': return "1000"; case '9': return "1001"; case 'A': return "1010"; case 'B': return "1011";
        case 'C': return "1100"; case 'D': return "1101"; case 'E': return "1110"; case 'F': return "1111";
        default: return "";
    }
}
string hexToBin(string hex) {
    string bin = "";
    for(char c : hex) bin += hexCharToBin(c);
    return bin;
}

string binToHex(string bin) {
    string hex = "";
    for(int i = 0; i < bin.length(); i += 4) {
        string group = bin.substr(i, 4);
        int val = stoi(group, nullptr, 2);
        if(val < 10) hex += to_string(val);
        else hex += (char)('A' + (val - 10));
    }
    return hex;
}
string decToBin(int dec) {
    string bin = "";
    for(int i = 3; i >= 0; i--) {
        bin += ((dec >> i) & 1) ? "1" : "0";
    }
    return bin;
}

string xorString(string a, string b) {
    string res = "";
    for(int i = 0; i < a.length(); i++) {
        res += (a[i] == b[i]) ? "0" : "1";
    }
    return res;
}

string permute(string input, const int* table, int n) {
    string output = "";
    for(int i = 0; i < n; i++) {
        output += input[table[i] - 1];
    }
    return output;
}

string leftShift(string input, int shifts) {
    return input.substr(shifts) + input.substr(0, shifts);
}

// Key Generation
vector<string> generateKeys(string keyHex) {
    vector<string> subkeys;
    string keyBin = hexToBin(keyHex);
    string k56 = permute(keyBin, PC1, 56);
    string C = k56.substr(0, 28);
    string D = k56.substr(28, 28);
    
    cout << "\n--- Key Generation ---\n";
    for(int i = 0; i < 16; i++) {
        C = leftShift(C, SHIFTS[i]);
        D = leftShift(D, SHIFTS[i]);
        string combined = C + D;
        string subkey = permute(combined, PC2, 48);
        subkeys.push_back(subkey);
        if(i == 0 || i == 15)
            cout << "Round " << (i+1) << " Key: " << binToHex(subkey) << endl;
    }
    return subkeys;
}

//Round Function
string feistelFunction(string R, string K) {
    string expandedR = permute(R, E, 48);
    string xored = xorString(expandedR, K);
    string sBoxOutput = "";
    for(int i = 0; i < 8; i++) {
        string chunk = xored.substr(i * 6, 6);
        int row = (chunk[0] - '0') * 2 + (chunk[5] - '0');
        int col = stoi(chunk.substr(1, 4), nullptr, 2);
        int val = S_BOX[i][row][col];
        sBoxOutput += decToBin(val);
    }
    return permute(sBoxOutput, P, 32);
}

// DES Encryption
string desProcess(string textHex, vector<string> subkeys, bool isEncrypt) {
    string textBin = hexToBin(textHex);
    string ipText = permute(textBin, IP, 64);
    string L = ipText.substr(0, 32);
    string R = ipText.substr(32, 32);
    
    cout << (isEncrypt ? "\n--- Encryption Rounds ---\n" : "\n--- Decryption Rounds ---\n");
    
    // 16 Rounds
    for(int i = 0; i < 16; i++) {
        string prevL = L;
        string tempR = R;
        string key = isEncrypt ? subkeys[i] : subkeys[15 - i];
        L = R;
        string f_result = feistelFunction(tempR, key);
        R = xorString(prevL, f_result);
        if(i == 0 || i == 15) {
             cout << "Round " << (i+1) << " | L: " << binToHex(L) << " | R: " << binToHex(R) << endl;
        }
    }
    string combined = R + L; 
    string cipherBin = permute(combined, FP, 64);
    
    return binToHex(cipherBin);
}

int main() {
    string plaintext = "1234567812345678"; 
    string key = "AABB09182736CCDD";
    
    cout << "========================================" << endl;
    cout << "    DES IMPLEMENTATION (Lab 3)    " << endl;
    cout << "========================================" << endl;
    cout << "Plaintext (Hex): " << plaintext << endl;
    cout << "Key (Hex)      : " << key << endl;
    
    // 1. Generate Keys
    vector<string> keys = generateKeys(key);
    
    // 2. Encrypt
    string ciphertext = desProcess(plaintext, keys, true);
    cout << "\nFinal Ciphertext (Hex): " << ciphertext << endl;
    
    // 3. Decrypt
    string decrypted = desProcess(ciphertext, keys, false);
    cout << "\nDecrypted Text (Hex)  : " << decrypted << endl;
    
    return 0;
}

---------------------------------------------------------------
  aes

  #include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

// --- AES Lookup Tables ---
static const unsigned char sbox[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

static const unsigned char inv_sbox[256] = {
    0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
    0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
    0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
    0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
    0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
    0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
    0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
    0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
    0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
    0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
    0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
    0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
    0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
    0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
    0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};

static const unsigned char Rcon[11] = {
    0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36
};

// --- Helper Functions ---
void printState(unsigned char state[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << hex << setfill('0') << setw(2) << (int)state[j][i] << " ";
        }
    }
    cout << endl;
}

unsigned char gmul(unsigned char a, unsigned char b) {
    unsigned char p = 0;
    for (int counter = 0; counter < 8; counter++) {
        if ((b & 1) != 0) p ^= a;
        bool hi_bit_set = (a & 0x80) != 0;
        a <<= 1;
        if (hi_bit_set) a ^= 0x1B;
        b >>= 1;
    }
    return p;
}

// --- Key Expansion ---
void KeyExpansion(unsigned char key[16], unsigned char roundKeys[176]) {
    for (int i = 0; i < 16; i++) {
        roundKeys[i] = key[i];
    }
    int bytesGenerated = 16;
    int rconIteration = 1;
    unsigned char temp[4];

    while (bytesGenerated < 176) {
        for (int i = 0; i < 4; i++) temp[i] = roundKeys[i + bytesGenerated - 4];

        if (bytesGenerated % 16 == 0) {
            unsigned char t = temp[0];
            temp[0] = temp[1]; temp[1] = temp[2]; temp[2] = temp[3]; temp[3] = t;
            for (int i = 0; i < 4; i++) temp[i] = sbox[temp[i]];
            temp[0] ^= Rcon[rconIteration++];
        }

        for (int i = 0; i < 4; i++) {
            roundKeys[bytesGenerated] = roundKeys[bytesGenerated - 16] ^ temp[i];
            bytesGenerated++;
        }
    }
}

// --- AES Transformations ---
void AddRoundKey(unsigned char state[4][4], unsigned char roundKey[176], int round) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            state[i][j] ^= roundKey[(round * 16) + (i * 4) + j];
        }
    }
}

void SubBytes(unsigned char state[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) state[i][j] = sbox[state[i][j]];
    }
}

void InvSubBytes(unsigned char state[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) state[i][j] = inv_sbox[state[i][j]];
    }
}

void ShiftRows(unsigned char state[4][4]) {
    unsigned char temp;
    // Row 1
    temp = state[1][0];
    state[1][0] = state[1][1]; state[1][1] = state[1][2]; state[1][2] = state[1][3]; state[1][3] = temp;
    // Row 2
    temp = state[2][0]; state[2][0] = state[2][2]; state[2][2] = temp;
    temp = state[2][1]; state[2][1] = state[2][3]; state[2][3] = temp;
    // Row 3
    temp = state[3][3];
    state[3][3] = state[3][2]; state[3][2] = state[3][1]; state[3][1] = state[3][0]; state[3][0] = temp;
}

void InvShiftRows(unsigned char state[4][4]) {
    unsigned char temp;
    // Row 1
    temp = state[1][3];
    state[1][3] = state[1][2]; state[1][2] = state[1][1]; state[1][1] = state[1][0]; state[1][0] = temp;
    // Row 2
    temp = state[2][0]; state[2][0] = state[2][2]; state[2][2] = temp;
    temp = state[2][1]; state[2][1] = state[2][3]; state[2][3] = temp;
    // Row 3
    temp = state[3][0];
    state[3][0] = state[3][1]; state[3][1] = state[3][2]; state[3][2] = state[3][3]; state[3][3] = temp;
}

void MixColumns(unsigned char state[4][4]) {
    unsigned char temp[4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) temp[j] = state[j][i];
        state[0][i] = gmul(temp[0], 2) ^ gmul(temp[1], 3) ^ temp[2] ^ temp[3];
        state[1][i] = temp[0] ^ gmul(temp[1], 2) ^ gmul(temp[2], 3) ^ temp[3];
        state[2][i] = temp[0] ^ temp[1] ^ gmul(temp[2], 2) ^ gmul(temp[3], 3);
        state[3][i] = gmul(temp[0], 3) ^ temp[1] ^ temp[2] ^ gmul(temp[3], 2);
    }
}

void InvMixColumns(unsigned char state[4][4]) {
    unsigned char temp[4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) temp[j] = state[j][i];
        state[0][i] = gmul(temp[0], 14) ^ gmul(temp[1], 11) ^ gmul(temp[2], 13) ^ gmul(temp[3], 9);
        state[1][i] = gmul(temp[0], 9) ^ gmul(temp[1], 14) ^ gmul(temp[2], 11) ^ gmul(temp[3], 13);
        state[2][i] = gmul(temp[0], 13) ^ gmul(temp[1], 9) ^ gmul(temp[2], 14) ^ gmul(temp[3], 11);
        state[3][i] = gmul(temp[0], 11) ^ gmul(temp[1], 13) ^ gmul(temp[2], 9) ^ gmul(temp[3], 14);
    }
}

// --- Main Encryption & Decryption Functions ---
void Encrypt(unsigned char plaintext[16], unsigned char roundKeys[176]) {
    unsigned char state[4][4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) state[j][i] = plaintext[(i * 4) + j];

    cout << "\n--- Encryption Process ---" << endl;
    AddRoundKey(state, roundKeys, 0);
    cout << "State after Initial AddRoundKey (Round 0): "; printState(state);

    for (int round = 1; round <= 9; round++) {
        SubBytes(state);
        ShiftRows(state);
        MixColumns(state);
        AddRoundKey(state, roundKeys, round);
        cout << "State after Round " << round << ": "; printState(state);
    }

    SubBytes(state);
    ShiftRows(state);
    AddRoundKey(state, roundKeys, 10);
    cout << "State after Round 10 (Ciphertext): "; printState(state);

    // Write back to plaintext array (now holds ciphertext)
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) plaintext[(i * 4) + j] = state[j][i];
}

void Decrypt(unsigned char ciphertext[16], unsigned char roundKeys[176]) {
    unsigned char state[4][4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) state[j][i] = ciphertext[(i * 4) + j];

    cout << "\n--- Decryption Process ---" << endl;
    AddRoundKey(state, roundKeys, 10);

    for (int round = 9; round >= 1; round--) {
        InvShiftRows(state);
        InvSubBytes(state);
        AddRoundKey(state, roundKeys, round);
        InvMixColumns(state);
    }

    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(state, roundKeys, 0);
    
    // Write back to ciphertext array (now holds decrypted plaintext)
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) ciphertext[(i * 4) + j] = state[j][i];
}

int main() {
    // Input vectors provided in the problem statement
    unsigned char plaintext[16] = {
        0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 
        0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff
    };
    unsigned char key[16] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };
    unsigned char roundKeys[176];

    cout << "Initial Plaintext:  ";
    for(int i=0; i<16; i++) cout << hex << setfill('0') << setw(2) << (int)plaintext[i];
    cout << "\nInitial Key:        ";
    for(int i=0; i<16; i++) cout << hex << setfill('0') << setw(2) << (int)key[i];
    cout << endl;

    KeyExpansion(key, roundKeys);
    
    // Encrypt
    Encrypt(plaintext, roundKeys);
    
    cout << "\nFinal Ciphertext:   ";
    for(int i=0; i<16; i++) cout << hex << setfill('0') << setw(2) << (int)plaintext[i];
    cout << endl;

    // Decrypt to Verify
    Decrypt(plaintext, roundKeys);

    cout << "\nDecrypted Plaintext:";
    for(int i=0; i<16; i++) cout << hex << setfill('0') << setw(2) << (int)plaintext[i];
    cout << endl;

    return 0;
}
