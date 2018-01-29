#include <iostream>
#include <unistd.h>
#include "src/rpi_gpio.h"
/* Example */
int main(void)
{
    rpi_gpio led(26, GPIO_DIR_OUT);
    for(int i = 0;i < 10; i++){
        led.write(true);
        std::cout << led.read() <<std::endl;
        usleep(1 *1000000);
        led.write(false);
        std::cout << led.read() <<std::endl;
        usleep(1 *1000000);
    }

    return 0;
}
