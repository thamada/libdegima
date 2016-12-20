//Time-stamp: <2013-01-12 01:03:20 robocar_HV>
/**
 * @file	DriveLog.h
 * @brief	プレイバック用ドライブログ読込管理クラス ヘッダファイル
 *
 * @date	2013/01/11
 * @author	Tsuyoshi Hamada
 * @par		Copyright:
 *		2013 XXX All rights reserved.
 */

#ifndef DRIVELOG_H
#define DRIVELOG_H

#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <iostream>
#include <cassert>

namespace degima
{
  class  DriveLog {
  public:
    DriveLog(const std::string& s);
    ~DriveLog();
    bool next_line();
    long int line_num;
    long int line_num_current;
    long int CNT;
    long int CNT_init;
    long int uTIME;
    long int uTIME_init;

    float STR_target; // Seering Wheal
    float STR_actual;
    int   ACL_target; // Accel Pedal
    int   ACL_actual;
    int   BRK_target; // Brake Pedal
    int   BRK_actual;
    int   SFT_target; // Shift Lever
    int   SFT_actual;

  private:
    std::string _filename;
    std::ifstream* ifs;
    template <class T>  T convStr(const std::string& s);
    int check_line_num(const std::string fname);
    void open_logfile();
    void close_logfile();
  };

} /* namespace degima */

#endif /* DRIVELOG_H */
