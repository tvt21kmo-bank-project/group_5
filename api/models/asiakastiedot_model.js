const db = require('../database.js');

const asiakastiedot = {
    getById: function(id, callback) {
      return db.query('select etunimi_asiakas,sukunimi_asiakas from asiakas join kortti on asiakas.idasiakas=kortti.asiakas_idasiakas join tili on tili.idtili=kortti.tili_idtili where idkortti=?', [id], callback);
    }
}

module.exports = asiakastiedot;