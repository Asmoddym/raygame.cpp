#ifndef MACRO_ENTITY_H_
# define MACRO_ENTITY_H_

# include "Registry.h"

// namespace macro {
//   struct Entity {
//     int id;
//     Registry &registry;
//
//     public:
//       inline Entity(Registry &r, int i) : registry { r }, id { i } {}
//       inline ~Entity() {}
//
//       template<typename... Cs, typename... Args>
//         inline Entity &set(Args&&... args) { return registry.set<Cs...>(id, args...); return *this; }
//
//       template<typename C>
//         inline C &get() { return registry.get<C>(id); }
//
//       template<typename C>
//         inline bool has() { return registry.has<C>(id); }
//   };
// }
//
#endif //MACRO_ENTITY_H_
