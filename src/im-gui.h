
#include "gui.h"

extern GUI* static_gui;
extern VulkanBase* app;
extern object* user;
extern object* config;
extern char*   userUID;


extern unsigned char* fontData;
extern int texWidth, texHeight;

extern bool keyboardCancelled;

extern uint16_t buttonHeight;
extern uint16_t paddingHeight;
extern uint16_t objectHeight;
extern uint16_t listHeight;

extern uint16_t shorterValWidth;
extern uint16_t buttonWidth;
extern uint16_t smallButtonWidth;
extern uint16_t rhsPadding;

extern uint16_t workspace1Width;
extern uint16_t workspace1Height;
extern uint16_t workspace2Width;
extern uint16_t workspace2Height;

#if defined(__ANDROID__) || defined(TEST_ANDROID_KEYBOARD)
extern uint16_t yOffsetTarget;
extern uint16_t yOffset;
extern uint16_t yOffsetCounter;
#endif

extern bool calendarView;
extern bool tableView;

extern ImVec4 actionColour;
extern ImVec4 actionBackground;
extern ImVec4 actionBackgroundActive;

extern ImVec4 propertyColour;
extern ImVec4 propertyBackground;
extern ImVec4 propertyBackgroundActive;

extern ImVec4 valueBackground;
extern ImVec4 valueBackgroundActive;

extern ImVec4 listBackground;
extern ImVec4 listBackgroundDark;

extern ImVec4 renderColour;
extern ImVec4 renderColourSoft;
extern ImVec4 renderBackground;
extern ImVec4 renderBackgroundActive;

extern ImVec4 ledOff;
extern ImVec4 ledOn;

extern ImVec4 btDisconnected;
extern ImVec4 btConnected;

extern ImVec4 schemeBrown;
extern ImVec4 schemeYellow;
extern ImVec4 schemeMauve;
extern ImVec4 schemePurple;
extern ImVec4 schemeGreen;
extern ImVec4 schemeLightPurple;
extern ImVec4 schemeDarkerPurple;
extern ImVec4 schemePlum;

void init_imgui(float width, float height);
void get_font_info();
void set_scaling();

void invoke_single_set(char* uid, char* key, char* val);
void invoke_single_add(char* uid, char* key, char* val);

