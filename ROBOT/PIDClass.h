#ifndef PID_h
#define PID_h

#include "Arduino.h"
#include "TINAH.h"



class PIDClass
{

  public:
    PIDClass(int k_p, int k_d);
    void tapeFollow();
    
    
    enum tapeFollowState
    {
      ON,
      STOP
    };

    void SetPIDState( PIDClass::tapeFollowState pidState)
    {
      _pidState = pidState;
    }

    PIDClass::tapeFollowState getPidState() const
    {
      return _pidState;
    }

  private:
    int _left_motor;
    int _right_motor;
    int _thresholdSpeed;
    int _k_p;
    int _k_d;
    int _qrd_left;
    int _qrd_right;
    int _minBlackTapeVoltage_Left;
    int _minBlackTapeVoltage_Right;
    int _error;
    

    PIDClass::tapeFollowState _pidState;
  

};
#endif

