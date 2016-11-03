// Copyright Doug Moen 2016.
// Distributed under The MIT License.
// See accompanying file LICENSE.md or https://opensource.org/licenses/MIT

#ifndef CURV_CONTEXT_H
#define CURV_CONTEXT_H

#include <list>
#include <curv/location.h>
#include <curv/frame.h>

namespace curv {

class Phrase;
class Environ;

/// A Context describes the source code Location and call stack
/// of a compile-time or run time error.
///
/// More specifically, Context is an abstract interface to an object that
/// converts compile-time or run-time data structures into a list of Locations.
///
/// Context objects are not allocated on the heap, and don't own the data
/// structures that they point to. Instances of Context subclasses are
/// constructed in argument position as rvalues, are passed as `const Context&`
/// parameters to functions that may throw a curv::Exception, and are finally
/// consumed by the curv::Exception constructor.
///
/// An empty Context argument is `{}`.
/// Subclasses of Context are used for non-empty contexts.
struct Context
{
    virtual void get_locations(std::list<Location>&) const;
};

struct At_Frame : public Context
{
    Frame* frame_;

    At_Frame(Frame* frame) : frame_(frame) {}

    virtual void get_locations(std::list<Location>& locs) const override;
};

void get_frame_locations(const Frame* f, std::list<Location>& locs);

struct At_Location : public Context
{
    Location loc_;
    Frame* eval_frame_;

    At_Location(Location loc, Frame* f)
    : loc_(loc), eval_frame_(f)
    {}

    virtual void get_locations(std::list<Location>&) const override;
};

/// Exception Context where we know the Phrase that contains the error.
struct At_Phrase : public Context
{
    const Phrase& phrase_;
    Frame* frame_;

    At_Phrase(const Phrase& phrase, Frame* frame);
    At_Phrase(const Phrase& phrase, Environ& env);

    virtual void get_locations(std::list<Location>& locs) const override;
};

} // namespace curv
#endif // header guard
