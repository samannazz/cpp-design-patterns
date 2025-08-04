#include <iostream>
#include <string>
#include <vector>
#include <memory>

// AFTER: Following Open/Closed Principle
// Can add new channels WITHOUT modifying existing code -- open for extension

/*
 * BENEFITS of this approach:
 * 1. EXTENSION WITHOUT MODIFICATION: Add new notification types without changing existing code
 * 2. FOLLOWS OCP: Classes are "closed for modification, open for extension"
 * 3. LOOSE COUPLING: Each notification type is independent
 * 4. EASY TO TEST: Can test each notification type in isolation
 * 5. SAFE CHANGES: Adding Discord won't break Email functionality
 * 
 * To add new notification types (WhatsApp, Discord, etc.), we just:
 * - Create a new class that inherits from NotificationSender
 * - No need to modify any existing code!
 */

// Abstract base class for all communication channels
class INotificationChannel{
public:
    virtual ~INotificationChannel() = default;
    virtual void send(const std::string& message) = 0;
    virtual std::string getType() const = 0;
};

// Email channel implementation
class EmailChannel : public INotificationChannel {
public:
    void send(const std::string& message) override {
        std::cout << "Email: " << message << std::endl;
    }
    
    std::string getType() const override {
        return "Email";
    }
};

// SMS channel implementation
class SMSChannel : public INotificationChannel {
public:
    void send(const std::string& message) override {
        std::cout << "SMS: " << message << std::endl;
    }
    
    std::string getType() const override {
        return "SMS";
    }
};

// Voice channel implementation
class VoiceChannel : public INotificationChannel {
public:
    void send(const std::string& message) override {
        std::cout << "Voice: " << message << std::endl;
    }
    
    std::string getType() const override {
        return "Voice";
    }
};

// NEW: Discord notification - also added WITHOUT modifying existing code!
class DiscordNotification : public INotificationChannel {
    public:
        void send(const std::string& message) override {
            std::cout << "Discord: " << message << std::endl;
        }
        
        std::string getType() const override {
            return "Discord";
        }
    };

// NotificationManager - NEVER needs modification when adding new channels!
class NotificationManager {
    private:
        std::vector<std::unique_ptr<INotificationChannel>> channels;
    
    public:
        void addChannel(std::unique_ptr<INotificationChannel> channel) {
            channels.push_back(std::move(channel));
        }
    
        void notifyAll(const std::string& message) {
            for (const auto& channel : channels) {
                channel->send(message);
            }
        }
    };
    

/*
 * SUCCESS: Can add new channels without modifying:
 * - NotificationManager class
 * - EmailChannel class  
 * - SMSChannel class
 * - VoiceChannel class
 * 
 * This follows Open/Closed Principle!
 */

int main() {
    std::cout << "=== AFTER: Open/Closed Principle Compliance ===" << std::endl;
    std::cout << "Solution: Extend functionality without modifying existing code" << std::endl;
    std::cout << std::endl;

    NotificationManager manager;
    
    // Add channels - no modification of existing code needed!
    manager.addChannel(std::make_unique<EmailChannel>());
    manager.addChannel(std::make_unique<SMSChannel>());
    manager.addChannel(std::make_unique<VoiceChannel>());
    manager.addChannel(std::make_unique<DiscordNotification>());
    
    std::cout << "Notifying all channels:" << std::endl;
    manager.notifyAll("Hello everyone!");
    
    std::cout << std::endl;
    std::cout << "SUCCESS: Can add new channels without modifying existing classes!" << std::endl;
    
    return 0;
}
