const express = require('express');
const router = express.Router();
const luottoraja = require('../models/luottoraja_model');

router.get('/:id?',
  function(request, response) {
    if (request.params.id) {
      luottoraja.getById(request.params.id, function(err, dbResult) {
        if(err) {
          response.json(err);
        } else {
          response.json(dbResult)
        }
      });
    } 
  });

  module.exports = router;