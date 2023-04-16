#include "Integration.hh"

#include <fstream>

// Saves the deck to a file
void Integration::saveDeck(const Deck& deck, const std::string& filename) {
  std::ofstream outfile(filename);

  if (outfile.is_open()) {
    // Write deck name
    outfile << deck.name << "\n";

    // Write cards
    for (const auto& card : deck.cards) {
      outfile << card.front << "\n";
      outfile << card.back << "\n";
      outfile << card.interval << "\n";
      outfile << card.easiness << "\n";
      outfile << card.lastReviewed << "\n";
      outfile << card.nextReview << "\n";
      outfile << card.repetitions << "\n";
      outfile << card.quality << "\n";
      outfile << card.history << "\n";
    }

    outfile.close();
  }
}

// Loads the deck from a file
Deck Integration::loadDeck(const std::string& filename) {
  std::ifstream infile(filename);
  Deck deck;

  if (infile.is_open()) {
    std::string line;
    bool firstLine = true;
    Card card;

    while (std::getline(infile, line)) {
      if (line.empty()) continue;

      if (firstLine) {
        deck.name = line;
        firstLine = false;
      } else {
        switch (card.field) {
          case CardField::FRONT:
            card.front = line;
            card.field = CardField::BACK;
            break;
          case CardField::BACK:
            card.back = line;
            card.field = CardField::INTERVAL;
            break;
          case CardField::INTERVAL:
            card.interval = std::stoi(line);
            card.field = CardField::EASINESS;
            break;
          case CardField::EASINESS:
            card.easiness = std::stof(line);
            card.field = CardField::LAST_REVIEWED;
            break;
          case CardField::LAST_REVIEWED:
            card.lastReviewed = std::stol(line);
            card.field = CardField::NEXT_REVIEW;
            break;
          case CardField::NEXT_REVIEW:
            card.nextReview = std::stol(line);
            card.field = CardField::REPETITIONS;
            break;
          case CardField::REPETITIONS:
            card.repetitions = std::stoi(line);
            card.field = CardField::QUALITY;
            break;
          case CardField::QUALITY:
            card.quality = std::stoi(line);
            card.field = CardField::HISTORY;
            break;
          case CardField::HISTORY:
            card.history = std::vector<int>(std::stoi(line));
            card.field = CardField::FRONT;
            deck.cards.push_back(card);
            card = Card();
            break;
        }
      }
    }

    infile.close();
  }

  return deck;
}
