#ifndef PRUTENGINE_NODE_HPP
#define PRUTENGINE_NODE_HPP

#include "./Transform.hpp"
#include <memory>
#include <vector>

namespace PrutEngine{
    class Node{
    protected:
        std::shared_ptr<Transform> transform;
        std::vector<std::shared_ptr<Node>> children;
    public:
        Node();
        virtual void update(const float& tpf);
        virtual void onKeyDown(const unsigned short& keycode);
        std::shared_ptr<Transform> getTransform() const;
        void add(std::shared_ptr<Node> node);
        void rm(std::shared_ptr<Node> node);
        ~Node();
    };
}

#endif