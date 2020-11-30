
#ifndef METRONOME_HEADER_SEEN
#define METRONOME_HEADER_SEEN

// #ifdef __cplusplus
// extern "C" {
// #endif

#include <IntervalTimer.h>

extern volatile unsigned int g_pulse_count;

void setup_metronome(void);


// #ifdef __cplusplus
// }
// #endif

#endif // METRONOME_HEADER_SEEN