#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "Scene.h"

#include "RenderComponent.h"
#include "MovementComponent.h"
#include "HealthComponent.h"
#include <Xinput.h>
#include "ServiceLocator.h"
#include "Grid.h"
#include "NPC.h"
#include "QbertCharacter.h"
#include "Disc.h"
#include "Hud.h"
#include "MenuScreen.h"
#include "IntermediateScreen.h"
#include "controlScreen.h"
#include "player2Component.h"
#include "ServiceLocator.h"
#include "HighScoreComponent.h"
#include "Winner.h"
#include "EggComponent.h"
#include "ChaseCharacter.h"

#include "time.h"
#include <iostream>

	const int WINDOW_WIDTH{ 640 }, WINDOW_HEIGHT{ 480 };

void load()
{
	const float worldScale{ 1.7f };
	const float titleScale{ 1.f };
	const float screenScale{ 0.8f };
	const float arrowScale{ 4.f };
	const int gridSize{ 7 };
	//auto& scene       = TG::SceneManager::GetInstance().CreateScene("Demo");
	auto& scene       = TG::SceneManager::GetInstance().CreateScene(TG::EMenuState::game);
	auto& input       = TG::InputManager::GetInstance();
	auto font         = TG::ResourceManager::GetInstance().LoadFont("Textures/Minecraft.ttf", 16);
	auto largeFont    = TG::ResourceManager::GetInstance().LoadFont("Textures/Minecraft.ttf", 60);
	auto cubeTexture  = TG::ResourceManager::GetInstance().LoadTexture("Textures/Qbert Cubes.png", true, worldScale);
	auto CurseTexture = TG::ResourceManager::GetInstance().LoadTexture("Textures/Qbert Curses.png", true, titleScale);
	auto QbertTexture = TG::ResourceManager::GetInstance().LoadTexture("Textures/Qbert P1 Spritesheet.png", true, worldScale, std::pair<int, int>(1,4));
	auto QbertTexture2 = TG::ResourceManager::GetInstance().LoadTexture("Textures/Qbert P2 Spritesheet.png", true, worldScale, std::pair<int, int>(1,4));
	auto snakeTexture = TG::ResourceManager::GetInstance().LoadTexture("Textures/Coily Spritesheet.png", true, worldScale, std::pair<int, int>(1, 10));
	auto samTexture   = TG::ResourceManager::GetInstance().LoadTexture("Textures/Slick Sam Spritesheet.png", true, worldScale, std::pair<int, int>(2, 2));
	auto wrongTexture = TG::ResourceManager::GetInstance().LoadTexture("Textures/Ugg Wrongway Spritesheet.png", true, worldScale, std::pair<int, int>(2, 4));
	auto DiscTexture  = TG::ResourceManager::GetInstance().LoadTexture("Textures/Disk Spritesheet.png", true, worldScale, std::pair<int, int>(1, 30));
	auto background   = TG::ResourceManager::GetInstance().LoadTexture("Textures/background.tga", true, worldScale);
	auto lvlTexture   = TG::ResourceManager::GetInstance().LoadTexture("Textures/Level 01 Title.png", true, worldScale);
	auto cubeIndTexture= TG::ResourceManager::GetInstance().LoadTexture("Textures/Color Icons Spritesheet.png", true, 1.5f, std::pair<int, int>(2, 6));
	auto HealthTexture= TG::ResourceManager::GetInstance().LoadTexture("Textures/Heart.png", true, worldScale);
	//Menus
	//-----------------
	//intro
	auto MenuIntroTexture= TG::ResourceManager::GetInstance().LoadTexture("Textures/intro.png", true, 2.8f);
	//pause
	auto PauseTexture = TG::ResourceManager::GetInstance().LoadTexture("Textures/Pause Screen.png", true, titleScale);
	//selection
	auto selectionTexture = TG::ResourceManager::GetInstance().LoadTexture("Textures/Game Title.png", true, titleScale);
	auto arrowTexture = TG::ResourceManager::GetInstance().LoadTexture("Textures/Selection Arrow.png", true, arrowScale);
	//intermediate
	auto MenuLvlTexture = TG::ResourceManager::GetInstance().LoadTexture("Textures/Level 01 Title.png", true, titleScale);
	auto MenuLvlTexture1  = TG::ResourceManager::GetInstance().LoadTexture("Textures/Level 02 Title.png", true, titleScale);
	auto MenuLvlTexture2  = TG::ResourceManager::GetInstance().LoadTexture("Textures/Level 03 Title.png", true, titleScale);
	//controls
	auto controlTexture = TG::ResourceManager::GetInstance().LoadTexture("Textures/controls Single.png", true, screenScale);
	auto controlTexture1 = TG::ResourceManager::GetInstance().LoadTexture("Textures/controls vs.png", true, screenScale);
	auto controlTexture2 = TG::ResourceManager::GetInstance().LoadTexture("Textures/controls coop.png", true, screenScale);
	//Game over
	auto gameOverTexture = TG::ResourceManager::GetInstance().LoadTexture("Textures/Game Over Title.png", true, worldScale);
	//Winer
	auto winnerTexture = TG::ResourceManager::GetInstance().LoadTexture("Textures/Victory Title.png", true, worldScale);
	auto scoreTexture = TG::ResourceManager::GetInstance().LoadTexture("Textures/newHigh.png", true, titleScale);


	//if NDEBUG
	TG::Locator::provide(std::make_unique< TG::GameAudio>());
	//Else 
	//TG::Locator::provide(std::make_unique< TG::LoggedAudio>());
	
	//TG::Locator::getAudio().playSound("Level");

	//----------------------------------------------------
	//GAME SCENE
	//---------------------------------------------------
	const glm::vec2 topCubePosition{ glm::vec2{ WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 5.f } };
	auto grid = std::make_unique<Game::Grid>(topCubePosition, gridSize , cubeTexture);
	const glm::vec2 cubeSize{ grid->GetCubeSize() };

	//SKIP LVL INPUT
	auto skip = std::make_unique<TG::SkipLvl>(grid.get());
	input.InputBinding(std::move(skip), SDL_SCANCODE_F1, EInputType::pressed);

	auto character = std::make_unique<Game::QbertCharacter>(topCubePosition, QbertTexture, cubeSize, CurseTexture);
	grid->SetGridSubject(character.get());
	character->SubscribeToGrid(grid.get());

	auto character2 = std::make_unique<Game::QbertCharacter>(topCubePosition, QbertTexture2, cubeSize, CurseTexture);
	character2->AddComponent<Game::Player2Component>(character2.get());
	grid->SetGridSubject(character2.get());
	character2->SubscribeToGrid(grid.get());

	//coily
	auto npc = std::make_unique<Game::NPC>(topCubePosition, snakeTexture, cubeSize, Game::ECharacterType::purple);
	npc->AddComponent<Game::Player2Component>(npc.get());
	npc->AddComponent<Game::EggComponent>(npc.get());
	npc->AddComponent<Game::ChaseCharacterComponent>(npc.get(), character.get());
	npc.get()->SetPositionOnGridByIndex(2, 2, cubeSize);
	grid->SetGridSubject(npc.get());
	
	//Slick
	auto npcGreen = std::make_unique<Game::NPC>(topCubePosition, samTexture, cubeSize, Game::ECharacterType::green);
	grid->SetGridSubject(npcGreen.get());
	
	//Sam
	auto npcGreen2 = std::make_unique<Game::NPC>(topCubePosition, samTexture, cubeSize, Game::ECharacterType::green, true);
	grid->SetGridSubject(npcGreen2.get());

	//Slick
	auto npcWrong = std::make_unique<Game::NPC>(topCubePosition, wrongTexture, cubeSize, Game::ECharacterType::wrong);
	grid->SetGridSubject(npcWrong.get());
	
	//Sam
	auto npcWrong2 = std::make_unique<Game::NPC>(topCubePosition, wrongTexture, cubeSize, Game::ECharacterType::wrong, true);
	grid->SetGridSubject(npcWrong2.get());


	auto disc = std::make_unique<Game::Disc>(DiscTexture, topCubePosition, cubeSize);
	disc->SetGridSubject(grid.get());
	auto disc2 = std::make_unique<Game::Disc>(DiscTexture, topCubePosition, cubeSize);
	disc2->SetGridSubject(grid.get());
	auto disc1 = std::make_unique<Game::Disc>(DiscTexture, topCubePosition, cubeSize);
	disc1->SetGridSubject(grid.get());
	auto disc12 = std::make_unique<Game::Disc>(DiscTexture, topCubePosition, cubeSize);
	disc12->SetGridSubject(grid.get());

	auto vChar = std::vector<Game::Character*>{character.get(), npc.get(), npcGreen.get(), npcGreen2.get(), npcWrong.get(), npcWrong2.get() };
	auto vChar2 = std::vector<Game::Character*>{ character2.get(), npc.get(), npcGreen.get(), npcGreen2.get(), npcWrong.get(), npcWrong2.get() };
	auto vTex = std::vector<std::shared_ptr<TG::Texture2D>>{background, HealthTexture, cubeIndTexture};
	auto vDisc = std::vector<Game::Disc* >{disc.get(), disc1.get(), disc2.get(), disc12.get()};
	auto hud = std::make_unique<Game::Hud>(vChar, vChar2, vDisc, vTex, font);
	hud->SubscribeToGrid(grid.get());

	//----------------------------------------------------
	//INPUT BINDING
	//---------------------------------------------------
	//inputMapping Character 1
	auto moveUp = std::make_unique<TG::Move>(character.get(), glm::vec2{0.f, 1.f});
	input.InputBinding(std::move(moveUp), SDL_SCANCODE_UP, EInputType::pressed);
	auto moveDown = std::make_unique<TG::Move>(character.get(), glm::vec2{ 0.f, -1.f });
	input.InputBinding(std::move(moveDown), SDL_SCANCODE_DOWN, EInputType::pressed);
	auto moveRight = std::make_unique<TG::Move>(character.get(), glm::vec2{ 1.f, 0.f });
	input.InputBinding(std::move(moveRight), SDL_SCANCODE_RIGHT, EInputType::pressed);
	auto moveLeft = std::make_unique<TG::Move>(character.get(), glm::vec2{ -1.f, 0.f });
	input.InputBinding(std::move(moveLeft), SDL_SCANCODE_LEFT, EInputType::pressed);

	//inputMapping XBox controller
	auto moveUp2 = std::make_unique<TG::Move>(character.get(), glm::vec2{ 0.f, 1.f });
	input.InputBinding(std::move(moveUp2), XINPUT_GAMEPAD_DPAD_UP, EInputType::pressed, 0);
	auto moveDown2 = std::make_unique<TG::Move>(character.get(), glm::vec2{ 0.f, -1.f });
	input.InputBinding(std::move(moveDown2), XINPUT_GAMEPAD_DPAD_DOWN, EInputType::pressed, 0);
	auto moveRight2 = std::make_unique<TG::Move>(character.get(), glm::vec2{ 1.f, 0.f });
	input.InputBinding(std::move(moveRight2), XINPUT_GAMEPAD_DPAD_RIGHT, EInputType::pressed, 0);
	auto moveLeft2 = std::make_unique<TG::Move>(character.get(), glm::vec2{ -1.f, 0.f });
	input.InputBinding(std::move(moveLeft2), XINPUT_GAMEPAD_DPAD_LEFT, EInputType::pressed, 0);

	//Character 2
	//Coily
	auto moveUp3 = std::make_unique<TG::Move>(npc.get(), glm::vec2{ 0.f, 1.f });
	input.InputBinding(std::move(moveUp3), XINPUT_GAMEPAD_DPAD_UP, EInputType::pressed, 1);
	auto moveDown3 = std::make_unique<TG::Move>(npc.get(), glm::vec2{ 0.f, -1.f });
	input.InputBinding(std::move(moveDown3), XINPUT_GAMEPAD_DPAD_DOWN, EInputType::pressed, 1);
	auto moveRight3 = std::make_unique<TG::Move>(npc.get(), glm::vec2{ 1.f, 0.f });
	input.InputBinding(std::move(moveRight3), XINPUT_GAMEPAD_DPAD_RIGHT, EInputType::pressed, 1);
	auto moveLeft3 = std::make_unique<TG::Move>(npc.get(), glm::vec2{ -1.f, 0.f });
	input.InputBinding(std::move(moveLeft3), XINPUT_GAMEPAD_DPAD_LEFT, EInputType::pressed, 1);

	//Qbert
	//inputMapping XBox controller
	 moveUp3 = std::make_unique<TG::Move>(character2.get(), glm::vec2{ 0.f, 1.f });
	input.InputBinding(std::move(moveUp3), XINPUT_GAMEPAD_DPAD_UP, EInputType::pressed, 1);
	 moveDown3 = std::make_unique<TG::Move>(character2.get(), glm::vec2{ 0.f, -1.f });
	input.InputBinding(std::move(moveDown3), XINPUT_GAMEPAD_DPAD_DOWN, EInputType::pressed, 1);
	 moveRight3 = std::make_unique<TG::Move>(character2.get(), glm::vec2{ 1.f, 0.f });
	input.InputBinding(std::move(moveRight3), XINPUT_GAMEPAD_DPAD_RIGHT, EInputType::pressed, 1);
	 moveLeft3 = std::make_unique<TG::Move>(character2.get(), glm::vec2{ -1.f, 0.f });
	input.InputBinding(std::move(moveLeft3), XINPUT_GAMEPAD_DPAD_LEFT, EInputType::pressed, 1);



	//----------------------------------------------------
	//Add to GAME scene
	//----------------------------------------------------

	scene.Add(std::move(hud));
	scene.Add(std::move(grid));
	scene.Add(std::move(disc));
	scene.Add(std::move(disc2));
	scene.Add(std::move(disc1));
	scene.Add(std::move(disc12));
	scene.Add(std::move(character));
	scene.Add(std::move(character2));
	scene.Add(std::move(npc));
	scene.Add(std::move(npcGreen));
	scene.Add(std::move(npcGreen2));
	scene.Add(std::move(npcWrong));
	scene.Add(std::move(npcWrong2));
		
	//----------------------------------------------------
	//INTRO SCENE
	//-----------------------------------------------
	auto& IntroScene = TG::SceneManager::GetInstance().CreateScene(TG::EMenuState::intro);
	auto introTexture = std::make_unique<TG::GameObject>();
	introTexture->AddComponent<TG::RenderComponent>(introTexture.get(), MenuIntroTexture);
	introTexture->AddComponent<TG::TextComponent>(introTexture.get(), "Press ENTER ", largeFont, glm::vec3 {120.f, 400.f, 0.f});

	//ENTER - START
	auto enter = std::make_unique<TG::Enter>(introTexture.get());
	input.InputBinding(std::move(enter), SDL_SCANCODE_RETURN, EInputType::pressed);
	auto start = std::make_unique<TG::Enter>(introTexture.get());
	input.InputBinding(std::move(start), XINPUT_GAMEPAD_START, EInputType::pressed, 0);

	//QUIT
	auto quit = std::make_unique<TG::Quit>(introTexture.get());
	input.InputBinding(std::move(quit), SDL_SCANCODE_ESCAPE, EInputType::pressed);
	quit = std::make_unique<TG::Quit>(introTexture.get());
	input.InputBinding(std::move(quit), XINPUT_GAMEPAD_Y, EInputType::pressed, 0);
	
	//ARROW UP
	auto MoveUp = std::make_unique<TG::MoveArrow>(introTexture.get(), true);
	input.InputBinding(std::move(MoveUp), SDL_SCANCODE_UP, EInputType::pressed);
	MoveUp = std::make_unique<TG::MoveArrow>(introTexture.get(), true);
	input.InputBinding(std::move(MoveUp), XINPUT_GAMEPAD_DPAD_UP, EInputType::pressed, 0);

	//ARROW DOWN
	auto MoveDown = std::make_unique<TG::MoveArrow>(introTexture.get(), false);
	input.InputBinding(std::move(MoveDown), SDL_SCANCODE_DOWN, EInputType::pressed);
	MoveDown = std::make_unique<TG::MoveArrow>(introTexture.get(), false);
	input.InputBinding(std::move(MoveDown), XINPUT_GAMEPAD_DPAD_DOWN, EInputType::pressed, 0);

	//MUTE
	auto mute = std::make_unique<TG::Mute>();
	input.InputBinding(std::move(mute), SDL_SCANCODE_M, EInputType::pressed);
	
	
	
	IntroScene.Add(std::move(introTexture));

	//----------------------------------------------------
	//INTERMEDIATE SCENE
	//-----------------------------------------------
	auto& InterScene = TG::SceneManager::GetInstance().CreateScene(TG::EMenuState::intermediate);

	auto interScreen = std::make_unique<Game::IntermedateScreen>(std::vector{ MenuLvlTexture, MenuLvlTexture1, MenuLvlTexture2 }, largeFont);

	InterScene.Add(std::move(interScreen));

	//----------------------------------------------------
	//PAUSE
	//-----------------------------------------------
	auto& pauseScene = TG::SceneManager::GetInstance().CreateScene(TG::EMenuState::pause);
	auto pauseScreen = std::make_unique<TG::GameObject>();
	pauseScreen->AddComponent<TG::RenderComponent>(pauseScreen.get(), PauseTexture);

	pauseScene.Add(std::move(pauseScreen));

	//----------------------------------------------------
	//SLECTION
	//-----------------------------------------------
	auto& selectionScene = TG::SceneManager::GetInstance().CreateScene(TG::EMenuState::selection);
	auto selectionScreen = std::make_unique<Game::MenuScreen>(selectionTexture, arrowTexture, largeFont);

	selectionScene.Add(std::move(selectionScreen));


	//----------------------------------------------------
	//CONTROL
	//-----------------------------------------------
	auto& controlScene = TG::SceneManager::GetInstance().CreateScene(TG::EMenuState::controls);

	auto controlScreen = std::make_unique<Game::controlScreen>(std::vector{ controlTexture ,controlTexture1 ,controlTexture2 });

	controlScene.Add(std::move(controlScreen));
	
	//----------------------------------------------------
	//GAME OVER
	//-----------------------------------------------
	auto& gameOverScene = TG::SceneManager::GetInstance().CreateScene(TG::EMenuState::gameOver);

	auto gameOverScreen = std::make_unique<TG::GameObject>();
	gameOverScreen->AddComponent<TG::RenderComponent>(gameOverScreen.get(), gameOverTexture);

	gameOverScene.Add(std::move(gameOverScreen));
	
	//----------------------------------------------------
	//WINNER
	//-----------------------------------------------
	auto& winnerScene = TG::SceneManager::GetInstance().CreateScene(TG::EMenuState::winner);

	auto winnerScreen = std::make_unique<Game::Winner>(winnerTexture, scoreTexture, font, largeFont);

	auto letterUp = std::make_unique<TG::ChangeLetter>(winnerScreen.get(), glm::vec2{ 0.f, 1.f });
	input.InputBinding(std::move(letterUp), SDL_SCANCODE_UP, EInputType::pressed);
	auto letterDown = std::make_unique<TG::ChangeLetter>(winnerScreen.get(), glm::vec2{ 0.f, -1.f });
	input.InputBinding(std::move(letterDown), SDL_SCANCODE_DOWN, EInputType::pressed);
	auto acceptLetter = std::make_unique<TG::ChangeLetter>(winnerScreen.get(), glm::vec2{ 1.f, 0.f });
	input.InputBinding(std::move(acceptLetter), SDL_SCANCODE_RETURN, EInputType::pressed);
	

	winnerScene.Add(std::move(winnerScreen));

	//-------------------------------------------
	//MenuStates

	TG::SceneManager::GetInstance().CreateMenu();
	
	
}

int main(int, char* [])
{
	srand(static_cast<uint32_t>(time(NULL)));
	TG::Minigin engine("../Data/", WINDOW_WIDTH, WINDOW_HEIGHT);
	engine.Run(load);

	return 0;
}