const express = require('express');
const router = express.Router();
const yhdistelma = require('../models/yhdistelma_model');

router.get('/:id?',
  function(request, response) {
    if (request.params.id) {
      yhdistelma.getById(request.params.id, function(err, dbResult) {
        if(err) {
          response.json(err);
        } else {
          response.json(dbResult)
        }
      });
    } 
  });

  module.exports = router;