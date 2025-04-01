/*

https://www.code-recipe.com/post/url-shortener-system-design

## Traffic Estimates

Total no. short URL generation requests per month = 100 million.

Therefore no. short URL requests per second = 100 million /(30 days * 24 hours * 3600 seconds ) ~ 40 URLs/sec.
Total short URL clicks or redirections per second (assuming 100:1 read to write ratio) = 40 URLs/sec * 100 = 4000 URLs/sec.


## Data Estimates

Most popular browsers support 2000 characters in a URL. So, lets say our long URL will at max take up to 2000 characters / 2KB.

Most URL shortener services create a short URL with 15-16 characters (We will see more on this later in our discussion). So we can say the short URL size is ~ 16 bytes.
Additionally we might need few more bytes to store metadata like creation timestamp, user details etc, lets say 50 bytes.

So, total storage needed per shortened URL ~ 2.1 KB.
Storage needed for 1 month = 2.1 KB * 100 million = 210 GB.
Storage needed for 1 year = 210 GB * 12 months ~ 2.5 TB. For 5 years this will be 12.5 TB.

*/