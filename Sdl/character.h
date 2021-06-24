#ifndef __Character_H__
#define __Character_H__
#include <SDL2/SDL.h>
#include "sdl_renderer.h" 
#include "sdl_texture.h"
#include "camera.h"
#include "stencil.h"
#include "animation.h"

class Character{

    private:
		//The X and Y offsets of the Character
		
		Animation an;
		//The velocity of the Character
		int mVelX, mVelY;
		SDL_Rect area;
		//dimensions of the Character
		Camera& cam;
		Stencil& stn;
		double degrees = 0.0;

    public:
		//Initializes the variables
		Character(SDL_Rect area, SdlTexture& texture, Camera& cam, Stencil& stn);


		//Moves the Character
		void update(int level_width, int level_height);

		//Shows the Character on the screen relative to the camera
		// void render( int camX, int camY );
		void render();

		SDL_Rect getRect();

		void moveRight();
		void moveLeft();
		void moveUp();
		void moveDown();

		void stopRight();
		void stopLeft();
		void stopUp();
		void stopDown();

		void lookAt(int x, int y);

		//Position accessors
		int getPosX();
		int getPosY();

};
#endif
