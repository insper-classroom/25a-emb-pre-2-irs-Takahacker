#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int LedPin = 4;
const int BTN_PIN = 28;
volatile int btn_flag = 0;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { 
    btn_flag = 1;
  } else if (events == 0x8) { 
    btn_flag = 2;
  }
}

int main() {
  stdio_init_all();
  gpio_init(LedPin);
  gpio_set_dir(LedPin, GPIO_OUT);
  gpio_init(BTN_PIN);
  gpio_set_dir(BTN_PIN, GPIO_IN);
  gpio_pull_up(BTN_PIN);
  gpio_set_irq_enabled_with_callback(
    BTN_PIN, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);

  int Led_flag = 0;

  while (true) {
    if (btn_flag == 1) {
      if (Led_flag == 0) {
        Led_flag = 1;
        gpio_put(LedPin, 0);
      } else {
        Led_flag = 0;
        gpio_put(LedPin, 1);
      }
      btn_flag = 0;
      printf("fall\n");
    } 
  }
}
