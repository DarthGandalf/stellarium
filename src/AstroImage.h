#ifndef ASTROIMAGE_H_
#define ASTROIMAGE_H_

#include "STexture.h"
#include "vecmath.h"

class Projector;
class Navigator;
class ToneReproductor;

//! Base class for any astro image with a fixed position
class AstroImage
{
public:
	AstroImage();
	AstroImage(STexture* tex, const Vec3d& v0, const Vec3d& v1, const Vec3d& v2, const Vec3d& v3);
	virtual ~AstroImage();
	
	// Draw the image on the screen. Assume that we are in Orthographic projection mode.
	void draw(Projector *prj, const Navigator *nav, ToneReproductor *eye);
private:
	STexture* tex;
	
	// Position of the 4 corners of the texture in texture coordinates
	Vec3d vertex[4];
};

#endif /*ASTROIMAGE_H_*/
