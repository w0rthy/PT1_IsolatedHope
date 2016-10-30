#include "g_pipes.h"

void INITIALIZEGAME(){
	RegisterState(new PipeState(&g_intro::Init,&g_intro::Stop,&g_intro::Draw),GAME_INTRO);
	RegisterState(new PipeState(&g_menu::Init,&g_menu::Stop,&g_menu::Draw),new PipeInput(&g_menu::Key,&g_menu::MouseMotion,&g_menu::MouseButton,nullptr),GAME_MENU);
	RegisterState(new PipeState(&g_mselect::Init,&g_mselect::Stop,&g_mselect::Draw),new PipeInput(nullptr,&g_mselect::MouseMotion,&g_mselect::MouseButton,nullptr),GAME_MODESELECT);
	RegisterState(new PipeState(&g_options::Init,&g_options::Stop,&g_options::Draw),new PipeInput(nullptr,nullptr,g_options::MouseButton,nullptr),GAME_OPTIONS);
	RegisterState(new PipeState(&g_game_classic::Init,&g_game_classic::Stop,&g_game_classic::Draw),new PipeInput(&g_game_classic::Key,&g_game_classic::MouseMotion,&g_game_classic::MouseButton,&g_game_classic::MouseWheel), GAME_MODE_CLASSIC);
	RegisterState(new PipeState(&g_postroundscreen::Init,&g_postroundscreen::Stop,&g_postroundscreen::Draw),new PipeInput(&g_postroundscreen::Key,nullptr,&g_postroundscreen::MouseButton,nullptr),GAME_POSTROUNDSCREEN);
	RegisterState(new PipeState(&g_difficultyselect::Init,&g_difficultyselect::Stop,&g_difficultyselect::Draw),new PipeInput(nullptr,&g_difficultyselect::MouseMotion,&g_difficultyselect::MouseButton,nullptr),GAME_DIFF_SELECT);
	//ChangeState(GAME_INTRO);
	ChangeState(GAME_MENU);
}