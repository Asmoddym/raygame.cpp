#ifndef MACRO_UTILS_DEBUG_HPP_
# define MACRO_UTILS_DEBUG_HPP_

# ifndef IF_DEBUG
#  ifdef DEBUG
#   define IF_DEBUG(Block) Block
#  else
#   define IF_DEBUG(Block)
#  endif
# endif

#endif // MACRO_UTILS_DEBUG_HPP_
