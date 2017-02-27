var songarea;
var logarea;
var generatorarea;

var music;

var play = function() {
  console.log("play");
}

var stop = function() {
  console.log("stop");
}

function el(id) {
  return document.getElementById(id);
}

window.onload = function() {
  console.log("yeah");

  music = music_init();
  
  songarea = el("song");
  generatorarea = el("generator");
  logarea = el("log");
  
  var song = songarea.value;
  //console.log(song);
  
  // logarea.value = logarea.value + JSON.stringify(asciichanges.parse(song), null, 2);
  // console.log(JSON.stringify(pegjs.parse(song), null, 2));
  
  el('play').onclick = function() {
    play();
  };
  
  el('stop').onclick = function() {
    stop();
  };
}
