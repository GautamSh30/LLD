/*

https://www.youtube.com/watch?v=E-KW1O3hLSg

1. User DB - SQL
    UserId : PK
    UserName: String
    Password: String Encrypted
    FirstName: String
    LastName: String
    Email: String
    LastLogin: DTTM
    Created: DTTM

2. Address DB - SQL
    AddressID : PK
    UserId: FK
    EffectiveDate: Date
    AddressType: String(billing/home/office)
    AddressLine1: String
    AddressLine2: String
    Country: String
    Zip: Alphanumeric

3. Product DB - NoSQL(MongoDB)

4. Order DB - NoSQL(MongoDB)

5. Review DB - NoSQL(Key-Value DB)


*/