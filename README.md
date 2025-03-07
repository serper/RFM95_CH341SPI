# CH341SPI

## Overview

CH341SPI is a C++ library designed to facilitate communication with SPI devices using the CH341 USB to SPI adapter. This library provides an abstraction layer for SPI communication, making it easier to interface with various SPI devices on Linux systems.

## Features

- **SPI Communication**: Supports standard SPI communication protocols.
- **GPIO Control**: Allows control of GPIO pins for interrupt handling.
- **Cross-Platform**: Designed to work on Linux systems with spidev support.
- **Modular Design**: Easily extendable to support additional SPI devices.

## Installation

To build and install the CH341SPI library, follow these steps:

1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/CH341SPI.git
    cd CH341SPI
    ```

2. Create a build directory and navigate to it:
    ```sh
    mkdir build
    cd build
    ```

3. Run CMake to configure the project:
    ```sh
    cmake ..
    ```

4. Build the project:
    ```sh
    make
    ```

5. Install the library:
    ```sh
    sudo make install
    ```

## Usage

### Creating an SPI Interface

To create an SPI interface using the CH341 adapter, include the necessary headers and use the `SPIFactory` class:

```cpp
#include "SPIFactory.hpp"

std::unique_ptr<SPIInterface> spi = SPIFactory::createLinuxSPI("/dev/spidev0.0", 1000000, 0);
```

### Communicating with SPI Devices

You can use the `transfer` method to send and receive data from SPI devices:

```cpp
std::vector<uint8_t> write_data = {0x01, 0x02, 0x03};
std::vector<uint8_t> read_data = spi->transfer(write_data);
```

### Controlling GPIO Pins

The library also provides methods to control GPIO pins:

```cpp
spi->pinMode(17, SPIInterface::OUTPUT);
spi->digitalWrite(17, true);
bool pin_value = spi->digitalRead(17);
```

## Documentation

For detailed documentation, please refer to the header files in the `include` directory. Each class and method is documented with comments explaining its purpose and usage.

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request with your changes. Ensure that your code adheres to the existing coding standards and includes appropriate tests.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Author

Sergio Pérez

For any questions or suggestions, feel free to contact me at sergio@example.com.
