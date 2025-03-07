# CH341SPI LoRa Interface Library

A C++ library for interfacing with LoRa modules (specifically RFM95) using CH341 USB-SPI adapters. This library provides a comprehensive interface for configuring and using LoRa communication.

## Features

- Full control over LoRa parameters (frequency, spreading factor, bandwidth, coding rate, etc.)
- Simple send/receive API
- Supports multiple CH341 devices connected simultaneously
- Temperature sensor support
- Beacon mode for automated periodic transmissions
- Cross-platform (Linux and Windows)

## Requirements

- C++14 compatible compiler
- CMake 3.10 or higher
- libusb-1.0 development libraries

## Building

```bash
mkdir build
cd build
cmake ..
make
```

## Usage Example

```cpp
#include "RFM95.hpp"
#include <iostream>
#include <vector>

int main() {
    // Initialize RFM95 with first CH341 device
    RFM95 radio(0);
    
    if (!radio.begin()) {
        std::cerr << "Failed to initialize radio" << std::endl;
        return 1;
    }
    
    // Configure radio parameters
    radio.setFrequency(868.1);  // 868.1 MHz (Europe)
    radio.setTxPower(17, true); // 17dBm with PA_BOOST
    radio.setSpreadingFactor(7);
    radio.setBandwidth(125.0);  // 125 kHz
    radio.setCodingRate(5);     // 4/5
    
    // Send a message
    std::vector<uint8_t> message = {'H', 'e', 'l', 'l', 'o'};
    if (radio.send(message)) {
        std::cout << "Message sent successfully" << std::endl;
    }
    
    return 0;
}
```

## Hardware Reference Design

You can use this library with a reference board design that is available at:
[https://oshwlab.com/serper/lora-usb-adapter](https://oshwlab.com/serper/lora-usb-adapter)

This design provides a complete USB-to-LoRa adapter using the CH341 chip and RFM95 module, allowing for easy integration with this software library.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.
