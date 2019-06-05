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
#include "Os/Task.hpp" // For Os::Task::Delay
#include <stdint.h> // for UINT32_MAX
#include <unistd.h> // For usleep

namespace RobotArm {

  static const NATIVE_INT_TYPE I2C_PORT_NUMBER = 0;
  static const U32 PI_HAT_SERVO_BOARD_ADDRESS = 0x40;
  static const U8 PRESCALE_VALUE_FOR_50HZ_PWM = 0x79;

  static const U8 START_TIME_REG = 0x06;
  static const U8 STOP_TIME_REG = 0x08;

  static const U8 REGISTERS_PER_SERVO = 4;

  static const NATIVE_UINT_TYPE SLEEP_BIT_SHIFT = 4;
  static const NATIVE_UINT_TYPE AUTO_INCREMENT_BIT_SHIFT = 5;
  static const NATIVE_UINT_TYPE RESET_BIT_SHIFT = 7;

  // From https://github.com/sparkfun/Pi_Servo_Hat/blob/master/Examples/servohat_50Hz.py
  static const U16 POS_90_DEGREES = 416; // Tim's is 505
  static const U16 NEG_90_DEGREES = 209; // Tim's is 88

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  ServoComponentComponentImpl ::
#if FW_OBJECT_NAMES == 1
    ServoComponentComponentImpl(
        const char *const compName
    ) :
      ServoComponentComponentBase(compName),
#else
    ServoComponentComponentImpl(void),
#endif
    m_servoNumber(UINT32_MAX),
    m_currentAngle(0.0)
  {
    // Initialize the buffer
    m_buffer.setbufferID(0);
    m_buffer.setmanagerID(0);
    m_buffer.setdata((U64) m_data);
    m_buffer.setsize(I2C_BUFFER_SIZE);
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

  void ServoComponentComponentImpl :: setAngleImpl(F32 angle)
  {
    FW_ASSERT(angle >= -90.0f);
    FW_ASSERT(angle <= 90.0f);

    // Set "start time" register to zero
    m_data[0] = START_TIME_REG + (REGISTERS_PER_SERVO * m_servoNumber);
    m_data[1] = 0;
    m_buffer.setsize(2);
    I2C_out(I2C_PORT_NUMBER, PI_HAT_SERVO_BOARD_ADDRESS, m_buffer); 

    // Here's what this is doing:
    // 1) (angle + 90.0f):
    //      Takes our angle, which is in the range [-90, 90], and converts it into the range [0, 180].
    // 2) ((angle + 90.0f) / 180.0f)):
    //      Takes our angle in the range [0, 180], and calculates the percentage of our max angle (180)
    //      our angle is. For example, if our angle is -90 -> 0.0, 0 -> 0.5, 90 -> 1.0.
    // 3) (POS_90_DEGREES - NEG_90_DEGREES):
    //      Calculate the range of the output units. This will give us the number of ticks there are in
    //      our output unit in the range that is equivalent to [0, 180] degrees.
    // 4) ((POS_90_DEGREES - NEG_90_DEGREES) * ((angle + 90.0f) / 180.0f)):
    //      Calculate the number of output units are equivalent to the percentage of 180 degrees that our
    //      input angle is. So if (POS_90_DEGREES - NEG_90_DEGREES) is 100, an input angle of 0.0 will 
    //      result in the following conversions: 
    //      0.0 in [-90, 90] -> 90.0 in [0, 180] -> 0.5 percent -> 50 ticks
    // 5) NEG_90_DEGREES + ((POS_90_DEGREES - NEG_90_DEGREES) * ((angle + 90.0f) / 180.0f)):
    //      Offset our number of ticks by the minimum value of our output unit. The number of ticks 
    //      calculated in (4) is relative to the range [NEG_90_DEGREES, POS_90_DEGREES], so we need
    //      to offset the calculated number of ticks by the minimum value in that range. In other 
    //      words, the value calculated is (4) assumes that NEG_90_DEGREES is zero. Since it is not 
    //      actually zero, we need to offset the value calculated in (4) by the actual value of 
    //      NEG_90_DEGREES.
    U16 stopTime = NEG_90_DEGREES + ((POS_90_DEGREES - NEG_90_DEGREES) * ((angle + 90.0f) / 180.0f));

    // Set "stop time" register to our calculate time
    m_data[0] = STOP_TIME_REG + (REGISTERS_PER_SERVO * m_servoNumber);
    m_data[1] = (U8) (stopTime & 0x00FF); // Least significant byte.
    m_data[2] = (U8) ((stopTime >> 8) & 0x00FF); // Most significant byte. 
    m_buffer.setsize(3);
    I2C_out(I2C_PORT_NUMBER, PI_HAT_SERVO_BOARD_ADDRESS, m_buffer); 
  
    // Send event(s)
    log_ACTIVITY_HI_SVO_AngleChange(m_servoNumber, m_currentAngle, angle, stopTime);

    // Send telemetry
    tlmWrite_SVO_Angle(angle);
    tlmWrite_SVO_Register(stopTime);

    m_currentAngle = angle;
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
    setAngleImpl(Angle);
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
    setAngleImpl(angle);
    this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
  }

  void ServoComponentComponentImpl ::
    SVO_DISABLE_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq
    )
  {
    // "Disable" the servo by putting it in sleep mode.
    m_data[0] = 0; // Register address zero
    m_data[1] = 1 << SLEEP_BIT_SHIFT; // Enable sleep mode.
    m_buffer.setsize(2);
    I2C_out(I2C_PORT_NUMBER, PI_HAT_SERVO_BOARD_ADDRESS, m_buffer); 

    this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
  }

  void ServoComponentComponentImpl ::
    SVO_ENABLE_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq
    )
  {
    // "Enable" the servo by re-configuring it, which exits sleep mode.
    configurePiHatBoard();
    I2C_out(I2C_PORT_NUMBER, PI_HAT_SERVO_BOARD_ADDRESS, m_buffer); 

    this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
  }

  // ----------------------------------------------------------------------
  // Configuration / Setup
  // ----------------------------------------------------------------------
  
  void ServoComponentComponentImpl :: configurePiHatBoard()
  {
    // Enable the chip
    m_data[0] = 0; // Register address zero
    m_data[1] = 1 << AUTO_INCREMENT_BIT_SHIFT; // Clear low-power (sleep) mode and enable the auto increment.
    m_buffer.setsize(2);
    I2C_out(I2C_PORT_NUMBER, PI_HAT_SERVO_BOARD_ADDRESS, m_buffer);

    // Set the sleep bit so that we can set the prescale value
    m_data[0] = 0; // Register address zero
    m_data[1] = 1 << SLEEP_BIT_SHIFT; // Enable normal mode.
    m_buffer.setsize(2);
    I2C_out(I2C_PORT_NUMBER, PI_HAT_SERVO_BOARD_ADDRESS, m_buffer); 

    Os::Task::delay(500);

    m_data[0] = 0xFE; // Register address zero
    m_data[1] = PRESCALE_VALUE_FOR_50HZ_PWM; // Enable normal mode.
    m_buffer.setsize(2);
    I2C_out(I2C_PORT_NUMBER, PI_HAT_SERVO_BOARD_ADDRESS, m_buffer); 

    // Re-enable the chip and reset from sleep mode. We can't read the I2C, so just assume that that we need to do the reset procedure.

    // 1) Clear the sleep bit.
    m_data[0] = 0; // Register address zero
    m_data[1] = 1 << AUTO_INCREMENT_BIT_SHIFT; // Clear low-power (sleep) mode and enable the auto increment.
    m_buffer.setsize(2);
    I2C_out(I2C_PORT_NUMBER, PI_HAT_SERVO_BOARD_ADDRESS, m_buffer);

    // 2) Wait for at least 500 us
    Os::Task::delay(500);

    // 3) Set the reset bit
    m_data[0] = 0; // Register address zero
    m_data[1] = (1 << RESET_BIT_SHIFT) & (1 << AUTO_INCREMENT_BIT_SHIFT); // Set the reset bit, keeping auto increment on.
    m_buffer.setsize(2);
    I2C_out(I2C_PORT_NUMBER, PI_HAT_SERVO_BOARD_ADDRESS, m_buffer);

    // Enable multi-byte writing
    m_data[0] = 0xFE;  
    m_data[1] = 0x1E;
    m_buffer.setsize(2);
    I2C_out(I2C_PORT_NUMBER, PI_HAT_SERVO_BOARD_ADDRESS, m_buffer);
  }

  void ServoComponentComponentImpl :: setServoNumber(
      U32 servoNumber  //!< The number of the servo on the Pi Hat Board occupied by this Servo.
    )
  {
    m_servoNumber = servoNumber;
  }

} // end namespace RobotArm
