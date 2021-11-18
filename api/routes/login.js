const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const login = require('../models/login_model.js');

router.post('/', 
  function(request, response) {
    if(request.body.idcard && request.body.pincode){
      const idcard = request.body.idcard;
      const pincode = request.body.pincode;
        login.checkPincode(idcard, function(dbError, dbResult) {
          if(dbError){
            response.json(dbError);
          }
          else{
              if (dbResult.length > 0) {
                bcrypt.compare(pincode,dbResult[0].pinkoodi, function(err,compareResult) {
                  if(compareResult) {
                    console.log("success");
                    response.send(true);
                }
                else {
                    console.log("wrong password");
                    response.send(false);
                }			
              }
              );
            }
            else{
              console.log("user does not exsist");
              response.send(false);
            }
          }
          }
        );
      }
    else{
      console.log("username or password missing");
      response.send(false);
    }
  }
);

module.exports=router;