namespace axes {

struct __attribute__((visibility("hidden"))) Axes {
  Axes(pybind11::object axes) {
    self = axes;
    load_attrs();
  }
  void load_attrs() {
    LOAD_VOID_ATTR(axhline, self);
    LOAD_NONVOID_ATTR(bar, self);
    LOAD_VOID_ATTR(bar_label, self);
    LOAD_NONVOID_ATTR(barh, self);
    LOAD_VOID_ATTR(fill, self);
    LOAD_VOID_ATTR(fill_between, self);
    LOAD_VOID_ATTR(fill_betweenx, self);
    LOAD_VOID_ATTR(get_xaxis_transform, self);
    LOAD_NONVOID_ATTR(get_xticklabels, self);
    LOAD_VOID_ATTR(grid, self);
    LOAD_VOID_ATTR(invert_yaxis, self);
    LOAD_VOID_ATTR(legend, self);
    LOAD_VOID_ATTR(plot, self);
    LOAD_VOID_ATTR(set, self);
    LOAD_VOID_ATTR(set_title, self);
    LOAD_VOID_ATTR(set_xlabel, self);
    LOAD_VOID_ATTR(set_xlim, self);
    LOAD_VOID_ATTR(set_xticks, self);
    LOAD_VOID_ATTR(set_ylabel, self);
    LOAD_VOID_ATTR(set_yticks, self);
  }
  pybind11::object self;

  // for passing as python object
  pybind11::object unwrap() { return self; }

  // axhline
  pybind11::object axhline;

  // bar
  container::BarContainer bar(const pybind11::tuple &args,
                              const pybind11::dict &kwargs);
  pybind11::object bar_attr;

  // bar_label
  pybind11::object bar_label;

  // barh
  container::BarContainer barh(const pybind11::tuple &args,
                               const pybind11::dict &kwargs);
  pybind11::object barh_attr;

  // fill
  pybind11::object fill;

  // fill_between
  pybind11::object fill_between;

  // fill_betweenx
  pybind11::object fill_betweenx;

  // get_xaxis_transform
  /// TODO: currently returns py::object
  pybind11::object get_xaxis_transform;

  // get_xticklabels
  std::vector<text::Text> get_xticklabels();
  pybind11::object get_xticklabels_attr;

  // grid
  pybind11::object grid;

  // invert_yaxis
  pybind11::object invert_yaxis;

  // legend
  pybind11::object legend;

  // plot
  pybind11::object plot;

  // set
  pybind11::object set;

  // set_title
  pybind11::object set_title;

  // set_xlabel
  pybind11::object set_xlabel;

  // set_xlim
  pybind11::object set_xlim;

  // set_xticks
  pybind11::object set_xticks;

  // set_ylabel
  pybind11::object set_ylabel;

  // set_yticks
  pybind11::object set_yticks;
};

// bar
container::BarContainer Axes::bar(const pybind11::tuple &args,
                                  const pybind11::dict &kwargs) {
  pybind11::object obj = bar_attr(*args, **kwargs);
  return container::BarContainer(obj);
}

// barh
container::BarContainer Axes::barh(const pybind11::tuple &args,
                                   const pybind11::dict &kwargs) {
  pybind11::object obj = barh_attr(*args, **kwargs);
  return container::BarContainer(obj);
}

// get_xticklabels
std::vector<text::Text> Axes::get_xticklabels() {
  pybind11::list ret = get_xticklabels_attr();
  std::vector<text::Text> texts;
  for (pybind11::size_t i = 0; i < ret.size(); ++i) {
    texts.push_back(text::Text(ret[i]));
  }
  return texts;
}

} // namespace axes