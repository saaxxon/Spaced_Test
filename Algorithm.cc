#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;

struct Card {
    int id;
    int interval;
    int repetitions;
    time_t next_review;
};

class SpacedRepetition {
private:
    double ease_factor;
    double minimum_interval;
    double initial_interval;
    double forgetting_index;
public:
    SpacedRepetition(double ease_factor, double minimum_interval, double initial_interval, double forgetting_index) {
        this->ease_factor = ease_factor;
        this->minimum_interval = minimum_interval;
        this->initial_interval = initial_interval;
        this->forgetting_index = forgetting_index;
    }
    double get_ease_factor() {
        return this->ease_factor;
    }
    double get_minimum_interval() {
        return this->minimum_interval;
    }
    double get_initial_interval() {
        return this->initial_interval;
    }
    double get_forgetting_index() {
        return this->forgetting_index;
    }
    double calculate_easiness_factor(Card card) {
        double easiness_factor = card.interval / this->initial_interval;
        easiness_factor = easiness_factor - 0.8 + 0.28 * card.repetitions - 0.02 * card.repetitions * card.repetitions;
        if (easiness_factor < 1.3) {
            easiness_factor = 1.3;
        }
        return easiness_factor;
    }
    int calculate_next_interval(Card card, double easiness_factor) {
        int next_interval = (int)round(card.interval * easiness_factor);
        if (next_interval < this->minimum_interval) {
            next_interval = (int)this->minimum_interval;
        }
        return next_interval;
    }
    int calculate_repetitions(Card card, double easiness_factor) {
        int repetitions = card.repetitions;
        if (easiness_factor <= 1.3) {
            repetitions = 0;
        }
        else {
            repetitions++;
        }
        return repetitions;
    }
    Card update_card(Card card, double easiness_factor) {
        time_t current_time = time(nullptr);
        int repetitions = calculate_repetitions(card, easiness_factor);
        int interval = calculate_next_interval(card, easiness_factor);
        card.repetitions = repetitions;
        card.interval = interval;
        card.next_review = current_time + interval * 86400;
        return card;
    }
};

int main() {
    // initialize the spaced repetition algorithm
    SpacedRepetition sr(2.5, 1, 10, 0.16);

    // create a new card
    Card card = { 1, 1, 0, time(nullptr) };

    // calculate the easiness factor for the card
    double easiness_factor = sr.calculate_easiness_factor(card);

    // update the card with the new easiness factor
    card = sr.update_card(card, easiness_factor);

    // print out the results
    cout << "Card id: " << card.id << endl;
    cout << "Repetitions: " << card.repetitions << endl;
    cout << "Interval: " << card.interval << " days" << endl;
    cout << "Next review: " << ctime(&card.next_review) << endl;

    return 0;
}
