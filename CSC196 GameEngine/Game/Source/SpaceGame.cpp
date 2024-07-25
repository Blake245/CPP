#include "SpaceGame.h"
#include "Scene.h"
#include "Transform.h"
#include "Scene.h"
#include "Enemy.h"
#include "Player.h"
#include "EnemyShooter.h"
#include "Pickup.h"
#include "GameData.h"
#include "Engine.h"
#include "Font.h"
#include "Text.h"
#include "MathUtils.h"
#include <string>

bool SpaceGame::Initialize()
{
    m_scene = new Scene(this);

    m_font = new Font();
    m_fontLarge = new Font();
    m_fontLarge->Load("Arcade.ttf", 60);
    m_font->Load("ArcadeClassic.ttf", 30);
    
    m_textScore = new Text(m_font);

    m_textLives = new Text(m_font);
    m_textTitle = new Text(m_fontLarge);

    g_engine.GetAudio().AddSound("Lazer.wav");
    g_engine.GetAudio().AddSound("Hit_Hurt2.wav");
    g_engine.GetAudio().AddSound("Explosion6.wav");
    g_engine.GetAudio().AddSound("GameMusic.wav");
    return true;
}

void SpaceGame::Shutdown()
{
}

void SpaceGame::Update(float dt)
{

    switch (m_state)
    {
    case eState::TITLE:
        if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_SPACE))
        {
            m_state = eState::START_GAME;
        }
        break;
    case SpaceGame::eState::START_GAME:
        //m_scene = 0;
        m_lives = 3;
        m_state = eState::START_LEVEL;
        break;
    case SpaceGame::eState::START_LEVEL:
    {
        m_scene->RemoveAll();
        Model* model = new Model{ GameData::shipPoints, Color{ 1, 0, 0 } };
        //create player
        Transform transform({ 400, 400}, Math::HalfPi * 3, 5);
        auto player = std::make_unique<Player>(800.0f, transform, model);
        player->SetDamping(2.0f);
        player->SetTag("Player");
        m_scene->AddActor(std::move(player));
        g_engine.GetAudio().PlaySound("GameMusic.wav");
        m_state = eState::GAME;
    }
        break;
    case SpaceGame::eState::GAME:
        // timer and enemy
        m_spawnTimer -= dt;
        m_isHitTimer -= dt;
        if (m_spawnTimer <= 0)
        {
            m_spawnTime = 1.0f;
            m_spawnTimer = m_spawnTime;
            m_spawnChance = randomf(1, 100);

            if (m_spawnChance > 10)
            {
                // Create Enemy
                Model* enemyModel = new Model{ GameData::enemyPoints, Color{ 1, 0, 1 } };
                auto enemy = std::make_unique<Enemy>(150.0f, Transform{ {random(100.0f, g_engine.GetRenderer().getWidth()), 0}, 0, 10 }, enemyModel);
                //enemy->SetDamping(1.0f);
                enemy->SetTag("Enemy");
                m_scene->AddActor(std::move(enemy));
            }
            else if (m_spawnChance < 10)
            {
                Model* enemyModel = new Model{ GameData::enemyPoints, Color{ 0, 1, 1 } };
                auto enemy = std::make_unique<EnemyShooter>(100.0f, Transform{ {random(100.0f, g_engine.GetRenderer().getWidth()), 0}, Math::HalfPi, 10 }, enemyModel);
                //enemy->SetDamping(1.0f);
                enemy->SetTag("Enemy");
                m_scene->AddActor(std::move(enemy));
            }
           
        }
        if (m_isHitTimer <= 0) m_isHit = false;
        break;
    case SpaceGame::eState::PLAYER_DEAD:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0)
        {
            m_state = eState::START_LEVEL;
        }
        break;
    case SpaceGame::eState::GAME_OVER:
        m_scene->RemoveAll();
        m_stateTimer -= dt;
        if (m_stateTimer <= 0)
        {
            m_state = eState::TITLE;
        }
        break;
    default:
        break;
    }

    m_scene->Update(dt);
}

void SpaceGame::Draw(Renderer& renderer)
{
    switch (m_state)
    {
    case SpaceGame::eState::TITLE:
        //draw text "Game Title"
        m_textTitle->Create(renderer, "Space Adventure", Color{ 1,0,0,1 });
        m_textTitle->Draw(renderer, g_engine.GetRenderer().getWidth() / 4, 300);
        break;
    case SpaceGame::eState::GAME_OVER:
        m_textTitle->Create(renderer, "GameOver", Color{ 1,0,0,1 });
       m_textTitle->Draw(renderer, 300, 300);
        break;
    case SpaceGame::eState::GAME:
        m_textScore->Draw(renderer, 20, 20);
        m_textLives->Draw(renderer, g_engine.GetRenderer().getWidth() - 150, 20);
    default:
        break;
    }

    // draw score
    std::string text = "Score, " + std::to_string(m_score);
    m_textScore->Create(renderer, text, { 0, 1, 0, 1 });
    
    //draw lives
    text = "Health " + std::to_string(m_lives);
    m_textLives->Create(renderer, text, { 0, 1, 0, 1 });
    

    m_scene->Draw(renderer);
}

void SpaceGame::OnPlayerDeath()
{
    if (!m_isHit)
    {
        m_isHit = true;
        m_lives--;
        // m_state = (m_lives == 0) ? eState::GAME_OVER : eState::PLAYER_DEAD;
        if (m_lives == 0)
        {
            m_state = eState::GAME_OVER;
        }
        m_stateTimer = 3;
        m_isHitTimer = 1;
    }
}

void SpaceGame::AddHealth()
{
    m_lives++;
    if (m_lives > 4)
    {
        m_lives = 4;
    }
}
