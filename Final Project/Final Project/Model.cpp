#include "Model.h"



Model::Model(){

}

Model::~Model(){ }

void Model::update(float deltaTime) {
	player.update(deltaTime);
}