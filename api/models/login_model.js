const db = require('../database.js');

const login={
  checkPincode: function(idcard, callback) {
      return db.query('SELECT pinkoodi FROM kortti WHERE idkortti = ?',[idcard], callback); 
    }
};
          
module.exports = login;