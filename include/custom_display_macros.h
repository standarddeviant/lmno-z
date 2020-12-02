#ifndef CUSTOM_DISPLAY_MACROS_HEADER_SEEN
#define CUSTOM_DISPLAY_MACROS_HEADER_SEEN

#include <menu.h>

/* make re-usable ArduinoMenu macros with specific choices/values/etc */
/*
FIELD(
    var.name, title, units,               // 0 --> 2
    min, max, step_size, fine_step_size,  // 3 --> 6
    action, event_mask, styles            // 7 --> 9
)

CHOOSE(
    var.name, id, title            // 0 --> 2
    ,action, event mask, styles,   // 3 --> 5
    ,value, ,value, [,value ...]   // 6 -->
)
*/


/* Rhythm Algo Choose */
#define RY_ALGO_CHOOSE(_var, _choose_name, _choose_str) \
CHOOSE(_var, _choose_name, _choose_str                  \
    ,doNothing, noEvent, noStyle                        \
    ,VALUE("Chr-U", 0, doNothing, noEvent)              \
    ,VALUE("Chr-L", 1, doNothing, noEvent)              \
    ,VALUE("FOLD",  2, doNothing, noEvent)              \
)                                                       \

#define RY_ALGO_PARAM(_var, _field_str, _unit_str, _min, _max, _lg_step, _sm_step) \
FIELD(_var, _field_str, _unit_str                       \
    ,_min, _max, _lg_step, _sm_step,                    \
    ,doNothing, noEvent, noStyle                        \
)                                                       \

#define RY_ALGO_LEN RY_ALGO_PARAM

/*
#define RY_ALGO_LEN(_var, _field_str, _unit_str, _min, _max, _lg_step, _sm_step) \
FIELD(_var, _field_str, _unit_str                       \
    ,_min, _max, _lg_step, _sm_step,                    \
    ,doNothing, noEvent, noStyle                        \
);                                                      \
*/

#endif /* CUSTOM_DISPLAY_MACROS_HEADER_SEEN */
