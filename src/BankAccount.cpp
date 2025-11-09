#include "BankAccount.h"
#include <stdexcept>
#include <iomanip>
#include <cctype>

void BankAccount::validateUniqueCode(const char* code) const {
    if (!code || strlen(code) != 6) {
        throw std::invalid_argument("Unique code must be exactly 6 characters (letter + 5 digits)");
    }
    
    if (!std::isalpha(code[0])) {
        throw std::invalid_argument("First character must be a letter");
    }
    
    for (int i = 1; i < 6; ++i) {
        if (!std::isdigit(code[i])) {
            throw std::invalid_argument("Last 5 characters must be digits");
        }
    }
}

void BankAccount::validateOwnerName(const char* name) const {
    if (!name || strlen(name) == 0) {
        throw std::invalid_argument("Owner name cannot be empty");
    }
}

void BankAccount::resizeDepositedArray() {
    if (depositedCount >= depositedCapacity) {
        int newCapacity = depositedCapacity == 0 ? 2 : depositedCapacity * 2;
        double* newArray = new double[newCapacity];
        
        for (int i = 0; i < depositedCount; ++i) {
            newArray[i] = depositedAmounts[i];
        }
        
        delete[] depositedAmounts;
        depositedAmounts = newArray;
        depositedCapacity = newCapacity;
    }
}

void BankAccount::resizeWithdrawnArray() {
    if (withdrawnCount >= withdrawnCapacity) {
        int newCapacity = withdrawnCapacity == 0 ? 2 : withdrawnCapacity * 2;
        double* newArray = new double[newCapacity];
        
        for (int i = 0; i < withdrawnCount; ++i) {
            newArray[i] = withdrawnAmounts[i];
        }
        
        delete[] withdrawnAmounts;
        withdrawnAmounts = newArray;
        withdrawnCapacity = newCapacity;
    }
}

BankAccount::BankAccount() 
    : uniqueCode(nullptr), ownerName(nullptr),
      depositedAmounts(nullptr), withdrawnAmounts(nullptr),
      depositedCount(0), withdrawnCount(0),
      depositedCapacity(0), withdrawnCapacity(0) {
    uniqueCode = new char[7];
    strcpy(uniqueCode, "A00000");
    ownerName = new char[1];
    ownerName[0] = '\0';
}

BankAccount::BankAccount(const char* uniqueCode, const char* ownerName)
    : depositedAmounts(nullptr), withdrawnAmounts(nullptr),
      depositedCount(0), withdrawnCount(0),
      depositedCapacity(0), withdrawnCapacity(0) {
    validateUniqueCode(uniqueCode);
    validateOwnerName(ownerName);
    
    this->uniqueCode = new char[strlen(uniqueCode) + 1];
    strcpy(this->uniqueCode, uniqueCode);
    
    this->ownerName = new char[strlen(ownerName) + 1];
    strcpy(this->ownerName, ownerName);
}

BankAccount::BankAccount(const BankAccount& other)
    : depositedCount(other.depositedCount), withdrawnCount(other.withdrawnCount),
      depositedCapacity(other.depositedCapacity), withdrawnCapacity(other.withdrawnCapacity) {
    
    uniqueCode = new char[strlen(other.uniqueCode) + 1];
    strcpy(uniqueCode, other.uniqueCode);
    
    ownerName = new char[strlen(other.ownerName) + 1];
    strcpy(ownerName, other.ownerName);
    
    depositedAmounts = new double[depositedCapacity];
    for (int i = 0; i < depositedCount; ++i) {
        depositedAmounts[i] = other.depositedAmounts[i];
    }
    
    withdrawnAmounts = new double[withdrawnCapacity];
    for (int i = 0; i < withdrawnCount; ++i) {
        withdrawnAmounts[i] = other.withdrawnAmounts[i];
    }
}

BankAccount::~BankAccount() {
    delete[] uniqueCode;
    delete[] ownerName;
    delete[] depositedAmounts;
    delete[] withdrawnAmounts;
}

const char* BankAccount::getUniqueCode() const {
    return uniqueCode;
}

const char* BankAccount::getOwnerName() const {
    return ownerName;
}

int BankAccount::getDepositedCount() const {
    return depositedCount;
}

int BankAccount::getWithdrawnCount() const {
    return withdrawnCount;
}

double BankAccount::getTotalDeposited() const {
    double total = 0.0;
    for (int i = 0; i < depositedCount; ++i) {
        total += depositedAmounts[i];
    }
    return total;
}

double BankAccount::getTotalWithdrawn() const {
    double total = 0.0;
    for (int i = 0; i < withdrawnCount; ++i) {
        total += withdrawnAmounts[i];
    }
    return total;
}

double BankAccount::getBalance() const {
    return getTotalDeposited() - getTotalWithdrawn();
}

void BankAccount::setUniqueCode(const char* code) {
    validateUniqueCode(code);
    delete[] uniqueCode;
    uniqueCode = new char[strlen(code) + 1];
    strcpy(uniqueCode, code);
}

void BankAccount::setOwnerName(const char* name) {
    validateOwnerName(name);
    delete[] ownerName;
    ownerName = new char[strlen(name) + 1];
    strcpy(ownerName, name);
}

void BankAccount::addDeposit(double amount) {
    if (amount < 0) {
        throw std::invalid_argument("Deposit amount cannot be negative");
    }
    resizeDepositedArray();
    depositedAmounts[depositedCount++] = amount;
}

void BankAccount::addWithdrawal(double amount) {
    if (amount < 0) {
        throw std::invalid_argument("Withdrawal amount cannot be negative");
    }
    resizeWithdrawnArray();
    withdrawnAmounts[withdrawnCount++] = amount;
}

bool BankAccount::hasEqualDepositsAndWithdrawals() const {
    return getTotalDeposited() == getTotalWithdrawn();
}

BankAccount& BankAccount::operator=(const BankAccount& other) {
    if (this != &other) {
        delete[] uniqueCode;
        delete[] ownerName;
        delete[] depositedAmounts;
        delete[] withdrawnAmounts;
        
        uniqueCode = new char[strlen(other.uniqueCode) + 1];
        strcpy(uniqueCode, other.uniqueCode);
        
        ownerName = new char[strlen(other.ownerName) + 1];
        strcpy(ownerName, other.ownerName);
        
        depositedCount = other.depositedCount;
        withdrawnCount = other.withdrawnCount;
        depositedCapacity = other.depositedCapacity;
        withdrawnCapacity = other.withdrawnCapacity;
        
        depositedAmounts = new double[depositedCapacity];
        for (int i = 0; i < depositedCount; ++i) {
            depositedAmounts[i] = other.depositedAmounts[i];
        }
        
        withdrawnAmounts = new double[withdrawnCapacity];
        for (int i = 0; i < withdrawnCount; ++i) {
            withdrawnAmounts[i] = other.withdrawnAmounts[i];
        }
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const BankAccount& account) {
    os << "Account Code: " << account.uniqueCode << "\n";
    os << "Owner: " << account.ownerName << "\n";
    os << "Deposits Count: " << account.depositedCount << "\n";
    os << "Withdrawals Count: " << account.withdrawnCount << "\n";
    
    os << "Deposits: ";
    if (account.depositedCount == 0) {
        os << "none";
    } else {
        for (int i = 0; i < account.depositedCount; ++i) {
            os << std::fixed << std::setprecision(2) << account.depositedAmounts[i];
            if (i < account.depositedCount - 1) os << ", ";
        }
    }
    os << "\n";
    
    os << "Withdrawals: ";
    if (account.withdrawnCount == 0) {
        os << "none";
    } else {
        for (int i = 0; i < account.withdrawnCount; ++i) {
            os << std::fixed << std::setprecision(2) << account.withdrawnAmounts[i];
            if (i < account.withdrawnCount - 1) os << ", ";
        }
    }
    os << "\n";
    
    os << "Total Deposited: " << std::fixed << std::setprecision(2) 
       << account.getTotalDeposited() << " BGN\n";
    os << "Total Withdrawn: " << std::fixed << std::setprecision(2) 
       << account.getTotalWithdrawn() << " BGN\n";
    os << "Balance: " << std::fixed << std::setprecision(2) 
       << account.getBalance() << " BGN\n";
    
    return os;
}

std::istream& operator>>(std::istream& is, BankAccount& account) {
    char code[10];
    char name[256];
    
    std::cout << "Enter account code (letter + 5 digits, e.g. A12345): ";
    is >> code;
    
    std::cout << "Enter owner name: ";
    is.ignore();
    is.getline(name, 256);
    
    account.setUniqueCode(code);
    account.setOwnerName(name);
    
    return is;
}

void BankAccount::saveToFile(std::ostream& os) const {
    os << uniqueCode << "\n";
    os << ownerName << "\n";
    os << depositedCount << "\n";
    for (int i = 0; i < depositedCount; ++i) {
        os << depositedAmounts[i] << "\n";
    }
    os << withdrawnCount << "\n";
    for (int i = 0; i < withdrawnCount; ++i) {
        os << withdrawnAmounts[i] << "\n";
    }
}

void BankAccount::loadFromFile(std::istream& is) {
    char code[10];
    char name[256];
    
    is >> code;
    is.ignore();
    is.getline(name, 256);
    
    delete[] uniqueCode;
    delete[] ownerName;
    uniqueCode = new char[strlen(code) + 1];
    strcpy(uniqueCode, code);
    ownerName = new char[strlen(name) + 1];
    strcpy(ownerName, name);
    
    is >> depositedCount;
    delete[] depositedAmounts;
    depositedAmounts = new double[depositedCount];
    depositedCapacity = depositedCount;
    for (int i = 0; i < depositedCount; ++i) {
        is >> depositedAmounts[i];
    }
    
    is >> withdrawnCount;
    delete[] withdrawnAmounts;
    withdrawnAmounts = new double[withdrawnCount];
    withdrawnCapacity = withdrawnCount;
    for (int i = 0; i < withdrawnCount; ++i) {
        is >> withdrawnAmounts[i];
    }
    is.ignore();
}

