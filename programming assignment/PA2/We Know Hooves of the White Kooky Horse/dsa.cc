#include "dsa.h"
#include <cstdio>
#include <cstdlib>
#include <random>

#define TODO()                                                                 \
  do {                                                                         \
    fprintf(stderr, "NOT IMPLEMENTED %s:%d", __FILE__, __LINE__);              \
    std::exit(1);                                                              \
  } while (0)

namespace lsort {
void merge(const List &la, const List &lb, List &out) {
 // return;
 puts("bullshit");
  for(auto la_iter=la.begin(),lb_iter=lb.begin();(la_iter != la.end()) && (lb_iter != lb.end());)
  {
    if(*la_iter <= *lb_iter)
    {
      out.push_front(*la_iter);
      ++la_iter;
    }
    else
    {
      out.push_front(*lb_iter);
      ++lb_iter;
    }
  }
  for(auto la_iter=la.begin();la_iter != la.end();++la_iter)
    out.push_front(*la_iter);
  for(auto lb_iter=lb.begin();lb_iter != lb.end();++lb_iter)
    out.push_front(*lb_iter);
}

void partition(const List &la, List &leq, List &gt, Key pivot) {
  for(auto it=la.begin();it!=la.end();++it)
  {
    if((*it<=pivot))
      leq.push_front(*it);
    else
      gt.push_front(*it);
  }
}

Key select_pivot(const List &la) {
  std::random_device r;
  std::default_random_engine e1(r());
  std::uniform_int_distribution<int> uniform_dist(0, list_size(la)-1);
  return uniform_dist(e1);
  return random_index(list_size(la));

}
} // namespace lsort