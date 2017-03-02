
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

function getSelectionHtml() {
  var html = "";
  if (typeof window.getSelection != "undefined") {
    var sel = window.getSelection();
    if (sel.rangeCount) {
      var container = document.createElement("div");
      for (var i = 0, len = sel.rangeCount; i < len; ++i) {
          container.appendChild(sel.getRangeAt(i).cloneContents());
      }
      html = container.innerHTML;
    }
  } 
  else if (typeof document.selection != "undefined") {
    if (document.selection.type == "Text") {
        html = document.selection.createRange().htmlText;
    }
  }
  return html;
}

function eval() {
  log('evaluating');
  try {
    selection = getSelectionHtml();
    log(selection);
   // eval(selection);
  } catch(error) {
    // log(error.message);
  }
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
  
  
  document.onkeypress = function(event) {
    var code = event.which || event.keyCode;
    
    if (event.altKey && code == 13) {
      eval();
    }
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
