/*!
 * @file
 * class DumpExpr
 *
 * This file is a part of easyLambda(ezl) project for parallel data
 * processing with modern C++ and MPI.
 *
 * @copyright Utkarsh Bhardwaj <haptork@gmail.com> 2015-2016
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying LICENSE.md or copy at * http://boost.org/LICENSE_1_0.txt)
 * */
#ifndef DUMPEXPR_EZL_H
#define DUMPEXPR_EZL_H

#include <ezl/mapreduce/DumpFile.hpp>

namespace ezl {
namespace detail {

/*!
 * @ingroup builder
 * For adding a `DumpFile` unit as a branch to the current unit. This
 * can be specified with property `dump` without finalizing build of
 * the current uni. The expression can be used by any unit builder
 * like `MapBuilder` `ReduceBuilder` etc.
 *
 * T is CRTP parent type.
 * */
template <class T> struct DumpExpr {

  DumpExpr() = default;

  auto& dump(std::string name = "", std::string header = "") {
    _name = name;
    _header = header;
    return ((T *)this)->self();
  }

  template <class I>
  auto buildAdd(I& obj) {
    if (_name != defStr) {
      auto dObj = std::make_shared<
          DumpFile<typename std::decay_t<decltype(obj)>::element_type::otype>>(_name, _header);
      obj->next(dObj, obj);
    }
  }

  auto dumpProps() { return std::tie(_name, _header); }

  void dumpProps(std::tuple<const std::string&, const std::string&> props) {
    std::tie(_name, _header) = props;
  }

  const std::string defStr{"__none__"};

  std::string _name{defStr};
  std::string _header{""};
};
}
} // namespace ezl ezl::detail

#endif // !DUMPEXPR_EZL_H
