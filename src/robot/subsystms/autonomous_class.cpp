#include "robot/robot_class.hpp"

#include "robot/devices/motor_class.hpp"
#include "robot/devices/timer_class.hpp"

#include "robot/subsystems/autonomous_class.hpp"
#include "robot/subsystems/holonomic_class.hpp"
#include "robot/subsystems/manipulator.hpp"

/* Base Functions */
Base_Event::Base_Event(Autonomous_Base_Status p_base_status, double p_delay, double p_x_position, double p_y_position, double p_orientation){
  m_base_status = p_base_status;
  m_delay = p_delay;
  m_x_position = p_x_position;
  m_y_position = p_y_position;
  m_orientation = p_orientation;
}

Base_Event Base_Event::base_translate_to(double p_x_position, double p_y_position, double p_delay){// Point to Point
  return Base_Event(BASE_TRANSLATE, p_delay, p_x_position, p_y_position, INT_MIN);
}

Base_Event Base_Event::base_orientate_to(double p_orientation, double p_delay){// Point Rotation
  return Base_Event(BASE_ORIENTATION, p_delay, INT_MIN, INT_MIN, p_orientation);
}

Base_Event Base_Event::base_turn_to(double p_x_position, double p_y_position, double p_delay){// Arc Turn
  return Base_Event(BASE_TURN, p_delay, p_x_position, p_y_position, INT_MIN);
}

Base_Event Base_Event::base_pose_to(double p_x_position, double p_y_position, double p_orientation, double p_delay){// Point to Point with Orientation Change
  return Base_Event(BASE_POSE, p_delay, p_x_position, p_y_position, p_orientation);
}

Base_Event Base_Event::base_align_to_goal(double p_delay){
  return Base_Event(BASE_POSE, p_delay, INT_MIN, INT_MIN, INT_MIN);
}

Base_Event Base_Event::base_stationary(double p_duration){
  return Base_Event(BASE_STATIONARY, p_duration, INT_MIN, INT_MIN, INT_MIN);
}

/* Intake Functions */
Intake_Event::Intake_Event(Autonomous_Intake_Status p_intake_status, Intake_Retract_Mode p_intake_retract, double p_delay){
  m_intake_status = p_intake_status;
  m_delay = p_delay;
}
  
Intake_Event Intake_Event::intake_store(double p_delay){
  return Intake_Event(AUTONOMOUS_INTAKE_STORE, INTAKE_RETRACT_NONE, p_delay);
}

Intake_Event Intake_Event::intake_goal(double p_delay){
  return Intake_Event(AUTONOMOUS_INTAKE_GOAL, INTAKE_RETRACT_NONE, p_delay);
}

Intake_Event Intake_Event::intake_grab(Intake_Retract_Mode p_intake_retract, double p_delay){
  return Intake_Event(AUTONOMOUS_INTAKE_GRAB, p_intake_retract, p_delay);
}

Intake_Event Intake_Event::intake_stationary(double p_delay){
  return Intake_Event(AUTONOMOUS_INTAKE_STATIONARY, INTAKE_RETRACT_NONE, p_delay);
}

/* Lift Functions */
Lift_Event::Lift_Event(Autonomous_Lift_Status p_lift_status, double p_delay){
  m_lift_status = p_lift_status;
  m_delay = p_delay;
}

Lift_Event Lift_Event::lift_score(double p_delay){
  return Lift_Event(AUTONOMOUS_LIFT_SCORE, p_delay);
}

Lift_Event Lift_Event::lift_sort(double p_delay){
  return Lift_Event(AUTONOMOUS_LIFT_SORT, p_delay);
}

Lift_Event Lift_Event::lift_stationary(double p_delay){
  return Lift_Event(AUTONOMOUS_LIFT_STATIONARY, p_delay);
}


Autonomous_Routine::Autonomous_Routine(Robot& p_robot, std::string p_routine_name, Robot_Alliance p_routine_alliance):
m_robot(p_robot),
m_base_timer(*new Timer()),
m_intake_timer(*new Timer()),
m_lift_timer(*new Timer()){
  m_routine_name = p_routine_name;
  m_routine_alliance = p_routine_alliance;
}



std::vector<Autonomous_Routine*> Autonomous_Routine::m_routines;
Autonomous_Routine* Autonomous_Routine::m_selected_routine;
int Autonomous_Routine::m_current_event = 0;
int Autonomous_Routine::m_previous_event = 0;

void Autonomous_Routine::set_selected_routine(std::string p_routine_name){
  for(auto x : m_routines){
    if(x->get_name() == p_routine_name)
      m_selected_routine = x;
  }
}

void Autonomous_Routine::task(){
  Robot& l_robot = m_selected_routine->m_robot;
  Holonomic& l_holonomic = l_robot.get_holonomic();
  Manipulator& l_manipulator = l_robot.get_manipulator();

  Robot_Event l_current_event = m_selected_routine->m_autonomous_events.at(m_current_event);
  
  if(m_current_event != m_previous_event){
    m_previous_event = m_current_event;

    m_selected_routine->m_base_timer.set_flag_delay(l_current_event.m_base_event.m_delay);
    m_selected_routine->m_lift_timer.set_flag_delay(l_current_event.m_lift_event.m_delay);
    m_selected_routine->m_intake_timer.set_flag_delay(l_current_event.m_intake_event.m_delay);
  }
  
  if(m_selected_routine->m_base_timer.get_preform_action()){
    // Change Base movement
  }
  else if(l_holonomic.get_movement_complete()){
    m_current_event++;
  }

  if(m_selected_routine->m_lift_timer.get_preform_action()){
    l_manipulator.set_autonomous_lift_status(l_current_event.m_lift_event.m_lift_status);
  }

  if(m_selected_routine->m_intake_timer.get_preform_action()){
    l_manipulator.set_autonomous_intake_status(l_current_event.m_intake_event.m_intake_status);
  }
}

void Autonomous_Routine::start_autonomous(){
  m_selected_routine->m_base_timer.reset_timer();
  m_selected_routine->m_lift_timer.reset_timer();
  m_selected_routine->m_base_timer.reset_timer();

  m_current_event = 0;
  m_previous_event = -1;
}

void Autonomous_Routine::end_autonomous(){

}