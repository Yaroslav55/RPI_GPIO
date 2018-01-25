/*
 *  GPIO lib for Raspberry PI
 *  https://github.com/
 *                          Dev Yaroslav
 *                                  24.01.18
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
        rpi_gpio();
        ~rpi_gpio();
        /* Primary Functions */
        void rasspberry_model(model mdl);
        int open(int gpioPin, std::string gpio_direction);
        int close(int gpioPin);
        int write(int gpioPin, bool value);
        int read(int gpioPin);
        /* Other */
        int printError(std::string error_mes);
        int checkPin(int gpioPin);

    private:
        std::ofstream file;
        int rpiModel = -1;
        std::vector<int> activePin;
        int RPI_GPIO[2][26] = {
            { 2, 3, 4, 17, 27, 22, 10, 9, 11, 5, 6, 13, 19, 26, 14,15, 18, 23, 24, 25, 8, 7, 12, 16, 20, 21},
            { 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 2, 22, 22, 22, 22, 22, 22, 22, 22, 22}
        };
    };

#endif // GPIO_H
