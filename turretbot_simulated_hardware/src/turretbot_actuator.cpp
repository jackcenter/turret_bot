#include "turretbot_simulated_hardware/turretbot_actuator.hpp"

#include <chrono>
#include <cmath>
#include <limits>
#include <memory>
#include <vector>

#include "hardware_interface/actuator_interface.hpp"
#include "hardware_interface/types/hardware_interface_type_values.hpp"
#include "rclcpp/rclcpp.hpp"

namespace turretbot_simulated_hardware
{
CallbackReturn TurretBotActuator::on_init(const hardware_interface::HardwareInfo & info)
{
  if (hardware_interface::ActuatorInterface::on_init(info) != CallbackReturn::SUCCESS)
  {
    return CallbackReturn::ERROR;
  }

  // Fake hardware start times
  hw_start_sec_ = stod(info_.hardware_parameters["example_param_hw_start_duration_sec"]);
  hw_stop_sec_ = stod(info_.hardware_parameters["example_param_hw_stop_duration_sec"]);
  hw_slowdown_ = stod(info_.hardware_parameters["example_param_hw_slowdown"]);

  hw_joint_state_ = std::numeric_limits<double>::quiet_NaN();
  hw_joint_command_ = std::numeric_limits<double>::quiet_NaN();

  const hardware_interface::ComponentInfo & joint = info_.joints[0];

  if (joint.command_interfaces.size() != 1)
  {
    RCLCPP_FATAL(
      rclcpp::get_logger("TurretBotActuator"),
      "Joint '%s' has %zu command interfaces found. 1 expected.", joint.name.c_str(),
      joint.command_interfaces.size());
    return CallbackReturn::ERROR;
  }

  if (joint.command_interfaces[0].name != hardware_interface::HW_IF_POSITION)
  {
    RCLCPP_FATAL(
      rclcpp::get_logger("TurretBotActuator"),
      "Joint '%s' have %s command interfaces found. '%s' expected.", joint.name.c_str(),
      joint.command_interfaces[0].name.c_str(), hardware_interface::HW_IF_POSITION);
    return CallbackReturn::ERROR;
  }

  if (joint.state_interfaces.size() != 1)
  {
    RCLCPP_FATAL(
      rclcpp::get_logger("TurretBotActuator"), "Joint '%s' has %zu state interface. 1 expected.",
      joint.name.c_str(), joint.state_interfaces.size());
    return CallbackReturn::ERROR;
  }

  if (joint.state_interfaces[0].name != hardware_interface::HW_IF_POSITION)
  {
    RCLCPP_FATAL(
      rclcpp::get_logger("TurretBotActuator"), "Joint '%s' have %s state interface. '%s' expected.",
      joint.name.c_str(), joint.state_interfaces[0].name.c_str(),
      hardware_interface::HW_IF_POSITION);
    return CallbackReturn::ERROR;
  }

  return CallbackReturn::SUCCESS;
}

CallbackReturn TurretBotActuator::on_configure(
  const rclcpp_lifecycle::State & /*previous_state*/)
{
  // START: This part here is for exemplary purposes - Please do not copy to your production code
  RCLCPP_INFO(
    rclcpp::get_logger("TurretBotActuator"), "Configuring ...please wait...");

  for (int i = 0; i < hw_start_sec_; i++)
  {
    rclcpp::sleep_for(std::chrono::seconds(1));
    RCLCPP_INFO(
      rclcpp::get_logger("TurretBotActuator"), "%.1f seconds left...",
      hw_start_sec_ - i);
  }
  // END: This part here is for exemplary purposes - Please do not copy to your production code

  // reset values always when configuring hardware
  hw_joint_command_ = 0.0;
  hw_joint_state_ = 0.0;

  RCLCPP_INFO(rclcpp::get_logger("TurretBotActuator"), "Successfully configured!");

  return CallbackReturn::SUCCESS;
}

std::vector<hardware_interface::StateInterface> TurretBotActuator::export_state_interfaces()
{
  std::vector<hardware_interface::StateInterface> state_interfaces;

  state_interfaces.emplace_back(hardware_interface::StateInterface(
    info_.joints[0].name, hardware_interface::HW_IF_POSITION, &hw_joint_state_));

  return state_interfaces;
}

std::vector<hardware_interface::CommandInterface> TurretBotActuator::export_command_interfaces()
{
  std::vector<hardware_interface::CommandInterface> command_interfaces;

  command_interfaces.emplace_back(hardware_interface::CommandInterface(
    info_.joints[0].name, hardware_interface::HW_IF_POSITION, &hw_joint_command_));

  return command_interfaces;
}

CallbackReturn TurretBotActuator::on_activate(const rclcpp_lifecycle::State & /*previous_state*/)
{
  // START: This part here is for exemplary purposes - Please do not copy to your production code
  RCLCPP_INFO(rclcpp::get_logger("TurretBotActuator"), "Activating ...please wait...");

  for (int i = 0; i < hw_start_sec_; i++)
  {
    rclcpp::sleep_for(std::chrono::seconds(1));
    RCLCPP_INFO(rclcpp::get_logger("TurretBotActuator"), "%.1f seconds left...", hw_start_sec_ - i);
  }
  // END: This part here is for exemplary purposes - Please do not copy to your production code

  // set some default values for joints
  if (std::isnan(hw_joint_state_))
  {
    hw_joint_state_ = 0;
    hw_joint_command_ = 0;
  }

  RCLCPP_INFO(rclcpp::get_logger("TurretBotActuator"), "Successfully activated!");

  return CallbackReturn::SUCCESS;
}

CallbackReturn TurretBotActuator::on_deactivate(const rclcpp_lifecycle::State & /*previous_state*/)
{
  // START: This part here is for exemplary purposes - Please do not copy to your production code
  RCLCPP_INFO(rclcpp::get_logger("TurretBotActuator"), "Deactivating ...please wait...");

  for (int i = 0; i < hw_stop_sec_; i++)
  {
    rclcpp::sleep_for(std::chrono::seconds(1));
    RCLCPP_INFO(rclcpp::get_logger("TurretBotActuator"), "%.1f seconds left...", hw_stop_sec_ - i);
  }

  RCLCPP_INFO(rclcpp::get_logger("TurretBotActuator"), "Successfully deactivated!");
  // END: This part here is for exemplary purposes - Please do not copy to your production code

  return CallbackReturn::SUCCESS;
}

hardware_interface::return_type TurretBotActuator::read()
{
  // START: This part here is for exemplary purposes - Please do not copy to your production code
  RCLCPP_INFO(rclcpp::get_logger("TurretBotActuator"), "Reading...");

  // Simulate IP Bot's movement
  hw_joint_state_ = hw_joint_state_ + (hw_joint_command_ - hw_joint_state_) / hw_slowdown_;
  RCLCPP_INFO(
    rclcpp::get_logger("TurretBotActuator"), "Got state %.5f for joint '%s'!", hw_joint_state_,
    info_.joints[0].name.c_str());

  RCLCPP_INFO(rclcpp::get_logger("TurretBotActuator"), "Joints successfully read!");
  // END: This part here is for exemplary purposes - Please do not copy to your production code

  return hardware_interface::return_type::OK;
}

hardware_interface::return_type turretbot_simulated_hardware::TurretBotActuator::write()
{
  RCLCPP_INFO(rclcpp::get_logger("TurretBotActuator"), "Writing...please wait...");

  // Simulate sending commands to the hardware
  RCLCPP_INFO(
    rclcpp::get_logger("TurretBotActuator"), "Got command %.5f for joint '%s'!", hw_joint_command_,
    info_.joints[0].name.c_str());

  RCLCPP_INFO(rclcpp::get_logger("TurretBotActuator"), "Joints successfully written!");
  // END: This part here is for exemplary purposes - Please do not copy to your production code

  return hardware_interface::return_type::OK;
}

}  // namespace turretbot_simulated_hardware

#include "pluginlib/class_list_macros.hpp"

PLUGINLIB_EXPORT_CLASS(
  turretbot_simulated_hardware::TurretBotActuator, hardware_interface::ActuatorInterface)
