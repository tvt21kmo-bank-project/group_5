const db = require('../database.js');

const asiakas = {
  getById: function(id, callback) {
    return db.query('select * from asiakas where idasiakas=?', [id], callback);
  },

  getAll: function(callback) {
    return db.query('select * from asiakas', callback);
  },

  add: function(asiakas, callback) {
    return db.query(
      'insert into asiakas (etunimi_asiakas,sukunimi_asiakas,osoite_asiakas,puhelin_asiakas) values(?,?,?,?)',
      [asiakas.etunimi_asiakas, asiakas.sukunimi_asiakas, asiakas.osoite_asiakas, asiakas.puhelin_asiakas],
      callback
    );
  },

  delete: function(id, callback) {
    return db.query('delete from asiakas where idasiakas=?', [id], callback);
  },

  update: function(id, asiakas, callback) {
    return db.query(
      'update asiakas set etunimi_asiakas=?, sukunimi_asiakas=?, osoite_asiakas=?, puhelin_asiakas=? where idasiakas=?',
      [asiakas.etunimi_asiakas, asiakas.sukunimi_asiakas, asiakas.osoite_asiakas, asiakas.puhelin_asiakas, id],
      callback
    );
  }
};

module.exports = asiakas;
