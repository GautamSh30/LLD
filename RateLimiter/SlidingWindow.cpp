#include <iostream>
#include <deque>
#include <chrono>

using namespace std;
using namespace std::chrono;

class RateLimiter {
private:
    int timeWindowSec;           // Time window in seconds
    int maxRequests;             // Allowed requests in time window
    deque<long long> timestamps; // Stores timestamps of accepted requests

    // Helper to get current timestamp in seconds
    long long getCurrentTime() {
        return duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
    }

public:
    RateLimiter(int windowSec, int capacity)
        : timeWindowSec(windowSec), maxRequests(capacity) {}

    bool isAllowed() {
        long long currentTime = getCurrentTime();

        // Remove timestamps older than timeWindowSec
        while (!timestamps.empty() && currentTime - timestamps.front() >= timeWindowSec) {
            timestamps.pop_front();
        }

        // Check if within limit
        if (timestamps.size() < maxRequests) {
            timestamps.push_back(currentTime); // Allow request
            return true;
        }

        return false; // Reject request
    }
};

int main() {
    RateLimiter rl(5, 3); // Allow 3 requests per 5 seconds

    for (int i = 0; i < 10; ++i) {
        if (rl.isAllowed()) {
            cout << "Request " << i + 1 << ": Allowed\n";
        } else {
            cout << "Request " << i + 1 << ": Denied (Rate limit exceeded)\n";
        }

        this_thread::sleep_for(chrono::seconds(1)); // Simulate 1-second gap between requests
    }

    return 0;
}
