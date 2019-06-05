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

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  LinuxI2CDriverComponentImpl ::
#if FW_OBJECT_NAMES == 1
    LinuxI2CDriverComponentImpl(
        const char *const compName
    ) :
      LinuxI2CDriverComponentBase(compName)
#else
    LinuxI2CDriverComponentImpl(void)
#endif
  {

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
    // TODO
  }

} // end namespace Drv
