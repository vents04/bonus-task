#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <set>
#include <map>
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif
#include "BankAccount.h"

// Function prototypes
void displayMainMenu();
void addBankAccount(std::vector<BankAccount>& accounts);
void addDepositToAccount(std::vector<BankAccount>& accounts);
void addWithdrawalToAccount(std::vector<BankAccount>& accounts);
void displayAllAccounts(const std::vector<BankAccount>& accounts);
void displayAccountDetails(const std::vector<BankAccount>& accounts);
void createAccountsFile(const std::vector<BankAccount>& accounts);
void displayOwnersWithMultipleAccounts(const std::vector<BankAccount>& accounts);
void displayDepositWithdrawalDifferences(const std::vector<BankAccount>& accounts);
void saveEqualAccountsToFile(const std::vector<BankAccount>& accounts);
void saveDataToFile(const std::vector<BankAccount>& accounts);
void loadDataFromFile(std::vector<BankAccount>& accounts);
int selectAccount(const std::vector<BankAccount>& accounts);
void clearScreen();
void pauseScreen();
int getValidatedInt(const std::string& prompt, int min = INT_MIN, int max = INT_MAX);
double getValidatedDouble(const std::string& prompt, double min = 0.0);

int main() {
    std::vector<BankAccount> accounts;
    
    loadDataFromFile(accounts);
    
    int choice;
    bool running = true;
    
    std::cout << "\n";
    std::cout << std::string(65, '=') << std::endl;
    std::cout << "          Bank Accounts Management System        " << std::endl;
    std::cout << std::string(65, '=') << std::endl;
    
    while (running) {
        displayMainMenu();
        choice = getValidatedInt("Enter choice: ", 0, 9);
        
        try {
            switch (choice) {
                case 1:
                    addBankAccount(accounts);
                    break;
                case 2:
                    addDepositToAccount(accounts);
                    break;
                case 3:
                    addWithdrawalToAccount(accounts);
                    break;
                case 4:
                    displayAllAccounts(accounts);
                    break;
                case 5:
                    displayAccountDetails(accounts);
                    break;
                case 6:
                    createAccountsFile(accounts);
                    break;
                case 7:
                    displayOwnersWithMultipleAccounts(accounts);
                    break;
                case 8:
                    displayDepositWithdrawalDifferences(accounts);
                    break;
                case 9:
                    saveEqualAccountsToFile(accounts);
                    break;
                case 0:
                    std::cout << "\nSaving data...\n";
                    saveDataToFile(accounts);
                    std::cout << "Thank you for using the system!\n";
                    running = false;
                    break;
                default:
                    std::cout << "Invalid option!\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "[ERROR] Error: " << e.what() << std::endl;
            pauseScreen();
        }
    }
    
    return 0;
}

void displayMainMenu() {
    std::cout << "\n" << std::string(65, '=') << std::endl;
    std::cout << "                        MAIN MENU                 " << std::endl;
    std::cout << std::string(65, '=') << std::endl;
    std::cout << "1. Add Bank Account" << std::endl;
    std::cout << "2. Add Deposit to Account" << std::endl;
    std::cout << "3. Add Withdrawal from Account" << std::endl;
    std::cout << "4. Display All Accounts" << std::endl;
    std::cout << "5. Display Account Details" << std::endl;
    std::cout << "6. Create Accounts File" << std::endl;
    std::cout << "7. Display Owners with Multiple Accounts" << std::endl;
    std::cout << "8. Display Deposit-Withdrawal Differences" << std::endl;
    std::cout << "9. Save Accounts with Equal Deposits and Withdrawals" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << std::string(65, '=') << std::endl;
}

void addBankAccount(std::vector<BankAccount>& accounts) {
    clearScreen();
    std::cout << "\n=== ADD BANK ACCOUNT ===\n\n";
    
    try {
        BankAccount account;
        std::cin >> account;
        accounts.push_back(account);
        std::cout << "\n[OK] Account added successfully!\n";
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Error adding account: " 
                  << e.what() << std::endl;
    }
    
    pauseScreen();
}

void addDepositToAccount(std::vector<BankAccount>& accounts) {
    clearScreen();
    
    if (accounts.empty()) {
        std::cout << "\n[ERROR] No accounts available! Add an account first.\n";
        pauseScreen();
        return;
    }
    
    std::cout << "\n=== ADD DEPOSIT ===\n\n";
    
    int accountIndex = selectAccount(accounts);
    if (accountIndex == -1) {
        return;
    }
    
    try {
        double amount = getValidatedDouble("Enter deposit amount: ");
        accounts[accountIndex].addDeposit(amount);
        std::cout << "\n[OK] Deposit added successfully!\n";
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Error adding deposit: " 
                  << e.what() << std::endl;
    }
    
    pauseScreen();
}

void addWithdrawalToAccount(std::vector<BankAccount>& accounts) {
    clearScreen();
    
    if (accounts.empty()) {
        std::cout << "\n[ERROR] No accounts available! Add an account first.\n";
        pauseScreen();
        return;
    }
    
    std::cout << "\n=== ADD WITHDRAWAL ===\n\n";
    
    int accountIndex = selectAccount(accounts);
    if (accountIndex == -1) {
        return;
    }
    
    try {
        double amount = getValidatedDouble("Enter withdrawal amount: ");
        accounts[accountIndex].addWithdrawal(amount);
        std::cout << "\n[OK] Withdrawal added successfully!\n";
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Error adding withdrawal: " 
                  << e.what() << std::endl;
    }
    
    pauseScreen();
}

void displayAllAccounts(const std::vector<BankAccount>& accounts) {
    clearScreen();
    
    if (accounts.empty()) {
        std::cout << "\n[ERROR] No accounts available!\n";
        pauseScreen();
        return;
    }
    
    std::cout << "\n=== ALL ACCOUNTS ===\n";
    for (size_t i = 0; i < accounts.size(); ++i) {
        std::cout << "\n[" << (i + 1) << "] ";
        std::cout << accounts[i];
        std::cout << std::string(65, '-') << std::endl;
    }
    
    pauseScreen();
}

void displayAccountDetails(const std::vector<BankAccount>& accounts) {
    clearScreen();
    
    if (accounts.empty()) {
        std::cout << "\n[ERROR] No accounts available!\n";
        pauseScreen();
        return;
    }
    
    int accountIndex = selectAccount(accounts);
    if (accountIndex == -1) {
        return;
    }
    
    std::cout << "\n=== ACCOUNT DETAILS ===\n\n";
    std::cout << accounts[accountIndex];
    
    pauseScreen();
}

void createAccountsFile(const std::vector<BankAccount>& accounts) {
    clearScreen();
    
    if (accounts.empty()) {
        std::cout << "\n[ERROR] No accounts available!\n";
        pauseScreen();
        return;
    }
    
    std::cout << "\n=== CREATE ACCOUNTS FILE ===\n\n";
    
    std::string filename;
    std::cout << "Enter filename: ";
    std::cin.ignore();
    std::getline(std::cin, filename);
    
    if (filename.empty()) {
        filename = "accounts.dat";
    }
    
    try {
        std::ofstream file(filename);
        if (!file) {
            throw std::runtime_error("Cannot create file");
        }
        
        file << accounts.size() << "\n";
        for (const auto& account : accounts) {
            account.saveToFile(file);
        }
        file.close();
        
        std::cout << "\n[OK] File \"" << filename << "\" created successfully!\n";
        std::cout << "  Accounts count: " << accounts.size() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Error creating file: " 
                  << e.what() << std::endl;
    }
    
    pauseScreen();
}

void displayOwnersWithMultipleAccounts(const std::vector<BankAccount>& accounts) {
    clearScreen();
    
    if (accounts.empty()) {
        std::cout << "\n[ERROR] No accounts available!\n";
        pauseScreen();
        return;
    }
    
    std::cout << "\n=== OWNERS WITH MULTIPLE ACCOUNTS ===\n\n";
    
    // Count accounts per owner
    std::map<std::string, int> ownerCount;
    for (const auto& account : accounts) {
        std::string ownerName = account.getOwnerName();
        ownerCount[ownerName]++;
    }
    
    // Collect owners with more than one account
    std::vector<std::string> multipleOwners;
    for (const auto& pair : ownerCount) {
        if (pair.second > 1) {
            multipleOwners.push_back(pair.first);
        }
    }
    
    if (multipleOwners.empty()) {
        std::cout << "No owners with more than one account.\n";
    } else {
        // Sort alphabetically
        std::sort(multipleOwners.begin(), multipleOwners.end());
        
        std::cout << "Owners with more than one account (sorted alphabetically):\n\n";
        
        for (const auto& owner : multipleOwners) {
            std::cout << "  * " << owner << " - " << ownerCount[owner] << " accounts\n";
        }
    }
    
    pauseScreen();
}

void displayDepositWithdrawalDifferences(const std::vector<BankAccount>& accounts) {
    clearScreen();
    
    if (accounts.empty()) {
        std::cout << "\n[ERROR] No accounts available!\n";
        pauseScreen();
        return;
    }
    
    std::cout << "\n=== DEPOSIT-WITHDRAWAL DIFFERENCES ===\n\n";
    
    std::cout << std::left << std::setw(15) << "Code" 
              << std::setw(25) << "Owner"
              << std::setw(20) << "Total Deposited"
              << std::setw(20) << "Total Withdrawn"
              << std::setw(15) << "Difference" << std::endl;
    std::cout << std::string(95, '-') << std::endl;
    
    for (const auto& account : accounts) {
        double totalDeposited = account.getTotalDeposited();
        double totalWithdrawn = account.getTotalWithdrawn();
        double difference = account.getBalance();
        
        std::cout << std::left << std::setw(15) << account.getUniqueCode()
                  << std::setw(25) << account.getOwnerName()
                  << std::fixed << std::setprecision(2)
                  << std::setw(20) << totalDeposited
                  << std::setw(20) << totalWithdrawn
                  << std::setw(15) << difference << std::endl;
    }
    
    pauseScreen();
}

void saveEqualAccountsToFile(const std::vector<BankAccount>& accounts) {
    clearScreen();
    
    if (accounts.empty()) {
        std::cout << "\n[ERROR] No accounts available!\n";
        pauseScreen();
        return;
    }
    
    std::cout << "\n=== SAVE ACCOUNTS WITH EQUAL DEPOSITS AND WITHDRAWALS ===\n\n";
    
    // Find accounts with equal deposits and withdrawals
    std::vector<BankAccount> equalAccounts;
    for (const auto& account : accounts) {
        if (account.hasEqualDepositsAndWithdrawals()) {
            equalAccounts.push_back(account);
        }
    }
    
    if (equalAccounts.empty()) {
        std::cout << "No accounts with equal deposits and withdrawals.\n";
        pauseScreen();
        return;
    }
    
    std::string filename = "equal_accounts.dat";
    
    try {
        std::ofstream file(filename);
        if (!file) {
            throw std::runtime_error("Cannot create file");
        }
        
        file << equalAccounts.size() << "\n";
        for (const auto& account : equalAccounts) {
            account.saveToFile(file);
        }
        file.close();
        
        std::cout << "[OK] File \"" << filename << "\" created successfully!\n";
        std::cout << "  Accounts count: " << equalAccounts.size() << "\n\n";
        
        std::cout << "Accounts with equal deposits and withdrawals:\n\n";
        for (const auto& account : equalAccounts) {
            std::cout << account;
            std::cout << std::string(65, '-') << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Error creating file: " 
                  << e.what() << std::endl;
    }
    
    pauseScreen();
}

void saveDataToFile(const std::vector<BankAccount>& accounts) {
    try {
        std::ofstream file("bank_accounts.dat");
        if (!file) {
            throw std::runtime_error("Cannot open file");
        }
        
        file << accounts.size() << "\n";
        for (const auto& account : accounts) {
            account.saveToFile(file);
        }
        file.close();
        
        std::cout << "\n[OK] Data saved successfully!\n";
        std::cout << "  Accounts count: " << accounts.size() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Error saving: " << e.what() << std::endl;
    }
}

void loadDataFromFile(std::vector<BankAccount>& accounts) {
    try {
        std::ifstream file("bank_accounts.dat");
        if (file) {
            size_t accountCount;
            file >> accountCount;
            file.ignore();
            
            accounts.clear();
            for (size_t i = 0; i < accountCount; ++i) {
                BankAccount account;
                account.loadFromFile(file);
                accounts.push_back(account);
            }
            file.close();
            
            std::cout << "\n[OK] Data loaded successfully!\n";
            std::cout << "  Accounts count: " << accounts.size() << "\n";
            pauseScreen();
        }
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Error loading: " << e.what() << std::endl;
    }
}

int selectAccount(const std::vector<BankAccount>& accounts) {
    std::cout << "\nAvailable accounts:\n";
    std::cout << std::string(65, '-') << std::endl;
    
    for (size_t i = 0; i < accounts.size(); ++i) {
        std::cout << "[" << (i + 1) << "] " << accounts[i].getUniqueCode() 
                  << " - " << accounts[i].getOwnerName() << std::endl;
    }
    
    std::cout << std::string(65, '-') << std::endl;
    int choice = getValidatedInt("Select account: ", 1, 
                                  static_cast<int>(accounts.size()));
    
    return choice - 1;
}

void clearScreen() {
#ifdef _WIN32
    // Windows-specific screen clear
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole != INVALID_HANDLE_VALUE) {
        COORD coordScreen = {0, 0};
        DWORD cCharsWritten;
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        
        if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
            DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
            FillConsoleOutputCharacter(hConsole, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten);
            FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
            SetConsoleCursorPosition(hConsole, coordScreen);
        }
    }
#else
    // Unix/Linux/Mac: Use ANSI escape codes
    std::cout << "\033[2J\033[1;1H";
#endif
}

void pauseScreen() {
    std::cout << "\nPress Enter to continue...";
    // Wait for Enter press (getline handles any existing newline or waits for input)
    std::string dummy;
    std::getline(std::cin, dummy);
}

int getValidatedInt(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "[ERROR] Invalid input! Please enter a number.\n";
        } else if (value < min || value > max) {
            std::cout << "[ERROR] Number must be between " << min << " and " << max << ".\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

double getValidatedDouble(const std::string& prompt, double min) {
    double value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "[ERROR] Invalid input! Please enter a number.\n";
        } else if (value < min) {
            std::cout << "[ERROR] Number must be at least " << min << ".\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

