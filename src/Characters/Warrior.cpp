#include "Warrior.h"


const float Time = 0.8;

Warrior::Warrior(Properties* props) : Character(props)
{
    m_Flip = SDL_FLIP_NONE;

    m_IsRunning = false;
    m_IsJumping = false;
    m_IsFalling = false;
    m_IsGrounded = false;
    m_IsAttacking = false;

    m_JumpTime = JUMP_TIME;
    m_JumpForce = JUMP_FORCCE;
    m_AttackTime = ATTACK_TIME;

    m_Collider = new Collider();
    m_Collider->SetBuffer(-13, -8, 30, 10);

    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(6.0f);

    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 1, 6, 120);
}

Warrior::~Warrior()
{
    //dtor
}
void Warrior::Draw()
{
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width,m_Height);

    //Test box collision
    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect box = m_Collider->Get();
    box.x -= cam.X;
    box.y -= cam.Y;
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}

void Warrior::Update(float dt)
{
    // idle
    m_IsRunning = false;
    m_RigidBody->UnSetForce();

    // run backward
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A) && !m_IsAttacking)
    {
        m_IsRunning = true;
        m_Flip = SDL_FLIP_HORIZONTAL;
        m_RigidBody->ApplyForceX(10 * BACKWARD);
    }

    // run forward
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D) && !m_IsAttacking)
    {
        m_IsRunning = true;
        m_Flip = SDL_FLIP_NONE;
        m_RigidBody->ApplyForceX(10 * FORWARD);
    }

    // attack
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_K))
    {
        m_RigidBody->UnSetForce();
        m_IsAttacking = true;
    }
    if(m_IsAttacking && m_AttackTime > 0)
    {
        m_AttackTime--;
    }
    if(m_AttackTime <= 0)
    {
        m_IsAttacking = false;
        m_AttackTime = ATTACK_TIME;
    }

    // jump
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_IsGrounded && !m_IsAttacking)
    {
        m_IsJumping = true;
        m_IsGrounded = false;
        m_RigidBody->ApplyForceY(UPWARD * m_JumpForce);
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_IsJumping && m_JumpTime >= 0 && !m_IsAttacking)
    {
        m_JumpTime--;
        m_RigidBody->ApplyForceY(UPWARD * m_JumpForce);
    }
    else
    {
        m_IsJumping = false;
        m_JumpTime = JUMP_TIME;
    }

    // fall
    if(!m_IsJumping && !m_IsGrounded)
        m_IsFalling = true;


    //Move on x axis
    m_RigidBody->Update(Time);
    m_LastSafePosition.X = m_Transform->X;
    m_Transform->X += m_RigidBody->Position().X;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 64, 64);

    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
        m_Transform->X = m_LastSafePosition.X;

    //Move on y axis
    m_RigidBody->Update(Time);
    m_LastSafePosition.Y = m_Transform->Y;
    m_Transform->Y += m_RigidBody->Position().Y;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 64, 64);

    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
    {
        m_IsGrounded = true;
        m_IsFalling = false;
        m_Transform->Y = m_LastSafePosition.Y;
    }
    else
    {
        m_IsGrounded = false;
    }

    m_Origin->X = m_Transform->X + m_Width / 2;
    m_Origin->Y = m_Transform->Y + m_Height / 2;

    AnimationState();
    m_Animation->Update();
}

void Warrior::AnimationState()
{
    //idling
    m_Animation->SetProps("player-idle", 1, 4, 150, m_Flip);

    //running
    if(m_IsRunning)
        m_Animation->SetProps("player-run", 1, 6, 120, m_Flip);

    //jumping
    if(m_IsJumping)
    {
        if(m_JumpTime > JUMP_TIME - 10)
            m_Animation->SetProps("player-jump-01", 1, 3, 120, m_Flip);
        else if(m_JumpTime < 5)
            m_Animation->SetProps("player-jump-03", 1, 1, 120, m_Flip);
        else
            m_Animation->SetProps("player-jump-02", 1, 2, 200, m_Flip);
    }

    //falling
    if(m_IsFalling)
        m_Animation->SetProps("player-jump-04", 1, 2, 200, m_Flip);

    //attacking
    if(m_IsAttacking)
        m_Animation->SetProps("player-attack-01", 1, 4, 100, m_Flip);
}


void Warrior::Clean()
{
    TextureManager::GetInstance()->Drop(m_TextureID);
}
