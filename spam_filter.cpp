#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>

class SpamDetector {
private:
    std::vector<std::string> spamKeywords;
    int threshold;

    // Helper function to convert a string to lowercase
    std::string toLowerCase(const std::string& str) {
        std::string lowerStr = str;
        std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
            [](unsigned char c){ return std::tolower(c); });
        return lowerStr;
    }

public:
    // Constructor: Sets the spam threshold and initializes the dictionary
    SpamDetector(int spamThreshold = 2) : threshold(spamThreshold) {
        // A basic list of common spam trigger words
        spamKeywords = {
            "free", "winner", "lottery", "urgent", "click", 
            "buy", "cheap", "guarantee", "money", "prize", 
            "cash", "crypto", "investment"
        };
    }

    // Main function to check if an email is spam
    bool isSpam(const std::string& emailText) {
        std::string lowerEmail = toLowerCase(emailText);
        int spamScore = 0;

        // StringStream is used to break the email into individual words
        std::stringstream ss(lowerEmail);
        std::string word;
        
        while (ss >> word) {
            // Remove basic punctuation from the word (e.g., "winner!" -> "winner")
            word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());

            // Check if the cleaned word exists in our spam keyword list
            for (const auto& keyword : spamKeywords) {
                if (word == keyword) {
                    spamScore++;
                    break; // Found a match, move to the next word in the email
                }
            }
        }

        // If the number of spam words meets or exceeds our limit, flag it
        return spamScore >= threshold;
    }
};

int main() {
    // Initialize detector. It will flag an email as spam if it finds 2 or more trigger words.
    SpamDetector detector(2); 

    // Example 1: A normal work email (Ham)
    std::string email1 = "Hello team, let's schedule a meeting for tomorrow to discuss the C++ project.";
    
    // Example 2: A blatant spam email
    std::string email2 = "URGENT! You are a WINNER! Click here to claim your free prize money now!";

    std::cout << "--- Email Spam Detector ---" << "\n\n";

    std::cout << "Email 1 text: \"" << email1 << "\"\n";
    std::cout << "Result: " << (detector.isSpam(email1) ? "[SPAM]" : "[NOT SPAM]") << "\n\n";

    std::cout << "Email 2 text: \"" << email2 << "\"\n";
    std::cout << "Result: " << (detector.isSpam(email2) ? "[SPAM]" : "[NOT SPAM]") << "\n";

    return 0;
}
