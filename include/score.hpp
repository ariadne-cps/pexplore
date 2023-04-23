/***************************************************************************
 *            score.hpp
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

/*! \file score.hpp
 *  \brief Class for defining the score with respect to a constraint.
 */

#ifndef PEXPLORE_SCORE
#define PEXPLORE_SCORE

#include "utility/container.hpp"
#include "utility/writable.hpp"
#include "pronest/configuration_search_point.hpp"

namespace pExplore {

using ProNest::ConfigurationSearchPoint;
using Utility::WritableInterface;
using Utility::Set;
using std::to_string;
using std::ostream;
using std::size_t;

//! \brief The score of a constraint
class ConstraintScore : public WritableInterface {
  public:
    ConstraintScore(Set<size_t> const& successes, Set<size_t> const& hard_failures, Set<size_t> const& soft_failures, double objective);

    Set<size_t> const& successes() const;
    Set<size_t> const& hard_failures() const;
    Set<size_t> const& soft_failures() const;

    double objective() const;

    //! \brief Ordering is minimum over hard_failures, then soft_failures, then objective
    //! \details Successes are not used
    bool operator<(ConstraintScore const& e) const;

    //! \brief Equality checking
    bool operator==(ConstraintScore const& e) const;

    virtual ostream& _write(ostream& os) const;
  private:
    Set<size_t> _successes;
    Set<size_t> _hard_failures;
    Set<size_t> _soft_failures;
    double _objective;
};

//! \brief The point + contraint score couple
class PointConstraintScore : public WritableInterface {
  public:
    PointConstraintScore(ConfigurationSearchPoint const& p, ConstraintScore const& evaluation);

    ConfigurationSearchPoint const& point() const;
    ConstraintScore const& evaluation() const;

    //! \brief Ordering uses the score
    bool operator<(PointConstraintScore const& s) const;

    virtual ostream& _write(ostream& os) const;
  private:
    ConfigurationSearchPoint _point;
    ConstraintScore _evaluation;
};

} // namespace pExplore

#endif // PEXPLORE_SCORE