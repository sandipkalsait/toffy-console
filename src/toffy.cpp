#include "toffy.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <random>
#include <algorithm>

// File to store logs
const std::string log_file = "/logs/toffy_log.txt";

// Helper function to log messages
void logMessage(const std::string& message) {
    std::ofstream log(log_file, std::ios_base::app);
    if (log.is_open()) {
        std::time_t current_time = std::time(0);
        std::tm* time_info = std::localtime(&current_time);
        char buffer[80];
        std::strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", time_info);
        log << "[" << buffer << "] " << message << std::endl;
    }
    log.close();
}

// Constructor: Read responses, feedback, and context from their respective files
Toffy::Toffy() {
    logMessage("Toffy bot initialized.");
    readResponsesFromFile();
    readFeedbackFromFile();
    readContextFromFile();
}

// Reads the responses from a CSV file
void Toffy::readResponsesFromFile() {
    std::ifstream file(responses_file);
    if (!file.is_open()) {
        logMessage("Error opening responses file!");
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string input, response;
        std::getline(ss, input, ',');
        std::getline(ss, response, ',');
        trained_responses[input] = response;
    }
    file.close();
    logMessage("Responses loaded from file.");
}

// Writes updated responses to the CSV file
void Toffy::writeResponsesToFile() {
    std::ofstream file(responses_file);
    for (const auto& pair : trained_responses) {
        file << pair.first << "," << pair.second << "\n";
    }
    file.close();
    logMessage("Responses saved to file.");
}

// Reads feedback data from a CSV file
void Toffy::readFeedbackFromFile() {
    std::ifstream file(feedback_file);
    if (!file.is_open()) {
        logMessage("Error opening feedback file!");
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string input;
        bool is_correct;
        std::getline(ss, input, ',');
        ss >> is_correct;
        feedback_data[input] = is_correct;
    }
    file.close();
    logMessage("Feedback loaded from file.");
}

// Writes feedback data to the CSV file
void Toffy::writeFeedbackToFile() {
    std::ofstream file(feedback_file);
    for (const auto& pair : feedback_data) {
        file << pair.first << "," << pair.second << "\n";
    }
    file.close();
    logMessage("Feedback saved to file.");
}

// Reads context data from a CSV file
void Toffy::readContextFromFile() {
    std::ifstream file(context_file);
    if (!file.is_open()) {
        logMessage("Error opening context file!");
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string input;
        int count;
        std::getline(ss, input, ',');
        ss >> count;
        context[input] = count;
    }
    file.close();
    logMessage("Context loaded from file.");
}

// Writes context data to the CSV file
void Toffy::writeContextToFile() {
    std::ofstream file(context_file);
    for (const auto& pair : context) {
        file << pair.first << "," << pair.second << "\n";
    }
    file.close();
    logMessage("Context saved to file.");
}

// Process user input and generate responses
std::string Toffy::process(const std::string& input, const std::string& name) {
    logMessage("Processing input: " + input);

    std::string response;

    // If the response is already trained, return it
    if (trained_responses.find(input) != trained_responses.end()) {
        response = trained_responses[input];
    }
    else if (input == "greet" + name) {
        response = "Hello, " + name + "! How can I assist you today?";
    }
    else {
        response = "Sorry, I don't know how to respond to that.";
    }

    logMessage("Response generated: " + response);
    return response;
}

// Method to generate a dynamic greeting message
std::string Toffy::greet(const std::string& name) {
    logMessage("Generating greeting for: " + name);
    return process("greet" + name, name);
}

// Train the chatbot by adding new responses
void Toffy::train(const std::string& input, const std::string& response) {
    trained_responses[input] = response;
    writeResponsesToFile(); // Save updated responses
    logMessage("Training: Added new response for input: " + input);
}

// Collect feedback on the chatbot's responses
void Toffy::feedback(const std::string& input, bool is_correct) {
    feedback_data[input] = is_correct;
    writeFeedbackToFile(); // Save feedback
    logMessage("Feedback collected: Input: " + input + " Correct: " + (is_correct ? "Yes" : "No"));
}

// Tokenize the input (split into words)
std::vector<std::string> Toffy::tokenize(const std::string& input) {
    logMessage("Tokenizing input: " + input);
    std::vector<std::string> tokens;
    std::istringstream ss(input);
    std::string token;
    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

// Simplified lemmatization (basic form)
std::string Toffy::lemmatize(const std::string& token) {
    logMessage("Lemmatizing token: " + token);
    if (token == "running") {
        return "run";
    }
    else if (token == "better") {
        return "good";
    }
    else {
        return token;
    }
}

// Update the context of the conversation
void Toffy::updateContext(const std::string& input) {
    logMessage("Updating context for input: " + input);
    if (context.find(input) == context.end()) {
        context[input] = 1;
    }
    else {
        context[input] += 1;
    }
    writeContextToFile(); // Save updated context
}

// Predict the user's intent based on past training
std::string Toffy::predictIntent(const std::string& input) {
    logMessage("Predicting intent for input: " + input);
    if (context.find(input) != context.end()) {
        return "I think you're asking about: " + input;
    }
    else {
        return "I'm not sure about that yet.";
    }
}
