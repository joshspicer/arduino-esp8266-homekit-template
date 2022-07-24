/*
 * my_accessory.c
 * Defines the accessory in C  using the Macro in characteristics.h
 *
 *  Created on: 2020-05-15
 *      Author: Mixiaoxiao (Wang Bin)
 *   Modified on: 2022-03-11
 *      Modifier: Josh Spicer <hello@joshspicer.com>
 */

#include <homekit/homekit.h>
#include <homekit/characteristics.h>

void my_accessory_identify(homekit_value_t _value) {
  printf("accessory identify\n");
}

homekit_characteristic_t green_button = HOMEKIT_CHARACTERISTIC_(PROGRAMMABLE_SWITCH_EVENT, NULL);
homekit_characteristic_t yellow_button = HOMEKIT_CHARACTERISTIC_(PROGRAMMABLE_SWITCH_EVENT, NULL);


homekit_accessory_t *accessories[] = {
    HOMEKIT_ACCESSORY(.id=1, .category=homekit_accessory_category_switch, .services=(homekit_service_t*[]) {
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Stateless Buttons"),
            HOMEKIT_CHARACTERISTIC(MANUFACTURER, "spicer.dev"),
            HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "0123456789"),
            HOMEKIT_CHARACTERISTIC(MODEL, "ESP8266"),
            HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "0.2"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, my_accessory_identify),
            NULL
        }),
        HOMEKIT_SERVICE(STATELESS_PROGRAMMABLE_SWITCH, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
            &green_button,
            HOMEKIT_CHARACTERISTIC(NAME, "Green"),
            NULL
        }),
        HOMEKIT_SERVICE(STATELESS_PROGRAMMABLE_SWITCH, .characteristics=(homekit_characteristic_t*[]) {
            &yellow_button,
            HOMEKIT_CHARACTERISTIC(NAME, "Yellow"),
            NULL
        }),
        NULL
    }),
    NULL
};

homekit_server_config_t config = {
    .accessories = accessories,
    .password = "111-44-333"
};
