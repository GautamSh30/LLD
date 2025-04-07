#include <iostream>
#include <unordered_map>
#include <deque>
#include <queue>
#include <chrono>
#include <thread>
#include <mutex>
#include <memory>

using namespace std;
using namespace std::chrono;

class RateLimiter {
public:
    virtual bool allowRequest(const string& userId) = 0;
    virtual ~RateLimiter() = default;
};

// Fixed Window Rate Limiter
class FixedWindowRateLimiter : public RateLimiter {
    int maxRequests;
    long windowSizeMillis;
    unordered_map<string, int> requestCounts;
    long long windowStart;
    mutex mtx;

public:
    FixedWindowRateLimiter(int maxReq, long winMillis)
        : maxRequests(maxReq), windowSizeMillis(winMillis) {
        windowStart = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    }

    bool allowRequest(const string& userId) override {
        lock_guard<mutex> lock(mtx);
        long long now = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        if (now - windowStart >= windowSizeMillis) {
            requestCounts.clear();
            windowStart = now;
        }
        requestCounts[userId]++;
        return requestCounts[userId] <= maxRequests;
    }
};

// Sliding Window Rate Limiter
class SlidingWindowRateLimiter : public RateLimiter {
    int maxRequests;
    long windowSizeMillis;
    unordered_map<string, deque<long long>> requestLogs;
    mutex mtx;

public:
    SlidingWindowRateLimiter(int maxReq, long winMillis)
        : maxRequests(maxReq), windowSizeMillis(winMillis) {}

    bool allowRequest(const string& userId) override {
        lock_guard<mutex> lock(mtx);
        long long now = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        auto& dq = requestLogs[userId];

        while (!dq.empty() && now - dq.front() >= windowSizeMillis) {
            dq.pop_front();
        }
        if ((int)dq.size() < maxRequests) {
            dq.push_back(now);
            return true;
        }
        return false;
    }
};

// Token Bucket Rate Limiter
class TokenBucketRateLimiter : public RateLimiter {
    int capacity;
    double refillRate;
    unordered_map<string, double> tokens;
    unordered_map<string, long long> lastRefillTimestamp;
    mutex mtx;

public:
    TokenBucketRateLimiter(int cap, double rate)
        : capacity(cap), refillRate(rate) {}

    bool allowRequest(const string& userId) override {
        lock_guard<mutex> lock(mtx);
        long long now = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

        if (!lastRefillTimestamp.count(userId)) {
            lastRefillTimestamp[userId] = now;
            tokens[userId] = capacity;
        }

        long long elapsed = now - lastRefillTimestamp[userId];
        double refill = (elapsed / 1000.0) * refillRate;
        tokens[userId] = min((double)capacity, tokens[userId] + refill);
        lastRefillTimestamp[userId] = now;

        if (tokens[userId] >= 1.0) {
            tokens[userId] -= 1.0;
            return true;
        }
        return false;
    }
};

// Leaky Bucket Rate Limiter
class LeakyBucketRateLimiter : public RateLimiter {
    int capacity;
    long leakRateMillis;
    unordered_map<string, queue<long long>> buckets;
    unordered_map<string, long long> lastLeakTime;
    mutex mtx;

public:
    LeakyBucketRateLimiter(int cap, long leakRate)
        : capacity(cap), leakRateMillis(leakRate) {}

    bool allowRequest(const string& userId) override {
        lock_guard<mutex> lock(mtx);
        long long now = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        auto& bucket = buckets[userId];

        if (!lastLeakTime.count(userId)) {
            lastLeakTime[userId] = now;
        }

        while (!bucket.empty() && now - bucket.front() >= leakRateMillis) {
            bucket.pop();
        }

        if ((int)bucket.size() < capacity) {
            bucket.push(now);
            return true;
        }
        return false;
    }
};

// Factory
class RateLimiterFactory {
public:
    static shared_ptr<RateLimiter> createRateLimiter(const string& type, int maxRequests, long windowSizeSeconds) {
        long windowMillis = windowSizeSeconds * 1000;
        if (type == "fixed") {
            return make_shared<FixedWindowRateLimiter>(maxRequests, windowMillis);
        } else if (type == "sliding") {
            return make_shared<SlidingWindowRateLimiter>(maxRequests, windowMillis);
        } else if (type == "token-bucket") {
            double refillRate = (1.0 * maxRequests) / windowSizeSeconds;
            return make_shared<TokenBucketRateLimiter>(maxRequests, refillRate);
        } else if (type == "leaky-bucket") {
            long leakMillis = (long)((1.0 * windowSizeSeconds * 1000) / maxRequests);
            return make_shared<LeakyBucketRateLimiter>(maxRequests, leakMillis);
        } else {
            throw invalid_argument("Unknown rate limiter type");
        }
    }
};

// Service
class RateLimiterService {
    unordered_map<string, shared_ptr<RateLimiter>> userRateLimiters;

public:
    void registerUser(const string& userId, const string& type, int maxRequests, long windowSizeSeconds) {
        userRateLimiters[userId] = RateLimiterFactory::createRateLimiter(type, maxRequests, windowSizeSeconds);
    }

    bool allowRequest(const string& userId) {
        if (!userRateLimiters.count(userId)) throw invalid_argument("User not registered");
        return userRateLimiters[userId]->allowRequest(userId);
    }
};

// Main
int main() {
    RateLimiterService service;
    service.registerUser("user_1", "fixed", 5, 10);
    service.registerUser("user_2", "sliding", 3, 5);
    service.registerUser("user_3", "token-bucket", 5, 10);
    service.registerUser("user_4", "leaky-bucket", 3, 4);

    for (int i = 0; i < 7; i++) {
        cout << "User 1 Request " << i + 1 << " : " << service.allowRequest("user_1") << endl;
        cout << "User 2 Request " << i + 1 << " : " << service.allowRequest("user_2") << endl;
        cout << "User 3 Request " << i + 1 << " : " << service.allowRequest("user_3") << endl;
        cout << "User 4 Request " << i + 1 << " : " << service.allowRequest("user_4") << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }

    return 0;
}
