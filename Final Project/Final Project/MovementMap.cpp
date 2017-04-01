#include "MovementMap.h"
#include <iostream>


MovementMap::MovementMap(int** tiles, int mapWidth, int mapHeight){
	this->mapWidth = mapWidth;
	this->mapHeight = mapHeight;

	//creating array of bools to signify which tiles can be moved into
	bool** canMove;
	canMove = new bool*[mapHeight];
	for (int y = 0; y < mapHeight; y++) {
		canMove[y] = new bool[mapWidth];
		for (int x = 0; x < mapWidth; x++) {
			if (tiles[y][x] == 1)	//checking if the current tile is a solid
				canMove[y][x] = false;
			//checking if the tile below is a solid or ladder
			else if (y < mapHeight - 1 && (tiles[y + 1][x] == 1 || tiles[y + 1][x] == 4 || tiles[y + 1][x] == 6 || tiles[y + 1][x] == 9)) {
				canMove[y][x] = true;
				//std::cout << "solid/ladder below" << std::endl;
			}
			//checking if the current tile is a ladder
			else if (tiles[y][x] == 4 || tiles[y][x] == 6) {
				canMove[y][x] = true;
				//std::cout << "This ladder" << std::endl;
			}
			//checking if the tile above can be moved through
			else if (y > 0 && canMove[y - 1][x]) {
				canMove[y][x] = true;
				//std::cout << "can move above" << std::endl;
			}
			//checking if the There is a corner to the left
			else if (y < mapHeight - 1 && x > 0 && tiles[y + 1][x - 1] == 1 && tiles[y][x - 1] != 1) {
				canMove[y][x] = true;
				//std::cout << "corner to lowerleft" << std::endl;
			}
			//checking if there is a corner to the right
			else if (y < mapHeight - 1 && x < mapWidth - 1 && tiles[y + 1][x + 1] == 1 && tiles[y][x + 1] != 1) {
				canMove[y][x] = true;
				//std::cout << "corner to lowerright" << std::endl;
			}
			else canMove[y][x] = false;

			//if (canMove[y][x])
			//	std::cout << x << "," << y << std::endl;
		}
	}

	//creating an array of nodes signifying in which direction from each location an entity can move
	map = new Node**[mapHeight];
	for (int y = 0; y < mapHeight; y++) {
		map[y] = new Node*[mapWidth];
		for (int x = 0; x < mapWidth; x++) {
			//creating a new node and setting it's location
			map[y][x] = new Node();
			map[y][x]->x = x;
			map[y][x]->y = y;

			//checking if an entity can move up
			if (y > 0 && canMove[y - 1][x]) {
				//checking if ladder is above
				if (tiles[y - 1][x] == 4 || tiles[y - 1][x] == 6)
					map[y][x]->up = true;
				//checking if corner to jump on to left
				else if (x > 0 && tiles[y][x - 1] == 1 && canMove[y - 1][x - 1])
					map[y][x]->up = true;
				//checking if corner to jump on to right
				else if (x < mapWidth - 1 && tiles[y][x + 1] == 1 && canMove[y - 1][x + 1])
					map[y][x]->up = true;
				//checking if current tile is top of ladder
				else if (tiles[y][x] == 9)
					map[y][x]->up = true;
			}
			//checking if entity can move down
			if (y < mapHeight - 1 && canMove[y + 1][x])
				map[y][x]->down = true;
			//checking if entity can move left
			if (x > 0 && canMove[y][x - 1])
				map[y][x]->left = true;
			//checking if entity can move right
			if (x < mapWidth - 1 && canMove[y][x + 1])
				map[y][x]->right = true;
		}
	}

	//deallocating array of open positions
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
	//creating an array of bools to mark with tiles have been visited
	bool** visited;
	visited = new bool*[mapHeight];
	for (int y = 0; y < mapHeight; y++) {
		visited[y] = new bool[mapWidth];
		for (int x = 0; x < mapWidth; x++) {
			visited[y][x] = false;
		}
	}

	//creating a queue to store nodes to check while searching for path
	std::queue<PathNode*> nodeToCheck;
	//creating the curNode, a closest node to target, and keeping track of the first node
	PathNode* curNode = new PathNode();
	PathNode* firstNode = curNode;
	PathNode* closestNode = curNode;

	//setting the first node in the path and setting that node to checked
	curNode->prevNode = NULL;
	curNode->curNode = map[(int)(start.y / 32)][ (int)(start.x / 32)];
	visited[(int)(start.y / 32)][(int)(start.x / 32)] = true;
	nodeToCheck.push(curNode);

	//std::cout << (int)(end.x / 32) << "," << (int)(end.y / 32) << std::endl;

	while (nodeToCheck.size() > 0) {
		//getting the next node
		curNode = nodeToCheck.front();
		//getting the location of the current node
		int i = 0;
		int x = curNode->curNode->x;
		int y = curNode->curNode->y;
		//std::cout << x << "," << y << std::endl;
		//std::cout << (int)(end.x / 32) << "," << (int)(end.y / 32) << std::endl;

		//checking if this node is where the target is
		if (x == (int)(end.x / 32) && y == (int)(end.y / 32))
			break;

		//checking if this node is closer to the target then the last closest node
		if ((int)(end.x / 32) == x && y > (int)(end.y / 32)) {
			if (closestNode != NULL) {
				if (closestNode->curNode->y > y)
					closestNode = curNode;
			}
		}

		//checking if the left node can be visited
		if (x > 0 && curNode->curNode->left && !visited[y][x - 1]) {
			PathNode* nextNode = new PathNode();
			nextNode->curNode = map[y][x - 1];
			curNode->nextNode[i] = nextNode;
			nextNode->prevNode = curNode;
			visited[y][x - 1] = true;
			nodeToCheck.push(nextNode);
			i++;
		}
		//checking if the right node can be visited
		if (x < mapWidth - 1 && curNode->curNode->right && !visited[y][x + 1]) {
			PathNode* nextNode = new PathNode();
			nextNode->curNode = map[y][x + 1];
			curNode->nextNode[i] = nextNode;
			nextNode->prevNode = curNode;
			visited[y][x + 1] = true;
			nodeToCheck.push(nextNode);
			i++;
		}
		//checking if the node above can be visited
		if (y > 0 && curNode->curNode->up && !visited[y - 1][x]) {
			PathNode* nextNode = new PathNode();
			nextNode->curNode = map[y - 1][x];
			curNode->nextNode[i] = nextNode;
			nextNode->prevNode = curNode;
			visited[y - 1][x] = true;
			nodeToCheck.push(nextNode);
			i++;
		}
		//checking if the node below can be visited
		if (y < mapHeight - 1 && curNode->curNode->down && !visited[y + 1][x]) {
			PathNode* nextNode = new PathNode();
			nextNode->curNode = map[y + 1][x];
			curNode->nextNode[i] = nextNode;
			nextNode->prevNode = curNode;
			visited[y + 1][x] = true;
			nodeToCheck.push(nextNode);
			i++;
		}

		//removing the current node from the list of nodes to check
		nodeToCheck.pop();
	}

	//std::cout << nodeToCheck.size() << std::endl;
	//creating a vector of vector2fs to hold the path to the target
	std::vector<sf::Vector2f>* path = new std::vector<sf::Vector2f>;
	if (nodeToCheck.size() == 0) {	//checking if a path was found
		curNode = closestNode;
		path->push_back(end);
	}

	while (curNode != NULL) {	//starting at the end, reversing through the nodes searched to get the path to the end
		path->push_back(sf::Vector2f(curNode->curNode->x * 32 + 16, curNode->curNode->y * 32 + 16));
		//std::cout << curNode->curNode->x << "," << curNode->curNode->y << std::endl;
		curNode = curNode->prevNode;
	}

	//if multiple points in the path, removing the first point if the starting point is passed it
	if (path->size() > 1) {
		if (path->at(path->size() - 1).x < start.x && path->at(path->size() - 2).x > start.x) 
			path->pop_back();
		else if (path->at(path->size() - 1).x > start.x && path->at(path->size() - 2).x < start.x)
			path->pop_back();
		else  if (path->at(path->size() - 1).y < start.y && path->at(path->size() - 2).y > start.y)
			path->pop_back();
		else if (path->at(path->size() - 1).y > start.y && path->at(path->size() - 2).y < start.y)
			path->pop_back();
	}

	//if (path->back())
	//clearing the queue checking nodes to use it for deallocating pathnodes from memory
	while (nodeToCheck.size() > 0)
		nodeToCheck.pop();

	//deallocating the pathnodes used to find the path
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

	//deallocating the visited bool array
	for (int y = 0; y < mapHeight; y++)
		delete visited[y];
	delete visited;

	//returning the path
	return path;
}