#include <iostream>
#include <vector>
#include <string>

// BEFORE: Violating Single Responsibility Principle
// This class does TOO MANY things!

/*
 * SRP VIOLATION EXPLANATION:
 * 
 * 1. "ONE REASON TO CHANGE" - This class has MULTIPLE reasons to change:
 *    - If logging format changes → class must change
 *    - If validation rules change → class must change  
 *    - If database storage changes → class must change
 *    - If display format changes → class must change
 * 
 * 2. "SEPARATION OF CONCERNS" - This class mixes different concerns:
 *    - Business logic (message processing)
 *    - Infrastructure (logging, database)
 *    - Presentation (display formatting)
 *    - Validation (input checking)
 * 
 * PROBLEMS:
 * - Hard to test individual parts
 * - Changes in one area affect others
 * - Difficult to reuse components
 * - Violates "Single Responsibility Principle"
 */

class MessageProcessor {
private:
    std::vector<std::string> database;

public:
    bool processMessage(const std::string& message, const std::string& sender) {
        // Concern 1: Logging
        std::cout << "LOG: Processing message from " << sender << std::endl;
        
        // Concern 2: Validation
        if (message.empty() || sender.empty()) {
            std::cout << "LOG: Validation failed" << std::endl;
            std::cout << "ERROR: Invalid input!" << std::endl;
            return false;
        }
        
        // Concern 3: Database
        database.push_back(message + " from " + sender);
        std::cout << "LOG: Stored in database" << std::endl;
        
        // Concern 4: Message Display
        std::cout << "DISPLAY: " << message << std::endl;
        std::cout << "SUCCESS: Message processed!" << std::endl;
        std::cout << "LOG: Processing complete" << std::endl;
        
        return true;
    }
    
    void showAll() {
        // Mixing Concerns: Logging + Display together
        std::cout << "LOG: Showing all messages" << std::endl;
        for (const auto& msg : database) {
            std::cout << "- " << msg << std::endl;
        }
    }
};

int main() {
    std::cout << "=== BEFORE: SRP VIOLATION EXAMPLE ===" << std::endl;
    
    MessageProcessor processor;
    
    // Test with valid message
    processor.processMessage("Hello World!", "Agent1");
    std::cout << std::endl;
    
    // Test with invalid message (empty)
    processor.processMessage("", "Agent");
    std::cout << std::endl;
    
    // Test with invalid sender (empty)
    processor.processMessage("Hi there!", "");
    std::cout << std::endl;
    
    processor.showAll();
    
    return 0;
}