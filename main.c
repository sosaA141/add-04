#include <stdio.h>
#include "pico/stdlib.h"

const uint TRIGGER = 27;
const uint ECHO = 26;
const uint led1 = 1;
const uint led2 = 2;
const uint led3 = 3;

float ultrasonic_get_distance_cm(uint8_t trigger, uint8_t echo) {
  gpio_put(trigger, true);
  sleep_us(10);
  gpio_put(trigger, false);
  while(!gpio_get(echo));
  absolute_time_t from = get_absolute_time();
  while(gpio_get(echo));
  absolute_time_t to = get_absolute_time();
  int64_t pulse_width = absolute_time_diff_us(from, to);
  float distance = pulse_width / 59.0;
   printf("distance: %.2f cm\r\n", distance);
  return distance;
}

void ultrasonic_init(uint8_t trigger, uint8_t echo) {
  gpio_init(trigger);  
  gpio_set_dir(trigger, true);
  gpio_put(trigger, false);
  gpio_init(echo);
  gpio_set_dir(echo, false);
}

int main() {

  stdio_init_all();
  sleep_ms(1000);
  printf("Listo!\r\n");

  gpio_init(led1);
  gpio_init(led2);
  gpio_init(led3);
  gpio_set_dir(led1, true);
  gpio_set_dir(led2, true);
  gpio_set_dir(led3, true);


  ultrasonic_init(TRIGGER, ECHO);

  while (true) {

    float d = ultrasonic_get_distance_cm(TRIGGER, ECHO);

    if(d<10) {
      gpio_put (led1, true);
      gpio_put (led2, false);
      gpio_put (led3, false);
    }

    if(d>=10 &&d<50) {
      gpio_put (led2, true);
      gpio_put (led1, false);
      gpio_put (led3, false);
    }

    if(d>=50 &&d<100) {
      gpio_put (led3, true);
      gpio_put (led2, false);
      gpio_put (led1, false);
    }

    sleep_ms(500);

  }
}
