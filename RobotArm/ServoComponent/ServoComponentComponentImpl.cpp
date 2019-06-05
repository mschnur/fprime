// ======================================================================
// \title  ServoComponentComponentImpl.cpp
// \author sjanoff
// \brief  cpp file for ServoComponent component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================


#include <RobotArm/ServoComponent/ServoComponentComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace RobotArm {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  ServoComponentComponentImpl ::
#if FW_OBJECT_NAMES == 1
    ServoComponentComponentImpl(
        const char *const compName
    ) :
      ServoComponentComponentBase(compName)
#else
    ServoComponentComponentImpl(void)
#endif
  {

  }

  void ServoComponentComponentImpl ::
    init(
        const NATIVE_INT_TYPE queueDepth,
        const NATIVE_INT_TYPE instance
    )
  {
    ServoComponentComponentBase::init(queueDepth, instance);
  }

  ServoComponentComponentImpl ::
    ~ServoComponentComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void ServoComponentComponentImpl ::
    SetServo_handler(
        const NATIVE_INT_TYPE portNum,
        F32 Angle
    )
  {
    // TODO
  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void ServoComponentComponentImpl ::
    SVO_SETANG_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        F32 angle
    )
  {
    // TODO
    this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
  }

  void ServoComponentComponentImpl ::
    SVO_DISABLE_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq
    )
  {
    // TODO
    this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
  }

  void ServoComponentComponentImpl ::
    SVO_ENABLE_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq
    )
  {
    // TODO
    this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
  }

} // end namespace RobotArm
