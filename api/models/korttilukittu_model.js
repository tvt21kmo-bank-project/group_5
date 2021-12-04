const db = require('../database.js');

const korttilukittu = {
  checkKorttilukko: function(id, callback) {
    return db.query('select korttilukittu from kortti where idkortti=?', [id], callback);
  },

  update: function(id, kortti, callback) {
    return db.query(
      'update kortti set korttilukittu=? where idkortti=?',
      [kortti.korttilukittu,id],
      callback
    );
  }
};

module.exports = korttilukittu;
