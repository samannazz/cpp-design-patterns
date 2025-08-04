#include <iostream>
#include <vector>
#include <string>

// AFTER: Following Single Responsibility Principle
// Each class has ONE job!

/*
 * SEPARATION OF CONCERNS Applied:
 *    - Logger: Only handles logging operations
 *    - Validator: Only handles input validation
 *    - Database: Only handles data storage/retrieval
 *    - Display: Only handles user interface/presentation
 * 
 * BENEFITS:
 * - Easy to test each class independently
 * - Changes are isolated to specific classes
 * - Components are reusable in other contexts
 * - Follows "Single Responsibility Principle"
 */

// Concern 1: Only Logging
class Logger {
public:
    void log(const std::string& message) {
        std::cout << "LOG: " << message << std::endl;
    }
};

// Concern 2: Only Validation
class Validator {
public:
    bool isValid(const std::string& message, const std::string& sender) {
        return !message.empty() && !sender.empty();
    }
};

// Concern 3: Only Database Storage
class Database {
private:
    std::vector<std::string> data;
public:
    void store(const std::string& item) {
        data.push_back(item);
    }
    
    std::vector<std::string> getAll() const {
        return data;
    }
};

// Concern 4: Only Display Operations
class Display {
public:
    void showMessage(const std::string& message) {
        std::cout << "DISPLAY: " << message << std::endl;
    }
    
    void showSuccess() {
        std::cout << "SUCCESS: Message processed!" << std::endl;
    }
    
    void showError() {
        std::cout << "ERROR: Invalid input!" << std::endl;
    }
    
    void showAll(const std::vector<std::string>& items) {
        for (const auto& item : items) {
            std::cout << "- " << item << std::endl;
        }
    }
};

class MessageProcessor {
private:
    Logger logger;
    Validator validator;
    Database database;
    Display display;

public:
    bool processMessage(const std::string& message, const std::string& sender) {
        logger.log("Processing message from " + sender);
        
        if (!validator.isValid(message, sender)) {
            logger.log("Validation failed");
            display.showError();
            return false;
        }
        
        database.store(message + " from " + sender);
        logger.log("Stored in database");
        
        display.showMessage(message);
        display.showSuccess();
        logger.log("Processing complete");
        
        return true;
    }
    
    void showAll() {
        logger.log("Showing all messages");
        display.showAll(database.getAll());
    }

    /*
     * NOTICE: This MessageProcessor class has ONE responsibility:
     * - Orchestrating the message processing workflow
     * 
     * It doesn't implement logging, validation, storage, or display logic.
     * It just coordinates the specialists who do that work.
     * 
     * REASON TO CHANGE: Only if the business workflow changes
     */
};

int main() {
    std::cout << "=== AFTER: SRP COMPLIANT EXAMPLE ===" << std::endl;
    
    MessageProcessor processor;
    
    // Test with valid message
    processor.processMessage("Hello World!", "Agent1");
    std::cout << std::endl;
    
    // Test with invalid message (empty)
    processor.processMessage("", "Agent2");
    std::cout << std::endl;
    
    // Test with invalid sender (empty)
    processor.processMessage("Hi there!", "");
    std::cout << std::endl;
    
    processor.showAll();
    
    return 0;
}