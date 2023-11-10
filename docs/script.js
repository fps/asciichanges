
var music;

function el(id) {
  return document.getElementById(id);
}

function log(text) {
  console.log(text);
}

function play() {
  log('play');
  music = music_init(10);
}

function pause() {
  log('pause');
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

function evaluate() {
  log('evaluating');
  try {
    editor = el('editor');
    var selection = '';
    if (editor.selectionStart == editor.selectionEnd) {
      //log('equal ' + editor.selectionStart);
      var lines = editor.value.split('\n');
      var line = 0;
      var character = 0;
      for (; line < lines.length; ++line) {
        // log('line: ' + lines[line] + ' ' + character);
        character = character + lines[line].length + 1;
        if (character > editor.selectionStart) {
          break;
        }
      }
      log(lines[line]);
      selection = lines[line]
    }
    else {
      selection = editor.value.substr(editor.selectionStart, editor.selectionEnd - editor.selectionStart);
    }
    log('selection: ' + selection);
    console.log(asciichanges.parse(selection));
  } catch(error) {
    log(error.message);
  }
}

window.onload = function() {
  console.log("h");
  
  log('Everyone wants LOG!');

  music = music_init(10);
    
  el('play').onclick = function() {
    play();
  };

  el('pause').onclick = function() {
    pause();
  };

  el('stop').onclick = function() {
    stop();
  };
  
  
  document.onkeypress = function(event) {
    var code = event.which || event.keyCode;
    
    if (event.altKey && code == 13) {
      evaluate();
    }
  };
}
