const express = require('express');
const router = express.Router();
const User = require('../models/User');

router.post('/', async (req, res) => {
  const { name, email, DOB } = req.body;
  const user = new User({ name, email, DOB });

  await user.save();
  res.json(user);
});

router.get('/', async (req, res) => {
  const users = await User.find();
  res.json(users);
});

module.exports = router;
