import qbs

Project {
    minimumQbsVersion: "1.7.1"

    CppApplication {
        consoleApplication: true
        files: [
            "main.cpp",
            "src/rpi_gpio.cpp",
            "src/rpi_gpio.h",
        ]
        qbs.architecture: "armv7a"
        Group {     // Properties for the produced executable
            fileTagsFilter: "application"

            qbs.install: true
            qbs.installDir: "/home/pi/RPI_GPIO"
        }
    }
}
