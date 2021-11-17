const db = require('../database.js');

const tili = {
  getById: function(id, callback) {
    return db.query('select * from tili where idtili=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from tili', callback);
  },
  add: function(tili, callback) {
    return db.query(
      'insert into tili (idtili,saldo,idomistaja,tilityyppi, luottoraja) values(?,?,?,?,?)',
      [tili.idtili, tili.saldo, tili.idomistaja, tili.tilityyppi, tili.luottoraja],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from tili where idtili=?', [id], callback);
  },
  update: function(id, tili, callback) {
    return db.query(
      'update tili set saldo=?, idomistaja=?, tilityyppi=?, luottoraja=? where idtili=?',
      [tili.saldo, tili.idomistaja, tili.tilityyppi, tili.luottoraja, id],
      callback
    );
  }
};
module.exports = tili;