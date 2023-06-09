/***************************************************************************
 *            test_constraint.cpp
 *
 *  Copyright  2023  Luca Geretti
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

#include "helper/test.hpp"
#include "helper/array.hpp"
#include "constraint.hpp"
#include "task_runner_interface.hpp"

using namespace pExplore;
using namespace Helper;

class TestRunnable : public TaskRunnable<TestRunnable> { };
typedef TestRunnable R;

namespace pExplore {
template<> struct TaskInput<R> {
    TaskInput(int i1_, Array<int> i2_) : i1(i1_), i2(i2_) { }
    int i1;
    Array<int> i2;
};
template<> struct TaskOutput<R> {
    TaskOutput(int o_) : o(o_) { }
    int o;
};
}

typedef TaskInput<R> I;
typedef TaskOutput<R> O;

class TestConstraint {
  public:

    void test_create_empty_constraint() {
        auto c = ConstraintBuilder<R>([](I const&, O const&) { return 0.0; }).build();
        auto input = I(2,{1,2});
        auto output = O(7);
        auto robustness = c.robustness(input, output, false);
        HELPER_TEST_PRINT(c)
        HELPER_TEST_EQUALS(c.group_id(),0)
        HELPER_TEST_EQUALS(c.success_action(), ConstraintSuccessAction::NONE)
        HELPER_TEST_EQUALS(c.failure_kind(), ConstraintFailureKind::NONE)
        HELPER_TEST_EQUALS(c.objective_impact(), ConstraintObjectiveImpact::NONE)
        HELPER_TEST_EQUALS(robustness,0.0)
    }

    void test_create_filled_constraint() {
        auto c = ConstraintBuilder<R>([](I const& input, O const& output) { return static_cast<double>(output.o + input.i1); })
                .set_name("chosen_step_size")
                .set_group_id(1)
                .set_success_action(ConstraintSuccessAction::DEACTIVATE)
                .set_failure_kind(ConstraintFailureKind::SOFT)
                .set_objective_impact(ConstraintObjectiveImpact::SIGNED)
                .build();
        auto input = I(2,{1,2});
        auto output = O(7);
        auto robustness = c.robustness(input, output, false);
        HELPER_TEST_PRINT(c)
        HELPER_TEST_EQUALS(c.group_id(),1)
        HELPER_TEST_EQUALS(c.success_action(), ConstraintSuccessAction::DEACTIVATE)
        HELPER_TEST_EQUALS(c.failure_kind(), ConstraintFailureKind::SOFT)
        HELPER_TEST_EQUALS(c.objective_impact(), ConstraintObjectiveImpact::SIGNED)
        HELPER_TEST_EQUALS(robustness,9)
    }

    void test() {
        HELPER_TEST_CALL(test_create_empty_constraint())
        HELPER_TEST_CALL(test_create_filled_constraint())
    }
};

int main() {
    TestConstraint().test();
    return HELPER_TEST_FAILURES;
}
