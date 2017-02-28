var editorarea;
var logarea;
var generatorarea;

var music;

function el(id) {
  return document.getElementById(id);
}

function log(text) {
  logarea.value = logarea.value + text + '\n';
  logarea.scrollTop = logarea.scrollHeight;
}

function play() {
  log('play');
  music = music_init();
}

function stop() {
  log('stop');
  music.audio_context.close();
}

window.onload = function() {
  console.log("h");
  
  editorarea = el('editor');
  generatorarea = el('generator');
  logarea = el('log');
  
  log('Everyone wants LOG!');

  el('play').onclick = function() {
    play();
  };
  
  el('stop').onclick = function() {
    stop();
  };
}
