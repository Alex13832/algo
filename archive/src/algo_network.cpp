///
/// \brief Source file for network algorithms.
/// \author alex011235
/// \date 2020-04-25
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include "../include/algo_network.hpp"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <random>

namespace algo::network {

namespace {

/// \brief Returns an array with uniformly distributed numbers between 0 and 1.
/// \param N The number of elements in the returned array.
/// \return Random numbers.
Arr RandArr(const int& N)
{
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);
  std::uniform_real_distribution<double> distribution(0.0, 1.0);

  Arr rand(N);
  std::for_each(rand.begin(), rand.end(), [&](double& x) { x = distribution(generator); });
  return rand;
}

/// \brief Returns the Euclidean L2 norm of the input array.
/// \param arr The input array.
/// \return L2 norm of arr.
constexpr auto L2Norm = [](const Arr& arr) {
  Arr cp{arr};
  std::transform(cp.begin(), cp.end(), cp.begin(), [](double x) { return x * x; });
  return sqrt(std::accumulate(cp.begin(), cp.end(), 0.0));
};

/// \brief Returns the L1 norm of the input arr.
/// \param arr The input array.
/// \return The L1 norm of arr.
constexpr auto L1Norm = [](const Arr& arr) {
  Arr cp{arr};
  std::transform(cp.begin(), cp.end(), cp.begin(), [](double x) { return std::abs(x); });
  return std::accumulate(cp.begin(), cp.end(), 0.0);
};

/// \brief Element-wise division of vec with d.
/// \param vec Input array.
/// \param d Denominator.
constexpr auto MatElemDiv = [](Arr& vec, const double& d) {
  std::transform(vec.begin(), vec.end(), vec.begin(), [&d](double x) { return x / d; });
  return true;
};

/// \brief Element-wise multiplication of mat with d.
/// \param mat Input matrix.
/// \param d Value for multiplication.
constexpr auto MatElemMult = [](Mat& mat, const double& d) {
  for (auto& arr : mat) {
    std::transform(arr.begin(), arr.end(), arr.begin(), [&d](double x) { return x * d; });
  }
  return true;
};

/// \brief Matrix addition.
/// \param M1 Input matrix 1.
/// \param M2 Input matrix 2.
/// \return The result of M1 + M2.
constexpr auto MatAdd = [](const Mat& M1, const Mat& M2) {
  Mat M{M1};
  for (size_t i = 0; i < M1.size(); i++) {
    for (size_t j = 0; j < M1[i].size(); j++) {
      M[i][j] += M2[i][j];
    }
  }
  return M;
};

/// \brief Multiples the matrix A with the array arr.
/// \param M Input matrix.
/// \param arr Input array.
/// \return M * arr
constexpr auto MatVecMult = [](const Mat& M, const Arr& arr) {
  Arr vtemp(arr.size(), 0);

  for (size_t i = 0; i < M.size(); i++) {
    for (size_t j = 0; j < M[i].size(); j++) {
      vtemp[i] += M[j][i] * arr[j];
    }
  }

  return vtemp;
};
}//namespace

Mat MatTransition(const Mat& M, const std::vector<int>& deg)
{
  size_t N = M.size();
  Mat p(N, Arr(N));

  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      double d = 0.9 * (M[i][j] / deg[i]) + 0.1 / N;
      p[i][j] = d;
    }
  }

  return p;
}

Arr PageRank(const Mat& W, const double& error, const double& damping)
{
  Mat M{W};
  size_t sz{M.size()};

  Arr vr{RandArr(sz)};
  double nrm{L1Norm(vr)};
  MatElemDiv(vr, nrm);

  double q{(1.0 - damping) / static_cast<double>(sz)};
  MatElemMult(M, damping);
  Mat rhs(sz, Arr(sz, q));
  Mat M_hat{MatAdd(M, rhs)};

  Arr v_end;
  double l2;

  // Repeat until L2-norm is smaller than the input error.
  do {
    v_end = vr;
    vr = MatVecMult(M_hat, vr);

    Arr temp(vr.size(), 0);
    for (size_t i = 0; i < vr.size(); i++) {
      temp[i] = vr[i] - v_end[i];
    }

    l2 = L2Norm(temp);

  } while (l2 > error);

  return vr;
}

}// namespace algo::network