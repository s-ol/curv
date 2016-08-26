// Copyright Doug Moen 2016.
// Distributed under The MIT License.
// See accompanying file LICENSE.md or https://opensource.org/licenses/MIT

#ifndef CURV_ANALYZER_H
#define CURV_ANALYZER_H

#include <curv/meaning.h>
#include <curv/builtin.h>

namespace curv {

struct Environ
{
    Environ* parent;
    size_t frame_nslots;
    size_t frame_maxslots;

    Environ(Environ* p = nullptr)
    : parent(p), frame_nslots(0), frame_maxslots(0)
    { }
    Shared<Meaning> lookup(const Identifier& id) const;
    virtual Shared<Meaning> single_lookup(const Identifier&, Atom) const = 0;
};

struct Builtin_Environ : public Environ
{
protected:
    const Namespace& names;
public:
    Builtin_Environ(const Namespace& n, Environ* p = nullptr)
    : Environ(p), names(n)
    {}
    virtual Shared<Meaning> single_lookup(const Identifier&, Atom) const;
};

struct Module_Environ : public Environ
{
protected:
    const Atom_Map<Shared<Phrase>>& names;
public:
    Module_Environ(
        Environ* p,
        const Atom_Map<Shared<Phrase>>& n)
    : Environ(p), names(n)
    {}
    virtual Shared<Meaning> single_lookup(const Identifier&, Atom) const;
};

inline Shared<Meaning>
analyze(const Phrase& ph, Environ& env)
{
    return ph.analyze(env);
}

Shared<Expression> analyze_expr(const Phrase& ph, Environ& env);

} // namespace
#endif // header guard
