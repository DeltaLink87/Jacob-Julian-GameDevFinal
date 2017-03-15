#include "MeleeAttack.h"


//Will create a pre-Constructor for melee attack that takes an int to set type then calls the default meleeattack constructor
MeleeAttack::MeleeAttack(int x, int y, int width, int height, float dir, Actor* newSource) : Attack(x, y, width, height, newSource) {
	
	this->type = 2;
	this->melee = true;
	if (this->type == DAGGER) {
    /*
     --TEMP--
		this->textureOfVisualRepresentation.loadFromFile("Assets/Textures/Items/DaggerAttackImage.png");
		this->visualRepresentation.setTexture(textureOfVisualRepresentation);
		if (newSource->isFacingRight())
			this->visualRepresentation.setScale(sf::Vector2f(.15, .2));
		else
			this->visualRepresentation.setScale(sf::Vector2f(-.15, .2));

		//std::cout << ((float) this->visualRepresentation.getLocalBounds().height) * this->visualRepresentation.getScale().y << std::endl;

		this->getHitBox().setSize(sf::Vector2f(this->visualRepresentation.getLocalBounds().width * this->visualRepresentation.getScale().x, this->visualRepresentation.getLocalBounds().height * this->visualRepresentation.getScale().y));
    */
    
    this->textureName = "Assets/Textures/Items/DaggerAttackImage";

		if (newSource->isFacingRight())
			this->sprite.setScale(sf::Vector2f(.15, .2));
		else
			this->sprite.setScale(sf::Vector2f(-.15, .2));
    
    
    //this->getHitBox().setSize(sf::Vector2f(this->sprite.getLocalBounds().width * this->sprite.getScale().x, this->sprite.getLocalBounds().height * this->sprite.getScale().y));
    this->getHitbox().setSize(sf::Vector2f(30,10));
    
		direction = dir;
		type = 1;
		thrust = true;
		anchor = newSource->getPosition();

		attackMotion = 0.1;
		

	}

	else if (this->type == SWORD) {
        
    this->textureName = "Assets/Textures/Items/DaggerAttackImage";
    
		if (newSource->isFacingRight()) {
      /* --TEMP--
			this->textureOfVisualRepresentation.loadFromFile("Assets/Textures/Items/DaggerAttackImage.png");
			this->visualRepresentation.setTexture(textureOfVisualRepresentation);
			this->visualRepresentation.setScale(sf::Vector2f(.15, .2));
      
      

			//this->getHitBox().setSize(sf::Vector2f(this->visualRepresentation.getLocalBounds().width * this->visualRepresentation.getScale().x, this->visualRepresentation.getLocalBounds().height * this->visualRepresentation.getScale().y));
			//this->sprite.setSize(this->getHitBox().getSize());
      */
      
      this->sprite.setScale(sf::Vector2f(.15,.2));

			direction = dir - ((120.0 / 180.0) * pi);
			std::cout << direction << std::endl;
			type = 2;
			anchor = newSource->getPosition();
		}
		else {
  /*
  --TEMP--
			this->textureOfVisualRepresentation.loadFromFile("Assets/Textures/Items/DaggerAttackImage.png");
			this->visualRepresentation.setTexture(textureOfVisualRepresentation);
			this->visualRepresentation.setScale(sf::Vector2f(.15, -.2));
    
      
			//this->getHitBox().setSize(sf::Vector2f(this->visualRepresentation.getLocalBounds().width * this->visualRepresentation.getScale().x, this->visualRepresentation.getLocalBounds().height * this->visualRepresentation.getScale().y));
			//this->sprite.setSize(this->getHitBox().getSize());
      */
      
      this->sprite.setScale(sf::Vector2f(.15,-.2));

			direction = dir + ((120.0 / 180.0) * pi);
			std::cout << direction << std::endl;
			type = 2;
			anchor = newSource->getPosition();



    }

	}

}

//Alternate constructor with a type differentiator at the end, used to determine attack behavior.
MeleeAttack::MeleeAttack(int x, int y, int width, int height, float dir, Actor* newSource, int t) : Attack(x, y, width, height, newSource) {
	this->type = t;	
  this->melee = true;
	if (this->type == DAGGER) {
    /*
     --TEMP--
		this->textureOfVisualRepresentation.loadFromFile("Assets/Textures/Items/DaggerAttackImage.png");
		this->visualRepresentation.setTexture(textureOfVisualRepresentation);
		if (newSource->isFacingRight())
			this->visualRepresentation.setScale(sf::Vector2f(.15, .2));
		else
			this->visualRepresentation.setScale(sf::Vector2f(-.15, .2));

		//std::cout << ((float) this->visualRepresentation.getLocalBounds().height) * this->visualRepresentation.getScale().y << std::endl;

		this->getHitBox().setSize(sf::Vector2f(this->visualRepresentation.getLocalBounds().width * this->visualRepresentation.getScale().x, this->visualRepresentation.getLocalBounds().height * this->visualRepresentation.getScale().y));
    */
    
    this->textureName = "Assets/Textures/Items/DaggerAttackImage";

		if (newSource->isFacingRight())
			this->sprite.setScale(sf::Vector2f(.15, .2));
		else
			this->sprite.setScale(sf::Vector2f(-.15, .2));
    
    
    //this->getHitBox().setSize(sf::Vector2f(this->sprite.getLocalBounds().width * this->sprite.getScale().x, this->sprite.getLocalBounds().height * this->sprite.getScale().y));
    this->getHitbox().setSize(sf::Vector2f(30,10));
    
		direction = dir;
		type = 1;
		thrust = true;
		anchor = newSource->getPosition();

		attackMotion = 0.1;
		

	}

	else if (this->type == SWORD) {
        
    this->textureName = "Assets/Textures/Items/DaggerAttackImage";
    
		if (newSource->isFacingRight()) {
      /*
      --TEMP--
			this->textureOfVisualRepresentation.loadFromFile("Assets/Textures/Items/DaggerAttackImage.png");
			this->visualRepresentation.setTexture(textureOfVisualRepresentation);
			this->visualRepresentation.setScale(sf::Vector2f(.15, .2));
      
      

			//this->getHitBox().setSize(sf::Vector2f(this->visualRepresentation.getLocalBounds().width * this->visualRepresentation.getScale().x, this->visualRepresentation.getLocalBounds().height * this->visualRepresentation.getScale().y));
			//this->sprite.setSize(this->getHitBox().getSize());
      */
      
      this->sprite.setScale(sf::Vector2f(.15,-.2));

			direction = dir - ((120.0 / 180.0) * pi);
			std::cout << direction << std::endl;
			type = 2;
			anchor = newSource->getPosition();
		}
		else {
      /*
      --TEMP--
			this->textureOfVisualRepresentation.loadFromFile("Assets/Textures/Items/DaggerAttackImage.png");
			this->visualRepresentation.setTexture(textureOfVisualRepresentation);
			this->visualRepresentation.setScale(sf::Vector2f(.15, -.2));
      
      
			//this->getHitBox().setSize(sf::Vector2f(this->visualRepresentation.getLocalBounds().width * this->visualRepresentation.getScale().x, this->visualRepresentation.getLocalBounds().height * this->visualRepresentation.getScale().y));
			//this->sprite.setSize(this->getHitBox().getSize());
   */
			direction = dir + ((120.0 / 180.0) * pi);
			std::cout << direction << std::endl;
			type = 2;
			anchor = newSource->getPosition();



    }

	}
}



MeleeAttack::~MeleeAttack() { }

void MeleeAttack::update(float deltaTime) {
	bool check = this->isRemoved();

	if (this->isRemoved()) {
		return;
	}

	//Update for thrust/stab type weapons
	else if (this->type == DAGGER) {

		if (attackMotion >= 1 || collidedWithTile) {
			thrust = false;
		}

		position.x = source->getPosition().x + source->getHitBox().getSize().x / 4 + source->getHitBox().getSize().x * cos(direction) * attackMotion * 1;
		position.y = source->getPosition().y + source->getHitBox().getSize().y / 4 + source->getHitBox().getSize().y * sin(direction) * attackMotion * 1;

		if (thrust)
			attackMotion += deltaTime * 2;
		else
			attackMotion -= deltaTime * 2;

		duration += deltaTime;

		if (duration >= 2.0)
			remove();


		this->sprite.setPosition(position);
    //rotation needs to be changed to sprite --TEMP--
		rotation(direction);
		hitBox.setPosition(position);
	}
  
  //Update for "swing" type weapons
  else if (this->type == SWORD) {

		if (collidedWithTile && duration < 1.8) {
			duration = 1.8;
		}


		if (duration > 1.3 && duration < 1.5) {
			if (source->isFacingRight())
				direction += deltaTime * ((1.0 / 3.0) * pi) * 10;
			else
				direction -= deltaTime * ((1.0 / 3.0) * pi) * 10;
		}

		duration += deltaTime;

		position.x = source->getPosition().x + source->getHitBox().getSize().x / 2 + source->getHitBox().getSize().x * cos(direction);
		position.y = source->getPosition().y + source->getHitBox().getSize().y / 2 + source->getHitBox().getSize().y * sin(direction);

		this->sprite.setPosition(position);
    
    //rotation needs to be changed to sprite --TEMP--
		rotation(direction);

		position.x += cos(direction) * 20;
		position.y += sin(direction) * 20;

		if (duration >= 2.0)
			remove();

		hitBox.setPosition(position);
	}
}

