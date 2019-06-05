// ======================================================================
// \title  ServoComponentComponentImpl.hpp
// \author sjanoff
// \brief  hpp file for ServoComponent component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef ServoComponent_HPP
#define ServoComponent_HPP

#include "RobotArm/ServoComponent/ServoComponentAc.hpp"

namespace RobotArm {

  class ServoComponentComponentImpl :
    public ServoComponentComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object ServoComponent
      //!
      ServoComponentComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName /*!< The component name*/
#else
          void
#endif
      );

      //! Initialize object ServoComponent
      //!
      void init(
          const NATIVE_INT_TYPE queueDepth, /*!< The queue depth*/
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object ServoComponent
      //!
      ~ServoComponentComponentImpl(void);

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for SetServo
      //!
      void SetServo_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          F32 Angle 
      );

    PRIVATE:

      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for SVO_SETANG command handler
      //! Servo angle set command from app
      void SVO_SETANG_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          F32 angle /*!< Input angle from command*/
      );

      //! Implementation for SVO_DISABLE command handler
      //! Command to disable the servo
      void SVO_DISABLE_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      );

      //! Implementation for SVO_ENABLE command handler
      //! Command to enable the servo
      void SVO_ENABLE_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      );


    };

} // end namespace RobotArm

#endif
