const express = require('express');
const router = express.Router();
const asiakastiedot = require('../models/asiakastiedot_model');

router.get('/:id?',
  function(request, response) {
    if (request.params.id) {
      asiakastiedot.getById(request.params.id, function(err, dbResult) {
        if(err) {
          response.json(err);
        } else {
          response.json(dbResult)
        }
      });
    } 
  });

  module.exports = router;