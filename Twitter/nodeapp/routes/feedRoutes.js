const express = require('express');
const router = express.Router();
const Feed = require('../models/Feed');

router.post('/', async (req, res) => {
  const { userID } = req.body;
  const feed = new Feed({ userID });

  await feed.save();
  res.json(feed);
});

router.get('/', async (req, res) => {
  const feeds = await Feed.find();
  res.json(feeds);
});

module.exports = router;
