/*
 *  GPIO lib for Raspberry PI
 *  https://github.com/
 *                          Dev Yaroslav
 *                                  24.01.18
 */
#include "rpi_gpio.h"
rpi_gpio::rpi_gpio()
{
}
rpi_gpio::~rpi_gpio()
{
//    for (int i = 0; i < activePin.size(); i++) {
//        close(activePin[i]);
//    }
}
void rpi_gpio::rasspberry_model(model mdl)
{
    rpiModel = mdl;
}
int rpi_gpio::printError(std::string error_mes)
{

    if (file.is_open()) {
        file.close();
    }
    std::cout << error_mes << std::endl;
    return -1;
}
int rpi_gpio::checkPin(int gpioPin)
{

    for (int i = 0; i < 26; i++) {
        if (gpioPin == RPI_GPIO[rpiModel][i]) {
            return 1;
        }
    }
    return 0;
}
int rpi_gpio::open(int gpioPin, std::string gpio_direction)
{
    std::stringstream pinDir;
    pinDir << "/sys/class/gpio/gpio" << gpioPin;
    if (rpiModel < 0) {
        return printError("Unknown Raspberry Pi model!");
    }
    if (!checkPin(gpioPin)) {
        return printError("GPIO pin error!");
    }
    if ((gpio_direction != GPIO_DIR_IN) && (gpio_direction != GPIO_DIR_OUT)) {
        return printError("GPIO direction error! Pin: " + gpioPin);
    }
    file.open("/sys/class/gpio/export", std::ios_base::in);
    if (!file.is_open()) {
        return printError("Error opening GPIO export file!");
    }
    file << gpioPin;
    file.close();
//    std::ofstream dir;
//    /**********GPIO direction**********/
//    pinDir << "/direction";
//    dir.open(pinDir.str().c_str(), std::ios_base::in);
//    if (!dir.is_open()) {
//        //close(gpioPin);
//        return printError("Error opening GPIO direction file! " + pinDir.str());
//    }
//    std::cout << gpio_direction <<std::endl;
//    dir << gpio_direction;
//    dir.close();

    activePin.push_back(gpioPin);

    return 1;
}
int rpi_gpio::close(int gpioPin)
{
    if (!checkPin(gpioPin)) {
        return printError("GPIO pin error!");
    }
    file.open("/sys/class/gpio/unexport", std::ios_base::in);
    if (!file.is_open()) {
        return printError("Error opening GPIO unexport file!");
    }
    file << gpioPin;
    file.close();
    return 1;
}
int rpi_gpio::write(int gpioPin, bool value)
{
    std::stringstream pinDir;
    pinDir << "/sys/class/gpio/gpio" << gpioPin << "/value";
    if (!checkPin(gpioPin)) {
        return printError("GPIO pin error!");
    }
    for (int i = 0; i < activePin.size(); i++) {
        if (gpioPin == activePin[i])
            break;
        else if (i == activePin.size())
            return printError("Error, not remember a pin!");
    }

    file.open(pinDir.str().c_str(), std::ios_base::in);
    char value_str[2] = { '0', '1' };
    if (!file.is_open()) {
        return printError("Error opening value, pin " + gpioPin);
    }
    file << value_str[value];
    file.close();

    return 1;
}
int rpi_gpio::read(int gpioPin)
{
    std::stringstream pinDir;
    pinDir << "/sys/class/gpio/gpio" << gpioPin << "/value";
    std::ifstream file_v(pinDir.str().c_str());
    char value;
    if (!file_v.is_open()) {
        return printError("Error reading value " + pinDir.str());
    }
    file_v >> value;
    if (value == '1') {
        file_v.close();
        return 1;
    } else if (value == '0') {
        file_v.close();
        return 0;
    } else {
        file_v.close();
        return printError("Unknown value in pin: " + gpioPin);
    }
}
