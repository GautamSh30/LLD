#include <iostream>
#include <chrono>
#include <cmath>

using namespace std;
using namespace std::chrono;

const double MAX_BUCKET_SIZE = 3.0;
const int REFILL_RATE = 1; // tokens per second

class TokenBucket {
private:
    double currentBucketSize;
    long long lastRefillTimestamp; // in nanoseconds

    long long getCurrentTimeInNanoseconds() {
        return duration_cast<nanoseconds>(steady_clock::now().time_since_epoch()).count();
    }

    void refill() {
        long long nowTime = getCurrentTimeInNanoseconds();
        double tokensToAdd = ((nowTime - lastRefillTimestamp) / 1e9) * REFILL_RATE;
        currentBucketSize = min(currentBucketSize + tokensToAdd, MAX_BUCKET_SIZE);
        lastRefillTimestamp = nowTime;
    }

public:
    TokenBucket() {
        currentBucketSize = MAX_BUCKET_SIZE;
        lastRefillTimestamp = getCurrentTimeInNanoseconds();
    }

    bool allowRequest(double tokens) {
        refill();

        if (currentBucketSize >= tokens) {
            currentBucketSize -= tokens;
            return true;
        }

        return false;
    }
};

int main() {
    TokenBucket tb;

    cout << "Request processed: " << tb.allowRequest(1) << endl; // true
    cout << "Request processed: " << tb.allowRequest(1) << endl; // true
    cout << "Request processed: " << tb.allowRequest(1) << endl; // true
    cout << "Request processed: " << tb.allowRequest(1) << endl; // false, request dropped

    return 0;
}
