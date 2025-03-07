#include "RFM95.hpp"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <signal.h>
#include <cstdlib> // For atoi

// Flag for handling Ctrl+C
volatile sig_atomic_t stop_flag = 0;

void signal_handler(int sig)
{
    std::cout << "\nInterrupted, finishing..." << std::endl;
    stop_flag = 1;
}

void print_usage()
{
    std::cout << "Usage: rfm95_example [tx|rx] <device_index> [message]" << std::endl;
    std::cout << "  tx: Transmitter mode (message required)" << std::endl;
    std::cout << "  rx: Receiver mode" << std::endl;
    std::cout << "  device_index: CH341 device index (0, 1, ...)" << std::endl;
    std::cout << "Examples:" << std::endl;
    std::cout << "  rfm95_example tx 0 \"Hello world\"  # Send from first device" << std::endl;
    std::cout << "  rfm95_example rx 1                # Receive from second device" << std::endl;
    std::cout << "  rfm95_example test 0              # Test first device" << std::endl;
}

int main(int argc, char **argv)
{
    // Set handler for Ctrl+C
    signal(SIGINT, signal_handler);

    if (argc < 3)
    {
        print_usage();
        return 1;
    }

    std::string mode = argv[1];
    int device_index = atoi(argv[2]);

    std::cout << "Using CH341 device #" << device_index << std::endl;

    // Create RFM95 instance with specified device index
    RFM95 radio(device_index);

    // Initialize
    if (!radio.begin())
    {
        std::cerr << "Error initializing RFM95 module" << std::endl;
        return 1;
    }

    // Configure common parameters
    radio.setFrequency(868.1);  // 868.1 MHz (Europe)
    radio.setTxPower(17, true); // 17dBm with PA_BOOST
    radio.setSpreadingFactor(7);
    radio.setBandwidth(125.0); // 125 kHz
    radio.setCodingRate(5);    // 4/5
    radio.setPreambleLength(8);
    radio.setSyncWord(0x12); // Private network

    // Display current configuration
    std::cout << "\nConfiguration:" << std::endl;
    std::cout << "Device: " << device_index << std::endl;
    std::cout << "Frequency: " << radio.getFrequency() << " MHz" << std::endl;
    std::cout << "TX Power: " << radio.getTxPower() << " dBm" << std::endl;
    std::cout << "Spreading Factor: " << radio.getSpreadingFactor() << std::endl;
    std::cout << "Bandwidth: " << radio.getBandwidth() << " kHz" << std::endl;
    std::cout << "Coding Rate: 4/" << radio.getCodingRate() << std::endl;
    std::cout << "Preamble Length: " << radio.getPreambleLength() << std::endl;

    if (mode == "tx")
    {
        // Transmitter mode
        if (argc < 4)
        {
            std::cerr << "Error: Message required for sending" << std::endl;
            print_usage();
            return 1;
        }

        std::string message = argv[3];
        std::vector<uint8_t> data(message.begin(), message.end());

        std::cout << "\nSending message: \"" << message << "\"" << std::endl;
        bool success = radio.send(data);

        if (success)
        {
            std::cout << "Message sent successfully" << std::endl;
        }
        else
        {
            std::cerr << "Error sending message" << std::endl;
        }
    }
    else if (mode == "rx")
    {
        // Receiver mode
        std::cout << "\nReceiver mode (device #" << device_index << "). Press Ctrl+C to exit." << std::endl;

        while (!stop_flag)
        {
            std::vector<uint8_t> data = radio.receive(3.0); // 3 second timeout

            if (!data.empty())
            {
                std::string message(data.begin(), data.end());

                std::cout << "Message received: \"" << message << "\"" << std::endl;
                std::cout << "RSSI: " << radio.getRSSI() << " dBm" << std::endl;
                std::cout << "SNR: " << radio.getSNR() << " dB" << std::endl;
            }
        }
    }
    else if (mode == "test")
    {
        // Test mode
        std::cout << "\nBasic communication test (device #" << device_index << "):" << std::endl;
        radio.testCommunication();

        std::cout << "\nVerifying operation mode:" << std::endl;
        radio.checkOperatingMode();

        std::cout << "\nVerifying IRQ flags:" << std::endl;
        radio.checkIRQFlags();

        std::cout << "\nPrinting key registers:" << std::endl;
        radio.printRegisters();

        // Temperature sensor test
        float temp = radio.readTemperature();
        std::cout << "\nTemperature: " << temp << "°C" << std::endl;
    }
    else
    {
        std::cerr << "Unknown mode: " << mode << std::endl;
        print_usage();
        return 1;
    }

    // Close device
    radio.end();

    return 0;
}