// generated 2007/4/6 16:01:19 CLT by chupacabrasx@amd64-3000.(none)
// using glademm V2.6.0
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/chupacabrasx/codeblocks/TreeGrowthSimulator/modeladorCambiosGL.glade
// for gtk 2.10.6 and gtkmm 2.10.6
//
// Please modify the corresponding derived classes in ./src/GUIDialogRefinar.cc


#if defined __GNUC__ && __GNUC__ < 3
#error This program will crash if compiled with g++ 2.x
// see the dynamic_cast bug in the gtkmm FAQ
#endif //
#include "config.h"
#include <gtkmmconfig.h>
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>2
//#include <sigc++/compatibility.h>
#define GMM_GTKMM_22_24(a,b) b
#else //gtkmm 2.2
#define GMM_GTKMM_22_24(a,b) a
#endif //
#include "GUIDialogRefinar_glade.hh"
#include <gdk/gdkkeysyms.h>
#include <gtkmm/accelgroup.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/adjustment.h>

GUIDialogRefinar_glade::GUIDialogRefinar_glade()
{  GUIDialogRefinar = this;
   gmm_data = new GlademmData(get_accel_group());
   cancelbutton4 = Gtk::manage(new class Gtk::Button(Gtk::StockID("gtk-cancel")));
   okbutton4 = Gtk::manage(new class Gtk::Button(Gtk::StockID("gtk-apply")));

   Gtk::RadioButton::Group _RadioBGroup_radiobuttonLeppDelaunay;
   radiobuttonLeppDelaunay = Gtk::manage(new class Gtk::RadioButton(_RadioBGroup_radiobuttonLeppDelaunay, "Lepp-Delaunay"));
   radiobuttonDelaunayLongestEdgeBisection = Gtk::manage(new class Gtk::RadioButton(_RadioBGroup_radiobuttonLeppDelaunay, "Delaunay Longest Edge Bisection"));
   vbox3 = Gtk::manage(new class Gtk::VBox(false, 0));
   alignment4 = Gtk::manage(new class Gtk::Alignment(0.5, 0.5, 1, 1));
   label20 = Gtk::manage(new class Gtk::Label("<b>Algoritmo</b>"));
   frame4 = Gtk::manage(new class Gtk::Frame());

   Gtk::RadioButton::Group _RadioBGroup_radiobuttonAnguloMinimo;
   radiobuttonAnguloMinimo = Gtk::manage(new class Gtk::RadioButton(_RadioBGroup_radiobuttonAnguloMinimo, "Angulo Minimo"));

   Gtk::Adjustment *spinbuttonAnguloMinimo_adj = Gtk::manage(new class Gtk::Adjustment(27, 0, 30, 1, 10, 10));
   spinbuttonAnguloMinimo = Gtk::manage(new class Gtk::SpinButton(*spinbuttonAnguloMinimo_adj, 1, 0));
   hbox3 = Gtk::manage(new class Gtk::HBox(false, 0));
   radiobuttonAreaCara = Gtk::manage(new class Gtk::RadioButton(_RadioBGroup_radiobuttonAnguloMinimo, "Area Cara Maxima"));

   Gtk::Adjustment *spinbuttonAreaCara_adj = Gtk::manage(new class Gtk::Adjustment(3, 0.10000000149, 1000, 0.10000000149, 10, 10));
   spinbuttonAreaCara = Gtk::manage(new class Gtk::SpinButton(*spinbuttonAreaCara_adj, 1, 2));
   hbox4 = Gtk::manage(new class Gtk::HBox(false, 0));
   radiobuttonLargoArcos = Gtk::manage(new class Gtk::RadioButton(_RadioBGroup_radiobuttonAnguloMinimo, "Largo Arcos Maximo"));

   Gtk::Adjustment *spinbuttonLargoArcos_adj = Gtk::manage(new class Gtk::Adjustment(3, 0.10000000149, 1000, 0.10000000149, 10, 10));
   spinbuttonLargoArcos = Gtk::manage(new class Gtk::SpinButton(*spinbuttonLargoArcos_adj, 1, 2));
   hbox5 = Gtk::manage(new class Gtk::HBox(false, 0));
   vbox5 = Gtk::manage(new class Gtk::VBox(false, 0));
   alignment5 = Gtk::manage(new class Gtk::Alignment(0.5, 0.5, 1, 1));
   label21 = Gtk::manage(new class Gtk::Label("<b>Criterio</b>"));
   frame5 = Gtk::manage(new class Gtk::Frame());
   vbox4 = Gtk::manage(new class Gtk::VBox(false, 0));
   cancelbutton4->set_flags(Gtk::CAN_FOCUS);
   cancelbutton4->set_flags(Gtk::CAN_DEFAULT);
   cancelbutton4->set_relief(Gtk::RELIEF_NORMAL);
   okbutton4->set_flags(Gtk::CAN_FOCUS);
   okbutton4->set_flags(Gtk::CAN_DEFAULT);
   okbutton4->set_relief(Gtk::RELIEF_NORMAL);
   GUIDialogRefinar->get_action_area()->property_layout_style().set_value(Gtk::BUTTONBOX_END);
   radiobuttonLeppDelaunay->set_flags(Gtk::CAN_FOCUS);
   radiobuttonLeppDelaunay->set_relief(Gtk::RELIEF_NORMAL);
   radiobuttonLeppDelaunay->set_mode(true);
   radiobuttonLeppDelaunay->set_active(false);
   radiobuttonDelaunayLongestEdgeBisection->set_flags(Gtk::CAN_FOCUS);
   radiobuttonDelaunayLongestEdgeBisection->set_relief(Gtk::RELIEF_NORMAL);
   radiobuttonDelaunayLongestEdgeBisection->set_mode(true);
   radiobuttonDelaunayLongestEdgeBisection->set_active(false);
   vbox3->pack_start(*radiobuttonLeppDelaunay, Gtk::PACK_SHRINK, 0);
   vbox3->pack_start(*radiobuttonDelaunayLongestEdgeBisection, Gtk::PACK_SHRINK, 0);
   alignment4->add(*vbox3);
   label20->set_alignment(0.5,0.5);
   label20->set_padding(0,0);
   label20->set_justify(Gtk::JUSTIFY_LEFT);
   label20->set_line_wrap(false);
   label20->set_use_markup(true);
   label20->set_selectable(false);
   frame4->set_shadow_type(Gtk::SHADOW_NONE);
   frame4->set_label_align(0,0.5);
   frame4->add(*alignment4);
   frame4->set_label_widget(*label20);
   radiobuttonAnguloMinimo->set_flags(Gtk::CAN_FOCUS);
   radiobuttonAnguloMinimo->set_relief(Gtk::RELIEF_NORMAL);
   radiobuttonAnguloMinimo->set_mode(true);
   radiobuttonAnguloMinimo->set_active(false);
   spinbuttonAnguloMinimo->set_flags(Gtk::CAN_FOCUS);
   spinbuttonAnguloMinimo->set_update_policy(Gtk::UPDATE_ALWAYS);
   spinbuttonAnguloMinimo->set_numeric(true);
   spinbuttonAnguloMinimo->set_digits(0);
   spinbuttonAnguloMinimo->set_wrap(false);
   hbox3->pack_start(*radiobuttonAnguloMinimo, Gtk::PACK_SHRINK, 0);
   hbox3->pack_start(*spinbuttonAnguloMinimo);
   radiobuttonAreaCara->set_flags(Gtk::CAN_FOCUS);
   radiobuttonAreaCara->set_relief(Gtk::RELIEF_NORMAL);
   radiobuttonAreaCara->set_mode(true);
   radiobuttonAreaCara->set_active(false);
   spinbuttonAreaCara->set_sensitive(false);
   spinbuttonAreaCara->set_flags(Gtk::CAN_FOCUS);
   spinbuttonAreaCara->set_update_policy(Gtk::UPDATE_ALWAYS);
   spinbuttonAreaCara->set_numeric(true);
   spinbuttonAreaCara->set_digits(2);
   spinbuttonAreaCara->set_wrap(false);
   hbox4->pack_start(*radiobuttonAreaCara, Gtk::PACK_SHRINK, 0);
   hbox4->pack_start(*spinbuttonAreaCara);
   radiobuttonLargoArcos->set_flags(Gtk::CAN_FOCUS);
   radiobuttonLargoArcos->set_relief(Gtk::RELIEF_NORMAL);
   radiobuttonLargoArcos->set_mode(true);
   radiobuttonLargoArcos->set_active(false);
   spinbuttonLargoArcos->set_sensitive(false);
   spinbuttonLargoArcos->set_flags(Gtk::CAN_FOCUS);
   spinbuttonLargoArcos->set_update_policy(Gtk::UPDATE_ALWAYS);
   spinbuttonLargoArcos->set_numeric(true);
   spinbuttonLargoArcos->set_digits(2);
   spinbuttonLargoArcos->set_wrap(false);
   hbox5->pack_start(*radiobuttonLargoArcos, Gtk::PACK_SHRINK, 0);
   hbox5->pack_start(*spinbuttonLargoArcos);
   vbox5->pack_start(*hbox3, Gtk::PACK_SHRINK, 0);
   vbox5->pack_start(*hbox4, Gtk::PACK_SHRINK, 0);
   vbox5->pack_start(*hbox5, Gtk::PACK_SHRINK, 0);
   alignment5->add(*vbox5);
   label21->set_alignment(0.5,0.5);
   label21->set_padding(0,0);
   label21->set_justify(Gtk::JUSTIFY_LEFT);
   label21->set_line_wrap(false);
   label21->set_use_markup(true);
   label21->set_selectable(false);
   frame5->set_shadow_type(Gtk::SHADOW_NONE);
   frame5->set_label_align(0,0.5);
   frame5->add(*alignment5);
   frame5->set_label_widget(*label21);
   vbox4->pack_start(*frame4);
   vbox4->pack_start(*frame5);
   GUIDialogRefinar->get_vbox()->set_homogeneous(false);
   GUIDialogRefinar->get_vbox()->set_spacing(0);
   GUIDialogRefinar->get_vbox()->pack_start(*vbox4);
   GUIDialogRefinar->set_title("Refinar");
   GUIDialogRefinar->set_modal(false);
   GUIDialogRefinar->property_window_position().set_value(Gtk::WIN_POS_NONE);
   GUIDialogRefinar->set_resizable(true);
   GUIDialogRefinar->property_destroy_with_parent().set_value(false);
   GUIDialogRefinar->set_has_separator(true);
   GUIDialogRefinar->add_action_widget(*cancelbutton4, -6);
   GUIDialogRefinar->add_action_widget(*okbutton4, -10);
   cancelbutton4->show();
   okbutton4->show();
   radiobuttonLeppDelaunay->show();
   radiobuttonDelaunayLongestEdgeBisection->show();
   vbox3->show();
   alignment4->show();
   label20->show();
   frame4->show();
   radiobuttonAnguloMinimo->show();
   spinbuttonAnguloMinimo->show();
   hbox3->show();
   radiobuttonAreaCara->show();
   spinbuttonAreaCara->show();
   hbox4->show();
   radiobuttonLargoArcos->show();
   spinbuttonLargoArcos->show();
   hbox5->show();
   vbox5->show();
   alignment5->show();
   label21->show();
   frame5->show();
   vbox4->show();
   GUIDialogRefinar->show();
   radiobuttonAnguloMinimo->signal_toggled().connect(sigc::mem_fun(*this, &GUIDialogRefinar_glade::on_radiobuttonAnguloMinimo_toggled), false);
   radiobuttonAreaCara->signal_toggled().connect(sigc::mem_fun(*this, &GUIDialogRefinar_glade::on_radiobuttonAreaCara_toggled), false);
   radiobuttonLargoArcos->signal_toggled().connect(sigc::mem_fun(*this, &GUIDialogRefinar_glade::on_radiobuttonLargoArcos_toggled), false);
}

GUIDialogRefinar_glade::~GUIDialogRefinar_glade()
{  delete gmm_data;
}
