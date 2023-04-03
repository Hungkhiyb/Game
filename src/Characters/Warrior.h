#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Input.h"
#include "Collider.h"
#include "Vector2D.h"
#include "Camera.h"
#include "CollisionHandler.h"

#define JUMP_TIME 20.0f
#define JUMP_FORCCE 15.0f

#define RUN_FORCE 5
#define ATTACK_TIME 20

class Warrior : public Character
{
    public:
        Warrior(Properties* props);
        ~Warrior();

        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();

    private:
        void AnimationState();

        bool m_IsRunning;
        bool m_IsJumping;
        bool m_IsFalling;
        bool m_IsGrounded;
        bool m_IsAttacking;

        float m_JumpTime;
        float m_JumpForce;
        float m_AttackTime;

        Collider* m_Collider;
        Animation* m_Animation;
        RigidBody* m_RigidBody;
        Vector2D m_LastSafePosition;
        SDL_RendererFlip m_Flip;
};

#endif // WARRIOR_H
