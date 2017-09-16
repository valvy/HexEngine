#include "prutengine/Node.hpp"
using namespace PrutEngine;

Node::Node(){
    this->transform = std::shared_ptr<Transform>(new Transform());
}

void Node::add(std::shared_ptr<Node> node){
    this->children.push_back(node);
}

void Node::rm(std::shared_ptr<Node> node){

}

void Node::update(const float& tpf){
    for(auto it : this->children){
        it->update(tpf);
    }
}

void Node::onKeyDown(const unsigned short& keycode){
    for(auto it : this->children){
        it->onKeyDown(keycode);
    }
}

std::shared_ptr<Transform> Node::getTransform() const{
    return this->transform;
}

Node::~Node(){
    this->transform.reset();
    this->children.clear();
}