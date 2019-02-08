/*
 * file: i2c-intf.hpp
 * purpose: Define an abstract interface class for interfacing an I2C communication bus.
 */

#ifndef I2C_INTERFACE_I2C_INTF_HPP
#define I2C_INTERFACE_I2C_INTF_HPP

#include <cstdint>

namespace i2c
{

template <typename Derived>
class I2cIntf
{
protected:

    I2cIntf() = default;
    virtual ~I2cIntf() = default;

public:
    bool open(uint16_t address)
    {
        return static_cast<Derived *>(this)->open(address);
    }

    bool close()
    {
        return static_cast<Derived *>(this)->close();
    }

    unsigned int write(uint8_t * data, unsigned int numberOfBytes)
    {
        return static_cast<Derived *>(this)->write(data, numberOfBytes);
    }

    unsigned int read(uint8_t * data, unsigned int numberOfBytes)
    {
        return static_cast<Derived *>(this)->read(data, numberOfBytes);
    }

    unsigned int getFrequency()
    {
        return static_cast<Derived *>(this)->getFrequency();
    }
};

} // namespace i2c

#endif // I2C_INTERFACE_I2C_INTF_HPP