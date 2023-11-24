//
// Created by Campo on 20/11/2023.
//

#include "Player.h"
#include "../Game.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/DrawComponents/DrawAnimatedComponent.h"
#include "../Components/DrawComponents/DrawPolygonComponent.h"
#include "../Components/ColliderComponents/AABBColliderComponent.h"


Player::Player(Game *game, float forwardSpeed): Actor(game), mForwardSpeed(forwardSpeed)
{

      mWidth=mHeight=64;
      mRigidBodyComponent= new RigidBodyComponent(this,1.0,10);
      mRigidBodyComponent->Set_is_mobile(true);

      mColliderComponent= new AABBColliderComponent(this,0,0,mWidth,mHeight,ColliderLayer::Player);


      mDrawComponent= new DrawSpriteComponent(this,"../Assets/placeholder.png",mWidth,mHeight,1000);
      SetUpdateDrawOrder(true);
}


void Player::OnProcessInput(const Uint8 *keyState)
{


    if(keyState[SDL_SCANCODE_D])
    {
        mRigidBodyComponent->ApplyForce(Vector2(mForwardSpeed,0));
        SetRotation(0);

    }

    
    if(keyState[SDL_SCANCODE_A])
    {
        mRigidBodyComponent->ApplyForce(Vector2(-1 * mForwardSpeed,0));
        SetRotation(Math::Pi);

    }

    if(keyState[SDL_SCANCODE_W])
    {
        mRigidBodyComponent->ApplyForce(Vector2(0,-1 * mForwardSpeed));


    }

    if(keyState[SDL_SCANCODE_S])
    {
        mRigidBodyComponent->ApplyForce(Vector2(0,mForwardSpeed));


    }


}

void Player::OnUpdate(float deltaTime)
{
    //mRigidBodyComponent->SetVelocity(Vector2::Zero);
    auto pos = GetPosition();
    auto pos_correct = Vector2();
    pos_correct.x = pos.x;pos_correct.y = pos.y;
    if(pos.y > (float)mGame->GetWindowHeight() - ((float)mHeight/2))
    {
        //SDL_Log("don't go bellow");
        //SetPosition(Vector2(pos.x,mGame->GetWindowHeight()- ((float)mHeight/2)));
        pos_correct.y = (float)mGame->GetWindowHeight()- ((float)mHeight/2);
    }



    if(pos.y< mGame->get_floor_height() )
    {
        //SetPosition(Vector2(pos.x,mGame->get_floor_height()));
        pos_correct.y = mGame->get_floor_height();
    }

    if(pos.x< mGame->GetCameraPos().x + ((float)mWidth/2))
    {
        //SetPosition(Vector2(mGame->GetCameraPos().x + ((float)mWidth/2),pos.y));
        pos_correct.x = mGame->GetCameraPos().x + ((float)mWidth/2);
    }

    if(pos.x> mGame->GetCameraPos().x + (float)mGame->GetWindowWidth() - ((float)mWidth/2))
    {
        //SetPosition(Vector2(mGame->GetCameraPos().x + (float)mGame->GetWindowWidth() - ((float)mWidth/2),pos.y));
        pos_correct.x = mGame->GetCameraPos().x + (float)mGame->GetWindowWidth() - ((float)mWidth/2);
    }

    SetPosition(pos_correct);

    if(GetUpdateDrawOrder()==true)
    {
        SetUpdateDrawOrder(false);
        mDrawComponent->SetDrawOrder((int)GetPosition().y);
        mGame->set_resort(true);
    }
}