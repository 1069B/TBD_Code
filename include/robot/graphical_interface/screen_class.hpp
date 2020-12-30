#include "robot/robot_main.hpp"

#ifndef SCREEN_CLASS_H
#define SCREEN_CLASS_H

namespace GUI{
  class Screen{
  private:
    lv_obj_t* m_screen;
    lv_style_t* m_style;

    std::vector<Rectangle*> m_rectangle_vector;
    std::vector<Label*> m_label_vector;
    std::vector<List*> m_list_vector;
    std::vector<Bar*> m_bar_vector;
    std::vector<Button*> m_button_vector;
    std::vector<Switch*> m_switch_vector;

    std::string m_screen_name;
    std::string m_error_screen;

    /* Static Members */
    static std::vector<Screen*> m_screen_vector;

    static std::string m_current_screen_name;
    static std::string m_previous_screen_name;
    static std::string m_next_screen_name;

    static Screen* m_current_screen_pointer;// TODO:: Created Deafult Screen
    static Screen* m_next_screen_pointer;

    static Data_Storing m_settings;


  public:
    /* Constructor */
    Screen();

    /* Getter Functions */
    std::string get_screen_name(){return m_screen_name; }

    lv_obj_t* get_screen(){return m_screen; }

    /* Add Functions */
    Rectangle& add_rectanlge();

    Label& add_label(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text);
    Label& add_label(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, int& p_int_value);
    Label& add_label(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, double& p_double_value);
    Label& add_label(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, std::string& p_string_value);
    Label& add_label(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, bool& p_bool_value);
    Label& add_label(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, std::function<int()> p_int_value);
    Label& add_label(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, std::function<double()> p_double_value);
    Label& add_label(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, std::function<std::string()> p_string_value);
    Label& add_label(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, std::function<bool()> p_bool_value);

    List& add_list();
    Bar& add_bar();
    Button& add_button();
    Switch& add_switch();

    /* Action */
    void draw_screen();

    void update_screen();

    void delete_screen();

    static void task();
  };
}

#endif // SCREEN_CLASS_H
