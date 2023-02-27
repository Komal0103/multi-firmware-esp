#include <stdio.h>
#include <stdbool.h>
#include "sra_board.h"
#include "switches.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"
#include "bootloader_init.h"
#include "bootloader_utility.h"
#include "bootloader_common.h"
#include "bootloader_hooks.h"

static const char *TAG = "factory_boot"

static int select_ota_partition(bootloader_state_t *bs);
static int selected_ota_partition(bootloader_state_t *bs);

static int select_ota_partition(){
}

static int selected_ota_partition(bootloader_state_t *bs){
    int boot_index;
    if read_switch(SWITCH_1){
    //boot into 1st OTA partition-ota_0
}
    return boot_index;
}

void app_main(){
    printf("factory bootloader has been started successfully");
    printf("Selected paritition number is %d", selected_ota_partition(bs));
}