#include <iostream>
#include <queue>
#include <thread>
#include <chrono>

using namespace std;

int main() {
    int bucketSize = 5;
    int outflowRate = 2; // requests per second
    queue<int> bucket;

    // Simulate 10 incoming requests
    for (int time = 1; time <= 10; ++time) {
        cout << "\nTime: " << time << "s\n";

        // Incoming request
        if (bucket.size() < bucketSize) {
            bucket.push(time);
            cout << "Request " << time << " added to the bucket.\n";
        } else {
            cout << "Request " << time << " dropped (Bucket Full).\n";
        }

        // Leak (process requests at outflowRate)
        for (int i = 0; i < outflowRate && !bucket.empty(); ++i) {
            cout << "Processing request: " << bucket.front() << endl;
            bucket.pop();
        }

        // Wait for 1 second
        this_thread::sleep_for(chrono::seconds(1));
    }

    // Process remaining requests in bucket
    cout << "\nProcessing remaining requests...\n";
    while (!bucket.empty()) {
        cout << "Processing request: " << bucket.front() << endl;
        bucket.pop();
        this_thread::sleep_for(chrono::seconds(1));
    }

    return 0;
}
