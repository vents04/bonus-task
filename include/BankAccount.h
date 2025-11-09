#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <iostream>
#include <cstring>

class BankAccount {
private:
    char* uniqueCode;        // Letter + 5 digits (e.g., "A12345")
    char* ownerName;         // Pointer to character string
    double* depositedAmounts; // Dynamic array of deposited amounts
    double* withdrawnAmounts; // Dynamic array of withdrawn amounts
    int depositedCount;      // Number of deposited amounts
    int withdrawnCount;      // Number of withdrawn amounts
    int depositedCapacity;   // Capacity of deposited array
    int withdrawnCapacity;   // Capacity of withdrawn array

    void validateUniqueCode(const char* code) const;
    void validateOwnerName(const char* name) const;
    void resizeDepositedArray();
    void resizeWithdrawnArray();

public:
    BankAccount();
    
    BankAccount(const char* uniqueCode, const char* ownerName);
    
    BankAccount(const BankAccount& other);
    
    ~BankAccount();

    const char* getUniqueCode() const;
    const char* getOwnerName() const;
    int getDepositedCount() const;
    int getWithdrawnCount() const;
    double getTotalDeposited() const;
    double getTotalWithdrawn() const;
    double getBalance() const; // Difference between deposited and withdrawn

    void setUniqueCode(const char* code);
    void setOwnerName(const char* name);
    
    void addDeposit(double amount);
    void addWithdrawal(double amount);
    
    bool hasEqualDepositsAndWithdrawals() const; // Check if totals are equal

    BankAccount& operator=(const BankAccount& other);
    
    friend std::ostream& operator<<(std::ostream& os, const BankAccount& account);
    friend std::istream& operator>>(std::istream& is, BankAccount& account);
    
    void saveToFile(std::ostream& os) const;
    void loadFromFile(std::istream& is);
};

#endif

