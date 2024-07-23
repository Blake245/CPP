#include "SpaceGame.h"
#include "Scene.h"
#include "Transform.h"
#include "Scene.h"
#include "Enemy.h"
#include "Player.h"
#include "GameData.h"
#include "Engine.h"
#include "Font.h"
#include "Text.h"
#include <string>

bool SpaceGame::Initialize()
{
    m_scene = new Scene(this);

    m_font = new Font();
    m_font->Load("Arcade.ttf", 20);
    
    m_textScore = new Text(m_font);

    m_textLives = new Text(m_font);
    m_textTitle = new Text(m_font);
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
        
        break;
    case SpaceGame::eState::START_GAME:
        m_scene = 0;
        m_lives = 0;
        m_state = eState::START_LEVEL;
        break;
    case SpaceGame::eState::START_LEVEL:
    {
        m_scene->RemoveAll();
        Transform transform{ Vector2{300, 300 }, 0, 3 };
        //Model* model 
        //create player
    }
        break;
    case SpaceGame::eState::GAME:
        // timer and enemy
        m_spawnTimer -= dt;
        if (m_spawnTimer <= 0)
        {
            m_spawnTime = 0.2f;
            m_spawnTimer = m_spawnTime;

            // Create Enemy
            Model* enemyModel = new Model{ GameData::shipPoints, Color{ 1, 0, 1 } };
            auto enemy = new Enemy(400, Transform{ {random(0, g_engine.GetRenderer().getWidth()), random(0,g_engine.GetRenderer().getHeight())}, 0, 2 }, enemyModel);
            enemy->SetDamping(1.0f);
            enemy->SetTag("Enemy");
            m_scene->AddActor(enemy);
            // create pickup
        }
        break;
    case SpaceGame::eState::PLAYER_DEAD:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0)
        {
            m_state = eState::START_LEVEL;
        }
        break;
    case SpaceGame::eState::GAME_OVER:
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
        m_textTitle->Create(renderer, "Game Title", Color{ 1,0,0,1 });
        m_textTitle->Draw(renderer, 400, 300);
        break;
    case SpaceGame::eState::GAME_OVER:
        m_textTitle->Create(renderer, "GameOver", Color{ 1,0,0,1 });
       m_textTitle->Draw(renderer, 400, 300);
        break;
    default:
        break;
    }

    // draw score
    std::string text = "Score " + std::to_string(m_score);
    m_textScore->Create(renderer, text, { 0, 1, 0, 1 });
    m_textScore->Draw(renderer, 20, 20);
    //draw lives
    text = "Lives " + std::to_string(m_score);
    m_textLives->Create(renderer, text, { 0, 1, 0, 1 });
    m_textLives->Draw(renderer, g_engine.GetRenderer().getWidth() - 80, 20);

    m_scene->Draw(renderer);
}

void SpaceGame::OnPlayerDeath()
{
    m_lives--;
    m_state = (m_lives == 0) ? eState::GAME_OVER : eState::PLAYER_DEAD;
    m_stateTimer = 3;
}
