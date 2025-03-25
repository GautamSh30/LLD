/*

## Traffic

1 billion total users with 200 million daily active users (DAU)
each user => 5 tweets/day => 1 billion tweets/day.
10% tweets are media files => additional 100 million files we would need to store.
1 billion requests per day => 12000 req/sec.


## Storage

each message => 100 bytes => 100 GB of database storage every day.
10% (100 million) are media files - each file is 50 KB => 5 TB/day.
10 years => 19 PB storage.


## Bandwidth

5.1 TB ingress/day => 60 MB per second.


## High-level estimate

 | Type                      | Estimate    |
 +---------------------------+-------------+
 | Daily active users (DAU)  | 100 million |
 | Requests per second (RPS) | 12K/s       |
 | Storage (per day)         | ~5.1 TB     |
 | Storage (10 years)        | ~19 PB      |
 | Bandwidth                 | ~60 MB/s    |

*/