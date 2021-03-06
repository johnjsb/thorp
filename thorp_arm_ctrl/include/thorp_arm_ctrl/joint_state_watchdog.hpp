/*
 * Author: Jorge Santos
 */

#pragma once

#include <deque>

#include <sensor_msgs/JointState.h>

#include <mag_common_cpp_libs/common.hpp>
namespace mcl = mag_common_libs;

namespace thorp_arm_ctrl
{

class JointStateWatchdog
{
public:
  JointStateWatchdog();
  ~JointStateWatchdog();

  void jointStateCB(const sensor_msgs::JointState& msg);

  double gripperOpening() { return mcl::mean(gripper_opening); }
  double gripperEffort() { return mcl::mean(gripper_effort); }

private:
  double gripper_pad_width;
  double gripper_finger_length;
  double gripper_min_opening;
  double gripper_max_opening;
  double gripper_center;
  bool gripper_invert;
  std::string gripper_joint;
  int gripper_joint_index = -1;

  const unsigned int HISTORY_SIZE = 10;
  std::deque<double> gripper_opening;
  std::deque<double> gripper_effort;

  ros::Subscriber joint_state_sub;
  ros::Publisher joint_state_pub;
};

};
