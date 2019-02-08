#include <chrono>
#include <csignal>
#include <iostream>
#include <thread>
#include <vector>
#include "i2c-linux-adapter.hpp"

template <typename T>
void writeBytes(i2c::I2cIntf<T> & i2cDriver);

static volatile bool run_flag;

int main()
{
    std::cout << "Hello, World!" << std::endl;
    std::string const DRIVER_PATH("/dev/i2c-1");
    i2c::I2cLinuxAdapter driver(DRIVER_PATH);

    signal(SIGINT, [](int /*sig */){run_flag = false;});

    run_flag = true;
    while (run_flag)
    {
        writeBytes(driver);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}

template <typename T>
void writeBytes(i2c::I2cIntf<T> & i2cDriver)
{
    if (i2cDriver.open(0x32u >> 1u))
    {
        std::vector<uint8_t> write_buffer{0x20, 0x77};
        i2cDriver.write(&write_buffer[0], write_buffer.size());

        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        std::vector<uint8_t> read_write_buffer{0x20};
        i2cDriver.write(&read_write_buffer[0], read_write_buffer.size());
        i2cDriver.read(&read_write_buffer[0], read_write_buffer.size());

        i2cDriver.close();
    }
}