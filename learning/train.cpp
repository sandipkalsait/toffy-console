#include "toffy.h"
#include <iostream>

// Function to train the Toffy bot with new input and response
void trainToffy(Toffy& toffy) {
    std::string input, response;

    std::cout << "Enter input to train Toffy: ";
    std::getline(std::cin, input);
    std::cout << "Enter response for input: ";
    std::getline(std::cin, response);

    // Train the bot with the new input and response
    toffy.train(input, response);
}

// Main function
int main() {
    Toffy toffy;  // Create an instance of the chatbot

    // Log initialization message
    std::cout << "Toffy Bot - Training Mode\n";

    // Start the training process
    trainToffy(toffy);

    // Log the completion of the training
    std::cout << "Training completed successfully!\n";

    return 0;
}
