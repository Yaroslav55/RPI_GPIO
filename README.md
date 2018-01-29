
RPI_GPIO
=============================
My lib for work with Raspberry Pi GPIO.

Example
-----------------------------

``` c++
#include "rpi_gpio.h"
int main(void)
{
    rpi_gpio led(26, GPIO_DIR_OUT);
    for(int i = 0;i < 10; i++){
        led.write(true);
        usleep(1 *1000000);
        
        led.write(false);
        usleep(1 *1000000);
    }

    return 0;
}
```
