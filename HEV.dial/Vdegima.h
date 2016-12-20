/**
 * Copyright(c) 2013 by Tsuyoshi Hamada, Nagasaki University 
 * All rights reserved
 */ 
#ifndef VDEGIMA_H
#define VDEGIMA_H

#include <iostream>
#include "HevCnt.h"

class Vdegima{
public:
  Vdegima();
  ~Vdegima();
  void set_mode_manual();
  void set_mode_program();
  void change_drive_mode();
  void HEV_setup();
  void HEV_SetStrAngle(int value);
  int debug();
 private:
  HevCnt* hev;
  void check_mode(DrvInf& _drvInf);
  bool send_command(DrvInf& _drvInf, float str, int brk, int acl, int sft);
};

#endif /* VDEGIMA_H */

