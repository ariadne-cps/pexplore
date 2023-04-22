/***************************************************************************
 *            test_evaluation.cpp
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

#include "utility/test.hpp"
#include "pronest/configuration_search_space.hpp"
#include "evaluation.hpp"

using namespace pExplore;
using namespace ProNest;

class TestEvaluation {
  public:

    static void test_ranking() {
        ConfigurationPropertyPath use_subdivisions("use_subdivisions");
        ConfigurationPropertyPath sweep_threshold("sweep_threshold");
        ConfigurationSearchParameter bp(use_subdivisions, false, List<int>({0, 1}));
        ConfigurationSearchParameter mp(sweep_threshold, true, List<int>({3, 4, 5, 6, 7}));
        ConfigurationSearchSpace space({bp, mp});

        ConfigurationSearchPoint point1 = space.make_point({{use_subdivisions, 1}, {sweep_threshold, 2}});
        ConfigurationSearchPoint point2 = space.make_point({{use_subdivisions, 1}, {sweep_threshold, 2}});
        ConfigurationSearchPoint point3 = space.make_point({{use_subdivisions, 1}, {sweep_threshold, 3}});
        ConfigurationSearchPoint point4 = space.make_point({{use_subdivisions, 0}, {sweep_threshold, 4}});

        {
            PointEvaluation a1(point1, {{}, {}, {}, 2.0});
            PointEvaluation a2(point2, {{}, {}, {}, 4.0});
            PointEvaluation a3(point3, {{}, {}, {}, 3.0});
            PointEvaluation a4(point4, {{}, {}, {}, -1.0});

            UTILITY_TEST_ASSERT(a1 < a2)
            UTILITY_TEST_ASSERT(a1 < a3)
            UTILITY_TEST_ASSERT(a4 < a1)
            UTILITY_TEST_ASSERT(a3 < a2)
            UTILITY_TEST_ASSERT(a4 < a3)
        }

        {
            PointEvaluation a1(point1, {{}, {1}, {}, 2.0});
            PointEvaluation a2(point2, {{}, {1}, {1}, 4.0});
            PointEvaluation a3(point3, {{}, {}, {1}, 3.0});
            PointEvaluation a4(point4, {{}, {}, {}, -1.0});
            PointEvaluation a5(point1, {{}, {1}, {}, 1.0});
            PointEvaluation a6(point2, {{}, {1}, {1, 2}, 4.0});
            PointEvaluation a7(point3, {{}, {}, {1, 2}, 4.0});
            PointEvaluation a8(point3, {{}, {1, 2}, {}, 2.0});

            UTILITY_TEST_ASSERT(a1 < a2)
            UTILITY_TEST_ASSERT(a3 < a1)
            UTILITY_TEST_ASSERT(a4 < a1)
            UTILITY_TEST_ASSERT(a3 < a2)
            UTILITY_TEST_ASSERT(a4 < a3)
            UTILITY_TEST_ASSERT(a5 < a1)
            UTILITY_TEST_ASSERT(a2 < a6)
            UTILITY_TEST_ASSERT(a3 < a7)
            UTILITY_TEST_ASSERT(a2 < a8)
        }

    }

    static void test() {
        UTILITY_TEST_CALL(test_ranking())
    }
};

int main() {
    TestEvaluation::test();
    return UTILITY_TEST_FAILURES;
}