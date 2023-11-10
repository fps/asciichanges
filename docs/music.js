function music_init(number_of_voices) {
  ret = {};
  
  ret.audio_context = new AudioContext();
  ret.sample_rate = ret.audio_context.sampleRate;
  console.log('sample rate: ' + ret.sample_rate);
  ret.seconds = 0;
  
  ret.voices = [];
  for (index = 0; index < number_of_voices; ++index)
  {
      console.log('creating voice ' + index);
      voice = {};

      voice.oscillator = new OscillatorNode(ret.audio_context);
      voice.gain = new GainNode(ret.audio_context);
      voice.oscillator.connect(voice.gain);
      voice.gain.connect(ret.audio_context.destination);
      
      ret.voices.push(voice);
  }

  return ret;
}
