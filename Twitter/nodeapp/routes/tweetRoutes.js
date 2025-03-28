const express = require('express');
const router = express.Router();
const Tweet = require('../models/Tweet');

router.post('/', async (req, res) => {
  const { userID, type, content } = req.body;
  const tweet = new Tweet({ userID, type, content });

  await tweet.save();
  res.json(tweet);
});

router.get('/', async (req, res) => {
  const tweets = await Tweet.find();
  res.json(tweets);
});

module.exports = router;
