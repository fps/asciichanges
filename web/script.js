var play = function() {
  console.log("play");
}

var stop = function() {
  console.log("stop");
}

var songarea;
var logarea;
var generatorarea;

window.onload = function() {
  console.log("yeah");

  songarea = document.getElementById("song");
  generatorarea = document.getElementById("generator");
  logarea = document.getElementById("log");
  
  var song = songarea.value;
  //console.log(song);
  
  logarea.value = logarea.value + JSON.stringify(pegjs.parse(song), null, 2);
  //console.log(JSON.stringify(pegjs.parse(song), null, 2));
  
  var ssong = {};
  ssong.songData = [
    {
      lfo_waveform: 0,
      lfo_amt: 0,
      lfo_osc1_freq: 0,
      lfo_osc2_freq: 0,
      osc1_waveform: 2,
      osc1_oct: 4,
      osc1_det: 0,
      osc1_detune: 0,
      osc1_vol: 4096,
      osc1_xenv: 0,
      osc2_waveform: 1,
      osc2_oct: 5,
      osc2_det: 0,
      osc2_detune: 0,
      osc2_vol: 4096,
      osc2_xenv: 0,
      noise_fader: 1,
      fx_resonance: 128,
      fx_filter: 2,
      fx_freq: 1000,
      fx_pan_amt: 0,
      fx_delay_time: 4,
      fx_delay_amt: 128,
      env_attack: 100,
      env_sustain: 1000,
      env_release: 1000,
      env_master: 1,
      fx_pan_freq: 16,
      lfo_freq: 16,
      p: [
        1
      ],
      c: [
        {
          n: [
            164,
            ,
            ,
            169,
            ,
            ,
            166,
            ,
            ,
            ,
            ,
            ,
            ,
            ,
            ,
            ,
            ,
            172,
            ,
            ,
            171,
            ,
            ,
            169,
            ,
            ,
            ,
            ,
            ,
            ,
            ,
            ,
            164,
            ,
          ]
        }
      ]
    }
  ];
  ssong.rowLen = 6615;
  ssong.songLen = 5;
  ssong.endPattern = 2;
  
  var songGen = new sonant(ssong);
  for (var t = 0; t < 1; t++)
      songGen.generate(t);
  var audio = songGen.createAudio();
  // audio.loop = true;
  audio.play();

}
