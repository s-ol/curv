// Copyright 2016-2018 Doug Moen
// Licensed under the Apache License, version 2.0
// See accompanying file LICENSE or https://www.apache.org/licenses/LICENSE-2.0

#ifndef LIBCURV_GEOM_SHAPE_H
#define LIBCURV_GEOM_SHAPE_H

#include <libcurv/gl_compiler.h>
#include <libcurv/frame.h>
#include <libcurv/location.h>
#include <cmath>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace curv {

struct Function;
struct Context;
struct System;
struct Program;
struct Phrase;

namespace geom {

using Vec3 = glm::dvec3;

// axis aligned bounding box
struct BBox
{
    double xmin, ymin, zmin;
    double xmax, ymax, zmax;
    bool empty2() const {
        return (xmin >= xmax || ymin >= ymax);
    }
    bool empty3() const {
        return (xmin >= xmax || ymin >= ymax || zmin >= zmax);
    }
    bool infinite2() const {
        return (xmin == -INFINITY || ymin == -INFINITY ||
                xmax == +INFINITY || ymax == +INFINITY);
    }
    bool infinite3() const {
        return (xmin == -INFINITY || ymin == -INFINITY || zmin == -INFINITY ||
                xmax == +INFINITY || ymax == +INFINITY || zmax == +INFINITY);
    }
    glm::dvec2 size2() const {
        return glm::dvec2(xmax - xmin, ymax - ymin);
    }
    glm::dvec3 size3() const {
        return glm::dvec3(xmax - xmin, ymax - ymin, zmax - zmin);
    }
    static BBox from_value(Value, const Context&);
};

struct Shape
{
    bool is_2d_;
    bool is_3d_;
    BBox bbox_;
    virtual double dist(double x, double y, double z, double t) = 0;
    virtual Vec3 colour(double x, double y, double z, double t) = 0;
};

struct Shape_Program final : public Shape
{
    // is_shape is initially false, becomes true after recognize() succeeds.
    bool is_shape() const { return is_2d_ || is_3d_; }

    // describes the source code for the shape expression
    Shared<const Phrase> nub_;

    Location location() const;
    System& system() const { return system_; }
    Frame* file_frame() const { return nullptr; }

    System& system_;

    // shape fields, filled in by recognize()
    Shared<Function> dist_fun_;
    Shared<Function> colour_fun_;
    std::unique_ptr<Frame> dist_frame_;
    std::unique_ptr<Frame> colour_frame_;

    Shape_Program(Program&);

    // If the value is a shape, fill in the shape fields and return true.
    bool recognize(Value);

    /// Invoke the Geometry Compiler on the shape's `dist` function.
    GL_Value gl_dist(GL_Value, GL_Compiler&) const;

    /// Invoke the Geometry Compiler on the shape's `colour` function.
    GL_Value gl_colour(GL_Value, GL_Compiler&) const;

    // Invoke the shape's `dist` function.
    double dist(double x, double y, double z, double t);

    // Invoke the shape's `colour` function.
    Vec3 colour(double x, double y, double z, double t);
};

}} // namespace
#endif // header guard
