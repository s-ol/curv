// Copyright 2016-2018 Doug Moen
// Licensed under the Apache License, version 2.0
// See accompanying file LICENSE or https://www.apache.org/licenses/LICENSE-2.0

#ifndef LIBCURV_PROGRAM_H
#define LIBCURV_PROGRAM_H

#include <libcurv/builtin.h>
#include <libcurv/frame.h>
#include <libcurv/meaning.h>
#include <libcurv/module.h>
#include <libcurv/source.h>
#include <libcurv/shared.h>
#include <libcurv/system.h>
#include <libcurv/list.h>

namespace curv {

struct Program
{
    const Source& source_;
    System& system_;
    const Namespace* names_ = nullptr;
    Frame *parent_frame_ = nullptr;
    Shared<Phrase> phrase_ = nullptr;
    Shared<Meaning> meaning_ = nullptr;
    Shared<Module_Expr> module_ = nullptr;
    std::unique_ptr<Frame> frame_ = nullptr;

    Program(
        const Source& source,
        System& system)
    :
        source_(source),
        system_(system)
    {}

    void compile(
        const Namespace* names = nullptr,
        Frame *parent_frame = nullptr);

    const Phrase& nub() const;

    std::pair<Shared<Module>, Shared<List>> denotes();

    Value eval();
};

} // namespace curv
#endif // header guard
