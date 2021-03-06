function music_init(number_of_voices) {
  ret = {};
  
  ret.audio_context = new AudioContext();
  ret.sample_rate = ret.audio_context.sampleRate;
  ret.buffer_size = 4096;
  ret.script_node = ret.audio_context.createScriptProcessor(ret.buffer_size, 0, 2);
  ret.seconds = 0;
  
  ret.voices = [];
  for (index = 0; index < number_of_voices; ++index)
  {
      console.log('creating voice ' + index);
      voice = {};
      // off = 0, on = 1
      voice.state = 0;
      voice.frequency = 440.0;
      voice.start_time = 0;
      voice.time_constant = 1.0;
      
      ret.voices.push(voice);
  }
  
  ret.fn = function(number_of_channels, number_of_samples, output_data) {
    for (var sample = 0; sample < number_of_samples; ++sample) {                                                            
      for (var channel = 0; channel < number_of_channels; ++channel) {                                                    
            output_data[channel][sample] = 0;                                                                                                                      
      }                                                                                                                   
    }                                                                                                                       
  };
  
  ret.script_node.onaudioprocess = function(audio_processing_event) {
    var output_buffer = audio_processing_event.outputBuffer;                                                                
    var number_of_samples = output_buffer.length;                                                                           
    var number_of_channels = output_buffer.numberOfChannels;                                                                
    var output_data = [null, null];                                                                                         
                                                                                                                            
    for (var channel = 0; channel < number_of_channels; ++channel) {                                                        
        output_data[channel] = output_buffer.getChannelData(channel);                                                       
    }                                                                                                                       
                                                                                                                        
    ret.fn(number_of_channels, number_of_samples, output_data);
    ret.seconds = ret.seconds + ret.buffer_size / ret.sample_rate;
  };
  ret.script_node.connect(ret.audio_context.destination);
  
  return ret;
}