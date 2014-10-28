#pragma once

#include <string>
#include <stdexcept>
#include <iostream>

#include <clang-c/Index.h>

#include "clang/string.hpp"
#include "vim/highlight.hpp"

namespace color_coded
{
  namespace clang
  {
    namespace token
    {
      /* Clang token/cursor -> Vim highlight group. */
      std::string to_string(CXTokenKind const token_kind,
                            CXCursorKind const cursor_kind,
                            CXTypeKind const cursor_type)
      {
        switch (token_kind)
        {
          case CXToken_Punctuation:
            return "Punctuation";
          case CXToken_Keyword:
            return "keyword";
          case CXToken_Identifier:
            switch(cursor_kind)
            {
              default:
                return "Error";
            }
          case CXToken_Literal:
            switch(cursor_kind)
            {
              case CXCursor_IntegerLiteral:
                return "Number";
              case CXCursor_FloatingLiteral:
                return "Float";
              case CXCursor_ImaginaryLiteral:
                return "Number";
              case CXCursor_StringLiteral:
                return "String";
              case CXCursor_CharacterLiteral:
                return "Character";
              case CXCursor_PreprocessingDirective:
                return "MacroDefinition";
              case CXType_Unexposed:
              default:
                return "Normal"; /* TODO: Why have unhandled things? */
            }
          case CXToken_Comment:
            return "Comment";
          default:
            return "Error";
        }
      }
    }
  }
}
