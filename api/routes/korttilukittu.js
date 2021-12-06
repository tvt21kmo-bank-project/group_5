const express = require('express');
const router = express.Router();
const korttiLukko = require('../models/korttilukittu_model');

router.get('/:idkortti',
  function(req, res) {
    korttiLukko.checkKorttilukko(req.params.idkortti, function(dbError, dbResult) {
      try {
      if(dbError) {
        res.json(dbError);
        console.log("Tapahtui virhe!");
      } else {
        let tila = dbResult[0].korttilukittu
        if(tila === 3) {
          res.send('3');
        } else {
            if(tila === 2) {
              res.send('2');
            } else if(tila === 1) {
              res.send('1');
            } else if(tila === 0) {
              res.send('0');
            } else {
              res.send("Does not exist")
            }
        }

      }
    } catch(e) {
      console.log("Does not exist");
      res.send("Does not exist");
    }

});
});

router.put('/:id',
function(request, response) {
  korttiLukko.update(request.params.id, request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});


module.exports = router;
