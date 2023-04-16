#include "Algorithm.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

double calculateInterval(double difficulty, double currentInterval, int responseTime, bool correct) {
    double nextInterval = 0;
    if (responseTime > 0 && correct) {
        if (currentInterval == 0) {
            nextInterval = 1;
        } else if (currentInterval == 1) {
            nextInterval = 6;
        } else {
            nextInterval = currentInterval * difficulty;
        }
    } else {
        nextInterval = 0;
    }
    return nextInterval;
}

Flashcard* readFlashcards(const std::string& filename) {
    std::fstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file " << filename << std::endl;
        return nullptr;
    }
    if (file.peek() == std::ifstream::traits_type::eof()) {
        std::cout << "Error: File " << filename << " is empty" << std::endl;
        return nullptr;
    }
    std::vector<Flashcard> flashcards;
    std::string line;
    while (std::getline(file, line)) {
        std::string::size_type sep = line.find(",");
        if (sep == std::string::npos) {
            std::cout << "Error: Invalid line in file " << filename << std::endl;
            return nullptr;
        }
        std::string front = line.substr(0, sep);
        std::string back = line.substr(sep + 1);
        Flashcard flashcard(front, back);
        flashcards.push_back(flashcard);
    }
    Flashcard* flashcardPtr = new Flashcard[flashcards.size()];
    for (int i = 0; i < flashcards.size(); i++) {
        flashcardPtr[i] = flashcards[i];
    }
    return flashcardPtr;
}

void writeFlashcards(const std::string& filename, const Flashcard* flashcards, int numFlashcards) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file " << filename << std::endl;
        return;
    }
    for (int i = 0; i < numFlashcards; i++) {
        file << flashcards[i].getFront() << "," << flashcards[i].getBack() << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }
    std::string filename = argv[1];
    Flashcard* flashcardPtr = readFlashcards(filename);
    if (flashcardPtr == nullptr) {
        return 1;
    }
    // Do something with flashcards...
    delete[] flashcardPtr;
    return 0;
}
