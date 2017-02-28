
var music;

function el(id) {
  return document.getElementById(id);
}

function log(text) {
  var log = el('log');
  log.value = log.value + text + '\n';
  log.scrollTop = log.scrollHeight;
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
  
  log('Everyone wants LOG!');

  el('play').onclick = function() {
    play();
  };
  
  el('stop').onclick = function() {
    stop();
  };
  
  el('show_help').onclick = function() {
    var help = el('help_wrapper');
    if(help.style.display == 'none') {
      help.style.display = 'flex';
    }
    else {
      help.style.display = 'none';
    }
  }
}
