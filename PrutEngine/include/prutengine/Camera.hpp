#ifndef PRUTENGINE_CAMERA_HPP
#define PRUTENGINE_CAMERA_HPP
//##include "./GameObject.hpp"

#include "./Node.hpp"

namespace PrutEngine{
    class AbstractScene;

    class Camera : public Node{
        friend AbstractScene;
    protected:
        virtual void update(const float& tpf) override;
    public:
        Camera(const Math::Vector<float,3>& startPos);
    };

}




#endif
