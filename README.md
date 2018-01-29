
RPI_GPIO
=============================
My lib for work with Raspberry Pi GPIO.

Example
-----------------------------

``` c++
#include "rpi_gpio.h"
int main(void)
{
    /* Add RPI_GPIO*class */
    rpi_gpio gpio;
    /* Set Raspberry Pi model */
    gpio.rasspberry_model(GPIO_RPI2_B);
    /* Open GPIO 26 with out direction */
    gpio.open(26, GPIO_DIR_OUT);
    /* Write value in 26 pin*/
    gpio.write(26, true);
    /* Read value in 26 pin*/
    gpio.read(26);
    
    return 0;
}
```
