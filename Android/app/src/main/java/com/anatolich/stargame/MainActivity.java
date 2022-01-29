package com.anatolich.stargame;


import org.libsdl.app.SDLActivity;

public class MainActivity extends SDLActivity {
    @Override
    final protected String[] getLibraries(){
        return new String[]{"StarKnights"};
    }

    @Override
    final protected String getMainFunction(){
        return "SDL_main";
    }

    @Override
    public void loadLibraries()
    {
        super.loadLibraries();
    }
}
