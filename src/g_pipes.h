#pragma once

#include "pt_main.h"
#include "pt_pipe.h"
#include "pt_textures.h"
#include "pt_drawx.h"
#include "pt_keyboard.h"
#include "pt_ui.h"

enum GamePipes {
	GAME_INTRO = 0,
	GAME_MENU = 1,
	GAME_MODESELECT = 2,
	GAME_OPTIONS = 3,
	GAME_MODE_CLASSIC = 4,
	GAME_POSTROUNDSCREEN = 5,
	GAME_DIFF_SELECT = 6
};

//PIPE METHODS
namespace g_intro{
	void Init();
	void Stop();
	void Draw();
}

namespace g_menu{
	void Init();
	void Stop();
	void Draw();
	void Key(char key, bool down, int x, int y);
	void MouseMotion(int x, int y, bool drag);
	void MouseButton(int button, bool down, int x, int y);
}

namespace g_mselect{
	void Init();
	void Stop();
	void Draw();
	void MouseMotion(int x, int y, bool drag);
	void MouseButton(int button, bool down, int x, int y);
}

namespace g_options{
	void Init();
	void Stop();
	void Draw();
	void MouseButton(int button, bool down, int x, int y);
}

namespace g_game_classic{
	void Init();
	void Stop();
	void Draw();
	void Key(char key, bool down, int x, int y);
	void MouseMotion(int x, int y, bool drag);
	void MouseButton(int button, bool down, int x, int y);
	void MouseWheel(bool fwd, int x, int y);
}

namespace g_postroundscreen{
	void Init();
	void Stop();
	void Draw();
	void Key(char key, bool down, int x, int y);
	void MouseButton(int button, bool down, int x, int y);
}

namespace g_difficultyselect{
	void Init();
	void Stop();
	void Draw();
	void MouseMotion(int x, int y, bool drag);
	void MouseButton(int button, bool down, int x, int y);
}