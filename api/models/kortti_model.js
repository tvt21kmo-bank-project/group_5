const db = require('../database.js');
const bcrypt = require('bcryptjs');

const kortti = {
  getById: function(id, callback) {
    return db.query('select * from kortti where idkortti=?', [id], callback);
  },

  getAll: function(callback) {
    return db.query('select * from kortti', callback);
  },

  add: function(kortti, callback) {

    bcrypt.hash(kortti.pinkoodi,10,function(err,hash){
    return db.query(
      'insert into kortti (idkortti,pinkoodi,tili_idtili,asiakas_idasiakas) values(?,?,?,?)',
      [kortti.idkortti,hash,kortti.tili_idtili,kortti.asiakas_idasiakas],
      callback
    );});
  },

  delete: function(id, callback) {
    return db.query('delete from kortti where idkortti=?', [id], callback);
  },

  update: function(id, kortti, callback) {
    bcrypt.hash(kortti.pinkoodi,10,function(err,hash){
    return db.query('update kortti set pinkoodi=? where idkortti=?',
      [hash, id],callback);
    });
  }
}

module.exports = kortti;