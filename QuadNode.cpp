#include "QuadNode.h"
#include <iostream>
#include <sstream>

cQuadNode::cQuadNode() : m_x(0.0f), m_y(0.0f), m_velocityX(0.0f), m_velocityY(0.0f), m_previousX(0.0f), m_previousY(0.0f) {
	x = 0.0f;
	y = 0.0f;
	width = 320;
	height = 240;

	id = 0;
	level = 0;
	maxLevel = 3;

	maxObjects = 1;
	numObjects = 0;

	parent = nullptr;

	isLeaf = true;
}

cQuadNode::~cQuadNode() {
	//nodes.clear();
	/*objects.clear();*/
}

void cQuadNode::setMaxLevel(int _maxLevel) {
	if (isLeaf == true) {
		maxLevel = _maxLevel;
	} else {
		for (unsigned short i=0; i<nodes.size(); ++i) {
			nodes.at(i)->setMaxLevel(_maxLevel);
		}
	}
}

void cQuadNode::setMaxObjects(int _maxObjects) {
	if (isLeaf == true) {
		maxObjects = _maxObjects;
	} else {
		for (unsigned short i=0; i<nodes.size(); ++i) {
			nodes.at(i)->setMaxObjects(_maxObjects);
		}
	}
}


//void cQuadNode::setX(float _x)
//{
//	if(isLeaf == true) {
//		x = _x;
//	}
//	else {
//		for(int i=0; i<nodes.size(); ++i) {
//			nodes.at(i)->setX(_x);
//		}
//	}
//}
//
//void cQuadNode::setY(float _y)
//{
//	if(isLeaf == true) {
//		y = _y;
//	}
//	else {
//		for(int i=0; i<nodes.size(); ++i) {
//			nodes.at(i)->setY(_y);
//		}
//	}
//}

void cQuadNode::clearAll() {
	if (isLeaf == true) {
		if (parent == nullptr)
			return;

		for (unsigned int i=0; i< parent->nodes.size(); ++i) {
			parent->nodes.at(i)->objects.clear();
			parent->nodes.at(i)->numObjects = 0;
		}

		parent->nodes.clear();
		parent->isLeaf = true;
		//nodes.clear();
	} else {
		for (unsigned int j=0; j<nodes.size(); ++j) {
			//if(_x >= nodes.at(j)->x  &&  _x <= nodes.at(j)->x+nodes.at(j)->width	&&	_y >= nodes.at(j)->y  &&  _y <= nodes.at(j)->y+nodes.at(j)->height) {
				//std::cout << "Node is not leaf\n";
				nodes.at(j)->clearAll();
			//}
		}
	}
}

void cQuadNode::clearNodeAt(float _x, float _y) {
	if (isLeaf == true) {
		if(parent == nullptr)
			return;

		for(unsigned int i=0; i < parent->nodes.size(); ++i) {
			parent->nodes.at(i)->objects.clear();
			parent->nodes.at(i)->numObjects = 0;
		}

		parent->nodes.clear();
		parent->isLeaf = true;
		//nodes.clear();
	}
	else {
		for (unsigned int j=0; j<nodes.size(); ++j) {
			if (_x >= nodes.at(j)->x  &&  _x <= nodes.at(j)->x+nodes.at(j)->width	&&	_y >= nodes.at(j)->y  &&  _y <= nodes.at(j)->y+nodes.at(j)->height) {				
				nodes.at(j)->clearNodeAt(_x, _y);
			}
		}
	}
}

cQuadNode &cQuadNode::getNodeAt(float _x, float _y) {
	if(isLeaf == false) {
		for(unsigned int j=0; j<nodes.size(); ++j) {
			if(_x >= nodes.at(j)->x  &&  _x <= nodes.at(j)->x+nodes.at(j)->width	&&	_y >= nodes.at(j)->y  &&  _y <= nodes.at(j)->y+nodes.at(j)->height) {
				//std::cout << "Node is not leaf\n";
				return nodes.at(j)->getNodeAt(_x, _y);
			}
		}
	}
	return *this;
}

std::vector<cObject*> &cQuadNode::getObjectsAt(float _x, float _y) {
	if (isLeaf == false) {
		for(unsigned int j=0; j<nodes.size(); ++j) {
			if(_x >= nodes.at(j)->x  &&  _x <= nodes.at(j)->x+nodes.at(j)->width	&&	_y >= nodes.at(j)->y  &&  _y <= nodes.at(j)->y+nodes.at(j)->height) {
				return nodes.at(j)->getObjectsAt(_x, _y);
			}
		}
	}
	return objects;
}

void cQuadNode::insert(cObject *object) {
	if (isLeaf == true) {		
		//std::cout << "inserted object into node " << id << " at level " << level << "\n";
		/*object->setNodeId(id);
		object->setNodeLevel(level);*/
		objects.push_back(object);
		//std::sort(objects.begin(), objects.end());
		
		++numObjects;

		if (numObjects > maxObjects && level < maxLevel) {
			//std::cout << "splitting node " << id << " at level " << level << "\n";
			split();
			numObjects = 0;
		}
	}
	else {
		// Check if points of the bounding box are inside the nodes
		for(unsigned int j=0; j<nodes.size(); ++j) {
				// Upper left
			if (object->getX() >= nodes.at(j)->x  &&  object->getX() <= nodes.at(j)->x+nodes.at(j)->width	&&	object->getY() >= nodes.at(j)->y  &&  object->getY() <= nodes.at(j)->y+nodes.at(j)->height
				||	// Upper right				
				object->getX()+object->getWidth() >= nodes.at(j)->x  &&  object->getX()+object->getWidth() <= nodes.at(j)->x+nodes.at(j)->width	&&	object->getY() >= nodes.at(j)->y  &&  object->getY() <= nodes.at(j)->y+nodes.at(j)->height
				||	// Lower left			
				object->getX() >= nodes.at(j)->x  &&  object->getX() <= nodes.at(j)->x + nodes.at(j)->width	&&	object->getY() + object->getHeight() >= nodes.at(j)->y  &&  object->getY() + object->getHeight() <= nodes.at(j)->y + nodes.at(j)->height
				||	// Lower right
				object->getX()+object->getWidth() >= nodes.at(j)->x  &&  object->getX()+object->getWidth() <= nodes.at(j)->x+nodes.at(j)->width	&&	object->getY()+object->getHeight() >= nodes.at(j)->y  &&  object->getY()+object->getHeight() <= nodes.at(j)->y+nodes.at(j)->height
				) {
				nodes.at(j)->insert( object );
				//std::sort(nodes.begin(), nodes.end());		
			}
		}
	}
}

void cQuadNode::split()
{
	isLeaf = false;

	nodes.clear();

	//Upper left
	nodes.push_back(new cQuadNode);
	nodes.at( nodes.size()-1)->parent = this;
	nodes.at( nodes.size()-1)->level = level + 1;
	nodes.at( nodes.size()-1)->maxLevel = maxLevel;
	nodes.at( nodes.size()-1)->id = 0;
	nodes.at( nodes.size()-1)->width = width/2;
	nodes.at( nodes.size()-1)->height = height/2;
	nodes.at( nodes.size()-1)->x = x;
	nodes.at( nodes.size()-1)->y = y;
	nodes.at( nodes.size()-1)->isLeaf = true;
	//std::cout << "split node " << id << " at level " << level << " into node " << 0 << " at level " << level + 1 << "\n";

	//Upper right
	nodes.push_back(new cQuadNode);
	nodes.at( nodes.size()-1)->parent = this;
	nodes.at( nodes.size()-1)->level = level + 1;
	nodes.at( nodes.size()-1)->maxLevel = maxLevel;
	nodes.at( nodes.size()-1)->id = 1;	
	nodes.at( nodes.size()-1)->width = width/2;
	nodes.at( nodes.size()-1)->height = height/2;
	nodes.at( nodes.size()-1)->x = x + width/2;
	nodes.at( nodes.size()-1)->y = y;
	nodes.at( nodes.size()-1)->isLeaf = true;
	//std::cout << "split node " << id << " at level " << level << " into node " << 1 << " at level " << level + 1 << "\n";

	//Lower left
	nodes.push_back(new cQuadNode);
	nodes.at( nodes.size()-1)->parent = this;
	nodes.at( nodes.size()-1)->level = level + 1;
	nodes.at( nodes.size()-1)->maxLevel = maxLevel;
	nodes.at( nodes.size()-1)->id = 2;
	nodes.at( nodes.size()-1)->width = width/2;
	nodes.at( nodes.size()-1)->height = height/2;
	nodes.at( nodes.size()-1)->x = x;
	nodes.at( nodes.size()-1)->y = y + height/2;
	nodes.at( nodes.size()-1)->isLeaf = true;
	//std::cout << "split node " << id << " at level " << level << " into node " << 2 << " at level " << level + 1 << "\n";

	//Lower right
	nodes.push_back(new cQuadNode);
	nodes.at( nodes.size()-1)->parent = this;
	nodes.at( nodes.size()-1)->level = level + 1;
	nodes.at( nodes.size()-1)->maxLevel = maxLevel;
	nodes.at( nodes.size()-1)->id = 3;	
	nodes.at( nodes.size()-1)->width = width/2;
	nodes.at( nodes.size()-1)->height = height/2;
	nodes.at( nodes.size()-1)->x = x + width/2;
	nodes.at( nodes.size()-1)->y = y + height/2;
	nodes.at( nodes.size()-1)->isLeaf = true;
	//std::cout << "split node " << id << " at level " << level << " into node " << 3 << " at level " << level + 1 << "\n";

	// Check if points of the bounding box are inside the nodes
	for(unsigned int i=0; i<objects.size(); ++i) {
		for(unsigned int j=0; j<nodes.size(); ++j) {
			// Upper left
			if(objects.at(i)->getX()+objects.at(i)->getWidth()/2 >= nodes.at(j)->x  &&  objects.at(i)->getX()+objects.at(i)->getWidth()/2 <= nodes.at(j)->x+nodes.at(j)->width	&&				objects.at(i)->getY()+objects.at(i)->getHeight()/2 >= nodes.at(j)->y  &&  objects.at(i)->getY()+objects.at(i)->getHeight()/2 <= nodes.at(j)->y+nodes.at(j)->height
				//||
				//// Upper right
				//objects.at(i)->x+objects.at(i)->width >= nodes.at(j)->x  &&  objects.at(i)->x+objects.at(i)->width <= nodes.at(j)->x+nodes.at(j)->width	&&	objects.at(i)->y >= nodes.at(j)->y  &&  objects.at(i)->y <= nodes.at(j)->y+nodes.at(j)->height
				//||
				//// Lower left
				//objects.at(i)->x >= nodes.at(j)->x  &&  objects.at(i)->x <= nodes.at(j)->x+nodes.at(j)->width	&&	objects.at(i)->y+objects.at(i)->height >= nodes.at(j)->y  &&  objects.at(i)->y+objects.at(i)->height <= nodes.at(j)->y+nodes.at(j)->height
				//||
				//// Lower right
				//objects.at(i)->x+objects.at(i)->width >= nodes.at(j)->x  &&  objects.at(i)->x+objects.at(i)->width <= nodes.at(j)->x+nodes.at(j)->width	&&	objects.at(i)->y+objects.at(i)->height >= nodes.at(j)->y  &&  objects.at(i)->y+objects.at(i)->height <= nodes.at(j)->y+nodes.at(j)->height
				) {
				//nodes.at(j)->isLeaf = true;
				nodes.at(j)->insert( objects.at(i) );
			}	
		}
	}

	objects.clear();
	//std::sort(nodes.begin(), nodes.end());
}

void cQuadNode::update(float time) {
	m_previousX = m_x;
	m_previousY = m_y;
	m_x += m_velocityX;
	m_y += m_velocityY;

	//if (isLeaf == true) {
	//	leftShape.setPosition(x + m_x, y + m_y);
	//	leftShape.setSize(sf::Vector2f(1, height));
	//	leftShape.setFillColor(sf::Color(128, 128, 128));

	//	rightShape.setPosition(x + width + m_x, y + m_y);
	//	rightShape.setSize(sf::Vector2f(1, height));
	//	rightShape.setFillColor(sf::Color(128, 128, 128));

	//	upShape.setPosition(x + m_x, y + m_y);
	//	upShape.setSize(sf::Vector2f(width, 1));
	//	upShape.setFillColor(sf::Color(128, 128, 128));

	//	downShape.setPosition(x + m_x, y + height + m_y);
	//	downShape.setSize(sf::Vector2f(width, 1));
	//	downShape.setFillColor(sf::Color(128, 128, 128));
	//}
	/*if (isLeaf == true) {
	leftShape.setPosition(x + m_x, y + m_y);
	rightShape.setPosition(x + width + m_x, y + m_y);
	upShape.setPosition(x + m_x, y + m_y);
	downShape.setPosition(x + m_x, y + height + m_y);
	}*/

}

void cQuadNode::draw( sf::RenderTarget &canvas ) {
	/*if(this == nullptr)
		return;*/

	/*for(int i=0; i<objects.size(); ++i) {
		objects.at(i)->draw(canvas);
	}*/
	

	if (isLeaf == true) {
		leftShape.setPosition(x + m_x, y + m_y);
		leftShape.setSize(sf::Vector2f(1.0f, (float)height));
		leftShape.setFillColor(sf::Color(128, 128, 128));

		rightShape.setPosition(x + (float)width + m_x, y + m_y);
		rightShape.setSize(sf::Vector2f(1.0f, (float)height));
		rightShape.setFillColor(sf::Color(128, 128, 128));

		upShape.setPosition(x + m_x, y + m_y);
		upShape.setSize(sf::Vector2f((float)width, 1.0f));
		upShape.setFillColor(sf::Color(128, 128, 128));

		downShape.setPosition(x + m_x, y + (float)height + m_y);
		downShape.setSize(sf::Vector2f((float)width, 1.0f));
		downShape.setFillColor(sf::Color(128, 128, 128));
		canvas.draw(leftShape);
		canvas.draw(rightShape);
		canvas.draw(upShape);
		canvas.draw(downShape);		
	}
	else {
		for (unsigned int i=0; i<nodes.size(); ++i) {
			if (nodes.at(i) != nullptr)
				nodes.at(i)->draw(canvas);
		}
	}

	
}