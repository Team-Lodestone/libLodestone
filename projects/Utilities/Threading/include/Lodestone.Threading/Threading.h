//
// Created by zero on 7/9/26.
//

#ifndef LODESTONE_THREADING_H
#define LODESTONE_THREADING_H

#define THREADING_TYPE_NONE 0
#define THREADING_TYPE_TBB 1
#define THREADING_TYPE_STL_TBB 2
#define THREADING_TYPE_OPENMP 3
#define THREADING_TYPE_STL 4

#if defined(_MSC_VER)
#define OMP_PARELLEL_FOR __pragma(omp parallel for)
#else
#define OMP_PARALLEL_FOR _Pragma("omp parallel for")
#endif

#if LODESTONE_THREADING_TYPE == THREADING_TYPE_TBB || LODESTONE_THREADING_TYPE == THREADING_TYPE_STL_TBB
#   define THREADING_HEADER <oneapi/tbb/parallel_for_each.h>
#elif LODESTONE_THREADING_TYPE == THREADING_TYPE_OPENMP
#   define THREADING_HEADER <omp.h>
#elif LODESTONE_THREADING_TYPE == THREADING_TYPE_STL
#   define THREADING_HEADER <algorithm>
#else
    //useless, just need it here lmao
#   define THREADING_HEADER <vector>
#endif

#if LODESTONE_THREADING_TYPE == THREADING_TYPE_TBB
#   define THREADED_LOOP_START_VEC(vector, capture...) oneapi::tbb::parallel_for_each(vector.begin(), vector.end(), [capture](auto &item) {
#   define THREADED_LOOP_END() })
#elif LODESTONE_THREADING_TYPE == THREADING_TYPE_STL_TBB || LODESTONE_THREADING_TYPE == THREADING_TYPE_STL
#   define THREADED_LOOP_START_VEC(vector, capture...) std::for_each(std::execution::par_unseq, vector.begin(), vector.end(), [capture](auto &item) {
#   define THREADED_LOOP_END() })
#elif LODESTONE_THREADING_TYPE == THREADING_TYPE_OPENMP
#   define THREADED_LOOP_START_VEC(vector, capture...)       \
OMP_PARALLEL_FOR                                     \
for (size_t i = 0; i < vector.size(); ++i) {         \
const auto &item = vector[i];

#   define THREADED_LOOP_END() }
#else
#   define THREADED_LOOP_START_VEC(vector, capture...) for (auto &item : vector) {
#   define THREADED_LOOP_END() }
#endif

#endif //LODESTONE_THREADING_H
