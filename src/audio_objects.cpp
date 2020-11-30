

#include "audio_objects.h"

// GUItool: begin automatically generated code
AudioSynthSimpleDrum     drumKick;         //xy=796,136
AudioSynthSimpleDrum     drumSnare;        //xy=796,191
AudioSynthSimpleDrum     drumHiHat;        //xy=800,236
AudioEffectBitcrusher    bitcrusherSnare;  //xy=955,190
AudioMixer4              mixerDrumA;       //xy=1135,198
AudioMixer4              mixerMelody;      //xy=1150,354
AudioMixer4              mixerL;           //xy=1380,234
AudioMixer4              mixerR;           //xy=1385,322
AudioOutputI2S           i2sOut;           //xy=1690,263

// 3 drums
AudioConnection          patchCordD1(drumKick,        0, mixerDrumA, 0);
AudioConnection          patchCordD2(drumSnare,       0, bitcrusherSnare, 0);
AudioConnection          patchCordD3(bitcrusherSnare, 0, mixerDrumA, 1);
AudioConnection          patchCordD4(drumHiHat,       0, mixerDrumA, 2);

// inter-mixer
AudioConnection          patchCordM1(mixerDrumA,   0, mixerL, 0);
AudioConnection          patchCordM2(mixerDrumA,   0, mixerR, 0);
AudioConnection          patchCordM4(mixerMelody, 0, mixerL, 1);
AudioConnection          patchCordM3(mixerMelody, 0, mixerR, 1);

// output-mixer
AudioConnection          patchCordM5(mixerL,      0, i2sOut, 0);
AudioConnection          patchCordM6(mixerR,      0, i2sOut, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1121,435
// GUItool: end automatically generated code

#define NUM_DRUMS (3)
AudioSynthSimpleDrum *objDrumList[NUM_DRUMS] {&drumKick, &drumSnare, &drumHiHat};
rhythm_t ryKick;
rhythm_t rySnare;
rhythm_t ryHiHat;
rhythm_t *ryDrumList[NUM_DRUMS] = {&ryKick, &rySnare, &ryHiHat};
rhythm_set_t ryDrums = {
    .reset = 64,               // uint16_t
    .reset_count = 0,          // uint16_t
    .num_rhythms = NUM_DRUMS,  // uint16_t
    ._reserved   = 0,          // uint16_t
    .rhythms = &(ryDrumList[0])
};

#define DELAY_LINE_NSAMP (AUDIO_BLOCK_SAMPLES*4)
short stringDelayLine[DELAY_LINE_NSAMP] = {0};
// short delayLineR[DELAY_LINE_NSAMP] = {0};


void setup_audio_objects(void) {
    unsigned char ixDrum;
    AudioSynthSimpleDrum *objDrum;
    AudioMemory(18);

    // set initial volume to -12dB
    sgtl5000_1.enable();
    sgtl5000_1.volume(0.5f);

    // TODO - move to rhythm_init, separate frome ventual melody_init
    // drum setup
    ixDrum = 0; // kick-drum
    objDrum = objDrumList[ixDrum];
    objDrum->frequency(55.0f);
    objDrum->length(200);
    objDrum->secondMix(0.3f);
    objDrum->pitchMod(0.6f);

    ixDrum = 1; // snare-drum
    objDrum = objDrumList[ixDrum];
    objDrum->frequency(300.0f);
    objDrum->length(80);
    objDrum->secondMix(0.3f);
    objDrum->pitchMod(0.45f);
    bitcrusherSnare.bits(8);
    bitcrusherSnare.sampleRate(1500.0f);
    // eubit_init(&eubitSnare, 32, 5, 0);

    ixDrum = 2; // "hi-hat"
    objDrum = objDrumList[ixDrum];
    objDrum->frequency(800.0f);
    objDrum->length(50);
    objDrum->secondMix(0.7f);
    objDrum->pitchMod(0.5f);
    // eubit_init(&eubitHiHat, 64, 15, 0);

    mixerDrumA.gain(0, 1.000f);
    mixerDrumA.gain(1, 0.500f);
    mixerDrumA.gain(2, 0.400f);

    // stringChorus.begin(stringDelayLine, DELAY_LINE_NSAMP, 1);
    // eubit_init(&eubitString, 24, 7, 7);
    // mixerMelody.gain(0, 0.6);
    // chorusL.begin(delayLineL, DELAY_LINE_NSAMP, 4);
    // chorusR.begin(delayLineL, DELAY_LINE_NSAMP, 4);
}
