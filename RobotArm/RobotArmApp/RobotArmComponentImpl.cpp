// ======================================================================
// \title  RobotArmComponentImpl.cpp
// \author erynqian
// \brief  cpp file for RobotArm component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================


#include <RobotArm/RobotArmApp/RobotArmComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace RobotArm {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  RobotArmComponentImpl ::
#if FW_OBJECT_NAMES == 1
    RobotArmComponentImpl(
        const char *const compName
    ) :
      RobotArmComponentBase(compName)
#else
    RobotArmComponentImpl(void)
#endif
  {

  }

  void RobotArmComponentImpl ::
    init(
        const NATIVE_INT_TYPE queueDepth,
        const NATIVE_INT_TYPE instance
    )
  {
    RobotArmComponentBase::init(queueDepth, instance);
  }

  RobotArmComponentImpl ::
    ~RobotArmComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void RobotArmComponentImpl ::
    Run_handler(
        const NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    // TODO
  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void RobotArmComponentImpl ::
    SET_Arm_Angle_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        F32 angle
    )
  {
    // TODO
    this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
  }

  void RobotArmComponentImpl ::
    SET_Base_Angle_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        F32 angle
    )
  {
    // TODO
    this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
  }

  void RobotArmComponentImpl ::
    SET_Height_Angle_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        F32 angle
    )
  {
    // TODO
    this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
  }

  void RobotArmComponentImpl ::
    SET_Length_Angle_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        F32 angle
    )
  {
    // TODO
    this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
  }

} // end namespace RobotArm
