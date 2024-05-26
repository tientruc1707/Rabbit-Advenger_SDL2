#include "GSMenu.h"

GSMenu::GSMenu() : GameStateBase(StateType::STATE_MENU),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{}), m_textGameName(nullptr)
{
}


GSMenu::~GSMenu()
{
}



void GSMenu::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");

	//background
	auto texture = ResourceManagers::GetInstance()->GetTexture("Enviroment/environment-preview.png");
	//auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);
	//rabbit
	texture = ResourceManagers::GetInstance()->GetTexture("Rabbit_menu.png");
	m_rabbit = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_rabbit->SetSize(200, 200);
	m_rabbit->Set2DPosition(SCREEN_WIDTH * 2 / 3, SCREEN_HEIDHT / 2 - m_rabbit->GetHeight() + 35);
	// play button
	texture = ResourceManagers::GetInstance()->GetTexture("Button/Play_button.png");
	std::shared_ptr<MouseButton> btnPlay = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnPlay->SetSize(225, 50);
	btnPlay->Set2DPosition(SCREEN_WIDTH * 3 / 4, SCREEN_HEIDHT * 2 / 3);
	btnPlay->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(btnPlay);

	//Setting game
	texture = ResourceManagers::GetInstance()->GetTexture("Button/Option_button.png");
	std::shared_ptr<MouseButton> btnOption = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnOption->SetSize(225, 50);
	btnOption->Set2DPosition(SCREEN_WIDTH * 3/4, btnPlay->Get2DPosition().y + btnPlay->GetHeight() + 20);
	btnOption->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_OPTION);
		});
	m_listButton.push_back(btnOption);

	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("Button/Quit_button.png");
	std::shared_ptr<MouseButton> btnClose = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	//btnClose = std::make_shared<MouseButton>(texture);
	btnClose->SetSize(225, 50);
	btnClose->Set2DPosition(SCREEN_WIDTH * 3 / 4, btnOption->Get2DPosition().y + btnOption->GetHeight() + 20);
	btnClose->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(btnClose);

	////CREDIT game
	//texture = ResourceManagers::GetInstance()->GetTexture("Button/Quit_button.png");
	//btnCredit = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	//btnCredit->Set2DPosition(SCREEN_WIDTH * 3 / 4, btnOption->Get2DPosition().y + btnOption->GetHeight() + 20);
	//btnCredit->SetSize(50,50);
	//btnCredit->SetOnClick([]() {
	//	GameStateMachine::GetInstance()->ChangeState(StateType::STATE_CREDIT);
	//	});
	//m_listButton.push_back(btnCredit);

	// game title
	///Set Font
	m_textColor = {110, 212, 144 };
	m_textGameName = std::make_shared<Text>("Data/Haedus.ttf", m_textColor);
	m_textGameName->SetSize(SCREEN_WIDTH / 3, 100);
	m_textGameName->Set2DPosition((SCREEN_WIDTH - m_textGameName->GetWidth())/2, SCREEN_HEIDHT / 3);
	m_textGameName->LoadFromRenderText("Rabbit Advenger");

	//Music
	m_Sound = std::make_shared<Sound>("Data/Sounds/Intro_menu.mp3");
	m_Sound->PlaySound();

	//bee
	texture = ResourceManagers::GetInstance()->GetTexture("Enemy/bee_flying.png");
	for (int i = 0; i < 7; ++i) {
		std::shared_ptr<SpriteAnimation> m_bee = std::make_shared<SpriteAnimation>(texture, 1, 8, 1, 0.1f);
		m_bee->SetFlip(SDL_FLIP_HORIZONTAL);
		m_bee->SetSize(50, 50);
		m_bee->Set2DPosition(rand() % 400 + 100, rand() % SCREEN_HEIDHT / 2);
		m_listBee.push_back(m_bee);
	}
}

void GSMenu::Exit()
{
	ResourceManagers::FreeInstance();
}


void GSMenu::Pause()
{
	m_Sound->StopSound();

}

void GSMenu::Resume()
{
	m_Sound->PlaySound();
}


void GSMenu::HandleEvents()
{
}

void GSMenu::HandleKeyEvents(SDL_Event& e)
{
}

void GSMenu::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button ->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSMenu::HandleMouseMoveEvents(int x, int y)
{
}
float time = 0.0f;
void GSMenu::Update(float deltaTime)
{
	time += deltaTime;
	//printf("DeltaTime = %f", deltaTime);
	if (time >= 1.5f)
	{
		time = 0.0f;
	}
	m_background->Update(deltaTime);
	for (auto &it : m_listButton)
	{
		it->Update(deltaTime);
	}
	for (auto &bee : m_listBee)
	{
		bee->Update(deltaTime);
	}
}

void GSMenu::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	m_rabbit->Draw(renderer);
	for (auto &it : m_listButton)
	{
		it->Draw(renderer);
	}
	m_textGameName->Draw(renderer);
	for (auto& bee : m_listBee)
	{
		bee->Draw(renderer);
	}
}
