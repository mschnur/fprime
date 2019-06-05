// ======================================================================
// \title  LinuxI2CDriverComponentImpl.cpp
// \author erynqian
// \brief  cpp file for LinuxI2CDriver component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================


#include <Drv/LinuxI2CDriver/LinuxI2CDriverComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"
#include "Fw/Types/Assert.hpp"

#include <unistd.h>  // for open/close
#include <fcntl.h>  // for ioctl
#include <sys/ioctl.h> // for ioctl
#include <linux/i2c-dev.h> // for i2c ioctl stuff
namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  LinuxI2CDriverComponentImpl ::
#if FW_OBJECT_NAMES == 1
    LinuxI2CDriverComponentImpl(
        const char *const compName
    ) :
      LinuxI2CDriverComponentBase(compName),
#else
    LinuxI2CDriverComponentImpl(void),
#endif
    m_i2cFileDescriptor(-1)
  {

  }

  void LinuxI2CDriverComponentImpl ::
    open(const char* i2cFilePath)
  {
    FW_ASSERT(i2cFilePath != NULL);
    m_i2cFileDescriptor = ::open(i2cFilePath, O_WRONLY);
    FW_ASSERT(m_i2cFileDescriptor != -1);
  }

  void LinuxI2CDriverComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    LinuxI2CDriverComponentBase::init(instance);
  }

  LinuxI2CDriverComponentImpl ::
    ~LinuxI2CDriverComponentImpl(void)
  {
    if (m_i2cFileDescriptor != -1) {
      close(m_i2cFileDescriptor);
    }
  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void LinuxI2CDriverComponentImpl ::
    I2CWrite_handler(
        const NATIVE_INT_TYPE portNum,
        U32 i2cAddress,
        Fw::Buffer &i2cBuffer
    )
  {
    FW_ASSERT(m_i2cFileDescriptor != -1);

    int ioctlStatus = ioctl(m_i2cFileDescriptor, I2C_SLAVE, i2cAddress); // Set the I2C address for upcoming
                                                                         //  transactions

    FW_ASSERT(ioctlStatus != -1);

    int writeStatus = write(m_i2cFileDescriptor, (void *) i2cBuffer.getdata(), i2cBuffer.getsize()); // initiate write

    FW_ASSERT(writeStatus != -1);
  }

} // end namespace Drv
