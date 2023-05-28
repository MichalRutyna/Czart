#include "../../lib/functionality/LTexture.h"

LTexture::LTexture()
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    std::cout << "Usunieto teksture o wymiarach " << mWidth << "x" << mHeight << std::endl;
    mfree();
}

void LTexture::mfree()
{
    //Free texture if it exists
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}
SDL_Surface* ScaledCopy(SDL_Surface* src, SDL_Rect* dstSize)
{
	SDL_Surface* scaledCopy(SDL_CreateRGBSurface(0,
		dstSize->w, dstSize->h,
		src->format->BitsPerPixel, 
		src->format->Rmask, src->format->Gmask, src->format->Bmask, src->format->Amask));

	// Get the old mode
	SDL_BlendMode oldBlendMode;
	SDL_GetSurfaceBlendMode(src, &oldBlendMode);

	// Set the new mode so copying the source won't change the source
	SDL_SetSurfaceBlendMode(src, SDL_BLENDMODE_NONE);

	// Do the copy
	if (SDL_BlitScaled(src, NULL, scaledCopy, dstSize) != 0)
	{
        exit(1);
	}

	// Restore the original blending mode
	SDL_SetSurfaceBlendMode(src, oldBlendMode);
	return scaledCopy;
}

bool LTexture::loadFromFile(rendererType& renderer, std::string path, int scaled_width, int scaled_height)
{
    //Get rid of preexisting texture
    mfree();

    //The final texture
    SDL_Texture* newTexture = NULL;

	SDL_Surface * stretchedSurface = new SDL_Surface();

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError());
    }
    else
    {
        if(scaled_width != -1 && scaled_height != -1)
        {
            SDL_Rect* stretchRect = new SDL_Rect();
            stretchRect->x = 0;
            stretchRect->y = 0;
            stretchRect->w = scaled_width;
            stretchRect->h = scaled_height;

            stretchedSurface = ScaledCopy(loadedSurface, stretchRect);
        }
        else stretchedSurface = loadedSurface;

        //Color key image
        SDL_SetColorKey(stretchedSurface, SDL_TRUE, SDL_MapRGB(stretchedSurface->format, 0, 0xFF, 0xFF)); //Wycina kolor cyjanowy

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer.get(), stretchedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        else
        {
            //Get image dimensions
            mWidth = stretchedSurface->w;
            mHeight = stretchedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(stretchedSurface);
    }

    //Return success
    mTexture = newTexture;
    return mTexture != NULL;
}

void LTexture::render(rendererType& renderer, int x, int y, std::shared_ptr<SDL_Rect> clip, double angle, std::shared_ptr<SDL_Point> center, SDL_RendererFlip flip)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    //Set clip rendering dimensions
    if (clip != nullptr)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx(renderer.get(), mTexture, clip.get(), &renderQuad, angle, center.get(), flip);
}

void LTexture::setColor(uint8_t red, uint8_t green, uint8_t blue){
    // Modulacja koloru tekstury
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::SetBlendMode(SDL_BlendMode blending) {
    SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(uint8_t alpha) {
    SDL_SetTextureAlphaMod(mTexture, alpha);
}

int LTexture::width()
{
    return mWidth;
}

int LTexture::height()
{
    return mHeight;
}

void LTexture::changeSize(int w, int h)
{
    mWidth = w;
    mHeight = h;
}
