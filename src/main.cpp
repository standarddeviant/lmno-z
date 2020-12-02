#include <Arduino.h>
#include <display_interface.h>
#include <metronome.h>
#include <rhythm.h>
#include <audio_objects.h>

void setup() {
    // put your setup code here, to run once:
    setup_display_interface();

    setup_audio_objects();
}

void loop() {
    static unsigned int loc_pulse_count = 0;
    unsigned int tmp_pulse_count;
    noInterrupts();
    tmp_pulse_count = g_pulse_count;
    interrupts();

    if(tmp_pulse_count != loc_pulse_count) {
        loc_pulse_count++;
        for(unsigned int ixDrum=0; ixDrum<NUM_DRUMS; ixDrum++) {
            uint8_t onset = rhythm_take(ryDrumList[ixDrum]);
            if(onset)
                objDrumList[ixDrum]->noteOn();
        } // end for(NUM_DRUMS...)
    } // 

    update_display_interface();

    // put your main code here, to run repeatedly:
}