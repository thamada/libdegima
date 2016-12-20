/**
 * @file	DriveLog.cpp
 * @brief	プレイバック用ドライブログ読込管理クラス 実装
 *
 * @date	2013/01/11
 * @author	Tsuyoshi Hamada
 * @par		Copyright:
 *		2013 XXX All rights reserved.
 */

#include "DriveLog.h"

namespace degima{

  DriveLog::DriveLog(const std::string& s){
    this->_filename = s;
    this->line_num = this->check_line_num(s);
    this->line_num_current = 0;
    this->open_logfile();
    assert(true == this->next_line());
    this->CNT_init = this->CNT;
    this->uTIME_init = this->uTIME;
  }

  bool DriveLog::next_line(){
    int n = this->line_num;

    if(n <= (this->line_num_current)){
      return false;
    }

    {
      std::string s[9];
      for(int i=0; i<9; i++)  *(this->ifs) >> s[i];
      //      std::cout << convStr<float>(s[0]) << "\t";
      //      std::cout << std::endl;


      // 0 "%ld\t", cnt++);
      // 1 "%ld\t", ((_s_time->tm_min)*60+(_s_time->tm_sec))*1000000+_getTime.tv_usec);
      // 2 "%3.2f\t", _strInf.targetAngle);
      //
      // 3 "%d\t",    _brakeInf.targetPedalStr);
      // 4 "%d\t",    _drvInf.targetPedalStr);
      // 5 "%d\t",    _drvInf.targetShift);
      //
      // 6 "%d\t",    _brakeInf.actualPedalStr);
      // 7 "%d\t",    _drvInf.actualPedalStr);
      // 8 "%d\t",    _drvInf.actualShift);
      
      this->CNT   = convStr<long int>  (s[0]); // counter
      this->uTIME = convStr<long int>  (s[1]); // time in usec

      this->STR_target = convStr<float>(s[2]);
      this->STR_actual = 0.0f;

      this->BRK_target = convStr<int>  (s[3]);
      this->ACL_target = convStr<int>  (s[4]);
      this->SFT_target = convStr<int>  (s[5]);

      this->BRK_actual = convStr<int>  (s[6]);
      this->ACL_actual = convStr<int>  (s[7]);
      this->SFT_actual = convStr<int>  (s[8]);
    }
    (this->line_num_current)++;
    return true;
  }

  DriveLog::~DriveLog(){
    this->close_logfile();
  }
  
  template <class T>
  T DriveLog::convStr(const std::string& s){
    std::istringstream is;
    is.str(s);
    T z;
    is >> z;
    return (z);
  }

  int DriveLog::check_line_num(const std::string fname){
    int n(0);
    char* fname_c = new char(fname.length()+1);
    strcpy(fname_c, fname.c_str());
    std::ifstream xxx(fname_c, std::ios::in);
    while(!xxx.fail()){
      std::string buf;
      getline(xxx, buf);
      if(!xxx.eof()) n++;
    }
    xxx.close();
    delete fname_c;
    return n;
  }

  void DriveLog::open_logfile(){
    std::string fname(this->_filename);
    char* fname_c = new char(fname.length()+1);
    strcpy(fname_c, fname.c_str());
    this->ifs = new std::ifstream (fname_c, std::ios::in);
    delete fname_c;
  }

  void DriveLog::close_logfile(){
    (this->ifs)->close();
  }

} /* namespace degima */


