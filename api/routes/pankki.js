const express = require('express');
const router = express.Router();
const pankki = require('../models/pankki_model');

router.get('/:idkortti',
function(req, res) {
  pankki.getDataTransfer(req.params.idkortti, function(dbError,dbResult) {
    try {
      if(dbError) {
        res.send("Haussa tapahtui virhe");
      } else {
        if(dbResult.length > 0) {
          res.json(dbResult);
        } else {
          res.json(dbError);
        }
      }
    } catch(e) {
      console.log("Tapahtui virhe");
      res.send("Tapahtui virhe");
    }
  })
});

router.post('/transfer_credit', function(req, res) {
  pankki.credit(req.body, function(err, dbResult) {
    if(err) {
      res.json(err);
    } else {
      res.json(dbResult.affectedRows);
      console.log("Credit nosto");
    }
  })
});

router.post('/transfer_debit', function(req, res) {
  pankki.debit(req.body, function(err, dbResult) {
    if(err) {
      res.json(err);
    } else {
      res.json(dbResult.affectedRows);
      console.log("Debit nosto");
    }
  })
});

module.exports = router;
