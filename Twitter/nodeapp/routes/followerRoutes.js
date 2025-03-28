const express = require('express');
const router = express.Router();
const Follower = require('../models/Follower');

router.post('/', async (req, res) => {
  const { followerID, followeeID } = req.body;
  const follower = new Follower({ followerID, followeeID });

  await follower.save();
  res.json(follower);
});

router.get('/', async (req, res) => {
  const followers = await Follower.find();
  res.json(followers);
});

module.exports = router;
