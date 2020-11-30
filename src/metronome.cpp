

#include <metronome.h>


IntervalTimer g_metronome;
volatile unsigned int g_pulse_tick = 0;
volatile float g_tempo_bpm = 100.0f;
volatile unsigned int g_meas_len = 4;
volatile unsigned int g_beat_div = 4;

#define PULSE_MICROS() (1000000.0f / g_tempo_bpm / g_beat_div * 60.0f)
volatile unsigned int g_pulse_micros = PULSE_MICROS();

volatile unsigned int g_pulse_count = 0;
void metronome_isr(void) {
    g_pulse_count++;
}

void setup_metronome(void) {
    g_metronome.begin(metronome_isr, g_pulse_micros);
}

void set_tempo_bpm(float in_tempo_bpm) {
    g_tempo_bpm = in_tempo_bpm;
    g_pulse_micros = PULSE_MICROS();
    g_metronome.update(g_pulse_micros);
}
