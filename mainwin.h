#ifndef __MAINWIN_H
#define __MAINWIN_H

#include "store.h"
#include <gtkmm.h>
#include <vector>
#include <algorithm>
#include <iomanip>

class Mainwin: public Gtk::Window
{
  public: Mainwin();
  virtual~Mainwin();

  protected:
    void on_save_click();
    void on_save_as_click(); // Saves the current store as the user wants
    void on_open_click(); // Lets the user open a file
    void on_about_click();
    void on_new_store();
    void on_new_customer_click();
    void on_view_customers_click();
    void on_new_order_click();
    void on_view_orders_click();
    void on_new_store_click(); // Create a new store
    void on_new_tool_click(); // Create a new tool selection
    void on_new_plant_click(); // Create a new plant selection 
    void on_new_mulch_click(); // Create a new mulch selection
    void on_view_products_click(); // View products
    void on_quit_click(); // Exit the program
  private:
    Gtk::Label * display; // Update display
    Store * store; // Current store
    std::string filename;
    Gtk::Label * msg;
    int get_int(std::string prompt);
    double get_double(std::string prompt);
    std::string get_string(std::string prompt);
    void set_status(std::string status = "");
};

#endif
