// generated 2006/8/15 19:41:35 CLT by chupacabrasx@amd64-3000.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to GUIDialogRefinar.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _GUIDIALOGREFINAR_HH
#  include "GUIDialogRefinar_glade.hh"
#  define _GUIDIALOGREFINAR_HH
class GUIDialogRefinar : public GUIDialogRefinar_glade
{  
	public:
		bool isLeppDelaunay();
		bool isDelaunayLongestEdgeBisection();
		bool isAnguloMinimo();
		bool isAreaCara();
		bool isLargoArcos();
		double anguloMinimo(); //Retorna en radianes
		double areaCara();
		double largoArcos();
	private:        
        void on_radiobuttonAnguloMinimo_toggled();
        void on_radiobuttonAreaCara_toggled();
        void on_radiobuttonLargoArcos_toggled();
};
#endif
