#include <Arduino.h>

#include <WM1110_Geolocation.hpp>
#include <WM1110_BLE.hpp>
#include <WM1110_Storage.hpp>
#include <WM1110_At_Config.hpp>

uint8_t cmd_data_buf[244] = {0};
uint8_t cmd_data_size = 0;

void setup()
{
    delay(100);
    Serial.begin(115200);
    while (!Serial) delay(100); 

    printf("WM1110 AT Config Example\r\n");

    wm1110_storage.begin();
    wm1110_storage.loadBootConfigParameters();

    wm1110_at_config.begin();

    wm1110_ble.begin();
    wm1110_ble.setName("Wio Tracker 1110");
    wm1110_ble.setStartParameters();
    wm1110_ble.startAdv();

}

void loop()
{
    if(wm1110_at_config.receiveSerialCmd(cmd_data_buf,&cmd_data_size))
    {
        cmd_parse_type = 0;
        wm1110_at_config.parseCmd((char *)cmd_data_buf,cmd_data_size);
        memset(cmd_data_buf, 0, cmd_data_size);
        cmd_data_size = 0;
    }

    if(wm1110_ble.getBleRecData(cmd_data_buf,&cmd_data_size))
    {
        cmd_parse_type = 1;
        wm1110_at_config.parseCmd((char *)cmd_data_buf,cmd_data_size);
        memset(cmd_data_buf,0,cmd_data_size);
        cmd_data_size = 0;
        cmd_parse_type = 0;
    }
}







