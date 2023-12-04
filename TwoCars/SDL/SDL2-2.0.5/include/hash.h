/*

 * 	Name:	SDL Wrapper

 * 	Author:	Hash Team

 * 	Description:	A c++ wrapper to hide Object Oriented nature of SDL

 */

//	Header files have different path in linux and windows
#if defined(_WIN32) || defined(_WIN64)	//	If Windows

	#include "SDL.h"

	#include "SDL_image.h"

	#include "SDL_ttf.h"

	#include "SDL_mixer.h"

#elif defined(__linux__)	//	If linux (Ubuntu tested successfully)

	#include "SDL2/SDL.h"

	#include "SDL2/SDL_image.h"

	#include "SDL2/SDL_ttf.h"

	#include "SDL2/SDL_mixer.h"

#endif



//	Define colors for SDL_FillRect function

#define  WHITE  0xFFFFFF

#define  RED    0xFF0000

#define  BLACK  0x000000

#define  BLUE   0x0000FF    

#define  GREEN  0x00FF00

#define  PINK   0xFF00FF

#define  PURPLE 0x400080

#define  YELLOW 0xFFFF00

#define  LIGHT_PURPLE  0x8000FF







SDL_Event event;

int ExitRequested=0;



struct mouse 

{

        int left ; 

        int right;

        int x ; 

        int y ; 

        int middle;

        int wheelUp ; 

        int wheelDown;

}Mouse;



#define MouseX	Mouse.x

#define MouseY	Mouse.y

#define MouseLB	Mouse.left

#define MouseRB	Mouse.right



SDL_Window *window;

inline void InitEngine(SDL_Surface* & screen,char* WindowsTitle,unsigned int WindowsWidth ,unsigned int WindowsHeight )

{

       atexit(SDL_Quit);



       if( SDL_Init(SDL_INIT_VIDEO) < 0 ) exit(1);





      //  SDL_WM_SetCaption(WindowsTitle,NULL);



      //  screen = SDL_SetVideoMode( WindowsHeight, WindowsWidth , 32 , SDL_DOUBLEBUF|SDL_HWSURFACE|SDL_ANYFORMAT);

     window = SDL_CreateWindow(WindowsTitle,
       0,
       0,
       WindowsWidth, WindowsHeight,
       SDL_WINDOW_OPENGL);
      // renderer = SDL_CreateRenderer(window, -1, 0);
       screen = SDL_GetWindowSurface( window ); 

       ExitRequested=0;
       
       

       // Inilialize SDL_mixer , exit if fail

       if( SDL_Init(SDL_INIT_AUDIO) < 0 ) exit(1);

       // Setup audio mode

       Mix_OpenAudio(22050,AUDIO_S16SYS,2,640);

       

       TTF_Init();

}

inline void InitEngine(SDL_Surface  * & screen,char* WindowsTitle)

{

       InitEngine(screen , WindowsTitle , 800,600);       

}

inline void InitEngine(SDL_Surface * & screen)

{

       InitEngine(screen,"HASH");

}







void Update ()

{

	 SDL_Event empty = {};
     event = empty; 
     while(SDL_PollEvent( &event ))

     switch (event.type)
     {
            case SDL_MOUSEBUTTONDOWN:

                 switch (event.button.button)

                 {

                 case 1:

                      Mouse.left=1;

                      break;

                 case 2:

                      Mouse.middle=1;

                      break;

                case 3: 

                      Mouse.right=1;

                      break;

               case 4:

                      Mouse.wheelUp=1;

                      break;

                case 5: 

                      Mouse.wheelDown=1;

                      break;
                 }

                 break;
               case SDL_MOUSEBUTTONUP:

                 switch (event.button.button)

                 {

                 case 1:

                      Mouse.left=0;

                      break;

                 case 2:

                      Mouse.middle=0;

                      break;

                case 3: 

                      Mouse.right=0;

                      break;

               case 4:

                      Mouse.wheelUp=0;

                      break;

                case 5: 

                      Mouse.wheelDown=0;

                      break;                               

            

                 }

                 break;

            case SDL_MOUSEMOTION:

                 Mouse.x=event.motion.x;

                 Mouse.y=event.motion.y;

                 break;

             case SDL_QUIT:

                ExitRequested = 1;

                break;

             case SDL_KEYDOWN:

                  if (event.key.keysym.sym==SDLK_ESCAPE)

                     ExitRequested=1;

                  break;
     }

}

inline void ShowCursor()

{

       SDL_ShowCursor(1);

}

inline void HideCursor()

{

       SDL_ShowCursor(0);

}

//+++++++++++++++++++++++



inline SDL_Surface *ImgLoader(char *file,bool bCKey, int r , int g , int b , int alpha)

{

    SDL_Surface *pic;

    pic = IMG_Load(file); // From SDL_image.h , load the image to pic

    // Log error message into stderr.txt if happened

    if(pic==NULL) fprintf(stderr,"Missing image %s : %s\n",file,IMG_GetError());

    if( bCKey ) {

        // Sets the color key (transparent pixel) in a blittable surface and RLE acceleration.

       SDL_SetColorKey(pic,SDL_TRUE,SDL_MapRGB(pic->format,r,g,b));

      }

    if(alpha) SDL_SetSurfaceAlphaMod(pic, 255 - alpha);

    // This function takes a surface and copies it to a new surface of the 

    // pixel format and colors of the video framebuffer, suitable for fast 

    // blitting onto the display surface.

    //pic = SDL_ConvertSurfaceFormat(pic,SDL_GetWindowPixelFormat(window),0);

    return (pic);

}

inline SDL_Surface *ImgLoader(char *file, int r , int g , int b )

{

       return ImgLoader(file,1,r,g,b,0);

}

inline SDL_Surface* ImgLoader(char* file,int r,int g,int b,int alpha)

{

       return ImgLoader(file,1,r,g,b,alpha);

}



// Load a normal picture into a surface

inline SDL_Surface *ImgLoader(char *file)       

                { return ImgLoader(file,0,0,0,0,0) ; }

                

// **********************************

//              Audio Functions

#define Sound Mix_Chunk

#define Music Mix_Music

inline void PlaySound(Sound* sound)

{

       Mix_PlayChannel(-1,sound,0);

}

inline void PlaySound(Sound* sound,int Count)

{

       if (Count!=0)

          Mix_PlayChannel(-1,sound,(Count>0)?Count-1:-1);

}

inline void PlayMusic(Music* music)

{

       Mix_PlayMusic(music,1);

}

inline void PlayMusic(Music* music,int Count)

{

       Mix_PlayMusic(music,Count);

}

inline Sound* LoadSound(char* path)

{

       return Mix_LoadWAV(path);

}

inline Music* LoadMusic(char* path)

{

       return Mix_LoadMUS(path);

}

inline void StopMusic()

{

       Mix_HaltMusic();

}

inline void StopAllSounds()

{

        Mix_HaltChannel(-1);

}            

inline void Free(Sound* sound)

{

       Mix_FreeChunk(sound);

}

inline void Free(Music* music)

{

    Mix_FreeMusic(music);

}



//	Overload of 'SDL_BlitSurface' accept cordination without struct

inline int SDL_BlitSurface(SDL_Surface *src, SDL_Surface *dst, int x,int y)

{

	SDL_Rect tempRect;

	tempRect.x=x;

	tempRect.y=y;

	return SDL_BlitSurface(src,NULL,dst,&tempRect);

}



inline SDL_Surface* TTF_RenderText_Solid(TTF_Font *font,const char *text,Uint8 r,Uint8 g,Uint8 b)

{

	SDL_Color c;

	c.r=r;

	c.g=g;

	c.b=b;

	return TTF_RenderText_Solid(font,text,c);

}

void SDL_UpdateScreen()
{
      SDL_UpdateWindowSurface(window);
}

