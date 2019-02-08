/*
 * file: i2c-linux-adapter.hpp
 * purpose: Implementation of the I2C CRTP interface for Linux.
 */

#ifndef I2C_INTERFACE_I2C_LINUX_ADAPTER_HPP
#define I2C_INTERFACE_I2C_LINUX_ADAPTER_HPP

#include <string>
#include "i2c-intf.hpp"

namespace i2c
{

class I2cLinuxAdapter : public I2cIntf<I2cLinuxAdapter>
{
public:

    explicit I2cLinuxAdapter(std::string const & driverFilepath);

    ~I2cLinuxAdapter() override;

    bool open(uint16_t address);

    bool close();

    unsigned int write(uint8_t * data, unsigned int numberOfBytes);

    unsigned int read(uint8_t * data, unsigned int numberOfBytes);

    unsigned int getFrequency();

private:

    std::string my_driverFilepath;
    int my_fileDescriptor;
    bool my_isOpen;
    unsigned int my_frequency;

};

} // namespace i2c

#endif // I2C_INTERFACE_I2C_LINUX_ADAPTER_HPP
