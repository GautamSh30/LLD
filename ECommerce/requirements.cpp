/*

https://www.codekarle.com/system-design/Amazon-system-design.html
https://medium.com/@ibrahim.zananiri/design-amazon-e-commerce-system-7f2dd57637bb

### Functional Requirements
    - Should provide a search functionality with delivery ETA
    - Should provide a catalog of all products
    - Should provide Cart and Wishlist features
    - Should handle payment flow smoothly
    - Should provide a view for all previous orders

### Non Functional Requirements
    - Low latency
    - High availability
    - High consistency

### E-commerce Capacity Planning Estimations

    | Category                    | Count                        | Metadata Size  | Total Size   |
    |-----------------------------|-----------------------------|---------------|-------------|
    | Users                       | 301.5 million               | 10 KB/user    | ~2.8 TB     |
    | Customers                   | 300 million                 | 25 KB/customer| ~7 TB       |
    | Sellers                     | 1.5 million                 | 50 KB/seller  | ~71.5 GB    |
    | Products                    | 100 million                 | 100 KB/product| ~9.3 TB     |
    | Merchandisable Items (2x)    | 200 million                 | 10 KB/item    | ~2 TB       |
    | Orders (1m/day for a year)   | 365 million                 | 25 KB/order   | ~8.5 TB     |

    Total Estimated Data Size: ~29.67 TB

### Actual Interview

    - Requirements: 
        - Search
        - Recommendation
        - Place Order
        - Order Status
        - Product reviews

    - Ass umptions
        - user profile creation provided
        - product onboarding provided
        - payment service provided

    - NFR
        - low latency -> recommendation, search
        - high consistency -> placing order, order status, payments

    - Estimations
        - 300M monthly active users
        - 300M * 10 search => 1000 Search/sec

        - Total products = 10M
        - 1 Product - 10MB => 100 TB storage

*/
