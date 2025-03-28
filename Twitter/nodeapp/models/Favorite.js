const mongoose = require('mongoose');
const { v4: uuidv4 } = require('uuid');

const favoriteSchema = new mongoose.Schema({
  id: { type: String, default: uuidv4, unique: true },
  userID: { type: String, required: true },
  tweetID: { type: String, required: true },
  createdAt: { type: Date, default: Date.now }
});

module.exports = mongoose.model('Favorite', favoriteSchema);
