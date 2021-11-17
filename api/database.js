const mysql = require('mysql');
const connection = mysql.createPool(process.env.SQL_SERVER);
module.exports = connection;
