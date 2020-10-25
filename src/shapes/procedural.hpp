

#pragma once

#include <shapes/shape.hpp>

namespace shapes
{
    enum class clockwise
    {
        cw,
        ccw
    };

    class procedural : public shape
    {
    public:
        constexpr static size_t gen_uv = 1ull << 0;
        constexpr static size_t gen_normal = 1ull << 1;
        constexpr static size_t gen_tangents = 1ull << 2;
        constexpr static size_t triangulate = 1ull << 3;

        explicit procedural(uint32_t smoothness, uint32_t cond_bits, float umax = 1, float vmax = 1, clockwise clockwise = clockwise::cw, bool closed = true);
        ~procedural() override = default;
        void generate(std::vector<uint8_t>& vertices, std::vector<uint8_t>& indices) override;

    protected:
        virtual math::vec3 get_position(float u, float v) = 0;
        virtual math::vec3 get_normal(float u, float v, math::vec3 position) = 0;
        virtual math::vec3 get_tangent(float u, float v, math::vec3 position) = 0;

    private:
        uint32_t m_smoothness;
        uint64_t m_cond_bits;

        float m_umax;
        float m_vmax;
        clockwise m_clockwise;
        bool m_closed;
    };
} // namespace shapes
