var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
const helmet = require('helmet');
const cors = require('cors');
var app = express();
const bcrypt = require('bcryptjs')

app.use(helmet());
app.use(cors());
const dotenv = require('dotenv');
dotenv.config();

const basicAuth = require('express-basic-auth');
app.use(basicAuth( {authorizer: myAuthorizer, authorizeAsync:true, }))

function myAuthorizer(username, password, cb) {
  if(username === process.env.authUser && password === process.env.authPass){
    return cb(null, true);
  } else {
    return cb(null, false);
  }
}

var indexRouter = require('./routes/index');
var usersRouter = require('./routes/users');
var asiakasRouter = require('./routes/asiakas');
var tiliRouter = require('./routes/tili');
var korttiRouter = require('./routes/kortti');
var loginIDRouter = require('./routes/loginID');
var loginRouter = require('./routes/login');
var creditdebitRouter = require('./routes/creditdebit');

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', indexRouter);
app.use('/users', usersRouter);
app.use('/asiakas', asiakasRouter);
app.use('/tili', tiliRouter);
app.use('/kortti', korttiRouter);
app.use('/loginID', loginIDRouter);
app.use('/login', loginRouter);
app.use('/creditdebit', creditdebitRouter);

module.exports = app;
