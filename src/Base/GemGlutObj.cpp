////////////////////////////////////////////////////////
//
// GEM - Graphics Environment for Multimedia
//
// zmoelnig@iem.kug.ac.at
//
// Implementation file
//
//    Copyright (c) 1997-1999 Mark Danks.
//    Copyright (c) G�nther Geiger.
//    Copyright (c) 2001-2002 IOhannes m zmoelnig. forum::f�r::uml�ute
//
//    For information on usage and redistribution, and for a DISCLAIMER OF ALL
//    WARRANTIES, see the file, "GEM.LICENSE.TERMS" in this distribution.
//
/////////////////////////////////////////////////////////

#include "GemGlutObj.h"

/////////////////////////////////////////////////////////
//
// GemGlutObj
//
/////////////////////////////////////////////////////////
// Constructor
//
/////////////////////////////////////////////////////////
GemGlutObj :: GemGlutObj(t_floatarg size)
    	   : GemShape(size)
{
#ifndef HAVE_LIBGLUT
  error("GemGlutObj: compiled without GLUT-support - no rendering of GLUT-objects");
#endif
}

/////////////////////////////////////////////////////////
// Destructor
//
/////////////////////////////////////////////////////////
GemGlutObj :: ~GemGlutObj()
{
    // in case we are deleted while still running
    stopRendering();
}

/////////////////////////////////////////////////////////
// static member function
//
/////////////////////////////////////////////////////////
void GemGlutObj :: obj_setupCallback(t_class *classPtr)
{}

