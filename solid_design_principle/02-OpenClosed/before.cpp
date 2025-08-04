#include <iostream>
#include <string>

// BEFORE: Violating Open/Closed Principle
// Must modify this class every time we add a new communication channel

/*
 * PROBLEMS with this approach:
 * 1. Every new notification type requires changing the notify class
 * 2. The class is not "closed for modification"
 * 3. All notification logic is mixed together
 * 4. Cannot test individual notification types in isolation
 * 5. Adding SMS might break Email functionality
 * 
 * What if we want to add: Slack, Discord, WhatsApp, Push notifications?
 * We'd have to keep modifying this class!
 */

class NotificationManager {
public:
    void notify(const std::string& message, const std::string& channel) {
        if (channel == "email") {
            std::cout << "Email: " << message << std::endl;
        }
        else if (channel == "sms") {
            std::cout << "SMS: " << message << std::endl;
        }
        // Adding voice required MODIFYING this method!
        else if (channel == "voice") {
            std::cout << "Voice: " << message << std::endl;
        }
        else {
            std::cout << "Unknown channel: " << channel << std::endl;
        }
    }
};

/*
 * PROBLEM: Adding "voice" channel required modifying the notify() method.
 * This violates Open/Closed Principle!
 */

int main() {
    std::cout << "=== BEFORE: Open/Closed Principle Violation ===" << std::endl;
    std::cout << "Problem: Must modify existing code to add new channels" << std::endl;
    std::cout << std::endl;

    NotificationManager manager;
    
    manager.notify("Hello via Email!", "email");
    manager.notify("Hello via SMS!", "sms");
    manager.notify("Hello via Voice!", "voice");  // Required code modification!
    manager.notify("Hello!", "unknown");
    
    std::cout << std::endl;
    std::cout << "PROBLEM: Adding voice channel required modifying NotificationManager!" << std::endl;
    
    return 0;
}
