#include "flasher.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sra_board.h"

static const char *TAG = "stm_flash";
//this program reads and writes the files to be flashed

#define FILE_PATH_MAX 128
#define BASE_PATH "/spiffs/"

esp_err_t flash(const char *file_name)
{
    esp_err_t err = ESP_FAIL;

    char file_path[FILE_PATH_MAX];
    sprintf(file_path, "%s%s", BASE_PATH, file_name);
    ESP_LOGI(TAG, "File name: %s", file_path);
    FILE *flash_file = fopen(file_path, "rb");

    if(flash_file == NULL){
        return err;
    }
    char command[100];
    strcpy(command, "idf.py -p /dev/ttyUSB0 flash monitor");
    system(command);

    // char chunk[128];
    // while(fgets(chunk, sizeof(chunk), flash_file) != NULL) {//reads a line from a specified string and stores in a variable
    //      fputs(chunk, stdout);//will print the output to the main output of the session. In this case, the tty
    // }

    fclose(flash_file);

    return ESP_OK;
}

void ota_task()