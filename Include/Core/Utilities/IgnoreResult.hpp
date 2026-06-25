#pragma once

#define XX_JOIN(A, B) XX_JOIN_INNER(A, B)
#define XX_JOIN_INNER(A, B) A##B
#define XX_IGNORE_RESULT(X) [[maybe_unused]] auto XX_JOIN(Ignore_, __LINE__) = X\

