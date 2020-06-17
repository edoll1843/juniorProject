var express = require('express');
var router = express.Router();
var fs = require('fs');
/* GET users listing. */
router.get('/', function(req, res, next) {
  res.render('searchForm',{title: 'serch Form'});
});

router.get('/searchForm',function(req,res,next){

      });

module.exports = router;
