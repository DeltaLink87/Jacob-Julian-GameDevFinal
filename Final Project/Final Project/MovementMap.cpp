#include "MovementMap.h"
#include <iostream>


MovementMap::MovementMap(int** tiles, int mapWidth, int mapHeight){
	this->mapWidth = mapWidth;
	this->mapHeight = mapHeight;

	bool** canMove;
	canMove = new bool*[mapHeight];
	for (int y = 0; y < mapHeight; y++) {
		canMove[y] = new bool[mapWidth];
		for (int x = 0; x < mapWidth; x++) {
			if (tiles[y][x] == 1)
				canMove[y][x] = false;
			else if (y < mapHeight - 1 && (tiles[y + 1][x] == 1 || tiles[y + 1][x] == 4 || tiles[y + 1][x] == 6)) {
				canMove[y][x] = true;
				//std::cout << "solid/ladder below" << std::endl;
			}
			else if (tiles[y][x] == 4 || tiles[y][x] == 6) {
				canMove[y][x] = true;
				//std::cout << "This ladder" << std::endl;
			}
			else if (y > 0 && canMove[y - 1][x]) {
				canMove[y][x] = true;
				//std::cout << "can move above" << std::endl;
			}
			else if (y < mapHeight - 1 && x > 0 && tiles[y + 1][x - 1] == 1 && tiles[y][x - 1] != 1) {
				canMove[y][x] = true;
				//std::cout << "corner to lowerleft" << std::endl;
			}
			else if (y < mapHeight - 1 && x < mapWidth - 1 && tiles[y + 1][x + 1] == 1 && tiles[y][x + 1] != 1) {
				canMove[y][x] = true;
				//std::cout << "corner to lowerright" << std::endl;
			}
			else canMove[y][x] = false;

			if (canMove[y][x])
				std::cout << x << "," << y << std::endl;
		}
	}

	map = new Node**[mapHeight];
	for (int y = 0; y < mapHeight; y++) {
		map[y] = new Node*[mapWidth];
		for (int x = 0; x < mapWidth; x++) {
			map[y][x] = new Node();
			map[y][x]->x = x;
			map[y][x]->y = y;

			if (y > 0 && canMove[y - 1][x]) {
				if (tiles[y - 1][x] == 4 || tiles[y - 1][x] == 6)
					map[y][x]->up = true;
				else if (x > 0 && tiles[y][x - 1] == 1 && canMove[y - 1][x - 1])
					map[y][x]->up = true;
				else if (x < mapWidth - 1 && tiles[y][x + 1] == 1 && canMove[y - 1][x + 1])
					map[y][x]->up = true;
			}
			if (y < mapHeight - 1 && canMove[y + 1][x])
				map[y][x]->down = true;
			if (x > 0 && canMove[y][x - 1])
				map[y][x]->left = true;
			if (x < mapWidth - 1 && canMove[y][x + 1])
				map[y][x]->right = true;
		}
	}

	for (int y = 0; y < mapHeight; y++)
		delete canMove[y];
	delete canMove;
}

MovementMap::~MovementMap() {
	for (int y = 0; y < mapHeight; y++) {
		for (int x = 0; x < mapWidth; x++) {
			delete map[y][x];
		}
		delete map[y];
	}
	delete map;
}

std::vector<sf::Vector2f>* MovementMap::getPath(sf::Vector2f start, sf::Vector2f end) {
	bool** visited;
	visited = new bool*[mapHeight];
	for (int y = 0; y < mapHeight; y++) {
		visited[y] = new bool[mapWidth];
		for (int x = 0; x < mapWidth; x++) {
			visited[y][x] = false;
		}
	}

	std::queue<PathNode*> nodeToCheck;
	PathNode* curNode = new PathNode();
	PathNode* firstNode = curNode;

	curNode->prevNode = NULL;
	curNode->curNode = map[(int)(start.y / 32)][ (int)(start.x / 32)];
	visited[(int)(start.y / 32)][(int)(start.x / 32)] = true;
	nodeToCheck.push(curNode);

	//std::cout << (int)(end.x / 32) << "," << (int)(end.y / 32) << std::endl;

	while (nodeToCheck.size() > 0) {
		curNode = nodeToCheck.front();

		int i = 0;
		int x = curNode->curNode->x;
		int y = curNode->curNode->y;
		//std::cout << x << "," << y << std::endl;
		//std::cout << (int)(end.x / 32) << "," << (int)(end.y / 32) << std::endl;

		if (x == (int)(end.x / 32) && y == (int)(end.y / 32))
			break;

		if (x > 0 && curNode->curNode->left && !visited[y][x - 1]) {
			PathNode* nextNode = new PathNode();
			nextNode->curNode = map[y][x - 1];
			curNode->nextNode[i] = nextNode;
			nextNode->prevNode = curNode;
			visited[y][x - 1] = true;
			nodeToCheck.push(nextNode);
			i++;
		}
		if (x < mapWidth - 1 && curNode->curNode->right && !visited[y][x + 1]) {
			PathNode* nextNode = new PathNode();
			nextNode->curNode = map[y][x + 1];
			curNode->nextNode[i] = nextNode;
			nextNode->prevNode = curNode;
			visited[y][x + 1] = true;
			nodeToCheck.push(nextNode);
			i++;
		}
		if (y > 0 && curNode->curNode->up && !visited[y - 1][x]) {
			PathNode* nextNode = new PathNode();
			nextNode->curNode = map[y - 1][x];
			curNode->nextNode[i] = nextNode;
			nextNode->prevNode = curNode;
			visited[y - 1][x] = true;
			nodeToCheck.push(nextNode);
			i++;
		}
		if (y < mapHeight - 1 && curNode->curNode->down && !visited[y + 1][x]) {
			PathNode* nextNode = new PathNode();
			nextNode->curNode = map[y + 1][x];
			curNode->nextNode[i] = nextNode;
			nextNode->prevNode = curNode;
			visited[y + 1][x] = true;
			nodeToCheck.push(nextNode);
			i++;
		}

		nodeToCheck.pop();
	}

	//std::cout << nodeToCheck.size() << std::endl;

	std::vector<sf::Vector2f>* path = new std::vector<sf::Vector2f>;
	while (curNode != NULL) {
		path->push_back(sf::Vector2f(curNode->curNode->x * 32 + 16, curNode->curNode->y * 32 + 16));
		//std::cout << curNode->curNode->x << "," << curNode->curNode->y << std::endl;
		curNode = curNode->prevNode;
	}

	if (path->size() > 1) {
		if (path->at(0).x < start.x && path->at(1).x > start.x)
			path->pop_back();
		else if (path->at(0).x > start.x && path->at(1).x < start.x)
			path->pop_back();
		else  if (path->at(0).y < start.y && path->at(1).y > start.y)
			path->pop_back();
		else if (path->at(0).y > start.y && path->at(1).y < start.y)
			path->pop_back();
	}

	//if (path->back())
	while (nodeToCheck.size() > 0)
		nodeToCheck.pop();

	nodeToCheck.push(firstNode);
	while (nodeToCheck.size() > 0) {
		PathNode* deleteThisNode = nodeToCheck.front();
		for (int i = 0; i < 4; i++) {
			if (deleteThisNode->nextNode[i] != NULL)
				nodeToCheck.push(deleteThisNode->nextNode[i]);
		}
		nodeToCheck.pop();
		delete deleteThisNode;
	}

	for (int y = 0; y < mapHeight; y++)
		delete visited[y];
	delete visited;

	return path;
}