const express = require('express');
const router = express.Router();
const Favorite = require('../models/Favorite');

router.post('/', async (req, res) => {
  const { userID, tweetID } = req.body;
  const favorite = new Favorite({ userID, tweetID });

  await favorite.save();
  res.json(favorite);
});

router.get('/', async (req, res) => {
  const favorites = await Favorite.find();
  res.json(favorites);
});

module.exports = router;
