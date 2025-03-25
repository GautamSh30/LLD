#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

class URLShortener {
private:
    unordered_map<string, string> keyToUrl;
    unordered_map<string, string> urlToKey;
    string elements;
    int counter;

public:
    URLShortener() {
        elements = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        counter = 1;
    }

    // Function to convert decimal to base62
    string convertDecimalToBase62(int num) {
        string result;
        while (num > 0) {
            result = elements[num % 62] + result;
            num /= 62;
        }
        return result.empty() ? "0" : result;
    }

    // Function to convert base62 to decimal
    int convertBase62ToDecimal(const string& str) {
        int result = 0;
        for (char ch : str) {
            if ('a' <= ch && ch <= 'z')
                result = result * 62 + (ch - 'a');
            else if ('A' <= ch && ch <= 'Z')
                result = result * 62 + (ch - 'A' + 26);
            else if ('0' <= ch && ch <= '9')
                result = result * 62 + (ch - '0' + 52);
        }
        return result;
    }

    // Function to create a short URL
    string createShortURL(const string& longUrl) {
        if (urlToKey.find(longUrl) != urlToKey.end()) {
            return "tinyurl.com/" + urlToKey[longUrl];
        }

        string shortKey = convertDecimalToBase62(counter);
        urlToKey[longUrl] = shortKey;
        keyToUrl[shortKey] = longUrl;
        counter++;
        
        return "tinyurl.com/" + shortKey;
    }

    // Function to get the original URL
    string getLongURL(const string& shortUrl) {
        string shortKey = shortUrl.substr(shortUrl.find_last_of('/') + 1);
        if (keyToUrl.find(shortKey) != keyToUrl.end()) {
            return keyToUrl[shortKey];
        }
        return "URL not found";
    }
};

int main() {
    URLShortener urlShortener;

    // Test cases
    string longUrl1 = "https://www.example.com/page1";
    string longUrl2 = "https://www.github.com";
    
    string shortUrl1 = urlShortener.createShortURL(longUrl1);
    string shortUrl2 = urlShortener.createShortURL(longUrl2);

    cout << "Shortened URL 1: " << shortUrl1 << endl;
    cout << "Shortened URL 2: " << shortUrl2 << endl;

    cout << "Original URL 1: " << urlShortener.getLongURL(shortUrl1) << endl;
    cout << "Original URL 2: " << urlShortener.getLongURL(shortUrl2) << endl;

    return 0;
}
