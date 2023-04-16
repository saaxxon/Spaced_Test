#include "GUI.h"

// Constructor for the GUI class
GUI::GUI() {
  // Initialize the main window
  mainWindow = new Gtk::Window();
  mainWindow->set_title("Spaced Test");
  mainWindow->set_border_width(10);

  // Initialize the deck list
  deckList = new Gtk::TreeView();
  deckList->set_headers_visible(false);
  deckList->signal_row_activated().connect(sigc::mem_fun(*this, &GUI::on_deck_activated));

  // Initialize the card list
  cardList = new Gtk::TreeView();
  cardList->set_headers_visible(false);
  cardList->signal_row_activated().connect(sigc::mem_fun(*this, &GUI::on_card_activated));

  // Initialize the deck and card models
  deckModel = Gtk::ListStore::create(deckColumns);
  cardModel = Gtk::ListStore::create(cardColumns);

  // Set the deck and card models for the deck and card lists
  deckList->set_model(deckModel);
  cardList->set_model(cardModel);

  // Initialize the deck and card columns for the deck and card lists
  deckList->append_column("", deckColumns.deckName);
  cardList->append_column("", cardColumns.cardFront);

  // Initialize the layout
  layout = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 0);
  layout->add(*deckList);
  layout->add(*cardList);

  // Add the layout to the main window
  mainWindow->add(*layout);

  // Show all widgets
  mainWindow->show_all();
}

// Destructor for the GUI class
GUI::~GUI() {
  delete mainWindow;
  delete deckList;
  delete cardList;
  delete layout;
}

// Updates the deck list with the latest deck data
void GUI::updateDeckList(const std::vector<Deck>& decks) {
  deckModel->clear();
  for (auto deck : decks) {
    Gtk::TreeModel::Row row = *(deckModel->append());
    row[deckColumns.deckName] = deck.name;
    row[deckColumns.deck] = deck;
  }
}

// Updates the card list with the latest card data
void GUI::updateCardList(const std::vector<Card>& cards) {
  cardModel->clear();
  for (auto card : cards) {
    Gtk::TreeModel::Row row = *(cardModel->append());
    row[cardColumns.cardFront] = card.front;
    row[cardColumns.card] = card;
  }
}

// Handles when a deck is activated in the deck list
void GUI::on_deck_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column) {
  Gtk::TreeModel::iterator iter = deckModel->get_iter(path);
  if (iter) {
    Gtk::TreeModel::Row row = *iter;
    Deck deck = row[deckColumns.deck];
    updateCardList(deck.cards);
  }
}

// Handles when a card is activated in the card list
void GUI::on_card_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column) {
  Gtk::TreeModel::iterator iter = cardModel->get_iter(path);
  if (iter) {
    Gtk::TreeModel::Row row = *iter;
    Card card = row[cardColumns.card];
    showCardDialog(card);
  }
}

// Shows the dialog for a card
void GUI::showCardDialog(const Card& card) {
  // Initialize the dialog window
  Gtk::Dialog dialog(card.front, *main Window);

// Add the card contents to the dialog window
Gtk::Label* label = new Gtk::Label(card.front + "\n\n" + card.back);
dialog.get_content_area()->add(*label);

// Show the dialog window and wait for a response
dialog.show_all();
dialog.run();
}

// Runs the GUI application
void GUI::run() {
Gtk::Main::run(*mainWindow);
}
