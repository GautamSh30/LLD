const mongoose = require('mongoose');
const { v4: uuidv4 } = require('uuid');

const feedSchema = new mongoose.Schema({
  id: { type: String, default: uuidv4, unique: true },
  userID: { type: String, required: true },
  updatedAt: { type: Date, default: Date.now }
});

module.exports = mongoose.model('Feed', feedSchema);
