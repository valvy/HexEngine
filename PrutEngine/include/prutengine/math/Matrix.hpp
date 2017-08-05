#ifndef PRUTENGINE_MATH_MATRIX_HPP
#define PRUTENGINE_MATH_MATRIX_HPP
#include <array>
namespace PrutEngine{
    namespace Math{
        template<typename T, size_t rows, size_t columns>
        class Matrix{
            std::array<T, rows * columns> data;
            public:
            Matrix(){

            }
        };
    }
}
#endif