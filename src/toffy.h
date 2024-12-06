#ifndef TOFFY_H
#define TOFFY_H

#include <string>
#include <vector>
#include <unordered_map>
#include <map>

class Toffy {
public:
    // Method to process user input and generate responses
    std::string process(const std::string& input, const std::string& name);

    // Method to generate a dynamic greeting message by calling process
    std::string greet(const std::string& name);

    // Method to "train" the chatbot with new responses, saved to CSV
    void train(const std::string& input, const std::string& response);

    // Method to collect feedback for improvement, saved to CSV
    void feedback(const std::string& input, bool is_correct);

    // Tokenization method to break input into words
    std::vector<std::string> tokenize(const std::string& input);

    // Method for lemmatization (simplified version)
    std::string lemmatize(const std::string& token);

    // Context tracking (keeps user conversation context in memory or file)
    void updateContext(const std::string& input);

    // Simple machine learning model: stores patterns to improve predictions
    std::string predictIntent(const std::string& input);

private:
    // File paths for dynamic data storage
    const std::string responses_file = "responses.csv";
    const std::string feedback_file = "feedback.csv";
    const std::string context_file = "context.csv";

    // Data containers
    std::unordered_map<std::string, std::string> trained_responses;
    std::unordered_map<std::string, bool> feedback_data;
    std::map<std::string, int> context;

    // Methods to read and write to files
    void readResponsesFromFile();
    void writeResponsesToFile();
    void readFeedbackFromFile();
    void writeFeedbackToFile();
    void readContextFromFile();
    void writeContextToFile();
};

#endif // TOFFY_H
