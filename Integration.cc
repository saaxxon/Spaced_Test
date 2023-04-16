// Integration.cc

#include "Integration.h"
#include "GUI.h"
#include "Algorithm.h"

void integrate_algorithm_with_gui(GUI& gui) {
  // Connect the button clicked signal to the corresponding callback function
  gui.connect_button_clicked_signal([&gui](){
    // Parse the user input
    std::string input = gui.get_input();
    InputData data = parse_input(input);
    
    // Create the review schedule
    std::vector<ReviewItem> schedule = create_review_schedule(data);
    
    // Format the schedule as a string
    std::string schedule_string = format_schedule(schedule);
    
    // Update the GUI with the review schedule
    gui.update_schedule(schedule_string);
  });
}
