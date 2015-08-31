#pragma once
#include <vector>
namespace mpr{
  template<class K, class V>
  std::vector<K> keys(std::unordered_map<K,V> map){
    std::vector<K> k;
    std::for_each(map.begin(), map.end(), 
      [&k](typename std::unordered_map<K,V>::value_type &p) {k.push_back(p.first);});
    return k;
  }

}
