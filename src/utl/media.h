#ifndef __RNV_MEDIA_H__
#define __RNV_MEDIA_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#define RNV_SOUND_SCREENSHOT "res/sounds/screenshot.wav"
#define RNV_SOUND_BTN_CLICK "res/sounds/btn-click.wav"

#define RNV_MUSIC_COUNT 5
#define RNV_MUSIC_DEFAULT_VOL 32
#define RNV_MUSIC_BACKGROUND_01 "res/music/ForestWalk-320bit.mp3"
#define RNV_MUSIC_BACKGROUND_02 "res/music/Illusory-Realm-MP3.mp3"
#define RNV_MUSIC_BACKGROUND_03 "res/music/sb_indreams.mp3"


typedef struct {
    u_int32_t vol_s;
    u_int32_t vol_m;
    u_int32_t c_m;
    struct {
        Mix_Chunk *screenshot;
        Mix_Chunk *btnclick;
    } sounds;
    Mix_Music *bg_music[RNV_MUSIC_COUNT];
} Media;

Media media;


void RNV_InitMedia(void);

void RNV_DestroyMedia(void);

void RNV_PlaySound(Mix_Chunk *sound);

void RNV_SoundVolume(int32_t vol);

void RNV_PlayMusic(void);

void RNV_PauseMusic(void);

void RNV_MusicVolume(int32_t vol);

#endif /* !__RNV_MEDIA_H__ */
