#include "utl/media.h"

void RNV_InitMedia(void)
{
    /* load sounds */
    media.vol_s = RNV_MUSIC_DEFAULT_VOL;
    RNV_SoundVolume(media.vol_s);

    media.sounds.screenshot = Mix_LoadWAV(RNV_SOUND_SCREENSHOT);
    if (media.sounds.screenshot == NULL)
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, 
                    "[RNV] Failed on sound: %s\n", Mix_GetError());
    media.sounds.btnclick = Mix_LoadWAV(RNV_SOUND_BTN_CLICK);
    if (media.sounds.btnclick == NULL)
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, 
                    "[RNV] Failed on sound: %s\n", Mix_GetError());
    
    /* load music */
    media.c_m = 0;
    media.vol_m = RNV_MUSIC_DEFAULT_VOL;
    RNV_MusicVolume(media.vol_m);

    media.bg_music[0] = Mix_LoadMUS(RNV_MUSIC_BACKGROUND_01);
    if (media.bg_music[0] == NULL)
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, 
                    "[RNV] Failed on music: %s\n", Mix_GetError());
    media.bg_music[1] = Mix_LoadMUS(RNV_MUSIC_BACKGROUND_02);
    if (media.bg_music[1] == NULL)
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, 
                    "[RNV] Failed on music: %s\n", Mix_GetError());
    media.bg_music[2] = Mix_LoadMUS(RNV_MUSIC_BACKGROUND_03);
    if (media.bg_music[2] == NULL)
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, 
                    "[RNV] Failed on music: %s\n", Mix_GetError());

    media.bg_music[3] = NULL;
    media.bg_music[4] = NULL;
}

void RNV_DestroyMedia(void)
{
    Mix_FreeChunk(media.sounds.screenshot);
    Mix_FreeChunk(media.sounds.btnclick);

    for (size_t i = 0; i < RNV_MUSIC_COUNT; i++)
    {
        if (media.bg_music[i] != NULL)
        {
            Mix_FreeMusic(media.bg_music[i]);
            media.bg_music[i] = NULL;
        }
    }
}

void RNV_PlaySound(Mix_Chunk *sound)
{
    if (sound != NULL)
    {
        Mix_PlayChannel(-1, sound, 0);
    }
}

void RNV_SoundVolume(int32_t vol)
{
    if ((media.vol_s + vol <= MIX_MAX_VOLUME) && (media.vol_s + vol >= 0))
    {
        media.vol_s += vol;
        Mix_Volume(-1, media.vol_s);
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, 
                    "[RNV] New sound volume: %d\n", media.vol_s);
    }
}

void RNV_PlayMusic(void)
{
    if (Mix_PlayingMusic() == 0)
    {
        if (media.c_m < RNV_MUSIC_COUNT)
        {
            media.c_m++;
        }
        else
        {
            media.c_m = 0;
        }
        if (media.bg_music[media.c_m] != NULL)
        {
            Mix_PlayMusic(media.bg_music[media.c_m], 0);
        }
    }
}

void RNV_PauseMusic(void)
{
    if (Mix_PlayingMusic() != 0)
    {
        if (Mix_PausedMusic() == 1)
        {
            Mix_ResumeMusic();
        }
        else
        {
            Mix_PauseMusic();
        }
    }
}

void RNV_MusicVolume(int32_t vol)
{
    if ((media.vol_m + vol <= MIX_MAX_VOLUME) && (media.vol_m + vol >= 0))
    {
        media.vol_m += vol;
        Mix_VolumeMusic(media.vol_m);
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, 
                    "[RNV] New music volume: %d\n", media.vol_m);
    }
}
