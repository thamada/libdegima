/**
 * Copyright(c) 2013 by Tsuyoshi Hamada, Nagasaki University 
 * All rights reserved
 */ 

#define TEST_ACCEL yes
#define TEST_BRAKE yes
#define TEST_STREERING yes

#include <iostream>
using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

double get_time(void)
{
  static struct timeval tv;
  static struct timezone tz;
  gettimeofday(&tv, &tz);
  return ((double)(tv.tv_sec  + tv.tv_usec*1.0e-6));
}

#include "DriveLog.h"
using namespace degima;


#include "Vdegima.h"


Vdegima::Vdegima(){
  hev = new HevCnt();
  this->HEV_setup();
}

Vdegima::~Vdegima(){
  DrvInf   _drvInf;
  cerr << "~Vdegima()" << endl;
  usleep(300000);
  set_mode_manual();
  usleep(300000);

  hev->GetDrvInf(&_drvInf);
  check_mode(_drvInf);

  hev->Stop();
  hev->Close();
}

void Vdegima::set_mode_manual(){
  hev->SetDrvMode(MODE_MANUAL);
  hev->SetStrMode(MODE_MANUAL);
  hev->SetDrvServo(0x00);
  hev->SetStrServo(0x00);
  sleep(1);
}

void Vdegima::set_mode_program(){
  hev->SetDrvMode(MODE_PROGRAM);
  hev->SetStrMode(MODE_PROGRAM);
  hev->SetDrvServo(0x10);
  hev->SetStrServo(0x10);
  sleep(1);
}

void Vdegima::change_drive_mode(){
  static bool mode = false;
  if(mode == false){
    std::cout << "PROGRAM MODE: ON" << std::endl;
    set_mode_program();
    mode = true;
  }else{
    std::cout << "PROGRAM MODE: OFF" << std::endl;
    set_mode_manual();
    mode = false;
  }
}

void Vdegima::check_mode(DrvInf& _drvInf)
{
  if     (_drvInf.mode == MODE_PROGRAM) {} //fprintf(stderr, "drv: Programm mode\n");
  else if(_drvInf.mode == MODE_MANUAL)  fprintf(stderr, "drv: Manual mode\n");
  else fprintf(stderr, "drv: Unknown mode [%d]\n", _drvInf.mode);
}


bool Vdegima::send_command(DrvInf& _drvInf, float str, int brk, int acl, int sft){

  int wait = 9950;
  static int sft0=0xffff;
  if(0xffff == sft0) sft0 = sft;

  hev->GetDrvInf(&_drvInf);
  check_mode(_drvInf);

  if(sft0 != sft){
    hev->SetDrvShiftMode(sft);
    sft0 = sft;
  }

  hev->SetStrAngle((int)(str*10.0f));
  hev->SetDrvStroke((int)acl);
  hev->SetBrakeStroke((int)brk);
  usleep(wait);

  return true;
}


void Vdegima::HEV_setup(){
  double t0 = get_time();
  int cnt = 0;
  //  BattInf  _battInf;
  //  BrakeInf _brakeInf;
  DrvInf   _drvInf;
  //  OtherInf _otherInf;
  //  StrInf   _strInf;
  //  int      _errCode;
  //  int      _errLevel;

  hev->Init();
  hev->Start();
  hev->SetDrvMode(MODE_MANUAL);
  hev->SetDrvServo(0x00);
  hev->SetStrMode(MODE_MANUAL);
  hev->SetStrServo(0x00);
  hev->SetDrvVeloc(0);
  hev->SetDrvStroke(0);
  hev->SetBrakeStroke(0);

  int n_wait = 300000;

  set_mode_program();

  hev->GetDrvInf(&_drvInf);
  check_mode(_drvInf);
  usleep(n_wait);

  int shift_pos;

  shift_pos = SHIFT_POS_N;
  hev->SetDrvShiftMode(shift_pos);
  hev->GetDrvInf(&_drvInf);
  check_mode(_drvInf);
  cerr << shift_pos <<endl;
  usleep(1000000);
}

void Vdegima::HEV_SetStrAngle(int value){
  DrvInf   _drvInf;
  hev->GetDrvInf(&_drvInf);
  check_mode(_drvInf);
  float angle = -(value-50)*150.0f;
  hev->SetStrAngle((int)angle);
  cerr << "angle=" << angle << endl;
}


int Vdegima::debug(){
  /**
  double t0 = get_time();
  int cnt = 0;
  BattInf  _battInf;
  BrakeInf _brakeInf;
  DrvInf   _drvInf;
  OtherInf _otherInf;
  StrInf   _strInf;
  int      _errCode;
  int      _errLevel;

  hev = new HevCnt();
  hev->Init();
  hev->Start();
  hev->SetDrvMode(MODE_MANUAL);
  hev->SetDrvServo(0x00);
  hev->SetStrMode(MODE_MANUAL);
  hev->SetStrServo(0x00);
  hev->SetDrvVeloc(0);
  hev->SetDrvStroke(0);
  hev->SetBrakeStroke(0);

  int n_wait = 300000;

  set_mode_program();

  hev->GetDrvInf(&_drvInf);
  check_mode(_drvInf);
  usleep(n_wait);

  int shift_pos;

  shift_pos = SHIFT_POS_N;
  hev->SetDrvShiftMode(shift_pos);
  hev->GetDrvInf(&_drvInf);
  check_mode(_drvInf);
  cerr << shift_pos <<endl;
  usleep(1000000);

  static DriveLog* drvLog;

  drvLog = new degima::DriveLog("log.txt");
  double t1 = get_time();

  while(drvLog->next_line()){
    double tt = (double)(drvLog->uTIME - drvLog->uTIME_init)/1000000.0f;
    long int cnt = drvLog->CNT - drvLog->CNT_init;
    float str = drvLog->STR_target;
    float brk = drvLog->BRK_target;
    float acl = drvLog->ACL_target;
    float sft = drvLog->SFT_target;
    send_command(_drvInf, str, brk, acl, sft);

    double t2 = get_time() - t1;

    cerr << (t2-tt) << "\t";  // 1
    cerr << tt << "\t";  // 1
    cerr << cnt << "\t"; // 2
    cerr << str << "\t"; // 3
    cerr << brk << "\t"; // 4 
    cerr << acl << "\t"; // 5
    cerr << sft << "\t"; // 6
    cerr << endl;
  }

  usleep(300000);
  shift_pos = SHIFT_POS_N;
  hev->SetDrvShiftMode(shift_pos);
  hev->GetDrvInf(&_drvInf);
  check_mode(_drvInf);
  cerr << shift_pos <<endl;
  usleep(1000000);

  usleep(300000);
  set_mode_manual();
  usleep(300000);

  hev->GetDrvInf(&_drvInf);
  check_mode(_drvInf);

  hev->Stop();
  hev->Close();
  */
  return 0;
}

