const mongoose = require('mongoose');
const { v4: uuidv4 } = require('uuid');

const followerSchema = new mongoose.Schema({
  id: { type: String, default: uuidv4, unique: true },
  followerID: { type: String, required: true },
  followeeID: { type: String, required: true }
});

module.exports = mongoose.model('Follower', followerSchema);
