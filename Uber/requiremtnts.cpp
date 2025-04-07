/*

https://www.hellointerview.com/learn/system-design/problem-breakdowns/uber

# Entities
    - Rider, Driver, Fare, Location, Ride

# API
    - POST /fare -> Fare
        Body: {
            pickupLocation, 
            destination
        }
    - POST /rides -> Ride
        Body: {
            fareId
        }
    - POST /drivers/location -> Success/Error
        Body: {
                lat, long
        }
        driverId is present in the session cookie or JWT and not in the body or path params
    - PATCH /rides/:rideId -> Ride
        Body: {
            accept/deny
        }

# Estimation
    - 100M DAU + 1M drivers
    - 10M rides/day
    - 10 actions(rides,fares,book rides) => 1B req/day
    - 12K req/sec

    - Each message -> 400 bytes => 400 GB/day
    - 1.4 PB per year and 14 PB per 10 year

    - 400GB ingress/day => 4 MB/sec

    


*/