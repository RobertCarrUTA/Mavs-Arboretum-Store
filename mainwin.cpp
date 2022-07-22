#include "mainwin.h"
#include "entrydialog.h"
#include <fstream>
#include <string>

Mainwin::Mainwin() : store{nullptr}, display{new Gtk::Label{}} { // store{nullptr} from lecture 13 slides page 27???

    // /////////////////
    // G U I   S E T U P
    // /////////////////

    set_default_size(500, 500);
    set_title("Manga Manager"); // COME BACK AND CHANGE THIS WHEN YOU HAVE A BETTER IDEA OF WHAT TO PUT!!!

    // Put a vertical box container as the Window contents
    Gtk::Box *vbox = Gtk::manage(new Gtk::VBox);
    add(*vbox);

    // /////// ////////////////////////////////////////////////////////////////
    // M E N U
    // Add a menu bar as the top item in the vertical box
    Gtk::MenuBar *menubar = Gtk::manage(new Gtk::MenuBar);
    vbox->pack_start(*menubar, Gtk::PACK_SHRINK, 0);

    //     F I L E
    // Create a File menu and add to the menu bar
    Gtk::MenuItem *menuitem_file = Gtk::manage(new Gtk::MenuItem("_File", true));
    menubar->append(*menuitem_file);
    Gtk::Menu *filemenu = Gtk::manage(new Gtk::Menu());
    menuitem_file->set_submenu(*filemenu);
    
    //         Q U I T
    // Append Quit to the File menu
    Gtk::MenuItem *menuitem_quit = Gtk::manage(new Gtk::MenuItem("_Quit", true));
    menuitem_quit->signal_activate().connect([this] {this->on_quit_click();});
    filemenu->append(*menuitem_quit);
    
    //     I N S E R T  
    // Create an Insert menu and add to the menu bar
    Gtk::MenuItem *menuitem_insert = Gtk::manage(new Gtk::MenuItem("_Insert", true));
    menubar->append(*menuitem_insert);
    Gtk::Menu *insertmenu = Gtk::manage(new Gtk::Menu());
    menuitem_insert->set_submenu(*insertmenu);
    
    //     N E W   S T O R E
    // Add a new store
    Gtk::MenuItem *menuitem_new = Gtk::manage(new Gtk::MenuItem("_New Store", true));
    menuitem_new->signal_activate().connect([this] {this->on_new_store_click();});
    filemenu->append(*menuitem_new);
    
    //     S A V E   S T O R E
    // Save a store to the default filename
    Gtk::MenuItem *save_button = Gtk::manage(new Gtk::MenuItem("_Save", true));
    //save_button->set_tooltip_markup("Save store to the default filename");
    save_button->signal_activate().connect([this] {this->on_save_click();});
    filemenu->append(*save_button);
    
    //         S A V E   S T O R E   A S
    // Append Save As... to the File menu
    Gtk::MenuItem *menuitem_save_as = Gtk::manage(new Gtk::MenuItem("Save _As", true));
    menuitem_save_as->signal_activate().connect([this] {this->on_save_as_click();});
    filemenu->append(*menuitem_save_as);

    //         O P E N   S T O R E
    // Append Open... to the File menu
    Gtk::MenuItem *menuitem_open = Gtk::manage(new Gtk::MenuItem("_Open", true));
    menuitem_open->signal_activate().connect([this] {this->on_open_click();});
    filemenu->append(*menuitem_open);
    
    //     H E L P
    // Create a Help menu and add to the menu bar
    Gtk::MenuItem *menuitem_help = Gtk::manage(new Gtk::MenuItem("_Help", true));
    menubar->append(*menuitem_help);
    Gtk::Menu *helpmenu = Gtk::manage(new Gtk::Menu());
    menuitem_help->set_submenu(*helpmenu);
    
    //           A B O U T
    // Append About to the Help menu
    Gtk::MenuItem *menuitem_about = Gtk::manage(new Gtk::MenuItem("_About", true));
    menuitem_about->signal_activate().connect([this] {this->on_about_click();});
    helpmenu->append(*menuitem_about);
    
    //    V I E W 
    // Create a View menu and add to the menu bar
    Gtk::MenuItem *menuitem_view = Gtk::manage(new Gtk::MenuItem("_View", true));
    menubar->append(*menuitem_view);
    Gtk::Menu *viewmenu = Gtk::manage(new Gtk::Menu());
    menuitem_view->set_submenu(*viewmenu);
    
    //    I N S E R T  C U S T O M E R
    // Append Tool to the Insert menu
    Gtk::MenuItem *menuitem_customer = Gtk::manage(new Gtk::MenuItem("_Customer", true));
    menuitem_customer->signal_activate().connect([this] {this->on_new_customer_click();});
    insertmenu->append(*menuitem_customer);
    
    //    V I E W  C U S T O M E R S
    // Append View Customer to the Insert menu
    Gtk::MenuItem *menuitem_view_customer = Gtk::manage(new Gtk::MenuItem("_View Customers", true));
    menuitem_view_customer->signal_activate().connect([this] {this->on_view_customers_click();});
    viewmenu->append(*menuitem_view_customer);
    
    //    V I E W  P R O D U C T S
    // Append View Products to the Insert menu
    Gtk::MenuItem *menuitem_view_products = Gtk::manage(new Gtk::MenuItem("_View Products", true));
    menuitem_view_products->signal_activate().connect([this] {this->on_view_products_click();});
    viewmenu->append(*menuitem_view_products);
    
    //           T O O L
    // Append Tool to the Insert menu
    Gtk::MenuItem *menuitem_tool = Gtk::manage(new Gtk::MenuItem("_Tool", true));
    menuitem_tool->signal_activate().connect([this] {this->on_new_tool_click();});
    insertmenu->append(*menuitem_tool);

    //           P L A N T
    // Append Plant to the Insert menu
    Gtk::MenuItem *menuitem_plant = Gtk::manage(new Gtk::MenuItem("_Plant", true));
    menuitem_plant->signal_activate().connect([this] {this->on_new_plant_click();});
    insertmenu->append(*menuitem_plant);
    
    //           M U L C H
    // Append Mulch to the Insert menu
    Gtk::MenuItem *menuitem_mulch = Gtk::manage(new Gtk::MenuItem("_Mulch", true));
    menuitem_mulch->signal_activate().connect([this] {this->on_new_mulch_click();});
    insertmenu->append(*menuitem_mulch);

    //           O R D E R
    // Append Order to the Insert menu
    Gtk::MenuItem *menuitem_order = Gtk::manage(new Gtk::MenuItem("_Order", true));
    menuitem_order->signal_activate().connect([this] {this->on_new_order_click();});
    insertmenu->append(*menuitem_order);
    
    //    V I E W  O R D E R S
    // Append View Orders to the Insert menu
    Gtk::MenuItem *menuitem_view_orders = Gtk::manage(new Gtk::MenuItem("_View Orders", true));
    menuitem_view_orders->signal_activate().connect([this] {this->on_view_orders_click();});
    viewmenu->append(*menuitem_view_orders);
    
    // ///////////// //////////////////////////////////////////////////////////
    // T O O L B A R
    // Add a toolbar to the vertical box below the menu
    Gtk::Toolbar *toolbar = Gtk::manage(new Gtk::Toolbar);
    vbox->pack_start(*toolbar, Gtk::PACK_SHRINK, 0);
    
    //     N E W   G A M E
    // Add a new game icon
    Gtk::ToolButton *new_store_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::NEW));
    new_store_button->set_tooltip_markup("Create a new store, discarding any unsaved progress");
    new_store_button->signal_clicked().connect([this] {this->on_new_store_click();});
    toolbar->append(*new_store_button);
    
    //     O P E N  S T O R E
    // Add a new Open Store icon
    Gtk::ToolButton *open_store_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::OPEN));
    open_store_button->set_tooltip_markup("Open a store file, discarding any unsaved progress");
    open_store_button->signal_clicked().connect([this] {this->on_open_click();});
    toolbar->append(*open_store_button);
    
    //     S A V E  S T O R E
    // Add a new Save Store icon
    Gtk::ToolButton *save_store_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::SAVE));
    save_store_button->set_tooltip_markup("Save a store file, saving all unsaved progress");
    save_store_button->signal_clicked().connect([this] {this->on_save_click();});
    toolbar->append(*save_store_button);
    
    //     S A V E  A S  S T O R E
    // Add a new Save As icon
    Gtk::ToolButton *save_as_store_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::SAVE_AS));
    save_as_store_button->set_tooltip_markup("Save As, saving the file under a user defined name");
    save_as_store_button->signal_clicked().connect([this] {this->on_save_as_click();});
    toolbar->append(*save_as_store_button);
    
    //     S E P A R A T O R
    // Add a little space between the file buttons and add buttons
    Gtk::SeparatorToolItem *sep1 = Gtk::manage(new Gtk::SeparatorToolItem());
    toolbar->append(*sep1);
    
    // Add a toggle button to enable computer to play as Player 2
    Gtk::Image *customer_image = Gtk::manage(new Gtk::Image{"woman.png"});
    Gtk::ToolButton *new_customer = Gtk::manage(new Gtk::ToggleToolButton(*customer_image));
    new_customer->set_tooltip_markup("Add a new customer to the store");
    new_customer->signal_clicked().connect([this] {this->on_new_customer_click();});
    toolbar->append(*new_customer);
    
    // Add a toggle button to enable computer to play as Player 2
    Gtk::Image *order_image = Gtk::manage(new Gtk::Image{"cart.png"});
    Gtk::ToolButton *new_order = Gtk::manage(new Gtk::ToggleToolButton(*order_image));
    new_order->set_tooltip_markup("Add a new order to the store");
    new_order->signal_clicked().connect([this] {this->on_new_order_click();});
    toolbar->append(*new_order);
    
    //     S E P A R A T O R
    // Add a little space between the new customer button and new order button
    Gtk::SeparatorToolItem *sep2 = Gtk::manage(new Gtk::SeparatorToolItem());
    toolbar->append(*sep2);
    
    // Add a toggle button to enable computer to play as Player 2
    Gtk::Image *tool_image = Gtk::manage(new Gtk::Image{"growing.png"});
    Gtk::ToolButton *new_tool_order = Gtk::manage(new Gtk::ToggleToolButton(*tool_image));
    new_tool_order->set_tooltip_markup("Add a new tool to the store");
    new_tool_order->signal_clicked().connect([this] {this->on_new_tool_click();});
    toolbar->append(*new_tool_order);
    
    // Add a toggle button to enable computer to play as Player 2
    Gtk::Image *plant_image = Gtk::manage(new Gtk::Image{"sprout.png"});
    Gtk::ToolButton *new_plant_order = Gtk::manage(new Gtk::ToggleToolButton(*plant_image));
    new_plant_order->set_tooltip_markup("Add a new plant to the store");
    new_plant_order->signal_clicked().connect([this] {this->on_new_plant_click();});
    toolbar->append(*new_plant_order);
    
    // Add a toggle button to enable computer to play as Player 2
    Gtk::Image *mulch_image = Gtk::manage(new Gtk::Image{"wheelbarrow.png"});
    Gtk::ToolButton *new_mulch_order = Gtk::manage(new Gtk::ToggleToolButton(*mulch_image));
    new_mulch_order->set_tooltip_markup("Add a new mulch to the store");
    new_mulch_order->signal_clicked().connect([this] {this->on_new_mulch_click();});
    toolbar->append(*new_mulch_order);
    
    //     S E P A R A T O R
    // Add a little space between the new products buttons and view all buttons
    Gtk::SeparatorToolItem *sep3 = Gtk::manage(new Gtk::SeparatorToolItem());
    toolbar->append(*sep3);
    
    // Add a toggle button to enable computer to play as Player 2
    Gtk::Image *customers_image = Gtk::manage(new Gtk::Image{"group.png"});
    Gtk::ToolButton *view_customers = Gtk::manage(new Gtk::ToggleToolButton(*customers_image));
    view_customers->set_tooltip_markup("View all customers in the current store");
    view_customers->signal_clicked().connect([this] {this->on_view_customers_click();});
    toolbar->append(*view_customers);
    
    // Add a toggle button to enable computer to play as Player 2
    Gtk::Image *orders_image = Gtk::manage(new Gtk::Image{"online-order.png"});
    Gtk::ToolButton *view_orders = Gtk::manage(new Gtk::ToggleToolButton(*orders_image));
    view_orders->set_tooltip_markup("View all orders in the current store");
    view_orders->signal_clicked().connect([this] {this->on_view_orders_click();});
    toolbar->append(*view_orders);
    
    // Add a toggle button to enable computer to play as Player 2
    Gtk::Image *products_image = Gtk::manage(new Gtk::Image{"gardening-tools.png"});
    Gtk::ToolButton *view_products = Gtk::manage(new Gtk::ToggleToolButton(*products_image));
    view_products->set_tooltip_markup("View all products in the current store");
    view_products->signal_clicked().connect([this] {this->on_view_products_click();});
    toolbar->append(*view_products);

    // Adding a scrollbar feature
    Gtk::ScrolledWindow *scroll_window = Gtk::manage(new Gtk::ScrolledWindow);
    scroll_window->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_ALWAYS);
    
    // S T A T U S   B A R   D I S P L A Y ////////////////////////////////////
    // Provide a status bar for store messages
    msg = Gtk::manage(new Gtk::Label());
    msg->set_hexpand(true);
    
    // For a message stack bonus, look at 
    // https://developer.gnome.org/gtkmm/stable/classGtk_1_1Statusbar.html
    
    // /////////////////////////// ////////////////////////////////////////////
    // M A I N   W I N D O W   D I S P L A Y
    //
    display = Gtk::manage(new Gtk::Label());
    display->set_hexpand(true);
    display->set_vexpand(true);
    scroll_window->add(*display);
    vbox->add(*scroll_window);
    vbox->pack_start(*msg, Gtk::PACK_SHRINK, 0);

    // Make the box and everything in it visible
    vbox->show_all();

    // Start a new store
    on_new_store();
    
}

Mainwin::~Mainwin() { }

// /////////////////
// C A L L B A C K S
// /////////////////

// COMBINED observer / callback

void Mainwin::on_save_click() {
    try {
        std::ofstream ofs{store->get_filename()};
        store->save(ofs);
    } catch(std::exception e) {
        Gtk::MessageDialog{*this, "Unable to save data", false, Gtk::MESSAGE_ERROR}.run();
    }
    msg->set_markup("You have just saved the store");
}
    
void Mainwin::on_save_as_click() {
    Gtk::FileChooserDialog dialog("Please choose a file",
          Gtk::FileChooserAction::FILE_CHOOSER_ACTION_SAVE);
    dialog.set_transient_for(*this);

    auto filter_store = Gtk::FileFilter::create();
    filter_store->set_name("Store files");
    filter_store->add_pattern("*.manga");
    dialog.add_filter(filter_store);
 
    auto filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any files");
    filter_any->add_pattern("*");
    dialog.add_filter(filter_any);

    dialog.set_filename("untitled.manga");

    //Add response buttons the the dialog:
    dialog.add_button("_Cancel", 0);
    dialog.add_button("_Save", 1);

    int result = dialog.run();

    if (result == 1) {
        try {
            std::ofstream ofs{dialog.get_filename()};
            store->save(ofs);
            if(!ofs) throw std::runtime_error{"Error writing file!"};
        } catch(std::exception& e) {
            Gtk::MessageDialog{*this, "Unable to save the store!"}.run();
        }
    }
    msg->set_markup("You have just saved the store as a file");
}

void Mainwin::on_open_click() {
    Gtk::FileChooserDialog dialog("Please choose a file", Gtk::FileChooserAction::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(*this);

    auto filter_store = Gtk::FileFilter::create();
    filter_store->set_name("Store files");
    filter_store->add_pattern("*.manga");
    dialog.add_filter(filter_store);
 
    auto filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any files");
    filter_any->add_pattern("*");
    dialog.add_filter(filter_any);

    dialog.set_filename("untitled.manga");

    //Add response buttons the the dialog:
    dialog.add_button("_Cancel", 0);
    dialog.add_button("_Open", 1);

    int result = dialog.run();
    
    if (result == 1) {
        try {
            std::string filename = "untitled.manga";
            filename = dialog.get_filename();
            std::ifstream ifs{filename};
            delete store; store = nullptr;
            store = new Store{ifs};
            on_view_products_click();
        } catch (std::exception& e) {
            Gtk::MessageDialog{*this, "Unable to open store: " + std::string{e.what()},
                false, Gtk::MESSAGE_WARNING}.run();
            on_new_store_click();
        }
    }
    on_view_products_click();
    msg->set_markup("You are currently viewing the store products");
}

void Mainwin::on_about_click() {
    Gtk::AboutDialog dialog;
    dialog.set_transient_for(*this); // Avoid the discouraging warning
    dialog.set_program_name("MANGA");
    auto logo = Gdk::Pixbuf::create_from_file("Garden.jpg");
    dialog.set_logo(logo);
    dialog.set_version("Version 0.3");
    dialog.set_copyright("Copyright 2020");
    dialog.set_license_type(Gtk::License::LICENSE_GPL_3_0);
    std::vector< Glib::ustring > authors = {"Robert L. Carr", "George F. Rice"};
    dialog.set_authors(authors);
    std::vector< Glib::ustring > artists = {
        "Logo Credit: Swallowtail Garden Seeds, licensed under CC BY 2.0 https://search.creativecommons.org/photos/9c918e72-433b-470d-98f8-1ffd1610f6ed", 
        "User Icon Credit: Made by Vitaly Gorbachev https://www.flaticon.com/authors/vitaly-gorbachev",
        "Shopping Icon Credit: Made by Pixel perfect https://www.flaticon.com/authors/pixel-perfect",
        "Tools Icon Credit: Made by iconixar https://www.flaticon.com/authors/iconixar",
        "Plant Icon Credit: Made by Freepik https://www.flaticon.com/authors/freepik",
        "Mulch Icon Credit: Made by iconixar https://www.flaticon.com/authors/iconixar",
        "Customers Icon Credit: Made by Freepik https://www.flaticon.com/authors/freepik",
        "View Orders Icon Credit: Made by Freepik https://www.flaticon.com/authors/freepik",
        "View Products Icon Credit: Made by photo3idea_studio https://www.flaticon.com/authors/photo3idea-studio"};
    dialog.set_artists(artists);
    dialog.run();
    msg->set_markup("You have opened the about page"); 
}

void Mainwin::on_new_store() { // this allows the first store to open as untitled until a new store is named on on_new_store_click()
    delete store;
    store = new Store{"Untitled"};
    msg->set_markup("You have just opened a new store");
}
 
void Mainwin::on_new_customer_click() {

    // Create the dialog on stack with title, avoiding the "discouraging warning"
    Gtk::Dialog dialog{"Enter New Customer Information", *this};

    // Accept the customer's name
    Gtk::Label l_name{"Name"};
    Gtk::Entry e_name;

    // Use an HBox to add a label to the left of the Entry
    Gtk::HBox hb_name;
    hb_name.pack_start(l_name);
    hb_name.pack_start(e_name);
    dialog.get_content_area()->pack_start(hb_name, Gtk::PACK_SHRINK, 0);

    // Accept the customer's phone number
    Gtk::Label l_phone{"Phone"};
    Gtk::Entry e_phone;

    // Use an HBox to add a label to the left of the Entry
    Gtk::HBox hb_phone;
    hb_phone.pack_start(l_phone);
    hb_phone.pack_start(e_phone);
    dialog.get_content_area()->pack_start(hb_phone, Gtk::PACK_SHRINK, 0);
    
    // Accept the customer's email
    Gtk::Label l_email{"Email"};
    Gtk::Entry e_email;

    // Use an HBox to add a label to the left of the Entry
    Gtk::HBox hb_email;
    hb_email.pack_start(l_email);
    hb_email.pack_start(e_email);
    dialog.get_content_area()->pack_start(hb_email, Gtk::PACK_SHRINK, 0);
    
    
    // https://valadoc.org/gtk+-3.0/Gtk.Entry.html was used to find the methods used below
    e_phone.set_placeholder_text("xxx-xxx-xxxx");
    e_email.set_placeholder_text("xxxx@domain.com");


    // Add 2 buttons (Gtk::Dialog handles buttons for you, just use add_button method!)
    // Button response IDs are from https://developer.gnome.org/gtkmm/stable/group__gtkmmEnums.html
    dialog.add_button("Insert", Gtk::RESPONSE_OK);
    dialog.add_button("Cancel", Gtk::RESPONSE_CANCEL);
    // NOTE: The x in the title bar is Gtk::RESPONSE_DELETE_EVENT
    int response;

    // It's ready!  Now display it to the user.
    dialog.show_all();

    while((response = dialog.run()) == Gtk::RESPONSE_OK) {

        // Data validation: If the user doesn't enter a name for the customer, complain
        if (e_name.get_text().size() == 0) {e_name.set_text("*required*"); continue;}
        if (e_phone.get_text().size() == 0) {e_phone.set_text("*required*"); continue;}
        if ((e_phone.get_text().size() >= 1) && (e_phone.get_text().size() < 10) || (e_phone.get_text().size() > 10)) {e_phone.set_text("*10 digit valid number*"); continue;}
        if (e_email.get_text().size() == 0) {e_email.set_text("*required*"); continue;}
         
            std::string name = e_name.get_text();
            std::string phone = e_phone.get_text();
            std::string email = e_email.get_text();
            store->add_customer(*(new Customer{name, phone, email}));
            on_view_customers_click();
            
            e_name.set_text("");
            e_phone.set_text("");
            e_email.set_text("");
            
            
         Gtk::MessageDialog{*this, "Customer " + name + " has been added." }.run();
    }
    msg->set_markup("You have added a new customer");
}

void Mainwin::on_view_customers_click() {
    std::string c = "Current customers\n----------------\n\n";
    store->sortCustomers();
    
    for(int i=0; i < store->customers(); ++i) {
        std::ostringstream oss;
        //store->sortByName(customer);
        oss << store->customer(i) << '\n';
        c += oss.str();
    }
    display->set_text(c);
    msg->set_markup("You are currently viewing the store customers");
}
 
void Mainwin::on_new_order_click() {
    
    set_status();
    int ordernum;
    std::ostringstream oss;
    
    // Select a customer
    {
      Gtk::Dialog dialog{"Order for which customer?", *this};
    
      Gtk::ComboBoxText cbt;
      for(int i=0; i<store->customers(); ++i) {
        oss.str("");
        oss << store->customer(i);
        cbt.append(oss.str());
      }
      cbt.set_active(store->customers()-1);
      dialog.get_content_area()->add(cbt);
    
      dialog.add_button("Start Order", 1);
      dialog.add_button("Cancel", 0);
    
      dialog.show_all();
    
      if(dialog.run() == 0) return; 
      ordernum = store->add_order(store->customer(cbt.get_active_row_number()));
      set_status("Created order " + std::to_string(ordernum));
    }
    
    // Select products
    {
      Gtk::MessageDialog dialog{*this, "Add to Order " + std::to_string(ordernum)};
      
      // Quantity (spin button)
      Gtk::HBox qbox;
      Gtk::Label lq{"Quantity"};
      qbox.add(lq);
      Gtk::SpinButton sb;
      sb.set_range(1.0, 99.0);
      sb.set_increments(1.0, 10.0);
      qbox.add(sb);
      dialog.get_content_area()->add(qbox);
      
      // Product (combo box text)
      Gtk::ComboBoxText cbt;
      for(int i=0; i<store->products(); ++i) {
        oss.str("");
        oss << store->product(i);
        cbt.append(oss.str());
      }
      dialog.get_content_area()->add(cbt);

      // Buttons
      dialog.add_button("Add to Order", 1);    
      dialog.add_button("Order Complete", 0);
    
      // Collect products
      while(true) {
        // Show current order
        oss.str("");
        oss << store->order(ordernum);
        dialog.set_secondary_text(oss.str());
        
        dialog.show_all();
    
        if(dialog.run() == 1)
          store->add_item(ordernum, store->product(cbt.get_active_row_number()), static_cast<int>(sb.get_value()));
        else
          break;
      }
    }
    
    // View the orders
    on_view_orders_click();
    msg->set_markup("You have added an order");
}

void Mainwin::on_view_orders_click() {
    std::ostringstream oss;
    oss << "<tt><u>Current Orders</u>\n";
    for(int i=0; i<store->orders(); ++i)
        oss << "ORDER " << i << '\n' << store->order(i) << "\n\n";
    oss << "</tt>";
    display->set_markup(oss.str());
    msg->set_markup("You are viewing the orders of the store");
}

void Mainwin::on_new_store_click() {
    delete store;
    store = nullptr;
    std::string name = get_string("Name of the new store?");
    store = new Store{name};
    on_view_products_click();
    msg->set_markup("You have just made a new store with a name");
}

void Mainwin::on_new_tool_click() {   

    // Create the dialog on stack with title, avoiding the "discouraging warning"
    Gtk::Dialog dialog{"Enter New Tool Information", *this};

    // Accept the product's name
    Gtk::Label l_name{"Name"};
    Gtk::Entry e_name;

    // Using an HBox to add a label to the left of the Entry
    Gtk::HBox hb_name;
    hb_name.pack_start(l_name);
    hb_name.pack_start(e_name);
    dialog.get_content_area()->pack_start(hb_name, Gtk::PACK_SHRINK, 0);
    
    // Let the user input a price of the new tool being added to the store
    //Gtk::HBox pbox;
    Gtk::Label l_price{"Price"};
    Gtk::SpinButton s_price;
    s_price.set_range(0,99);
    s_price.set_increments(1,5);
    s_price.set_value(5);

    // Use an HBox to add a label to the left of the SpinButton
    Gtk::HBox hb_price;
    hb_price.pack_start(l_price);
    hb_price.pack_start(s_price);
    dialog.get_content_area()->pack_start(hb_price, Gtk::PACK_SHRINK, 0);
    
    // Let the user add a description to the new tool being added to the store
    Gtk::Label l_description{"Description"};
    Gtk::Entry e_description;

    // Use an HBox to add a label to the left of the Entry
    Gtk::HBox hb_description;
    hb_description.pack_start(l_description);
    hb_description.pack_start(e_description);
    dialog.get_content_area()->pack_start(hb_description, Gtk::PACK_SHRINK, 0);

    // Add 2 buttons (Gtk::Dialog handles buttons for you, just use add_button method!)
    // Button response IDs are from https://developer.gnome.org/gtkmm/stable/group__gtkmmEnums.html
    dialog.add_button("Add Tool", Gtk::RESPONSE_OK);
    dialog.add_button("Cancel", Gtk::RESPONSE_CANCEL);
    // NOTE: The x in the title bar is Gtk::RESPONSE_DELETE_EVENT
    int response;

    // It's ready!  Now display it to the user.
    dialog.show_all();

    while((response = dialog.run()) == Gtk::RESPONSE_OK) {

        // Data validation: If the user doesn't enter a name for the tool or description, complain
        if (e_name.get_text().size() == 0) {e_name.set_text("*required*"); continue;}
        if (e_description.get_text().size() == 0) {e_description.set_text("*required*"); continue;}
         
            std::string name = e_name.get_text();
            double price = static_cast<double>(s_price.get_value()); https://lazka.github.io/pgi-docs/Gtk-3.0/classes/SpinButton.html
            std::string description = e_description.get_text();
            store->add_product(*(new Tool{name, price, description}));
            on_view_products_click();
            
            e_name.set_text("");
            s_price.set_text("");
            e_description.set_text("");
            
            
         Gtk::MessageDialog{*this, name + " has been added to your tool products"  }.run();
    }
    
    msg->set_markup("You have created a new tool");
}

void Mainwin::on_new_plant_click() {    
        
    // Create the dialog on stack with title, avoiding the "discouraging warning"
    Gtk::Dialog dialog{"Enter New Plant Information", *this};

    // Accept the plant's name
    Gtk::Label l_name{"Name"};
    Gtk::Entry e_name;

    // Use an HBox to add a label to the left of the Entry
    Gtk::HBox hb_name;
    hb_name.pack_start(l_name);
    hb_name.pack_start(e_name);
    dialog.get_content_area()->pack_start(hb_name, Gtk::PACK_SHRINK, 0);
    
    // Let the user input a price of the new plant being added to the store
    //Gtk::HBox pbox;
    Gtk::Label l_price{"Price"};
    //pbox.add(l_price);
    Gtk::SpinButton s_price;
    s_price.set_range(0,99);
    s_price.set_increments(1,5);
    s_price.set_value(5);

    // Use an HBox to add a label to the left of the SpinButton
    Gtk::HBox hb_price;
    hb_price.pack_start(l_price);
    hb_price.pack_start(s_price);
    dialog.get_content_area()->pack_start(hb_price, Gtk::PACK_SHRINK, 0);
    
    // Let the user add a description to the new plant being added to the store
    Gtk::Label l_description{"Description"};
    Gtk::Entry e_description;

    // Use an HBox to add a label to the left of the Entry
    Gtk::HBox hb_description;
    hb_description.pack_start(l_description);
    hb_description.pack_start(e_description);
    dialog.get_content_area()->pack_start(hb_description, Gtk::PACK_SHRINK, 0);
    
    // Accept the plant's species
    Gtk::Label l_species{"Species"};
    Gtk::Entry e_species;

    // Use an HBox to add a label to the left of the Entry
    Gtk::HBox hb_species;
    hb_species.pack_start(l_species);
    hb_species.pack_start(e_species);
    dialog.get_content_area()->pack_start(hb_species, Gtk::PACK_SHRINK, 0);
    
    // Let the user select an exposure to the new plant being added to the store
    //Gtk::HBox pbox;
    Gtk::Label l_exposure{"Exposure? (1) Shade (2) Part Sun (3) Sun"};
    Gtk::SpinButton s_exposure;
    s_exposure.set_range(1,3);
    s_exposure.set_increments(1,1);
    s_exposure.set_value(1);
    
    // Use an HBox to add a label to the left of the SpinButton
    Gtk::HBox hb_exposure;
    hb_exposure.pack_start(l_exposure);
    hb_exposure.pack_start(s_exposure);
    dialog.get_content_area()->pack_start(hb_exposure, Gtk::PACK_SHRINK, 0);

    // Add 2 buttons (Gtk::Dialog handles buttons for you, just use add_button method!)
    // Button response IDs are from https://developer.gnome.org/gtkmm/stable/group__gtkmmEnums.html
    dialog.add_button("Add Plant", Gtk::RESPONSE_OK);
    dialog.add_button("Cancel", Gtk::RESPONSE_CANCEL);
    // NOTE: The x in the title bar is Gtk::RESPONSE_DELETE_EVENT
    int response;

    // It's ready!  Now display it to the user.
    dialog.show_all();

    while((response = dialog.run()) == Gtk::RESPONSE_OK) {

        // Data validation: If the user doesn't enter a name for the customer, complain
        if (e_name.get_text().size() == 0) {e_name.set_text("*required*"); continue;}
        //if (e_price == 0) {e_price.set_text("*required*"); continue;}
        if (e_description.get_text().size() == 0) {e_description.set_text("*required*"); continue;}
         
            std::string name = e_name.get_text();
            double price = static_cast<double>(s_price.get_value()); https://lazka.github.io/pgi-docs/Gtk-3.0/classes/SpinButton.html
            std::string description = e_description.get_text();
            std::string species = e_species.get_text();
            double e = static_cast<double>(s_exposure.get_value());
            Exposure exposure = (e==1.0) ? Exposure::SHADE : ((e==3.0) ? Exposure::SUN : Exposure::PARTSUN);
            
            store->add_product(*(new Plant{name, price, description, species, exposure}));
            on_view_products_click();
            
            e_name.set_text("");
            s_price.set_text("");
            e_description.set_text("");
            e_species.set_text("");
            s_exposure.set_text("");
            
            
            Gtk::MessageDialog{*this, name + " has been added to your plant products"  }.run();
    }
    msg->set_markup("You have added a new plant to the store");
}

void Mainwin::on_new_mulch_click() {
        
    // Create the dialog on stack with title, avoiding the "discouraging warning"
    Gtk::Dialog dialog{"Add A New Mulch To The Store", *this};

    // Accept the mulch's name
    Gtk::Label l_name{"Name"};
    Gtk::Entry e_name;

    // Use an HBox to add a label to the left of the Entry
    Gtk::HBox hb_name;
    hb_name.pack_start(l_name);
    hb_name.pack_start(e_name);
    dialog.get_content_area()->pack_start(hb_name, Gtk::PACK_SHRINK, 0);
    
    // Let the user input a price of the new mulch being added to the store
    Gtk::Label l_price{"Price"};
    Gtk::SpinButton s_price;
    s_price.set_range(0,99);
    s_price.set_increments(1,5);
    s_price.set_value(5);

    // Use an HBox to add a label to the left of the SpinButton
    Gtk::HBox hb_price;
    hb_price.pack_start(l_price);
    hb_price.pack_start(s_price);
    dialog.get_content_area()->pack_start(hb_price, Gtk::PACK_SHRINK, 0);
    
    // Let the user add a description to the new mulch being added to the store
    Gtk::Label l_description{"Description"};
    Gtk::Entry e_description;

    // Use an HBox to add a label to the left of the Entry
    Gtk::HBox hb_description;
    hb_description.pack_start(l_description);
    hb_description.pack_start(e_description);
    dialog.get_content_area()->pack_start(hb_description, Gtk::PACK_SHRINK, 0);
    
    // Let the user input a volume of the new mulch being added to the store
    Gtk::Label l_volume{"Volume (ft^3) "};
    Gtk::SpinButton s_volume;
    s_volume.set_range(1,99);
    s_volume.set_increments(1,5);
    s_volume.set_value(5);
    
    // Use an HBox to add a label to the left of the SpinButton
    Gtk::HBox hb_volume;
    hb_volume.pack_start(l_volume);
    hb_volume.pack_start(s_volume);
    dialog.get_content_area()->pack_start(hb_volume, Gtk::PACK_SHRINK, 0);
    
    // Let the user select a material to the new mulch being added to the store
    Gtk::Label l_material{"Material? (1) Rubber (2) Pine (3) Cedar (4) Hardwood"};
    Gtk::SpinButton s_material;
    s_material.set_range(1,4);
    s_material.set_increments(1,1);
    s_material.set_value(1);
    
    // Use an HBox to add a label to the left of the SpinButton
    Gtk::HBox hb_material;
    hb_material.pack_start(l_material);
    hb_material.pack_start(s_material);
    dialog.get_content_area()->pack_start(hb_material, Gtk::PACK_SHRINK, 0);

    // Add 2 buttons (Gtk::Dialog handles buttons for you, just use add_button method!)
    // Button response IDs are from https://developer.gnome.org/gtkmm/stable/group__gtkmmEnums.html
    dialog.add_button("Add Mulch", Gtk::RESPONSE_OK);
    dialog.add_button("Cancel", Gtk::RESPONSE_CANCEL);
    // NOTE: The x in the title bar is Gtk::RESPONSE_DELETE_EVENT
    int response;

    // It's ready!  Now display it to the user.
    dialog.show_all();

    while((response = dialog.run()) == Gtk::RESPONSE_OK) {

        // Data validation: If the user doesn't enter a name for the mulch or description, complain
        if (e_name.get_text().size() == 0) {e_name.set_text("*required*"); continue;}
        if (e_description.get_text().size() == 0) {e_description.set_text("*required*"); continue;}
         
            std::string name = e_name.get_text();
            double price = static_cast<double>(s_price.get_value());
            std::string description = e_description.get_text();
            int volume = static_cast<int>(s_volume.get_value());
            int i = static_cast<int>(s_material.get_value());
            Material material;
            if(i == 1) {material = Material::RUBBER;}
            else if (i == 2) {material = Material::PINE;}
            else if (i == 3) {material = Material::CEDAR;}
            else {material = Material::HARDWOOD;}
            store->add_product(*(new Mulch{name, price, description, volume, material}));
            on_view_products_click();
            
            e_name.set_text("");
            s_price.set_text("");
            e_description.set_text("");
            s_volume.set_text("");
            s_material.set_text("");
            
            store->add_product(*(new Mulch{name, price, description, volume, material}));
            on_view_products_click();
            
            Gtk::MessageDialog{*this, name + " has been added to your mulch products" }.run();
    }
        
        msg->set_markup("You have created a new mulch");
}

void Mainwin::on_view_products_click() {
    std::string s = "Current Products\n----------------\n\n";
    for(int i=0; i < store->products(); ++i) {
        std::ostringstream oss;
        oss << store->product(i) << '\n';
        s += oss.str();
    }
    display->set_text(s);
    msg->set_markup("You are viewing the store's products");
}

void Mainwin::on_quit_click() {
    close(); // closes the software
}

std::string Mainwin::get_string(std::string prompt) {
    EntryDialog edialog(*this, "<big>New Product</big>", true, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_OK_CANCEL);
    edialog.set_secondary_text(prompt, true);
    if(edialog.run() == Gtk::RESPONSE_CANCEL) throw std::runtime_error{"CANCEL"};
    return edialog.get_text();
}

double Mainwin::get_double(std::string prompt) {
    while(true) {
        try {
            return std::stod(get_string(prompt));
        } catch(std::exception& e) {
            std::cerr << "ERROR: " << e.what() << std::endl;
        }
    }
}

int Mainwin::get_int(std::string prompt) {
    while(true) {
        try {
            return std::stoi(get_string(prompt));
        } catch(std::exception& e) {
            std::cerr << "ERROR: " << e.what() << std::endl;
        }
    }
}

void Mainwin::set_status(std::string status) {
    msg->set_markup(status);
}
