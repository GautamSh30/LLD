const express = require('express');
const mongoose = require('mongoose');
const dotenv = require('dotenv');

dotenv.config();
const app = express();
app.use(express.json());

const userRoutes = require('./routes/userRoutes');
const tweetRoutes = require('./routes/tweetRoutes');
const followerRoutes = require('./routes/followerRoutes');
const favoriteRoutes = require('./routes/favoriteRoutes');
const feedRoutes = require('./routes/feedRoutes');

app.use('/users', userRoutes);
app.use('/tweets', tweetRoutes);
app.use('/followers', followerRoutes);
app.use('/favorites', favoriteRoutes);
app.use('/feeds', feedRoutes);

mongoose.connect(process.env.MONGODB_URI, {})
  .then(() => console.log('MongoDB connected'))
  .catch(err => console.error(err));

module.exports = app;
