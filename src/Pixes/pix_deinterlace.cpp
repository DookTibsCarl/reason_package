/*
 *  pix_deinterlace.cpp
 *  GEM_darwin
 *
 *  Created by lincoln on 11/18/05.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */

#include "pix_deinterlace.h"

CPPEXTERN_NEW(pix_deinterlace)

/////////////////////////////////////////////////////////
//
// pix_2grey
//
/////////////////////////////////////////////////////////
// Constructor
//
/////////////////////////////////////////////////////////
pix_deinterlace :: pix_deinterlace()
{ 
	m_mode = 1;
}

/////////////////////////////////////////////////////////
// Destructor
//
/////////////////////////////////////////////////////////
pix_deinterlace :: ~pix_deinterlace()
{ }

void pix_deinterlace :: processYUVImage(imageStruct &image)
{

int	row, col,field1,field2,field3;
	int temp1, temp2,temp3;
	
	unsigned char *pixels=image.data;
	
	field1 = 0;
	field2 = image.xsize*2;
	field3 = image.xsize*4;
	
	if (m_mode){
	
	for (row = 0; row < (image.ysize/2)-1; row++){
		
		for (col = 0; col < image.xsize; col++){
			
				
				pixels[field2] = (pixels[field1] + pixels[field3]) / 2;
				field1++;
				field2++; 
				field3++;
								pixels[field2] = (pixels[field1] + pixels[field3]) / 2;
				field1++;
				field2++;
				field3++;
		}
		field1+=image.xsize;
		field2+=image.xsize;
		field1+=image.xsize;
		field2+=image.xsize;
		field3+=image.xsize;
		field3+=image.xsize;
	}
	}else{
	for (row = 0; row < (image.ysize/2)-1; row++){
		
		for (col = 0; col < image.xsize; col++){
			
				
				temp1 = abs(pixels[field1] - pixels[field2]);
				
				if (temp1 > 10) pixels[field2] = (pixels[field1] + pixels[field3]) / 2;
				
				field1++;
				field2++; 
				field3++;
				//pixels[field2] = pixels[field1];
				//pixels[field2] = (pixels[field1] + pixels[field2]) /2;
				//pixels[field2] = (pixels[field1] + pixels[field2] + pixels[field3]) / 3;
				/*
				temp1 = (pixels[field1] + pixels[field2]) / 2;
				temp2 = (pixels[field2] + pixels[field3]) / 2;
				pixels[field2] = (temp1 + temp2) / 2;*/
				
				temp1 = abs(pixels[field1] - pixels[field2]);
				
				if (temp1 > 10) pixels[field2] = (pixels[field1] + pixels[field3]) / 2;
				
				field1++;
				field2++;
				field3++;
		}
		field1+=image.xsize;
		field2+=image.xsize;
		field1+=image.xsize;
		field2+=image.xsize;
		field3+=image.xsize;
		field3+=image.xsize;
	}	
	}


}

#ifdef __VEC__
void pix_deinterlace :: processYUVAltivec(imageStruct &image)
{

	union{
		unsigned char			c[16];
		vector unsigned char	v;
	}charBuffer;

	int	row, col,field1,field2,field3, stride;
	vector unsigned char temp1, temp2,temp3, thresh;
	vector bool char mask, mask2;
	
	vector unsigned char *pixels=(vector unsigned char *)image.data;
	
	//stride = image.xsize/4; //this is to test a crash
	stride = image.xsize/8; //eight pixels per vector
	field1 = 0;
	field2 = stride;
	field3 = stride*2;
	
	temp1 = vec_splat_u8(0);
	
	charBuffer.c[0] = 10;
	thresh = charBuffer.v;
	thresh = vec_splat(thresh,0);
	
	if (m_mode){
	
	for (row = 0; row < (image.ysize/2)-1; row++){
		
		for (col = 0; col < stride; col++){
			
				pixels[field2] = vec_avg(pixels[field1],pixels[field3]);
				
				//pixels[field2] = temp1;
				//pixels[field2] = pixels[field1];
				
				field1++;
				field2++; 
				field3++;
			
			}
			
		field1+=stride;
		field2+=stride;
		field3+=stride;
		}
	}else{
		
		for (row = 0; row < (image.ysize/2)-1; row++){
			
			for (col = 0; col < stride; col++){
				
				//vec_sub should give modulo difference of field1 and field2
				temp2 = vec_subs(pixels[field1],pixels[field2]);
				
				temp3 = vec_subs(pixels[field2],pixels[field1]);
				
				//compare diff to min to get mask
				
				mask = vec_cmpgt(temp2, thresh);
				mask2 = vec_cmpgt(temp3, thresh);
				
				mask = vec_or(mask,mask2);
				
				//vec_avg field1 and field3 
				
				temp3 = vec_avg(pixels[field1],pixels[field3]);
				
				//vec_sel avg and field2 using the mask 
				
				pixels[field2] = vec_sel(pixels[field2],temp3,(vector unsigned char)mask);
					
				field1++;
				field2++; 
				field3++; 
					
					
			}
		field1+=stride;
		field2+=stride;
		field3+=stride;
		}
	}
	
	
}
#endif //__VEC__
/////////////////////////////////////////////////////////
// static member function
//
/////////////////////////////////////////////////////////
void pix_deinterlace :: obj_setupCallback(t_class *classPtr)
{ 
	class_addmethod(classPtr, (t_method)&pix_deinterlace::modeMessCallback, gensym("mode"),A_FLOAT,A_NULL);
}

void pix_deinterlace :: modeMessCallback(void *data,t_floatarg mode)
{
	
	GetMyClass(data)->m_mode = (int)mode;
	
}
