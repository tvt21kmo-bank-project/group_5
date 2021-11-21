const db = require('../database.js');

const login = {
  checkID: function(idkortti, callback) {
      return db.query('select idkortti from kortti where idkortti = ?', [idkortti], callback);
    }
};

module.exports = login;
