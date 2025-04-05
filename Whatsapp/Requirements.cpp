/*

https://www.youtube.com/watch?v=cr6p0n0N-VA

- Functional Requirements
    - Start group chats
    - Send/receive messages
    - Send/receive media
    - Access messages after I've been offline

- Non Functional Requirements
    - Delivered with low latency < 500ms
    - Guarantee delivery messages
    - Billions of users, high throughput
    - Messages not stored unneccessarily
    - Fault Tolerant

- Core Entities
    - User
    - Chat
    - Messages
    - Client

-- Web Sockets / Polling / SSE / WebRTC

- API
    - Commands Sent                                 
        - createChat              newMessage                      
        - sendMessage             chatUpdate                      
        - createAttachment                                  
        - modifyParticipants         
        
- Estimations
    - 50M DAU
    - 10 message to 4 diff people => 2B req/day
    - 5% media files => 100M files/day extra 
    - 24K req/sec

- Storage
    - Each msg 100B, 2B * 100B => ~200GB/day
    - Media 100KB, 100M * 100KB => 10TB/day
    - For 10 years, Total storage = 38PB

- Bandwidth
    - 10.2TB/ day => 120MB/sec

*/