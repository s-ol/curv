// Copyright 2016-2018 Doug Moen
// Licensed under the Apache License, version 2.0
// See accompanying file LICENSE or https://www.apache.org/licenses/LICENSE-2.0

#ifndef LIBCURV_GEOM_GLSL_H
#define LIBCURV_GEOM_GLSL_H

#include <ostream>

namespace curv { namespace geom {

struct Shape_Program;

// Export a shape's dist and colour functions as a set of GLSL definitions.
void glsl_function_export(const Shape_Program&, std::ostream&);

}} // namespace
#endif // header guard
