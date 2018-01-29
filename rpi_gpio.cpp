/*
 *  GPIO lib for Raspberry PI
 *  https://github.com/Yaroslav55/RPI_GPIO
 *                      Dev Yaroslav
 *                              24.01.18
 */
#include "rpi_gpio.h"
rpi_gpio::rpi_gpio(int gpioPin, std::string value)
{
    gPin = gpioPin;
    open(gPin, value);
}
rpi_gpio::~rpi_gpio()
{
    close();
}
int rpi_gpio::printError(std::string error_mes)
{

    if (file.is_open()) {
        file.close();
    }
    std::cout << error_mes << std::endl;
    return -1;
}
int rpi_gpio::open(int gpioPin, std::string gpio_direction)
{
    std::stringstream pinDir;
    pinDir << "/sys/class/gpio/gpio" << gpioPin;
    if ((gpio_direction != GPIO_DIR_IN) && (gpio_direction != GPIO_DIR_OUT)) {
        return printError("GPIO direction error! Pin: " + gpioPin);
    }
    file.open("/sys/class/gpio/export", std::ios_base::in);
    if (!file.is_open()) {
        return printError("Error opening GPIO export file!");
    }
    file << gpioPin;
    file.close();
    /**********GPIO direction**********/
    pinDir << "/direction";
    file.open(pinDir.str().c_str(), std::ios_base::in);
    if (!file.is_open()) {
        close();
        gPin = -1;
        return printError("Error opening GPIO direction file!(Possibly you not have a root) " + pinDir.str());
    }
    file << gpio_direction;
    file.close();

    return 1;
}
int rpi_gpio::close()
{
    if( gPin == -1 ){
        return printError("Error opening GPIO direction file!(Possibly you not have a root) ");
    }
    file.open("/sys/class/gpio/unexport", std::ios_base::in);
    if (!file.is_open()) {
        return printError("Error opening GPIO unexport file!");
    }
    file << gPin;
    file.close();
    return 1;
}
int rpi_gpio::write(bool value)
{
    std::stringstream pinDir;
    pinDir << "/sys/class/gpio/gpio" << gPin << "/value";
    if( gPin == -1 ){
        return printError("Error opening GPIO direction file!(Possibly you not have a root) " + pinDir.str());
    }
    file.open(pinDir.str().c_str(), std::ios_base::in);
    char value_str[2] = { '0', '1' };
    if (!file.is_open()) {
        return printError("Error opening value, pin " + gPin);
    }
    file << value_str[value];
    file.close();

    return 1;
}
int rpi_gpio::read()
{
    std::stringstream pinDir;
    pinDir << "/sys/class/gpio/gpio" << gPin << "/value";
    std::ifstream file_v(pinDir.str().c_str());
    char value;
    if( gPin == -1 ){
        return printError("Error opening GPIO direction file!(Possibly you not have a root) ");
    }
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
        return printError("Unknown value in pin: " + gPin);
    }
}
