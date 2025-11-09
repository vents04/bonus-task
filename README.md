# Система за Управление на Банкови Сметки
## Bank Accounts Management System

### 📋 Описание / Description

Бонус задача за дисциплината "Езици за Програмиране" - приложение за управление на банкови сметки.

Bonus task for "Programming Languages" - application for managing bank accounts.

---

## 📁 Структура на Проекта / Project Structure

```
.
├── src/                    # Source files
│   ├── main.cpp
│   └── BankAccount.cpp
├── include/                # Header files
│   └── BankAccount.h
├── build/                  # Compiled object files (native, generated)
├── build_win/              # Compiled object files (Windows, generated)
├── docs/                   # Documentation
├── Makefile               # Build configuration
├── README.md              # This file
├── .gitignore             # Git ignore rules
└── bank_system           # Executable (generated)
```

---

## 🛠️ Технически Изисквания / Technical Requirements

**Prerequisites:**
To run the project, you'll need a C++ compiler with C++11 support (g++ or clang++) and Make for compilation. The Makefile is written to work on Windows, macOS, and Linux without additional modifications.

On Windows, you'll need MinGW/MSYS2, Git Bash, or WSL to access Make commands. On macOS, you can install Xcode Command Line Tools, while on Linux, build tools are usually already installed or can be installed through the package manager.

You can verify your setup by checking if `make` and `g++` (or `clang++`) are available in your terminal.

✓ Клас BankAccount с пълна капсулация  
✓ Private инстанционни променливи  
✓ Уникален код (буква + 5 цифри)  
✓ Име на притежателя (указател към символен низ)  
✓ Динамични масиви за вноски и тегления  
✓ Конструктор, деструктор, копиращ конструктор  
✓ Предефиниран << оператор  
✓ Четене и записване във файл  
✓ Динамично въвеждане на данни чрез конзолно меню  

---

## 🔧 Компилация / Compilation

The Makefile is written to work on Windows, macOS, and Linux without additional modifications. It supports cross-compilation from macOS/Linux to Windows using MinGW.

### Using Makefile (Recommended):
```bash
make              # Compile the project for native platform
make windows      # Cross-compile for Windows (.exe)
make all-platforms # Build for both native and Windows
make run          # Compile and run
make clean        # Remove build artifacts
make clean-data   # Remove data files
make clean-all    # Remove everything including build dirs
make rebuild      # Clean and recompile
make structure    # Show project structure
make help         # Show all available commands
```

### Windows Cross-Compilation:
To build a Windows executable from macOS or Linux, you need MinGW-w64 installed:

**On macOS:**
```bash
brew install mingw-w64
make windows
```

**On Linux (Ubuntu/Debian):**
```bash
sudo apt-get install mingw-w64
make windows
```

This will create `bank_system.exe` that runs on Windows without requiring any additional DLLs (statically linked).

### Manual Compilation:
```bash
g++ -std=c++11 -Wall -Wextra -pedantic -Iinclude \
    src/main.cpp src/BankAccount.cpp \
    -o bank_system
```

---

## 🚀 Използване / Usage

```bash
./bank_system
```

### Основни Функции / Main Features:

1. **Добави банкова сметка / Add Bank Account**
2. **Добави вноска към сметка / Add Deposit to Account**
3. **Добави теглене от сметка / Add Withdrawal from Account**
4. **Покажи всички сметки / Display All Accounts**
5. **Покажи детайли на сметка / Display Account Details**
6. **Създай файл от сметки / Create Accounts File**
7. **Покажи притежатели с повече от една сметка / Display Owners with Multiple Accounts** (sorted alphabetically)
8. **Покажи разликите между вноски и тегления / Display Deposit-Withdrawal Differences**
9. **Запиши сметки с равни вноски и тегления / Save Accounts with Equal Deposits and Withdrawals**

---

## 📚 Клас / Class

### BankAccount
Представлява банкова сметка с характеристики:
- **Уникален код (Unique Code)**: Буква + 5 цифри (напр. "A12345")
- **Име на притежателя (Owner Name)**: Указател към символен низ
- **Вноски (Deposits)**: Динамичен масив от суми
- **Тегления (Withdrawals)**: Динамичен масив от суми

**Методи:**
- Конструктор по подразбиране
- Конструктор с параметри
- Копиращ конструктор
- Деструктор
- Оператор за присвояване
- Предефиниран оператор `<<` за извеждане
- Предефиниран оператор `>>` за въвеждане
- `saveToFile()` - записване във файл
- `loadFromFile()` - зареждане от файл
- `addDeposit()` - добавяне на вноска
- `addWithdrawal()` - добавяне на теглене
- `getTotalDeposited()` - обща сума на вноските
- `getTotalWithdrawn()` - обща сума на тегленията
- `getBalance()` - баланс (разлика между вноски и тегления)
- `hasEqualDepositsAndWithdrawals()` - проверка дали вноските и тегленията са равни

---

## ✅ Валидация / Validation

- **Уникален код**: Точно 6 символа - първият е буква, следващите 5 са цифри
- **Име на притежателя**: Не може да е празно
- **Суми**: Не могат да бъдат отрицателни

---

## 📊 Файлове с Данни / Data Files

- `bank_accounts.dat` - Съхранява всички банкови сметки (автоматично при изход)
- `accounts.dat` - Файл, създаден от опция 6 (Create Accounts File)
- `equal_accounts.dat` - Файл със сметки с равни вноски и тегления (опция 9)

---

## 🎯 Изисквания от Заданието / Task Requirements

✓ **1. Създава файл от обекти – банкови сметки**  
   Реализирано чрез опция 6 в менюто

✓ **2. Извежда имената на притежателите на повече от една банкови сметки, подредени по азбучен ред**  
   Реализирано чрез опция 7 в менюто

✓ **3. Извежда разликите от внесени и изтеглени суми**  
   Реализирано чрез опция 8 в менюто

✓ **4. Записва в нов файл информацията за сметките, за които внесените и изтеглени суми са еднакви**  
   Реализирано чрез опция 9 в менюто

---

## 🔍 Технологии / Technologies

- **Език**: C++11
- **Компилатор**: g++
- **Build система**: Make
- **STL**: vector, string, iostream, fstream, algorithm, map, set
- **Валидация**: exception handling
- **Динамична памет**: new/delete за масиви и низове

---

## 👨‍💻 Автор / Author

Бонус задача за университет  
University Bonus Task  
© 2025

---

## 📝 Бележки / Notes

- Програмата автоматично записва данните при изход
- Данните се зареждат автоматично при старт (ако файлът съществува)
- Всички изисквания от заданието са изпълнени
- Кодът е организиран в професионална структура
- Компилира без грешки и предупреждения
- Използва динамична памет за масиви и низове според изискванията

---

**Успех! / Good luck!** 🎯

