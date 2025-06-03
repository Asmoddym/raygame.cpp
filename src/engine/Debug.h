#ifndef MACRO_DEBUG_HPP_
# define MACRO_DEBUG_HPP_

# include "Log.h"

# ifndef DebugIf
#  ifdef DEBUG
#   define DebugIf(Block) Block
#  else
#   define DebugIf(Block)
#  endif
# endif

# ifndef DebugLog
#  define DebugLog ::macro::Log::d
# endif

#endif // MACRO_DEBUG_HPP_
