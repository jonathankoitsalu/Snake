require('dotenv').config();
const express = require('express');
const mongoose = require('mongoose');
const APIKEY = process.env.APIKEY;

mongoose.connect(process.env.ATLASDB, {useNewUrlParser: true, useUnifiedTopology: true ,useFindAndModify:false})

/*
This creates the model for each database inside a Collection
highscore will have a name and a score which will be added at the end of each game
and speed will only have one item that will update whenever anyone use a button on the webpage

*/
const highScore = new mongoose.Schema({
    name: {
        type: String, 
        required:true
    },
    score:  {
        type: Number
    }
});

const speed = new mongoose.Schema({
    newspeed: {
        type: String, 
        required:true
    },
    what: {
        type: String
    }
});

const Speed = mongoose.model('speed', speed);
const Highscore = mongoose.model('item', highScore);

/*
 Create an object with express() and set its view enginge to EJS which is a template rendering engine
 Give the application access to the static folder for css files and images
 Use json and set urlencoded:extended to true for parsing data from database and requests
 */
const app = express();

app.set('view engine', 'ejs');
app.use(express.static('public'));
app.use(express.json());
app.use(express.urlencoded({
  extended: true
}));

/*
 * Renders index page
 */
app.get('/', function(req, res) {
    Highscore.find({}).sort({score : -1}).exec(function(err, highscores){
    res.render("highscore", {highscores: highscores});
    });
});

app.get('/conny', function(req, res) {
    Highscore.find({}).sort({score : -1}).exec(function(err, highscores){
    res.render("highscorec", {highscores: highscores});
    });
});

/*
 Returns a json object with a list of the 10 highest scores
*/
app.get('/gethighscore', function(req, res) {
    Highscore.find({}).sort({score : -1}).exec(function(err, highscores){
        var returndata = [];
        if (highscores.length >9){
            for(var i =0; i < 10; i++){
                returndata[i] = [highscores[i].name, highscores[i].score];    
            }
        }else{
            for(var i =0; i < highscores.length; i++){
                returndata[i] = [highscores[i].name, highscores[i].score];    
            } 
        }
        res.send(returndata);
    });
});

/*
Enables scores to be sent to database
*/
app.get('/score', function(req, res) {
    if(req.query.apikey==APIKEY){
        const highscore = new Highscore({
            name: req.query.name,
            score: req.query.score,
        })
        console.log(highscore.name)
        console.log(highscore.score)
        highscore.save(function(err){
            if(!err){
                res.send("Thank you for playing");
            }else{
                console.log(err)
            }
        })
    }
    else{
        res.send("<center><iframe width='560' height='315' src='https://www.youtube.com/embed/K3PrSj9XEu4' title='YouTube video player' frameborder='0' allow='accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture' allowfullscreen></iframe></center>");
    }
});

/*
Used by arduino to get the current speed variable from database
*/
app.get('/getspeed', function(req, res) {
    Speed.find({}).sort({score : -1}).exec(function(err, speed){
        console.log(speed[0].newspeed);
        var thespeed = speed[0].newspeed;
        res.send(thespeed);
    });
});

/*
Used by webpage to set the speed variable.
 */
app.get('/setspeed1', function(req, res){
    res.redirect('/setspeed?speed=1&apikey='+APIKEY);
});
app.get('/setspeed2', function(req, res){
    res.redirect('/setspeed?speed=2&apikey='+APIKEY);
});
app.get('/setspeed3', function(req, res){
    res.redirect('/setspeed?speed=3&apikey='+APIKEY);
});

/*
 API endpoint to actually change the speed variable in database
 updates a single post in db. 
 */
app.get('/setspeed', function(req, res) { 
    if(req.query.apikey==APIKEY){
    Speed.findOneAndUpdate({}, { newspeed: req.query.speed }, function(err, result) {
        if (err) {
          res.send(err);
        } else {
            res.redirect('/');
        }
      });
    }
    else{
        res.send("<center><iframe width='560' height='315' src='https://www.youtube.com/embed/K3PrSj9XEu4' title='YouTube video player' frameborder='0' allow='accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture' allowfullscreen></iframe></center>");
    }
});

/*
Start the app
 */
app.listen(process.env.PORT, function() {
    console.log("listening on port " + process.env.PORT);
})