const express = require('express');
const router = express.Router();
const creditDebit = require('../models/creditdebit_model');

router.get('/:idkortti',
  function(req, res) {
    creditDebit.checkAccType(req.params.idkortti, function(dbError, dbResult) {
      try {
      if(dbError) {
        res.json(dbError);
        console.log("Tapahtui virhe!");
      } else {
        let tyyppi = dbResult[0].tilityyppi
        if(tyyppi === 'credit,debit') {
          res.send(true);
        } else {
          res.send(false);
        }
      }
    } catch(e) {
      console.log("Does not exist");
      res.send("Does not exist");
    }

});
});

module.exports = router;
