// example from
// https://matplotlib.org/stable/gallery/images_contours_and_fields/quiver_demo.html

#include <pybind11/embed.h>
#include <pybind11/stl.h>

#include <matplotlibcpp17/pyplot.h>
#include <matplotlibcpp17/quiver.h>

#include <xtensor/xbuilder.hpp>
#include <xtensor/xview.hpp>

#include <vector>
#include <algorithm>
#include <string>

namespace py = pybind11;
using namespace py::literals;
using namespace std;
using namespace matplotlibcpp17;

int main1() {
  auto [X0, Y0] = xt::meshgrid(xt::arange<double>(0.0, 2 * M_PI, 0.2),
                               xt::arange<double>(0.0, 2 * M_PI, 0.2));
  auto U0 = xt::cos(X0);
  auto V0 = xt::sin(Y0);
  // to vector
  vector<double> X(X0.begin(), X0.end()), Y(Y0.begin(), Y0.end()),
      U(U0.begin(), U0.end()), V(V0.begin(), V0.end());

  auto plt = matplotlibcpp17::pyplot::import();
  auto [fig1, ax1] = plt.subplots();
  ax1.set_title(args_("Arrows scale with plot width, not view"));
  auto Q = ax1.quiver(args_(X, Y, U, V), kwargs_("units"_a = "width"));
  auto qk =
      ax1.quiverkey(args_(Q.unwrap(), 0.9, 0.9, 2, R"($2 \frac{m}{s}$)"),
                    kwargs_("labelpos"_a = "E", "coordinates"_a = "figure"));
#if USE_GUI
  plt.show();
#else
  plt.savefig(args_("quiver_demo_1.png"));
#endif
  return 0;
}

int main2() {
  auto [X0, Y0] = xt::meshgrid(xt::arange<double>(0.0, 2 * M_PI, 0.6),
                               xt::arange<double>(0.0, 2 * M_PI, 0.6));
  auto U0 = xt::cos(X0);
  auto V0 = xt::sin(Y0);
  // to vector
  vector<double> X(X0.begin(), X0.end()), Y(Y0.begin(), Y0.end()),
      U(U0.begin(), U0.end()), V(V0.begin(), V0.end());

  auto plt = matplotlibcpp17::pyplot::import();
  auto [fig1, ax1] = plt.subplots();
  ax1.set_title(args_("pivot='mid'; every third arrow; units='inches'"));
  auto Q = ax1.quiver(args_(X, Y, U, V),
                      kwargs_("pivot"_a = "mid", "units"_a = "inches"));
  auto qk =
      ax1.quiverkey(args_(Q.unwrap(), 0.9, 0.9, 1, R"($1 \frac{m}{s}$)"),
                    kwargs_("labelpos"_a = "E", "coordinates"_a = "figure"));
  ax1.scatter(args_(X, Y), kwargs_("color"_a = "r", "s"_a = 5));

#if USE_GUI
  plt.show();
#else
  plt.savefig(args_("quiver_demo_2.png"));
#endif
  return 0;
}

int main3() {
  auto [X0, Y0] = xt::meshgrid(xt::arange<double>(0.0, 2 * M_PI, 0.2),
                               xt::arange<double>(0.0, 2 * M_PI, 0.2));
  auto U0 = xt::cos(X0);
  auto V0 = xt::sin(Y0);
  auto M0 = xt::hypot(U0, V0);
  vector<double> X(X0.begin(), X0.end()), Y(Y0.begin(), Y0.end()),
      U(U0.begin(), U0.end()), V(V0.begin(), V0.end()), M(M0.begin(), M0.end());

  auto plt = matplotlibcpp17::pyplot::import();
  auto [fig1, ax1] = plt.subplots();
  ax1.set_title(args_("pivot='tip'; scales with x view"));
  auto Q = ax1.quiver(args_(X, Y, U, V, M),
                      kwargs_("units"_a = "x", "pivot"_a = "tip",
                              "width"_a = 0.022, "scale"_a = 1.0 / 0.15));
  auto qk =
      ax1.quiverkey(args_(Q.unwrap(), 0.9, 0.9, 1, R"($1 \frac{m}{s}$)"),
                    kwargs_("labelpos"_a = "E", "coordinates"_a = "figure"));
  ax1.scatter(args_(X, Y), kwargs_("color"_a = "0.5", "s"_a = 1));

#if USE_GUI
  plt.show();
#else
  plt.savefig(args_("quiver_demo_3.png"));
#endif

  return 0;
}

int main() {
  py::scoped_interpreter guard{};
  main1();
  main2();
  main3();
}
