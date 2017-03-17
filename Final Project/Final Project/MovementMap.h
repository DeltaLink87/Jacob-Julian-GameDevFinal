#pragma once
#include <vector>
#include <queue>
#include <SFML/Graphics.hpp>

class MovementMap
{
public:
	MovementMap(int**, int, int);
	~MovementMap();

	std::vector<sf::Vector2f>* getPath(sf::Vector2f, sf::Vector2f);

private:
	class Node {
	public:
		int x = 0, y = 0;
		bool up = false;
		bool down = false;
		bool left = false;
		bool right = false;
	};

	class PathNode {
	public:
		PathNode() { 
			nextNode = new PathNode*[4];
			nextNode[0] = NULL;
			nextNode[1] = NULL;
			nextNode[2] = NULL;
			nextNode[3] = NULL;
			prevNode = NULL;
			curNode = NULL;
		};

		PathNode* prevNode;
		Node* curNode;
		PathNode** nextNode;
	};

	Node*** map;
	int mapHeight;
	int mapWidth;
};

