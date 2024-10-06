// ChatGPT-4o generated the following code on 05_OCTOBER_2024.

#include <iostream>
#include <cmath>
#include <cstdlib>

// Function to calculate GCD (Greatest Common Divisor)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to calculate (base^exp) % mod using modular exponentiation
long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) // If exp is odd, multiply base with result
            result = (result * base) % mod;
        exp = exp >> 1;   // Divide exp by 2
        base = (base * base) % mod;  // Square the base
    }
    return result;
}

// Function to calculate modular multiplicative inverse using the extended Euclidean algorithm
long long mod_inverse(long long e, long long phi) {
    long long t = 0, new_t = 1;
    long long r = phi, new_r = e;
    while (new_r != 0) {
        long long quotient = r / new_r;
        t = t - quotient * new_t;
        std::swap(t, new_t);
        r = r - quotient * new_r;
        std::swap(r, new_r);
    }
    if (r > 1) return -1;  // e is not invertible
    if (t < 0) t += phi;
    return t;
}

int main() {
    // Step 1: Key generation (Using small primes for simplicity)
    int p = 61; // First prime number
    int q = 53; // Second prime number
    long long n = p * q; // n = p * q
    long long phi = (p - 1) * (q - 1); // Euler's Totient function

    // Step 2: Choose e such that 1 < e < phi and gcd(e, phi) = 1
    long long e = 17; // Commonly used public exponent
    if (gcd(e, phi) != 1) {
        std::cout << "e and phi(n) are not coprime. Choose a different e." << std::endl;
        return -1;
    }

    // Step 3: Compute the private key (d)
    long long d = mod_inverse(e, phi);
    if (d == -1) {
        std::cout << "Modular inverse of e does not exist." << std::endl;
        return -1;
    }

    // Step 4: Display the public and private keys
    std::cout << "Public Key: (" << e << ", " << n << ")" << std::endl;
    std::cout << "Private Key: (" << d << ", " << n << ")" << std::endl;

    // Step 5: Encrypt a message (m must be less than n)
    long long m; // Plaintext message
    std::cout << "Enter a message to encrypt (as an integer less than " << n << "): ";
    std::cin >> m;
    if (m >= n) {
        std::cout << "Message is too large. It must be less than " << n << "." << std::endl;
        return -1;
    }

    // Encryption: c = m^e % n
    long long c = mod_exp(m, e, n);
    std::cout << "Encrypted message: " << c << std::endl;

    // Step 6: Decrypt the message
    // Decryption: m = c^d % n
    long long decrypted_message = mod_exp(c, d, n);
    std::cout << "Decrypted message: " << decrypted_message << std::endl;

    return 0;
}
