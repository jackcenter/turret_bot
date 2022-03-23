#pragma once

#include <memory>
#include <string>
#include <vector>

#include "hardware_interface/actuator_interface.hpp"
#include "hardware_interface/handle.hpp"
#include "hardware_interface/hardware_info.hpp"
#include "hardware_interface/system_interface.hpp"
#include "hardware_interface/types/hardware_interface_return_values.hpp"
#include "rclcpp/macros.hpp"
#include "turretbot_simulated_hardware/visibility.h"

namespace turretbot_simulated_hardware
{
class TurretBotActuator : public hardware_interface::ActuatorInterface
{
public:
  RCLCPP_SHARED_PTR_DEFINITIONS(TurretBotActuator);

  TURRETBOT_SIMULATED_HARDWARE_PUBLIC
  CallbackReturn on_init(const hardware_interface::HardwareInfo & info) override;

  TURRETBOT_SIMULATED_HARDWARE_PUBLIC
  std::vector<hardware_interface::StateInterface> export_state_interfaces() override;

  TURRETBOT_SIMULATED_HARDWARE_PUBLIC
  std::vector<hardware_interface::CommandInterface> export_command_interfaces() override;

  TURRETBOT_SIMULATED_HARDWARE_PUBLIC
  CallbackReturn on_configure(const rclcpp_lifecycle::State & previous_state) override;

  TURRETBOT_SIMULATED_HARDWARE_PUBLIC
  CallbackReturn on_activate(const rclcpp_lifecycle::State & previous_state) override;

  TURRETBOT_SIMULATED_HARDWARE_PUBLIC
  CallbackReturn on_deactivate(const rclcpp_lifecycle::State & previous_state) override;

  // TURRETBOT_SIMULATED_HARDWARE_PUBLIC
  // CallbackReturn on_shutdown(const rclcpp_lifecycle::State & previous_state) override;

  TURRETBOT_SIMULATED_HARDWARE_PUBLIC
  hardware_interface::return_type read() override;

  TURRETBOT_SIMULATED_HARDWARE_PUBLIC
  hardware_interface::return_type write() override;

private:
  // Parameters for the Turret Bot simulation
  double hw_start_sec_;
  double hw_stop_sec_;
  double hw_slowdown_;

  // Store the command and state for the simulated robot
  double hw_joint_command_;
  double hw_joint_state_;
};

}  // namespace ros2_control_demo_hardware
