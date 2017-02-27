function music_init() {
  ret = {};
  
  ret.audio_context = new AudioContext();
  ret.sample_rate = ret.audio_context.sampleRate;
  ret.script_node = ret.audio_context.createScriptProcessor(4096, 0, 2);
  ret.state = 'stopped';
  
  ret.script_node.onaudioprocess = function(audio_processing_event) {
    var output_buffer = audio_processing_event.outputBuffer;                                                                
    var number_of_samples = output_buffer.length;                                                                           
    var number_of_channels = output_buffer.numberOfChannels;                                                                
    var output_data = [null, null];                                                                                         
                                                                                                                            
    for (var channel = 0; channel < number_of_channels; ++channel) {                                                        
        output_data[channel] = output_buffer.getChannelData(channel);                                                       
    }                                                                                                                       
                                                                                                                            
    for (var sample = 0; sample < number_of_samples; ++sample) {                                                            
      for (var channel = 0; channel < number_of_channels; ++channel) {                                                    
            output_data[channel][sample] = 0;                                                                                                                      
      }                                                                                                                   
    }                                                                                                                       
  };
  ret.script_node.connect(ret.audio_context.destination);
  
  return ret;
}