#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

struct Flashcard {
    string question;
    string answer;
    int difficulty;
    int interval;
};

vector<Flashcard> readFlashcards(string filename) {
    vector<Flashcard> flashcards;
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            Flashcard card;
            card.question = line;
            getline(file, card.answer);
            file >> card.difficulty;
            file >> card.interval;
            flashcards.push_back(card);
            file.ignore(); // ignore the blank line
        }
        file.close();
    }
    return flashcards;
}

void writeFlashcards(string filename, Flashcard* flashcards, int numCards) {
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < numCards; i++) {
            file << flashcards[i].question << endl;
            file << flashcards[i].answer << endl;
            file << flashcards[i].difficulty << endl;
            file << flashcards[i].interval << endl;
            if (i != numCards - 1) {
                file << endl;
            }
        }
        file.close();
    }
}

int calculateInterval(int difficulty, int interval, int responseTime, bool answeredCorrectly) {
    double easinessFactor = 0.1 - (difficulty - 1) * (0.08 + (difficulty - 1) * 0.02);
    if (answeredCorrectly) {
        interval = 1;
    } else if (difficulty > 1) {
        interval *= easinessFactor;
    }
    interval = round(interval);
    return interval;
}

int main() {
    string filename = "flashcards.txt";
    vector<Flashcard> flashcards = readFlashcards(filename);
    int numCards = flashcards.size();
    Flashcard* flashcardPtr = &flashcards[0];
    random_device rd;
    mt19937 g(rd());
    shuffle(flashcards.begin(), flashcards.end(), g);
    int currentCard = 0;
    int numCorrect = 0;
    int numIncorrect = 0;
    int totalTime = 0;
    while (true) {
        Flashcard& card = flashcardPtr[currentCard];
        cout << card
                cout << "Question: " << card.question << endl;
    string userInput;
    cout << "Enter your answer: ";
    getline(cin, userInput);
    if (userInput == card.answer) {
        cout << "Correct!" << endl;
        numCorrect++;
        int responseTime;
        cout << "Enter your response time (in seconds): ";
        cin >> responseTime;
        totalTime += responseTime;
        card.interval = calculateInterval(card.difficulty, card.interval, responseTime, true);
        currentCard++;
        if (currentCard == numCards) {
            cout << "You have reviewed all flashcards!" << endl;
            break;
        }
        char continueReviewing;
        cout << "Do you want to continue reviewing? (y/n): ";
        cin >> continueReviewing;
        if (continueReviewing == 'n') {
            break;
        }
    } else {
        cout << "Incorrect. The correct answer is: " << card.answer << endl;
        numIncorrect++;
        card.interval = calculateInterval(card.difficulty, card.interval, 0, false);
        currentCard++;
        if (currentCard == numCards) {
            cout << "You have reviewed all flashcards!" << endl;
            break;
        }
        char continueReviewing;
        cout << "Do you want to continue reviewing? (y/n): ";
        cin >> continueReviewing;
        if (continueReviewing == 'n') {
            break;
        }
    }
}
for (int i = 0; i < numCards; i++) {
    Flashcard& card = flashcardPtr[i];
    writeFlashcards(filename, flashcardPtr, numCards);
}
double averageTime = totalTime / numCards;
cout << "Number of flashcards reviewed: " << numCards << endl;
cout << "Number of correct responses: " << numCorrect << endl;
cout << "Number of incorrect responses: " << numIncorrect << endl;
cout << "Total time spent reviewing (in seconds): " << totalTime << endl;
cout << "Average response time (in seconds): " << averageTime << endl;
return 0;
}
