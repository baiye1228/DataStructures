/**
 * ************************************************************************
 * @filename: sports.h
 *
 * @brief : 运动会安排比赛
 *
 *
 * @author : baiyebzx (baiyebzx1228@gmail.com)
 * @date : 2024-08-25
 *
 * ************************************************************************
 */

#ifndef _SPORTS_H_
#define _SPORTS_H_

namespace bu_tools {

class Sports {

private:
  int m_game_num;      //比赛项目数
  int m_max_attend;    //每个运动员最多允许参加的比赛项目数
  int m_anthelete_num; //运动员人数
  int *m_collusion;    //项目冲突矩阵
  int *game_arrange;   //比赛安排

public:
  void ArrangeSports();
};

} // namespace bu_tools

#endif // _SPORTS_H_