#include "toffy.h"
#include <iostream>

// Function to collect feedback for a specific input
void giveFeedback(Toffy& toffy) {
    std::string input;
    bool is_correct;

    // Get the input from the user for feedback
    std::cout << "Enter input for feedback: ";
    std::getline(std::cin, input);

    // Ask if the response was correct
    std::cout << "Was the response correct? (1 for yes, 0 for no): ";
    std::cin >> is_correct;
    std::cin.ignore();  // Clear the input buffer

    // Provide feedback to the bot
    toffy.feedback(input, is_correct);
}

// Main function to trigger feedback collection
int main() {
    Toffy toffy;  // Create an instance of the chatbot

    // Log the start of the feedback collection
    std::cout << "Toffy Bot - Feedback Mode\n";

    // Start the feedback process
    giveFeedback(toffy);

    // Log the completion of feedback collection
    std::cout << "Feedback has been recorded!\n";

    return 0;
}
