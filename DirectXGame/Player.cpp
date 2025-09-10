#include "Player.h"
#include "worldDimensionSwitching.h"

Player::~Player() {
	delete sprite_;
	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}
}

void Player::Initialize() {
	dxCommon_ = KamataEngine::DirectXCommon::GetInstance();
	input_ = KamataEngine::Input::GetInstance();
	textureHandle_ = KamataEngine::TextureManager::Load("Player/Player1.png");
	sprite_ = Sprite::Create(textureHandle_, PlayerPosition_);
	textureHandle2_ = KamataEngine::TextureManager::Load("Player/Player1_Another.png");
	sprite2_ = Sprite::Create(textureHandle2_, PlayerPosition_);
	worldDimensionSwitching_ = new WorldDimensionSwitching();
	worldDimensionSwitching_->Initialize();
}

void Player::Update() {
	
	PlayerPosition_ = sprite_->GetPosition();
	PlayerPosition_ = sprite2_->GetPosition();
	worldDimensionSwitching_->Update();
	 // 入力処理 (WASDで移動)
    const float speed = 5.0f;  // 移動速度（調整可）
    if (input_->PushKey(DIK_W)) {
		if (PlayerPosition_.y > 0) {
			PlayerPosition_.y -= speed;  // 上
		}
    }
    if (input_->PushKey(DIK_S)) {
		if (PlayerPosition_.y < 330) {
			PlayerPosition_.y += speed;  // 下
		}
        
    }
    if (input_->PushKey(DIK_A)) {
		if (PlayerPosition_.x > 0) {
			PlayerPosition_.x -= speed; 
		}
         // 左
    }
    if (input_->PushKey(DIK_D)) {
		if (PlayerPosition_.x < 800) {
			PlayerPosition_.x += speed;  // 右
		}
        
    }

	sprite_->SetPosition(PlayerPosition_);
	sprite2_->SetPosition(PlayerPosition_);

	

	
	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	
	}
	
	 if (input_->TriggerKey(DIK_G)) {
        if (fireTimer_ <= 0) {
            Fire();
        }
    }

	 if (fireTimer_ > 0) {
        fireTimer_--;
    }

	  // 弾の更新
    for (PlayerBullet* bullet : bullets_) {
        bullet->Update();
    }

    //// --- ここで画面外の弾を削除 ---
    //  bullets_.remove_if([&](PlayerBullet* bullet) {
    //    bool erase = false;

    //    // 画面外チェック
    //    if (bullet->IsOutOfScreen()) {
    //        erase = true;
    //    }

    //    // 敵との当たり判定
    //    if (enemy && !enemy->IsDead()) {
    //        if (CheckCollision(bullet->GetPosition(), bullet->GetRadius(),
    //                           enemy->GetPosition(), enemy->GetRadius())) {
    //            erase = true;
    //            enemy->OnHit();  // 敵のHPを減らす
    //        }
    //    }

    //    if (erase) {
    //        delete bullet;
    //        return true;
    //    }
    //    return false;
    //});
}

void Player::Draw() {
	if (worldDimensionSwitching_->isWorldDimensionSwitching_ == true) {
		sprite_->Draw();
	}
	if (worldDimensionSwitching_->isWorldDimensionSwitching_ == false) {
		sprite2_->Draw();
	}
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw();
	}
}

void Player::Fire() {
	// 発射間隔の調整

	if (fireTimer_ > 0) {
		return;
	}
	Vector2 bulletPos = sprite_->GetPosition();
	Vector2 bulletPos2 = sprite2_->GetPosition();
	bulletPos.x += 50.0f; // 弾の出現位置を調整
	bulletPos2.x += 50.0f;
	PlayerBullet* newBullet = new PlayerBullet();
	newBullet->Initialize(bulletPos, bulletPos2);
	bullets_.push_back(newBullet);
	fireTimer_ = kFireInterval;
}

//void Player::CheckCollision(Vector2 posA, float radiusA, Vector2 posB, float radiusB)
//{
//	float dx = posA.x - posB.x;
//    float dy = posA.y - posB.y;
//    float distanceSq = dx * dx + dy * dy;
//    float radiusSum = radiusA + radiusB;
//	
//}



