#include "robot/robot_main.hpp"
#include "robot/devices/data_storage_class.hpp"

#ifndef OPTICAL_CLASS_H
#define OPTICAL_CLASS_H

namespace SENSOR{
  class Optical{
  private:
    Robot& m_robot;

    std::string m_name;
    short m_port{};
    short m_pwm_value{};

    Data_Storing m_settings;

  public:
    //Constructor
    Optical(Robot &p_robot, std::string const p_name, short const p_port, short const p_pwm_value);

    //Getter Functions
    short get_port(){ return m_port; }

    std::string get_name(){ return m_name; }

    double get_hue(){ return pros::c::optical_get_hue(m_port); }

    double get_saturation(){ return pros::c::optical_get_saturation(m_port); }

    double get_brightness(){ return pros::c::optical_get_brightness(m_port); }

    long get_proximity(){ return pros::c::optical_get_proximity(m_port); }

    long get_led_pwm(){ return pros::c::optical_get_led_pwm(m_port); }

    pros::c::optical_rgb_s_t get_rgb(){ return pros::c::optical_get_rgb(m_port); }

    pros::c::optical_raw_s_t get_raw(){ return pros::c::optical_get_raw(m_port); }

    pros::c::optical_direction_e_t get_gesture(){ return pros::c::optical_get_gesture(m_port); }

    pros::c::optical_gesture_s_t get_gesture_raw(){ return pros::c::optical_get_gesture_raw(m_port); }

    //Setter Functions
    void set_led_pwm(short const p_pwm_value);

    void set_port(short const p_port);

    //Action Functions
    void enable_gesture(){ pros::c::optical_enable_gesture(m_port); }

    void disable_gesture(){ pros::c::optical_disable_gesture(m_port); }
  };
}

#endif //OPTICAL_CLASS_H
