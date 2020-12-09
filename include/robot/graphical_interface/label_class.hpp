#include "robot/robot_main.hpp"

#ifndef LABEL_CLASS_H
#define LABEL_CLASS_H

namespace GUI{
  template <class T = std::string>
  class Label{
  private:
    short m_xOrigin{};
    short m_yOrigin{};

    std::string m_text{};

    T m_dynamic_functionality;

    lv_obj_t* m_label{};
    lv_style_t* m_style{};

    /*  Converstion Functions pointer -> std::string */
    std::string evaluate_value(int* p_pointer){ return std::to_string(*p_pointer); }

    std::string evaluate_value(double* p_pointer){ return std::to_string(*p_pointer).substr(0, std::to_string(*p_pointer).find(".")+3); }

    std::string evaluate_value(std::string* p_pointer){ return *p_pointer; }

    std::string evaluate_value(bool* p_pointer);

    /*  Converstion Functions function -> std::string */
    std::string evaluate_value(std::function<int()> p_function){ return std::to_string(p_function()); }

    std::string evaluate_value(std::function<double()> p_function){ return std::to_string(p_function()).substr(0, std::to_string(p_function()).find(".")+3); }

    std::string evaluate_value(std::function<std::string()> p_function){ return p_function(); }

    std::string evaluate_value(std::function<bool()> p_function);

    /*  No Dynamic Feature */
    std::string evaluate_value(std::string p_pointer){ return "Error"; }

  public:
    /*  Constuctors  */
    Label<T>(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text);

    Label<T>(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, T p_dynamic_functionality);

    /*  Getting Function  */
    short get_xOrigin(){ return m_xOrigin; }

    short get_yOrigin(){ return m_yOrigin; }

    std::string get_text(){ return m_text; }

    T get_dynamic_functionality(){ return m_dynamic_functionality; }

    lv_style_t* get_style(){ return m_style; }

    /*  Setter Function  */
    void set_xOrgin(short const p_xOrigin){ m_xOrigin = p_xOrigin; }

    void set_yOrgin(short const p_yOrigin){ m_yOrigin = p_yOrigin; }

    void set_text(std::string const p_text){ m_text = p_text; }

    void set_dynamic_functionality(T p_dynamic_functionality){ m_dynamic_functionality = p_dynamic_functionality; }

    void set_style(lv_style_t& p_style){ m_style = &p_style; }

    /*  Action Functions */
    void draw_label();// TODO: Add Screen& p_screen

    void update_label();// TODO: Add Screen& p_screen

    std::string format_text();
  };
}

template class GUI::Label<int*>;
template class GUI::Label<double*>;
template class GUI::Label<std::string*>;
template class GUI::Label<bool*>;

template class GUI::Label<std::function<int()>>;
template class GUI::Label<std::function<double()>>;
template class GUI::Label<std::function<std::string()>>;
template class GUI::Label<std::function<bool()>>;

#endif // LABEL_CLASS_H
