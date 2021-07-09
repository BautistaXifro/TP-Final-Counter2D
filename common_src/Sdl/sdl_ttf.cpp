#include "sdl_ttf.h"

SdlTtf::SdlTtf(SdlRenderer& renderer, std::string path, int size):renderer(renderer){
    printf("arranco a inicilizarse ttf\n");
    if( TTF_Init() == -1 ){
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
    }

    this->font = TTF_OpenFont( path.c_str(), size );
    if( this->font == NULL ){
		printf( "Failed to load the font! SDL_ttf Error: %s\n", TTF_GetError() );
	}
    printf("termino de inicilizarse ttf\n");
    // SDL_Surface* textSurface = TTF_RenderText_Solid( this->font, "Boca", {0xff,0xff,0xff});
    // SdlTexture texture(this->renderer, textSurface);
    // SDL_FreeSurface( textSurface );
    // texture.render(250, 250);
}

SdlTtf::~SdlTtf(){
    if (this->font != NULL){
        TTF_CloseFont(this->font);
        this->font = NULL;
        TTF_Quit();
    }
}

SdlTexture SdlTtf::createTextureFromText(std::string text, struct Color color){
    SDL_Surface* textSurface = TTF_RenderText_Solid( this->font, text.c_str(), {color.r,color.g,color.b});
	if( textSurface == NULL ){
        printf("- %s -\n", text.c_str());
		printf( "No se pudo crear la textura. SDL_ttf Error: %s\n", TTF_GetError() );
	} 

    SdlTexture texture(this->renderer, textSurface);
    SDL_FreeSurface( textSurface );
    return texture;
}
