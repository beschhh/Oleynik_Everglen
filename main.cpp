#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

constexpr int MAX_WORD_LENGTH = 20;
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

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    const char original[MAX_WORD_LENGTH + 1] = "computer";
    char encrypted[MAX_WORD_LENGTH + 1];
    char userGuess[MAX_WORD_LENGTH + 1];

    int key = std::rand() % 5 + 1;
    int attempts = INITIAL_ATTEMPTS;

    encryptWord(original, encrypted, key);

    std::cout << "Игра «Дешифратор слов»" << std::endl;
    std::cout << "Расшифруйте слово: " << encrypted << std::endl;
    std::cout << "У вас " << attempts << " попытки." << std::endl;
    std::cout << "Введите слово или команду hint для подсказки." << std::endl;

    while (attempts > 0) {
        std::cout << "> ";
        std::cin >> userGuess;

        if (std::strcmp(userGuess, "hint") == 0) {
            revealOneLetter(original, encrypted);
            std::cout << "Подсказка: " << encrypted << std::endl;
            std::cout << "Осталось попыток: " << attempts << std::endl;
            continue;
        }

        if (!isLowercaseWord(userGuess)) {
            std::cout << "Введите слово английскими буквами в нижнем регистре." << std::endl;
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

    std::cout << "Попытки закончились. Загаданное слово: " << original << std::endl;

    return 0;
}