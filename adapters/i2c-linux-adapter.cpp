/*
 * file: i2c-linux-adapter.cpp
 * purpose: Implementation of the I2C interface for Linux systems.
 */

#include <iostream>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <zconf.h>
#include "i2c-linux-adapter.hpp"

namespace i2c
{

I2cLinuxAdapter::I2cLinuxAdapter(std::string const &driverFilepath)
    : I2cIntf(),
      my_driverFilepath(driverFilepath),
      my_fileDescriptor(0),
      my_isOpen(false),
      my_frequency(400000u)
{
    // Empty constructor
}

I2cLinuxAdapter::~I2cLinuxAdapter()
{
    if (this->my_isOpen)
    {
        this->close();
    }
}

bool I2cLinuxAdapter::open(uint16_t address)
{
    bool retVal(false);
    if (!this->my_isOpen)
    {
        this->my_fileDescriptor = ::open(this->my_driverFilepath.c_str(), O_RDWR);
        if (this->my_fileDescriptor < 0)
        {
            std::cerr << "Error: Could not open driver file: " << this->my_driverFilepath;
            this->my_fileDescriptor = 0;
        }
        else
        {
            if (ioctl(this->my_fileDescriptor, I2C_SLAVE, address) >= 0)
            {
                this->my_isOpen = true;
                retVal = true;
            }
        }
    }
    return retVal;
}

bool I2cLinuxAdapter::close()
{
    auto retVal(false);
    if (this->my_isOpen)
    {
        ::close(this->my_fileDescriptor);
        this->my_fileDescriptor = 0;
        this->my_isOpen = false;
        retVal = true;
    }
    return retVal;
}

unsigned int I2cLinuxAdapter::write(uint8_t * data, unsigned int numberOfBytes)
{
    ssize_t bytes_written(0);
    if (this->my_isOpen)
    {
        bytes_written = ::write(this->my_fileDescriptor, data, numberOfBytes);
    }
    return static_cast<unsigned int>(bytes_written);
}

unsigned int I2cLinuxAdapter::read(uint8_t * data, unsigned int numberOfBytes)
{
    ssize_t bytes_read(0);
    if (this->my_isOpen)
    {
        bytes_read = ::read(this->my_fileDescriptor, data, numberOfBytes);
    }
    return static_cast<unsigned int>(bytes_read);
}

} // namespace i2c
