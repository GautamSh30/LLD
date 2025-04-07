/*

https://systemsdesign.cloud/SystemDesign/RateLimiter

# QPS
    - 100000 DAU
    - 50% uses daily => 50000 active users
    - 2 actions - page views, API calls => 100000 actions/session
    - avg session duration 30mins(1800 sec) => 55 QPS

# Rate limiter Config
    - 10 diff config for diff groups and resources

# Data Storage
    - rate limit database -> user/group id, resource id, limit, remaining tokens
    - Entry size = 100bytes
    - 100000 * 10 * 100 bytes/entry = 10GB

# Monitoring
    - Log entries -> Timestamp, user/group id, resource id, request timestamp, rate limit decision
    - Entry size = 500 bytes
    - 50 GB/sec

# Data Storage
    - Low latency apps with limited requirements -> in memory db
    - Efficient storage and retrieveal of large amounts of rate limit data -> key-value db
    - Complex config with specific needs -> relational db

*/