// https://leetcode.com/problems/design-twitter/description/

#include <bits/stdc++.h>
using namespace std;

class Twitter {
    private:
        int time;
        unordered_map<int, unordered_set<int>> followers; // Stores followers
        unordered_map<int, vector<pair<int, int>>> Tweets; // Stores tweets (time, tweetId)
    public:
        Twitter() {
            time=0;
        }
        
        void postTweet(int userId, int tweetId) {
            Tweets[userId].emplace_back(time,tweetId);
            time++;
        }
        
        vector<int> getNewsFeed(int userId) {
            priority_queue<pair<int,int>> pq;
            for(auto i: Tweets[userId]) pq.push(i);
            for(auto i: followers[userId]){
                for(auto j: Tweets[i]) pq.push(j);
            }
            vector<int> feed;
            int count=10;
            while(!pq.empty() && count){
                feed.push_back(pq.top().second);
                pq.pop();
                count--;
            }
            return feed;
        }
        
        void follow(int followerId, int followeeId) {
            followers[followerId].insert(followeeId);
        }
        
        void unfollow(int followerId, int followeeId) {
            followers[followerId].erase(followeeId); 
        }
    };
    
/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */