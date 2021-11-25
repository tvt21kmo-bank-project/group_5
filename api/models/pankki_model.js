const db = require('../database.js');

const pankki = {
  getDataTransfer: function(idkortti, callback) {
    return db.query('select idtili, idkortti from asiakas join kortti on asiakas.idasiakas = kortti.asiakas_idasiakas join tili on kortti.tili_idtili = tili.idtili where idkortti = ?', [idkortti], callback);
  },

  credit: function(pd, callback) {
    return db.query('call transfer_credit(?,?,?)', [pd.tilitunnus, pd.korttitunnus, pd.maara], callback);
  },

  debit: function(pd,callback) {
    return db.query('call transfer_debit(?,?,?)', [pd.tilitunnus, pd.korttitunnus, pd.maara], callback);
  }
};

module.exports = pankki;
