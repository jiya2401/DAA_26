//  TIME & SPACE COMPLEXITY SUMMARY
//  Method               Time        Space       Notes
//  Iterative Factorial  O(n)        O(1)        Uses a simple loop
//  Recursive Factorial  O(n)        O(n)        Extra space due to call stack

#include <iostream>
#include <chrono> 

unsigned long long factorialIterative(int n) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

unsigned long long factorialRecursive(int n) {
    if (n <= 1) return 1;
    return n * factorialRecursive(n - 1);
}

int main() {
    int n;
    std::cout << "Enter a non-negative integer (e.g., 20): ";

    if (!(std::cin >> n) || n < 0) {
        std::cerr << "Invalid input! Please enter a non-negative integer." << std::endl;
        return 1;
    }

     if (n > 20) {
        std::cout << "Warning: Result may overflow (exceeds 64-bit range).\n";
    } 

    // Measure Iterative Implementation
    auto startIter = std::chrono::high_resolution_clock::now();
    unsigned long long resIter = factorialIterative(n);
    auto endIter = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> durationIter = endIter - startIter;

    // Measure Recursive Implementation
    auto startRec = std::chrono::high_resolution_clock::now();
    unsigned long long resRec = factorialRecursive(n);
    auto endRec = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> durationRec = endRec - startRec;

    // Output Results
    std::cout << "\n--- Results for " << n << "! ---" << std::endl;
    std::cout << "Iterative Result : " << resIter << std::endl;
    std::cout << "Iterative Time   : " << durationIter.count() << " ns" << std::endl;
    std::cout << "-------------------------------" << std::endl;
    std::cout << "Recursive Result : " << resRec << std::endl;
    std::cout << "Recursive Time   : " << durationRec.count() << " ns" << std::endl;

    return 0;
}