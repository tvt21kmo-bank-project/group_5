const express = require('express');
const router = express.Router();
const creditDebit = require('../models/creditdebit_model');

router.get('/:idkortti',
  function(req, res) {
    creditDebit.checkAccType(req.params.idkortti, function(dbError, dbResult) {
      if(dbError) {
        res.json(dbError);
        console.log("Tapahtui virhe!");
      } else {
        var tyyppi = dbResult[0].tilityyppi
        if(tyyppi === 'credit,debit') {
          res.send(true);
        } else {
          res.send(false);
        }
      }

});
});

module.exports = router;
