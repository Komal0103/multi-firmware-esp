#include "flasher.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sra_board.h"
#include "esp_ota_ops.h"
#include <esp_http_server.h>

static const char *TAG = "stm_flash";
//this program reads and writes the files to be flashed

#define FILE_PATH_MAX 128
#define BASE_PATH "/spiffs/"

esp_err_t flash(const char *file_name)
{
    char buffer[1000];
    esp_ota_handle_t ota_handle;
    const esp_partition_t *current_partition = esp_ota_get_running_partition();
    printf("Current running partition %s", current_partition -> label);
    const esp_partition_t *ota_partition = esp_ota_get_next_update_partition(current_partition);
    printf("Next running partition %s", ota_partition -> label);
    if (esp_ota_begin(ota_partition, OTA_SIZE_UNKNOWN, &ota_handle)!=ESP_OK)
        ESP_LOGI(TAG, "memory could not be alloted");
    // ESP_ERROR_CHECK();
    esp_err_t err = ESP_FAIL;
    ESP_LOGI(TAG, "Starting OTA example");

    char file_path[FILE_PATH_MAX];
    sprintf(file_path, "%s%s", BASE_PATH, file_name);
    ESP_LOGI(TAG, "File name: %s", file_path);
    long int file_size = get_file_size(file_path);
    FILE *flash_file = fopen(file_path, "rb");

    if(flash_file == NULL){
        return err;
    }
    // char command[100];
    // strcpy(command, "idf.py -p /dev/ttyUSB0 flash monitor");
    // system(command);

    // char chunk[128];
    // while(fgets(chunk, sizeof(chunk), flash_file) != NULL) {//reads a line from a specified string and stores in a variable
        
        //  fputs(chunk, stdout);//will print the output to the main output of the session. In this case, the tty
    // }
    while (file_size>0)
    {
        // int length = httpd_req_recv(file_name, buffer, MIN(file_size, sizeof(buffer)));
        fgets(buffer, sizeof(buffer), flash_file);
        // flash firmware chunk, already uploaded
        if (esp_ota_write(ota_handle, (const void *)buffer, sizeof(buffer))!=ESP_OK){
            // httpd_resp_send_err(file_name, HTTPD_500_INTERNAL_SERVER_ERROR, "Flash Error");
            ESP_LOGI(TAG, "cannot write ota file");
			return ESP_FAIL;
        }
        file_size -= sizeof(buffer);
    }
    if (esp_ota_end(ota_handle)==ESP_OK)
        ESP_LOGI(TAG, "file written successfully in container");

    fclose(flash_file);
    vTaskDelay(500 / portTICK_PERIOD_MS);

    return ESP_OK;
}

long int get_file_size(const char *file_path){
    FILE *flash_file = fopen(file_path, "rb");
    if (flash_file==NULL){
        return ESP_FAIL;
    }
    fseek(flash_file, 0, SEEK_END);
    long int size=ftell(flash_file);
    fclose(flash_file);
    return size;
}