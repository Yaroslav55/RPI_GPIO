/*
 *  GPIO lib for Raspberry PI
 *  https://github.com/Yaroslav55/RPI_GPIO
 *                      Dev Yaroslav
 *                              24.01.18
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#ifndef GPIO_H
#define GPIO_H

const std::string GPIO_DIR_IN = "in";
const std::string GPIO_DIR_OUT = "out";

typedef enum{
    GPIO_RPI2_B = 0,
    GPIO_RPI3_B
} model;

class rpi_gpio {
    public:
        rpi_gpio(int gpioPin, std::string value);
        ~rpi_gpio();
        /* Primary Functions */
        int close();
        int write(bool value);
        int read();
    private:
        int gPin;
        std::ofstream file;
        /* Other */
        int open(int gpioPin, std::string gpio_direction);
        int printError(std::string error_mes);
    };

#endif // GPIO_H
