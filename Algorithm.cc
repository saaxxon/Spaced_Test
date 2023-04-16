#include "Algorithm.h"

// Initializes the SuperMemo algorithm
void SuperMemo::init(Card& card) {
  card.easinessFactor = 2.5;
  card.repetitions = 0;
  card.interval = 1;
}

// Calculates the next interval and easiness factor for a card
void SuperMemo::calculate(Card& card, int responseQuality) {
  float easinessFactor = card.easinessFactor;
  int repetitions = card.repetitions;
  int interval = card.interval;

  if (responseQuality < 3) {
    repetitions = 0;
    interval = 1;
  } else {
    easinessFactor = calculateEasinessFactor(easinessFactor, responseQuality);
    repetitions++;
    interval = calculateInterval(repetitions, easinessFactor);
  }

  card.easinessFactor = easinessFactor;
  card.repetitions = repetitions;
  card.interval = interval;
}

// Calculates the new easiness factor for a card
float SuperMemo::calculateEasinessFactor(float easinessFactor, int responseQuality) {
  float newEasinessFactor = easinessFactor - 0.8 + 0.28 * responseQuality - 0.02 * responseQuality * responseQuality;
  newEasinessFactor = std::max(newEasinessFactor, 1.3f);
  return newEasinessFactor;
}

// Calculates the new interval for a card
int SuperMemo::calculateInterval(int repetitions, float easinessFactor) {
  if (repetitions == 1) {
    return 1;
  } else if (repetitions == 2) {
    return 6;
  } else {
    int interval = ceil(easinessFactor * calculateInterval(repetitions - 1, easinessFactor));
    return interval;
  }
}
