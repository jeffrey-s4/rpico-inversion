#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "LCD_st7735/LCD_st7735.h"
#include "arducam_hm01b0/arducam_hm01b0.h"

uint8_t image_data[96 * 96];
struct arducam_config config;


int main(){
#ifndef PICO_DEFAULT_LED_PIN
#warning blink example requires a board with a regular LED
#else

  // start serial and mark LED
  stdio_init_all();
  const uint LED_PIN = PICO_DEFAULT_LED_PIN;
  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);

  // start screen
  ST7735_Init();
  ST7735_DrawImage(0, 0, 80, 160, arducam_logo);
  sleep_ms(1000);

  // put your setup code here, to run once:
  // camera setup
  config.sccb = i2c0;
  config.sccb_mode = I2C_MODE_16_8;
  config.sensor_address = 0x24;
  config.pin_sioc = PIN_CAM_SIOC;
  config.pin_siod = PIN_CAM_SIOD;
  config.pin_resetb = PIN_CAM_RESETB;
  config.pin_xclk = PIN_CAM_XCLK;
  config.pin_vsync = PIN_CAM_VSYNC;
  config.pin_y2_pio_base = PIN_CAM_Y2_PIO_BASE;
  config.pio = pio0;
  config.pio_sm = 0;
  config.dma_channel = 0;
  arducam_init(&config);

  ST7735_FillScreen(ST7735_BLACK);

  while (1) {
    // turn LED on
    gpio_put(LED_PIN, 1);

    // capture frame to camera image data buffer and write to display buffer
    arducam_capture_frame(&config, (uint8_t *)image_data);
    uint8_t displayBufArr[96 * 96 * 2];
    uint8_t *displayBuf = (uint8_t*) &displayBufArr;
    uint16_t index = 0;
    for (int x = 0; x < 96 * 96; x++) {
      uint16_t imageRGB =
          ST7735_COLOR565(image_data[x], image_data[x], image_data[x]);
      displayBuf[index] = (uint8_t)(imageRGB >> 8) & 0xFF;
      index++;
      displayBuf[index] = (uint8_t)(imageRGB)&0xFF;
      index++;
    }

    ST7735_DrawImage(0, 0, 96, 96, displayBuf);
    gpio_put(LED_PIN, 0);

    // sleep for 35ms --> draw frames at about 30fps
    // sleep for 17ms --> draw frames at about 60fps
    sleep_ms(1/60*1000);
  }
#endif
}

