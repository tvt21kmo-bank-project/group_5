const db = require('../database.js');

const credeb = {
  checkAccType: function(acctype, callback) {
    return db.query('select tilityyppi from tili inner join kortti on kortti.idkortti = tili.idtili where idkortti = ?', [acctype], callback);
  }
};

module.exports = credeb;
