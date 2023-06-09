/***************************************************************************
 *            task_interface.hpp
 *
 *  Copyright  2007-20  Luca Geretti
 *
 ****************************************************************************/

/*
 * This file is part of pExplore, under the MIT license.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*! \file task_interface.hpp
 *  \brief The interface for tasks.
 */

#ifndef PEXPLORE_TASK_INTERFACE_HPP
#define PEXPLORE_TASK_INTERFACE_HPP

#include <chrono>
#include "helper/container.hpp"
#include "helper/tuple.hpp"
#include "helper/string.hpp"
#include "pronest/configuration_search_point.hpp"

namespace pExplore {

using Helper::String;
using Helper::Set;
using Helper::Pair;
using Helper::Map;
using Helper::List;
using ProNest::ConfigurationSearchPoint;
using ProNest::Configuration;

class PointScore;
template<class R> class Constraint;
template<class R> class ConstrainingState;

template<class R> struct TaskInput;
template<class R> struct TaskOutput;
template<class R> struct Task;

template<class R>
class TaskInterface {
  public:
    typedef TaskInput<R> InputType;
    typedef TaskOutput<R> OutputType;
    typedef Configuration<R> ConfigurationType;

    //! \brief The name of the task, to be used for thread naming
    virtual String name() const = 0;
    //! \brief Return the constraining state for the task
    virtual ConstrainingState<R> const& constraining_state() const = 0;
    //! \brief Set the constraints for the task
    virtual void set_constraints(List<Constraint<R>> const& constraints) = 0;
    //! \brief Update the constraining state given the \a input and \a output
    virtual void update_constraining_state(InputType const& input, OutputType const& output) = 0;

    //! \brief The task to be performed, taking \a in as input and \a cfg as a configuration of the parameters
    virtual OutputType run(InputType const& in, ConfigurationType const& cfg) const = 0;
};

} // namespace pExplore

#endif // PEXPLORE_TASK_INTERFACE_HPP
