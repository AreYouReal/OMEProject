#pragma once

#include <memory>
#include <vector>
#include <map>

template<typename T>
using sp = std::shared_ptr<T>;

template<typename T>
using up = std::unique_ptr<T>;

template<typename T>
using wp = std::weak_ptr<T>;

using string = std::string;

template<typename T>
using vec = std::vector<T>;

template<typename T, typename V>
using map = std::map<T, V>;
