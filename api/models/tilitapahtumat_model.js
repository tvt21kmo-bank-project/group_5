const db = require('../database.js');

const tilitapahtumat = {
  getTapahtumat: function(id, callback) {
      return db.query('select etunimi_asiakas, sukunimi_asiakas, summa, tapahtuma, date, idomistaja, idtili from tilitapahtumat left join tili on tilitapahtumat.tili_idTili=tili.idtili left join kortti on tili.idtili=kortti.tili_idtili left join asiakas on kortti.asiakas_idasiakas=asiakas.idasiakas where kortti.idkortti=?', [id], callback);
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