

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
