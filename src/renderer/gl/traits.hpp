


#pragma once

#include <renderer/renderer.hpp>
#include <misc/debug.hpp>

#include <glad/glad.h>

namespace renderer::gl::traits
{
    struct gl_type
    {
        GLuint gl_format;
        size_t type_size;
    };


    inline gl_type get_gl_type(::renderer::data_type type)
    {
        switch (type) {
            case data_type::f32:
                return {GL_FLOAT, sizeof(float)};
            case data_type::f16:
                return {GL_FLOAT, sizeof(float) / 2};
            case data_type::u32:
                return {GL_UNSIGNED_INT, sizeof(uint32_t)};
            case data_type::u16:
                return {GL_UNSIGNED_SHORT, sizeof(uint16_t)};
            case data_type::u8:
                return {GL_UNSIGNED_BYTE, sizeof(uint8_t)};
            default:
                ASSERT(false && "invalid type.");
        }
    }


    inline GLenum get_gl_shader_stage(::renderer::shader_stage_name shader_stage_name)
    {
        switch (shader_stage_name) {
            case shader_stage_name::vertex:
                return GL_VERTEX_SHADER;
            case shader_stage_name::fragment:
                return GL_FRAGMENT_SHADER;
            case shader_stage_name::geometry:
                return GL_GEOMETRY_SHADER;
        }
    }


    inline GLenum get_gl_texture_type(const ::renderer::texture_descriptor& descriptor)
    {
        switch (descriptor.type) {
            case texture_type::d2:
                return descriptor.size.length == 1 ? GL_TEXTURE_2D : GL_TEXTURE_2D_ARRAY;
            case texture_type::d3:
                return GL_TEXTURE_3D;
            case texture_type::cube:
                return descriptor.size.length == 1 ? GL_TEXTURE_CUBE_MAP : GL_TEXTURE_CUBE_MAP_ARRAY;
            case texture_type::attachment:
                return GL_TEXTURE_2D;
            default:
                ASSERT(false && "invalid texture type.");
        }
    }


    inline GLenum get_gl_fmt(::renderer::texture_format fmt) {
        switch (fmt) {
            case texture_format::r:
                return GL_R;
            case texture_format::rg:
                return GL_RG;
            case texture_format::rgba:
                return GL_RGBA;
        }
    }


    inline std::tuple<GLenum, GLenum, GLenum> get_texture_formats(const ::renderer::texture_descriptor& descriptor)
    {
        switch (descriptor.pixels_data_type) {
            case data_type::f32:
                switch (descriptor.format) {
                    case texture_format::r:
                        return {GL_FLOAT, GL_R32F, GL_R};
                    case texture_format::rg:
                        return {GL_FLOAT, GL_RG32F, GL_RG};
                    case texture_format::rgba:
                        return {GL_FLOAT, GL_RGBA32F, GL_RGBA};
                }
            case data_type::f16:
                switch (descriptor.format) {
                    case texture_format::r:
                        return {GL_FLOAT, GL_R16F, GL_R};
                    case texture_format::rg:
                        return {GL_FLOAT, GL_RG16F, GL_RG};
                    case texture_format::rgba:
                        return {GL_FLOAT, GL_RGBA16F, GL_RGBA};
                }
            case data_type::u32:
                switch (descriptor.format) {
                    case texture_format::r:
                        return {GL_UNSIGNED_INT, GL_R32UI, GL_R};
                    case texture_format::rg:
                        return {GL_UNSIGNED_INT, GL_RG32UI, GL_RG};
                    case texture_format::rgba:
                        return {GL_UNSIGNED_INT, GL_RGBA32UI, GL_RGBA};
                }
            case data_type::u16:
                switch (descriptor.format) {
                    case texture_format::r:
                        return {GL_UNSIGNED_SHORT, GL_R16, GL_R};
                    case texture_format::rg:
                        return {GL_UNSIGNED_SHORT, GL_RG16, GL_RG};
                    case texture_format::rgba:
                        return {GL_UNSIGNED_SHORT, GL_RGBA16, GL_RGBA};
                }
            case data_type::u8:
                switch (descriptor.format) {
                    case texture_format::r:
                        return {GL_UNSIGNED_BYTE, GL_R8, GL_R};
                    case texture_format::rg:
                        return {GL_UNSIGNED_BYTE, GL_RG8, GL_RG};
                    case texture_format::rgba:
                        return {GL_UNSIGNED_BYTE, GL_RGBA8, GL_RGBA};
                }
            case data_type::d24:
                return {GL_FLOAT, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT};
            default:
                ASSERT(false && "invalid texture data type.");
        }
    }


    inline size_t get_parameter_size(::renderer::parameter_type type)
    {
        switch (type) {
            case parameter_type::vec4:
                return sizeof(float) * 4;
            case parameter_type::mat2x4:
                return 2 * (sizeof(float) * 4);
            case parameter_type::mat3x4:
                return 3 * (sizeof(float) * 4);
            case parameter_type::mat4:
                return 4 * (sizeof(float) * 4);
        }
    }

    inline size_t get_gl_geom_topology(::renderer::geometry_topology topology, bool adjacent)
    {
        switch (topology) {
            case geometry_topology::points:
                return GL_POINTS;
            case geometry_topology::lines:
                return adjacent ? GL_LINES_ADJACENCY : GL_LINES;
            case geometry_topology::line_strips:
                return adjacent ? GL_LINE_STRIP_ADJACENCY : GL_LINE_STRIP;
            case geometry_topology::triangles:
                return  adjacent ? GL_TRIANGLES_ADJACENCY : GL_TRIANGLES;
            case geometry_topology::triangles_strip:
                return adjacent ? GL_TRIANGLES_ADJACENCY : GL_TRIANGLE_STRIP;
        }
    }

} // namespace renderer::gl::traits
