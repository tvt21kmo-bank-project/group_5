const express = require('express');
const router = express.Router();
const korttityyppi = require('../models/creditdebit_model');

router.get('/:idkortti',
  function(req, res) {
    korttityyppi.checkAccType(req.params.idkortti, function(dbError, dbResult) {
      try {
      if(dbError) {
        res.json(dbError);
        console.log("Tapahtui virhe!");
      } else {
        let tyyppi = dbResult[0].tilityyppi
        if(tyyppi === 'credit,debit') {
          res.send('yhdistelma');
        } else if (tyyppi === 'credit'){
          res.send('credit');
        } else if (tyyppi === 'debit'){
          res.send('debit');
        }
      }
      
    } catch(e) {
      console.log("Does not exist");
      res.send("Does not exist");
    }

});
});

module.exports = router;

