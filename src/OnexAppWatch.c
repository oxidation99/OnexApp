
#include <boards.h>
#include <onex-kernel/log.h>
#include <onex-kernel/time.h>
#include <onex-kernel/gpio.h>
#include <onex-kernel/blenus.h>
#include <onex-kernel/gfx.h>
#include <onex-kernel/touch.h>
#include <onf.h>
#include <onr.h>

object* sensors;
object* controllers;
object* user;

char* deviceuid;
char* sensorsuid;
char* controllersuid;
char* useruid;

void button_changed(int);

static touch_info_t ti;
static bool new_touch_info=false;

void touched(touch_info_t touchinfo)
{
  ti=touchinfo;
  new_touch_info=true;
}

static bool evaluate_user(object* sensors, void* pressed);
static bool evaluate_sensors_io(object* sensors, void* pressed);
static bool evaluate_controllers_io(object* sensors, void* pressed);

void* x;
#define WHERESTHEHEAP(s) x = malloc(1); log_write("heap after %s: %x\n", s, x);

int main()
{
  log_init();
  time_init();
  gpio_init();
  blenus_init(0);

  gfx_init();
  gfx_screen_colour(0xC618);
  gfx_text_colour(0x001F);
  gfx_screen_fill();
  touch_init(touched);

  onex_init("");

  gpio_mode_cb(BUTTON_1, INPUT_PULLDOWN, button_changed);
  gpio_mode(   BUTTON_ENABLE, OUTPUT);
  gpio_set(    BUTTON_ENABLE, 1);
  gpio_mode(CHARGE_SENSE, INPUT);

  gpio_mode(LCD_BACKLIGHT_HIGH, OUTPUT);

  onex_set_evaluators("device",      evaluate_device_logic, 0);
  onex_set_evaluators("user",        evaluate_user, 0);
  onex_set_evaluators("sensors",                         evaluate_sensors_io, 0);
  onex_set_evaluators("controllers", evaluate_edit_rule, evaluate_controllers_io, 0);

  object_set_evaluator(onex_device_object, "device");
  user       =object_new(0, "user",        "user", 8);
  sensors    =object_new(0, "sensors",     "sensors", 8);
  controllers=object_new(0, "controllers", "editable controllers", 4);

  deviceuid     =object_property(onex_device_object, "UID");
  useruid       =object_property(user, "UID");
  sensorsuid    =object_property(sensors, "UID");
  controllersuid=object_property(controllers, "UID");

  object_property_add(onex_device_object, (char*)"user", useruid);
  object_property_add(onex_device_object, (char*)"io",   sensorsuid);
  object_property_add(onex_device_object, (char*)"io",   controllersuid);

  object_property_set(user, "viewing", deviceuid);
  object_property_set(controllers, "backlight", "on");

  onex_run_evaluators(controllersuid, 0);

  gfx_pos(10, 10);
  gfx_text("OnexOS");

  while(1){

    onex_loop();

    if(new_touch_info){
      new_touch_info=false;
/*
      if(ti.gesture==TOUCH_GESTURE_TAP_LONG){
        gpio_set(LCD_BACKLIGHT_HIGH, !LEDS_ACTIVE_STATE);
      }
      else {
        gpio_set(LCD_BACKLIGHT_HIGH, LEDS_ACTIVE_STATE);
      }
*/
    }
  }
}

void button_changed(int pressed)
{
  onex_run_evaluators(sensorsuid, (void*)(bool)pressed);
}

bool evaluate_sensors_io(object* o, void* pressed)
{
  char* s=(char*)(pressed? "down": "up");
  object_property_set(sensors, "button", s);

  char b[16];
  int batt=gpio_get(CHARGE_SENSE);
  snprintf(b, 16, "%s", batt? "battery": "charging");
  object_property_set(sensors, "battery-charge", b);

  return true;
}

bool evaluate_controllers_io(object* o, void* d)
{
  if(object_property_is(controllers, "backlight", "on")){
    gpio_set(LCD_BACKLIGHT_HIGH, LEDS_ACTIVE_STATE);
  } else {
    gpio_set(LCD_BACKLIGHT_HIGH, !LEDS_ACTIVE_STATE);
  }
  return true;
}

bool evaluate_user(object* o, void* d)
{
//draw_ui();
  return true;
}



