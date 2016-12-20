#include "DriveLog.h"
#include <iostream>

using namespace std;

int main()
{
  degima::DriveLog log("log.txt");

  while(log.next_line()){
    float tt = (log.uTIME - log.uTIME_init)/1000000.0f;
    long int cnt = log.CNT - log.CNT_init;
    float str = log.STR_target;
    float brk = log.BRK_target;
    float acl = log.ACL_target;
    float sft = log.SFT_target;

    cout << tt << "\t";  // 1
    cout << cnt << "\t"; // 2
    cout << str << "\t"; // 3
    cout << brk << "\t"; // 4 
    cout << acl << "\t"; // 5
    cout << sft << "\t"; // 6
    cout << endl;
  }
  return 0;
}

