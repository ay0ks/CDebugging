#pragma once

#include <setjmp.h>
#include <stdbool.h>
#include <stdint.h>

#define assert($Expression, ...)                                               \
  ((void)((!!($Expression))                                                    \
          || (CDebugging_Assert(__FILE__, __func__, __LINE__, #$Expression, __VA_ARGS__))))

#define assert_equals($Left, $Right, ...)                                      \
  ((void)((!!($Left == $Right))                                                \
          || (CDebugging_Assert(__FILE__, __func__, __LINE__, #$Left " == " #$Right, __VA_ARGS__))))

void
CDebugging_Assert(
  const char *const a_File,
  const char *const a_Function,
  const uint64_t a_Line,
  const char *const a_Expression,
  ...
);

void
CDebugging_Abort();

typedef struct CDebuggingBreakpoint
{
  bool m_Armed;
  struct
  {
    const char *m_File;
    const char *m_Function;
    uint64_t m_Line;
  } m_SetSite;
  struct
  {
    jmp_buf m_Buffer;
    const char *m_File;
    const char *m_Function;
    uint64_t m_Line;
  } m_JumpSite;
} CDebuggingBreakpoint;

void
CDebuggingBreakpoint_Set(
  CDebuggingBreakpoint *a_Breakpoint,
  const char *const a_File,
  const char *const a_Function,
  const uint64_t a_Line
);

void
CDebuggingBreakpoint_Break(
  CDebuggingBreakpoint *a_Breakpoint,
  const char *const a_File,
  const char *const a_Function,
  const uint64_t a_Line
);

void
CDebuggingBreakpoint_Clear(CDebuggingBreakpoint *a_Breakpoint);

#define breakpoint_set($Breakpoint)                                            \
  (CDebuggingBreakpoint_Set($Breakpoint, __FILE__, __func__, __LINE__))

#define breakpoint_trigger($Breakpoint)                                        \
  (CDebuggingBreakpoint_Break($Breakpoint, __FILE__, __func__, __LINE__))

#define breakpoint_clear($Breakpoint) (CDebuggingBreakpoint_Clear($Breakpoint))
