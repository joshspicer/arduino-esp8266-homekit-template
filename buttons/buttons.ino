/*
   switch.ino

    Created on: 2020-05-15
        Author: Mixiaoxiao (Wang Bin)
    Modified on: 2021-07-24
        Modifier: Josh Spicer <hello@joshspicer.com>
*/

#include <Arduino.h>
#include <arduino_homekit_server.h>
#include "wifi_info.h"

#define LOG_D(fmt, ...) printf_P(PSTR(fmt "\n"), ##__VA_ARGS__);

void setup()
{
  Serial.begin(115200);
  wifi_connect(); // in wifi_info.h
//  homekit_storage_reset(); // to remove the previous HomeKit pairing storage when you first run this new HomeKit example
  my_homekit_setup();
}

void loop()
{
  my_homekit_loop();
  delay(10);
}

//==============================
// HomeKit setup and loop
//==============================

// access your HomeKit characteristics defined in my_accessory.c
extern "C" homekit_server_config_t config;

extern "C" homekit_characteristic_t green_button;
extern "C" homekit_characteristic_t yellow_button;

static uint32_t next_heap_millis = 0;

static uint32_t next_debounce = 0;

#define GREEN_PIN 0  // D3
#define YELLOW_PIN 2 // D4

void my_homekit_setup()
{
  pinMode(GREEN_PIN, INPUT);
  pinMode(YELLOW_PIN, INPUT);
  arduino_homekit_setup(&config);
}

void my_homekit_loop()
{
  arduino_homekit_loop();

  int greenRead = digitalRead(GREEN_PIN);
  int yellowRead = digitalRead(YELLOW_PIN);

  bool checkValues = false;
  const uint32_t t = millis();
  if (t > next_debounce)
  {
    checkValues = true;
  }

  // Green Button Pressed
  if (checkValues && greenRead == LOW)
  {
    LOG_D("GREEN");
    homekit_characteristic_notify(&green_button,  green_button.value);

    next_debounce = t + 500; // Only check values after 0.5 seconds
  }

  // Yellow Button Pressed
  if (checkValues && yellowRead == LOW)
  {
    LOG_D("YELLOW");
    homekit_characteristic_notify(&yellow_button, yellow_button.value);

    next_debounce = t + 500; // Only check values after 0.5 seconds
  }

  if (t > next_heap_millis)
  {
    // show heap info every 5 seconds
    next_heap_millis = t + 5 * 1000;
    LOG_D("Free heap: %d, HomeKit clients: %d",
          ESP.getFreeHeap(), arduino_homekit_connected_clients_count());
  }
}
