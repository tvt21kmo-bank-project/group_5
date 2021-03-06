const express = require('express');
const router = express.Router();
const tilitapahtumat = require('../models/tilitapahtumat_model');


router.get('/:id',
 function(request, response) {
  if (request.params.id) {
    tilitapahtumat.getTapahtumat(request.params.id, function(err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    });
  }
});


router.post('/',
function(request, response) {
  tilitapahtumat.add(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(request.body);
    }
  });
});

router.post('/list_tilitapahtumat', function(req, res) {
  tilitapahtumat.tapahtumalista(req.body, function(err,dbResult) {
      if(err) {
        res.json(err);
      } else {
        console.log(dbResult[0]);
        res.json(dbResult[0]);
      //  console.log("Tilitapahtumalista tulostettu");
      }
  })
});


router.delete('/:id',
function(request, response) {
  tilitapahtumat.delete(request.params.id, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});


router.put('/:id',
function(request, response) {
  tilitapahtumat.update(request.params.id, request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

module.exports = router;
