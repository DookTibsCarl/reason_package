/*-----------------------------------------------------------------
  LOG
  GEM - Graphics Environment for Multimedia

  Generate particles

  Copyright (c) 1997-1999 Mark Danks. mark@danks.org
  Copyright (c) G�nther Geiger. geiger@epy.co.at
  Copyright (c) 2001-2002 IOhannes m zmoelnig. forum::f�r::uml�ute. IEM. zmoelnig@iem.kug.ac.at
  For information on usage and redistribution, and for a DISCLAIMER OF ALL
  WARRANTIES, see the file, "GEM.LICENSE.TERMS" in this distribution.

  -----------------------------------------------------------------*/

#ifndef INCLUDE_PART_SINK_H_
#define INCLUDE_PART_SINK_H_

#include "Base/GemBase.h"
#include "papi.h"

/*-----------------------------------------------------------------
  -------------------------------------------------------------------
  CLASS

  part_sink
    
  Generate particles

  DESCRIPTION

  -----------------------------------------------------------------*/
class GEM_EXTERN part_sink : public GemBase
{
  CPPEXTERN_HEADER(part_sink, GemBase)

    public:

  //////////
  // Constructor
  part_sink(int argc, t_atom*argv);
    	
  //////////
  virtual void 	render(GemState *state);

 protected:
    	
  //////////
  // Destructor
  virtual ~part_sink();
		
  //////////
  // kill inside?
  void			killMess(int num);
  bool			m_kill;

  //////////
  // vel.domain
  PDomainEnum           m_domain;
  void                  domainMess(t_symbol *s);
  float			m_arg[9];
  void			vectorMess(int argc, t_atom*argv);
	
 private:

  //////////
  // static member functions
  static void		killMessCallback(void *data, t_floatarg num);
  static void		domainMessCallback(void *data, t_symbol*s);
  static void		vectorMessCallback(void *data, t_symbol*, int, t_atom*);
};

#endif	// for header file