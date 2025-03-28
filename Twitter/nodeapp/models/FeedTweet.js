const mongoose = require('mongoose');
const { v4: uuidv4 } = require('uuid');

const feedTweetSchema = new mongoose.Schema({
  id: { type: String, default: uuidv4, unique: true },
  tweetID: { type: String, required: true },
  feedID: { type: String, required: true }
});

module.exports = mongoose.model('FeedTweet', feedTweetSchema);
