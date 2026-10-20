#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

constexpr int MAX_WORD_LENGTH = 100;
constexpr int INPUT_CAPACITY = 1000;
constexpr int INITIAL_ATTEMPTS = 3;

void encryptWord(const char* original, char* encrypted, int key) {
    int i = 0;

    while (original[i] != '\0') {
        encrypted[i] = original[i] + key;

        if (encrypted[i] > 'z') {
            encrypted[i] -= 26;
        }

        i++;
    }

    encrypted[i] = '\0';
}

void revealOneLetter(const char* original, char* encrypted) {
    const char* originalPtr = original;
    char* encryptedPtr = encrypted;

    while (*originalPtr != '\0') {
        if (*encryptedPtr != *originalPtr) {
            *encryptedPtr = *originalPtr;
            return;
        }

        originalPtr++;
        encryptedPtr++;
    }
}

bool checkAnswer(const char* userGuess, const char* original, int& attempts) {
    if (std::strcmp(userGuess, original) == 0) {
        return true;
    }

    attempts--;
    return false;
}

bool isLowercaseWord(const char* text) {
    if (*text == '\0') {
        return false;
    }

    for (const char* p = text; *p != '\0'; p++) {
        if (*p < 'a' || *p > 'z') {
            return false;
        }
    }

    return true;
}

void readLine(char* buffer, int capacity) {
    int i = 0;
    char ch;

    while (std::cin.get(ch) && ch != '\n') {
        if (i < capacity - 1) {
            buffer[i] = ch;
            i++;
        }
    }

    buffer[i] = '\0';
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    const char original[MAX_WORD_LENGTH + 1] = "computer";
    char encrypted[MAX_WORD_LENGTH + 1];
    char userGuess[INPUT_CAPACITY];

    int key = std::rand() % 5 + 1;
    int attempts = INITIAL_ATTEMPTS;

    encryptWord(original, encrypted, key);

    std::cout << "Игра «Дешифратор слов»" << std::endl;
    std::cout << "Расшифруйте слово: " << encrypted << std::endl;
    std::cout << "У вас 3 попытки." << std::endl;
    std::cout << "Введите слово или команду hint для подсказки." << std::endl;

    while (attempts > 0) {
        std::cout << "> ";
        readLine(userGuess, INPUT_CAPACITY);

        if (std::strcmp(userGuess, "hint") == 0) {
            revealOneLetter(original, encrypted);
            std::cout << "Подсказка: " << encrypted << std::endl;
            std::cout << "Осталось попыток: " << attempts << std::endl;
            continue;
        }

        if (!isLowercaseWord(userGuess)) {
            std::cout << "Неверный ввод. Введите слово английскими буквами в нижнем регистре." << std::endl;
            continue;
        }

        if (checkAnswer(userGuess, original, attempts)) {
            std::cout << "Поздравляем! Вы угадали слово." << std::endl;
            return 0;
        }

        if (attempts > 0) {
            std::cout << "Неверно. Осталось попыток: " << attempts << std::endl;
        }
    }

    std::cout << "Попытки закончились. Вы проиграли." << std::endl;
    std::cout << "Загаданное слово: " << original << std::endl;

    return 0;
}
