#ifndef AUDIO_OBJECTS_HEADER_SEEN
#define AUDIO_OBJECTS_HEADER_SEEN

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "rhythm.h"

#define NUM_DRUMS (3)

// GUItool: begin automatically generated code
extern AudioSynthSimpleDrum     drumKick;        //xy=796,136
extern AudioSynthSimpleDrum     drumSnare;       //xy=796,191
extern AudioSynthSimpleDrum     drumHiHat;       //xy=800,236
extern AudioEffectBitcrusher    bitcrusherSnare; //xy=955,190
extern AudioMixer4              mixerDrum;       //xy=1135,198
extern AudioMixer4              mixerMelody;     //xy=1150,354
extern AudioMixer4              mixerL;          //xy=1380,234
extern AudioMixer4              mixerR;          //xy=1385,322
extern AudioOutputI2S           i2sOut;          //xy=1690,263
extern AudioControlSGTL5000     sgtl5000_1;      //xy=1121,435
// GUItool: end automatically generated code


extern rhythm_t ryKick;
extern rhythm_t rySnare;
extern rhythm_t ryHiHat;

extern AudioSynthSimpleDrum *objDrumList[NUM_DRUMS];
extern rhythm_t *ryDrumList[NUM_DRUMS];

void setup_audio_objects(void);



#endif // AUDIO_OBJECTS_HEADER_SEEN
