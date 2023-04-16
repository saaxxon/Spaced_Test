#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

// Define a struct to represent a flashcard
struct Flashcard {
    string question;
    string answer;
    int difficulty;
    int interval;
};

// Define a function to calculate the interval between repetitions
int calculateInterval(int difficulty, int interval, double responseTime, bool correctAnswer) {
    double easinessFactor = 2.5 - (difficulty - 1) * 0.2;
    if (!correctAnswer) {
        easinessFactor -= 0.8;
    }
    if (easinessFactor < 1.3) {
        easinessFactor = 1.3;
    }
    interval = ceil(interval * easinessFactor);
    if (interval < 1) {
        interval = 1;
    }
    return interval;
}

// Define a function to read in flashcards from a file
Flashcard* readFlashcards(string filename, int& numCards) {
    ifstream infile(filename.c_str());
    if (!infile) {
        cerr << "Error: Could not open file '" << filename << "' for reading." << endl;
        exit(1);
    }
    vector<Flashcard> flashcards;
    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        string question, answer;
        if (!(iss >> question >> answer)) {
            cerr << "Error: Invalid input line: " << line << endl;
            exit(1);
        }
        flashcards.push_back({question, answer, 1, 1});
    }
    numCards = flashcards.size();
    Flashcard* cards = new Flashcard[numCards];
    copy(flashcards.begin(), flashcards.end(), cards);
    return cards;
}

// Define a function to write flashcards to a file
void writeFlashcards(string filename, Flashcard* cards, int numCards) {
    ofstream outfile(filename.c_str());
    if (!outfile) {
        cerr << "Error: Could not open file '" << filename << "' for writing." << endl;
        exit(1);
    }
    for (int i = 0; i < numCards; i++) {
        outfile << cards[i].question << " " << cards[i].answer << endl;
    }
    outfile.close();
}

// Define a function to print out the list of flashcards
void printFlashcards(Flashcard* cards, int numCards) {
    for (int i = 0; i < numCards; i++) {
        cout << cards[i].question << " " << cards[i].answer << " " << cards[i].difficulty << " " << cards[i].interval << endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <flashcard-file>" << endl;
        exit(1);
    }
    string filename = argv[1];
    int numCards;
    Flashcard* flashcards = readFlashcards(filename, numCards);
    int currentCard = 0;
    int numCorrect = 0;
    int numIncorrect = 0;
    double totalTime = 0.0;

    srand(time(nullptr));

    while (true) {
        Flashcard& card = flashcards[currentCard];
        cout << card.question << endl;
        string answer;
        cin >> answer;
        double responseTime = difftime(time(nullptr), mktime(localtime(&t)));
        bool correctAnswer =
    if (answer == card.answer) {
        cout << "Correct!" << endl;
        card.difficulty++;
        numCorrect++;
        card.interval = calculateInterval(card.difficulty, card.interval, responseTime, true);
    } else {
        cout << "Incorrect. The correct answer is: " << card.answer << endl;
        card.difficulty = 1;
        numIncorrect++;
        card.interval = calculateInterval(card.difficulty, card.interval, responseTime, false);
    }
    totalTime += responseTime;
    cout << "Time taken: " << responseTime << " seconds" << endl;
    currentCard++;
    if (currentCard == numCards) {
        currentCard = 0;
        random_shuffle(&flashcards[0], &flashcards[numCards]);
    }
    cout << "Number of correct answers: " << numCorrect << endl;
    cout << "Number of incorrect answers: " << numIncorrect << endl;
    cout << "Total time taken: " << totalTime << " seconds" << endl;
    writeFlashcards(filename, flashcards, numCards);

    // check if the user wants to continue reviewing
    char continueReviewing;
    cout << "Do you want to continue reviewing? (y/n) ";
    cin >> continueReviewing;
    if (continueReviewing == 'n') {
        break;
    }
}
delete[] flashcards;
return 0;
}
