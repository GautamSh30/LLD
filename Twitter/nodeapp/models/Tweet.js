const mongoose = require('mongoose');
const { v4: uuidv4 } = require('uuid');

const tweetSchema = new mongoose.Schema({
  id: { type: String, default: uuidv4, unique: true },
  userID: { type: String, required: true },
  type: { type: String, enum: ['text', 'image', 'video'], required: true },
  content: { type: String, required: true },
  createdAt: { type: Date, default: Date.now }
});

module.exports = mongoose.model('Tweet', tweetSchema);
