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
        if(tila === 1) {
          res.send(true);
        } else if(tila === 0) {
          res.send(false);
        } else{
            res.send("korjaa koodi")
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
