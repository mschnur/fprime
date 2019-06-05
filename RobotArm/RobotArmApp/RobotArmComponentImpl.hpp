// ======================================================================
// \title  RobotArmComponentImpl.hpp
// \author erynqian
// \brief  hpp file for RobotArm component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef RobotArm_HPP
#define RobotArm_HPP

#include "RobotArm/RobotArmApp/RobotArmComponentAc.hpp"

namespace RobotArm {

  class RobotArmComponentImpl :
    public RobotArmComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object RobotArm
      //!
      RobotArmComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName /*!< The component name*/
#else
          void
#endif
      );

      //! Initialize object RobotArm
      //!
      void init(
          const NATIVE_INT_TYPE queueDepth, /*!< The queue depth*/
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object RobotArm
      //!
      ~RobotArmComponentImpl(void);

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for Run
      //!
      void Run_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          NATIVE_UINT_TYPE context /*!< The call order*/
      );

    PRIVATE:

      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for SET_Arm_Angle command handler
      //! Set arm angle
      void SET_Arm_Angle_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          F32 angle /*!< Arm angle*/
      );

      //! Implementation for SET_Base_Angle command handler
      //! Set base angle
      void SET_Base_Angle_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          F32 angle /*!< Base angle*/
      );

      //! Implementation for SET_Height_Angle command handler
      //! Set height angle
      void SET_Height_Angle_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          F32 angle /*!< Angle to send*/
      );

      //! Implementation for SET_Length_Angle command handler
      //! Set length angle
      void SET_Length_Angle_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          F32 angle /*!< Angle to send*/
      );


    };

} // end namespace RobotArm

#endif
