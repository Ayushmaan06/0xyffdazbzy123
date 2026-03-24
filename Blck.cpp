#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

const int BLOCK_SIZE = 16; 

// --- PUT YOUR ENCRYPTION ALGO HERE ---
void encryptBlock(const uint8_t* in, uint8_t* out) {
    for (int i = 0; i < BLOCK_SIZE; i++) out[i] = in[i] ^ 0x42; 
}

// --- PUT YOUR DECRYPTION ALGO HERE ---
void decryptBlock(const uint8_t* in, uint8_t* out) {
    for (int i = 0; i < BLOCK_SIZE; i++) out[i] = in[i] ^ 0x42; 
}

// --- CBC MODE ---
vector<uint8_t> encryptCBC(vector<uint8_t> plaintext, vector<uint8_t> iv) {
    vector<uint8_t> ciphertext(plaintext.size());
    vector<uint8_t> prev_block = iv;
    uint8_t temp[BLOCK_SIZE];

    for (size_t i = 0; i < plaintext.size(); i += BLOCK_SIZE) {
        // 1. XOR plaintext with previous ciphertext (or IV)
        for(int j=0; j<BLOCK_SIZE; j++) temp[j] = plaintext[i+j] ^ prev_block[j];
        
        // 2. Encrypt the result
        encryptBlock(temp, &ciphertext[i]);
        
        // 3. Update previous block for next round
        for(int j=0; j<BLOCK_SIZE; j++) prev_block[j] = ciphertext[i+j];
    }
    return ciphertext;
}

vector<uint8_t> decryptCBC(vector<uint8_t> ciphertext, vector<uint8_t> iv) {
    vector<uint8_t> plaintext(ciphertext.size());
    vector<uint8_t> prev_block = iv;
    uint8_t temp[BLOCK_SIZE];

    for (size_t i = 0; i < ciphertext.size(); i += BLOCK_SIZE) {
        // 1. Decrypt ciphertext
        decryptBlock(&ciphertext[i], temp);
        
        // 2. XOR with previous ciphertext to get actual plaintext
        for(int j=0; j<BLOCK_SIZE; j++) plaintext[i+j] = temp[j] ^ prev_block[j];
        
        // 3. Update previous block
        for(int j=0; j<BLOCK_SIZE; j++) prev_block[j] = ciphertext[i+j];
    }
    return plaintext;
}

int main() {
    vector<uint8_t> plaintext(32, 0x07); 
    vector<uint8_t> iv(BLOCK_SIZE, 0x99); // Initial Vector

    vector<uint8_t> ct = encryptCBC(plaintext, iv);
    vector<uint8_t> pt = decryptCBC(ct, iv);

    cout << "CBC Encrypted First Byte: " << hex << (int)ct[0] << endl;
    cout << "CBC Decrypted First Byte: " << hex << (int)pt[0] << endl;
    return 0;
}

----------------------------------------------------------------
  #include <iostream>
#include <vector>

using namespace std;

const int BLOCK_SIZE = 16; 

// --- PUT YOUR ENCRYPTION ALGO HERE ---
void encryptBlock(const uint8_t* in, uint8_t* out) {
    for (int i = 0; i < BLOCK_SIZE; i++) out[i] = in[i] ^ 0x42; 
}

// NOTE: CFB doesn't use block decryption! It only uses block encryption.

// --- CFB MODE ---
vector<uint8_t> encryptCFB(vector<uint8_t> plaintext, vector<uint8_t> iv) {
    vector<uint8_t> ciphertext(plaintext.size());
    vector<uint8_t> feedback = iv;
    uint8_t temp[BLOCK_SIZE];

    for (size_t i = 0; i < plaintext.size(); i += BLOCK_SIZE) {
        // 1. Encrypt the feedback (IV or previous ciphertext)
        encryptBlock(feedback.data(), temp);
        
        // 2. XOR with plaintext to get ciphertext
        for(int j = 0; j < BLOCK_SIZE; j++) {
            ciphertext[i+j] = plaintext[i+j] ^ temp[j];
            feedback[j] = ciphertext[i+j]; // Update feedback
        }
    }
    return ciphertext;
}

vector<uint8_t> decryptCFB(vector<uint8_t> ciphertext, vector<uint8_t> iv) {
    vector<uint8_t> plaintext(ciphertext.size());
    vector<uint8_t> feedback = iv;
    uint8_t temp[BLOCK_SIZE];

    for (size_t i = 0; i < ciphertext.size(); i += BLOCK_SIZE) {
        // 1. Encrypt the feedback (same as encryption process)
        encryptBlock(feedback.data(), temp);
        
        // 2. XOR with ciphertext to get back the plaintext
        for(int j = 0; j < BLOCK_SIZE; j++) {
            plaintext[i+j] = ciphertext[i+j] ^ temp[j];
            feedback[j] = ciphertext[i+j]; // Update feedback
        }
    }
    return plaintext;
}

int main() {
    vector<uint8_t> plaintext(32, 0x0A); 
    vector<uint8_t> iv(BLOCK_SIZE, 0x99); 

    vector<uint8_t> ct = encryptCFB(plaintext, iv);
    vector<uint8_t> pt = decryptCFB(ct, iv);

    cout << "CFB Encrypted First Byte: " << hex << (int)ct[0] << endl;
    cout << "CFB Decrypted First Byte: " << hex << (int)pt[0] << endl;
    return 0;
}
---------------------------------------------------------------------------------
  #include <iostream>
#include <vector>

using namespace std;

const int BLOCK_SIZE = 16; 

// --- PUT YOUR ENCRYPTION ALGO HERE ---
void encryptBlock(const uint8_t* in, uint8_t* out) {
    for (int i = 0; i < BLOCK_SIZE; i++) out[i] = in[i] ^ 0x42; 
}

// Simple function to increment the counter
void incrementCounter(vector<uint8_t>& counter) {
    for (int i = BLOCK_SIZE - 1; i >= 0; --i) {
        counter[i]++;
        if (counter[i] != 0) break; // If no overflow, stop carrying
    }
}

// --- CTR MODE ---
vector<uint8_t> encryptCTR(vector<uint8_t> plaintext, vector<uint8_t> nonce) {
    vector<uint8_t> ciphertext(plaintext.size());
    vector<uint8_t> counter = nonce;
    uint8_t temp[BLOCK_SIZE];

    for (size_t i = 0; i < plaintext.size(); i += BLOCK_SIZE) {
        // 1. Encrypt the counter
        encryptBlock(counter.data(), temp);
        
        // 2. XOR with plaintext
        for(int j = 0; j < BLOCK_SIZE; j++) {
            ciphertext[i+j] = plaintext[i+j] ^ temp[j];
        }
        
        // 3. Increment counter for next block
        incrementCounter(counter);
    }
    return ciphertext;
}

// Decryption in CTR is EXACTLY the same as encryption!
vector<uint8_t> decryptCTR(vector<uint8_t> ciphertext, vector<uint8_t> nonce) {
    return encryptCTR(ciphertext, nonce);
}

int main() {
    vector<uint8_t> plaintext(32, 0x0C); 
    vector<uint8_t> nonce(BLOCK_SIZE, 0x00); // Usually Nounce + Counter split

    vector<uint8_t> ct = encryptCTR(plaintext, nonce);
    vector<uint8_t> pt = decryptCTR(ct, nonce);

    cout << "CTR Encrypted First Byte: " << hex << (int)ct[0] << endl;
    cout << "CTR Decrypted First Byte: " << hex << (int)pt[0] << endl;
    return 0;
}
---------------------------------------------------------
  #include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

const int BLOCK_SIZE = 16; // 16 bytes for AES

// --- PUT YOUR ENCRYPTION ALGO HERE ---
void encryptBlock(const uint8_t* in, uint8_t* out) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        out[i] = in[i] ^ 0x42; // Dummy encryption (XOR)
    }
}

// --- PUT YOUR DECRYPTION ALGO HERE ---
void decryptBlock(const uint8_t* in, uint8_t* out) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        out[i] = in[i] ^ 0x42; // Dummy decryption (XOR)
    }
}

// --- ECB MODE ---
vector<uint8_t> encryptECB(vector<uint8_t> plaintext) {
    vector<uint8_t> ciphertext(plaintext.size());
    for (size_t i = 0; i < plaintext.size(); i += BLOCK_SIZE) {
        encryptBlock(&plaintext[i], &ciphertext[i]);
    }
    return ciphertext;
}

vector<uint8_t> decryptECB(vector<uint8_t> ciphertext) {
    vector<uint8_t> plaintext(ciphertext.size());
    for (size_t i = 0; i < ciphertext.size(); i += BLOCK_SIZE) {
        decryptBlock(&ciphertext[i], &plaintext[i]);
    }
    return plaintext;
}

int main() {
    // 32 bytes of dummy data (2 exact blocks)
    vector<uint8_t> plaintext(32, 0x05); 

    vector<uint8_t> ct = encryptECB(plaintext);
    vector<uint8_t> pt = decryptECB(ct);

    cout << "ECB Encrypted First Byte: " << hex << (int)ct[0] << endl;
    cout << "ECB Decrypted First Byte: " << hex << (int)pt[0] << endl;
    return 0;
}
----------------------------------------------------------
  #include <iostream>
#include <vector>

using namespace std;

const int BLOCK_SIZE = 16; 

// --- PUT YOUR ENCRYPTION ALGO HERE ---
void encryptBlock(const uint8_t* in, uint8_t* out) {
    for (int i = 0; i < BLOCK_SIZE; i++) out[i] = in[i] ^ 0x42; 
}

// --- OFB MODE ---
vector<uint8_t> encryptOFB(vector<uint8_t> plaintext, vector<uint8_t> iv) {
    vector<uint8_t> ciphertext(plaintext.size());
    vector<uint8_t> feedback = iv;
    uint8_t temp[BLOCK_SIZE];

    for (size_t i = 0; i < plaintext.size(); i += BLOCK_SIZE) {
        // 1. Encrypt the feedback 
        encryptBlock(feedback.data(), temp);
        
        // 2. Update feedback for the NEXT round *before* XORing
        for(int j = 0; j < BLOCK_SIZE; j++) feedback[j] = temp[j];
        
        // 3. XOR with plaintext
        for(int j = 0; j < BLOCK_SIZE; j++) {
            ciphertext[i+j] = plaintext[i+j] ^ temp[j];
        }
    }
    return ciphertext;
}

// Decryption in OFB is EXACTLY the same as encryption!
vector<uint8_t> decryptOFB(vector<uint8_t> ciphertext, vector<uint8_t> iv) {
    return encryptOFB(ciphertext, iv); // Re-run the same logic
}

int main() {
    vector<uint8_t> plaintext(32, 0x0B); 
    vector<uint8_t> iv(BLOCK_SIZE, 0x99); 

    vector<uint8_t> ct = encryptOFB(plaintext, iv);
    vector<uint8_t> pt = decryptOFB(ct, iv);

    cout << "OFB Encrypted First Byte: " << hex << (int)ct[0] << endl;
    cout << "OFB Decrypted First Byte: " << hex << (int)pt[0] << endl;
    return 0;
}
