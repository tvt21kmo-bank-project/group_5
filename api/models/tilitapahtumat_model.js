const db = require('../database.js');

const tilitapahtumat = {
  getTapahtumat: function(id, callback) {
      return db.query('select * from tilitapahtumat where idkortti = ?', [id], callback);
    },
    add: function(tilitapahtumat, callback) {
      return db.query(
        'insert into tilitapahtumat (idtilitapahtumat,date,tapahtuma,summa, tili_idTili, idkortti) values(?,?,?,?,?,?)',
        [tilitapahtumat.idtilitapahtumat, tilitapahtumat.date, tilitapahtumat.tapahtuma, tilitapahtumat.summa, tilitapahtumat.tili_idTili, tilitapahtumat.idkortti],
        callback
      );
    },
    delete: function(id, callback) {
      return db.query('delete from tilitapahtumat where idtilitapahtumat=?', [id], callback);
    },
    update: function(id, tilitapahtumat, callback) {
      return db.query(
        'update tilitapahtumat set date=?, tapahtuma=?, summa=?, tili_idTili=?, idkortti=? where idtilitapahtumat=?',
        [tilitapahtumat.date, tilitapahtumat.tapahtuma, tilitapahtumat.summa, tilitapahtumat.tili_idTili, tilitapahtumat.idkortti, id],
        callback
      );
    }
  };
  module.exports = tilitapahtumat;