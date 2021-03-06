#include <Arduino.h>
#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <menu.h>
#include <menuIO/serialIn.h>
#include <menuIO/serialOut.h>
#include <menuIO/adafruitGfxOut.h>
#include <menuIO/encoderIn.h>
#include <menuIO/keyIn.h>
#include <menuIO/chainStream.h>

#include <custom_display_macros.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define OLED_I2C_ADDR 0x3C

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 gfx(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define LEDPIN A3

// rotary encoder pins
#define encA    2
#define encB    3
#define encBtn  4

result showEvent(eventMask e,navNode& nav,prompt& item) {
    Serial.print(F("event:"));
    Serial.print(e);
    return proceed;
}

int test=55;
int ledCtrl=LOW;

result myLedOn() {
    ledCtrl=HIGH;
    return proceed;
}
result myLedOff() {
    ledCtrl=LOW;
    return proceed;
}

result alert(menuOut& o,idleEvent e);
result doAlert(eventMask e, prompt &item);

// TOGGLE(ledCtrl,setLed,"Led: ",doNothing,noEvent,noStyle//,doExit,enterEvent,noStyle
//     ,VALUE("On",HIGH,doNothing,noEvent)
//     ,VALUE("Off",LOW,doNothing,noEvent)
// );


const char* constMEM hexDigit MEMMODE="0123456789ABCDEF";
const char* constMEM hexNr[] MEMMODE={"0","x",hexDigit,hexDigit};
char buf1[]="0x11";


/* TODO can these vars be referenced directly from a struct?
        i.e. - does the underlying CHOOSE macro use a pointer? */
int ryKickAlgo=0;
int ryKickAlgoLen=0;
int ryKickAlgoP1=0;
int ryKickAlgoP2=0;
RY_ALGO_CHOOSE(ryKickAlgo, ryKickAlgoChoose, "algo");
// RY_ALGO_CHOOSE(ryKickAlgo, ryKickAlgoChoose, "algo");
// RY_ALGO_LEN(ryKickAlgoLen, "len", "", 1, 256, 4, 1)
// RY_ALGO_PARAM(ryKickAlgoP1, "p1", "", 0, 256, 4, 1)
// RY_ALGO_PARAM(ryKickAlgoP2, "p2", "", 0, 256, 4, 1)
// RY_ALGO_NUMINT(ryKickAlgoP0, ryKickAlgoParam0)
// MENU(ryKickMenu,"Kick Rhythm")
MENU(ryDrumMenu, "Drum Rhythms", doNothing, noEvent, wrapStyle
    ,SUBMENU(ryKickAlgoChoose)
    ,FIELD(ryKickAlgoLen,"len", ""
        ,1, 256, 4, 1
        ,doNothing, noEvent, wrapStyle)
    ,FIELD(ryKickAlgoP1,"len", ""
        ,1, 256, 4, 1
        ,doNothing, noEvent, wrapStyle)
    ,FIELD(ryKickAlgoP2,"len", ""
        ,1, 256, 4, 1
        ,doNothing, noEvent, wrapStyle)
    ,EXIT("<Back")
);

MENU(mainMenu,"Main menu",doNothing,noEvent,wrapStyle
    ,SUBMENU(ryDrumMenu)
    // ,SUBMENU(setLed)
    // ,OP("LED On",myLedOn,enterEvent)
    // ,OP("LED Off",myLedOff,enterEvent)
    // ,OP("Alert test",doAlert,enterEvent)
    // ,EDIT("Hex",buf1,hexNr,doNothing,noEvent,noStyle)
    ,EXIT("<Back")
);

// define menu colors --------------------------------------------------------
//  {{disabled normal,disabled selected},{enabled normal,enabled selected, enabled editing}}
//monochromatic color table
const colorDef<uint16_t> colors[6] MEMMODE={
    {{WHITE,BLACK},{WHITE,BLACK,BLACK}},//bgColor
    {{BLACK,WHITE},{BLACK,WHITE,WHITE}},//fgColor
    {{BLACK,WHITE},{BLACK,WHITE,WHITE}},//valColor
    {{BLACK,WHITE},{BLACK,WHITE,WHITE}},//unitColor
    {{BLACK,WHITE},{WHITE,WHITE,WHITE}},//cursorColor
    {{BLACK,WHITE},{WHITE,BLACK,BLACK}},//titleColor
};

#define gfxWidth 128
#define gfxHeight 64
#define fontX 6
//5
#define fontY 9
#define MAX_DEPTH 5

encoderIn<encA,encB> encoder;//simple quad encoder driver
encoderInStream<encA,encB> encStream(encoder,4);// simple quad encoder fake Stream

//a keyboard with only one key as the encoder button
keyMap encBtn_map[]={{-encBtn,defaultNavCodes[enterCmd].ch}};//negative pin numbers use internal pull-up, this is on when low
keyIn<1> encButton(encBtn_map);//1 is the number of keys

serialIn serial(Serial);
MENU_INPUTS(in,&encStream,&encButton,&serial);

#define textScale 1
MENU_OUTPUTS(out,MAX_DEPTH
    ,ADAGFX_OUT(gfx,colors,fontX,fontY,{0,0,gfxWidth/fontX,gfxHeight/fontY})
    ,SERIAL_OUT(Serial)
);

NAVROOT(nav,mainMenu,MAX_DEPTH,in,out);

result alert(menuOut& o,idleEvent e) {
    if (e==idling) {
        o.setCursor(0,0);
        o.print(F("alert test"));
        o.setCursor(0,1);
        o.print(F("press [select]"));
        o.setCursor(0,2);
        o.print(F("to continue..."));
    }
    return proceed;
}

result doAlert(eventMask e, prompt &item) {
    nav.idleOn(alert);
    return proceed;
}

//when menu is suspended
result idle(menuOut& o,idleEvent e) {
    // o.setCursor(0,0);    
    // o.print(F("suspended..."));
    // o.setCursor(0,1);
    // o.print(F("press [select]"));
    // o.setCursor(0,2);
    // o.print(F("to continue"));
    return proceed;
}

void setup_display_interface(void) {
    pinMode(LEDPIN,OUTPUT);
    Serial.begin(115200);
    while(!Serial);
    Serial.println(F("menu 4.x test"));
    Serial.flush();
    nav.idleTask=idle;//point a function to be used when menu is suspended

    SPI.begin();


    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!gfx.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDR)) { // Address for 128x64
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }
    delay(2000);

    encButton.begin();
    encoder.begin();

    gfx.clearDisplay();
    gfx.println(F("Menu 4.x test on GFX"));
    // gfx.setContrast(50);
    gfx.display(); // show splashscreen
    delay(2000);
    gfx.clearDisplay();
    gfx.display(); // show splashscreen
    // gfx.drawRect(0, 0, 84, 48, 1);
}

void update_display_interface(void) {
    nav.doInput();
    if(nav.changed(0)) {
        nav.doOutput();
        gfx.display();
    }
}

