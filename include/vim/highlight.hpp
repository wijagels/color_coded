#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <clang-c/Index.h>

#include "clang/string.hpp"
#include "clang/token_pack.hpp"
#include "clang/translation_unit.hpp"
//#include "clang/token.hpp"

#include "vim/commands.hpp"

#define DUMP_SHIT 1

namespace color_coded
{
  namespace cursor
  {
    CXChildVisitResult visit(CXCursor const cursor, CXCursor const parent,
                             CXClientData const data);
  }

  namespace vim
  {
    struct highlight
    {
      highlight() = delete;
      highlight(std::string const &ty, std::size_t const l,
                std::size_t const c, std::string const &tok)
        : type{ ty }
        , line{ l }
        , column{ c }
        , token{ tok }
      { }

      std::string type;
      std::size_t line, column;
      std::string token; /* TODO: Only need the size. */
    };

    template <typename G, typename C, typename K, typename T>
    void stuff(G &group, C cursor, K cursor_kind, T cursor_type,
               std::size_t const start_line,
               std::size_t const start_col, clang::string const &spell)
    {
      auto const func([&](auto cursor_type)
      {
        switch(cursor_type)
        {
          case CXType_Unexposed:
            group.emplace_back("Variable", start_line, start_col, spell.c_str());
            break;

          /* Builtin types */
          case CXType_Void:
          case CXType_Bool:
          case CXType_Char_U:
          case CXType_UChar:
          case CXType_Char16:
          case CXType_Char32:
          case CXType_UShort:
          case CXType_UInt:
          case CXType_ULong:
          case CXType_ULongLong:
          case CXType_UInt128:
          case CXType_Char_S:
          case CXType_SChar:
          case CXType_WChar:
          case CXType_Short:
          case CXType_Int:
          case CXType_Long:
          case CXType_LongLong:
          case CXType_Int128:
          case CXType_Float:
          case CXType_Double:
          case CXType_LongDouble:
          case CXType_NullPtr:
          case CXType_Overload:
          case CXType_Dependent:
          case CXType_ObjCId:
          case CXType_ObjCClass:
          case CXType_ObjCSel:
            group.emplace_back("Variable", start_line, start_col, spell.c_str());
            break;

          case CXType_Complex:
          case CXType_Pointer:
          case CXType_BlockPointer:
          case CXType_LValueReference:
          case CXType_RValueReference:
          case CXType_Record:
          case CXType_Typedef:
          case CXType_ObjCInterface:
          case CXType_ObjCObjectPointer:
          case CXType_ConstantArray:
          case CXType_Vector:
          case CXType_IncompleteArray:
          case CXType_VariableArray:
          case CXType_DependentSizedArray:
            group.emplace_back("Variable", start_line, start_col, spell.c_str());
            break;

          case CXType_MemberPointer:
            group.emplace_back("MemberRef", start_line, start_col, spell.c_str());
            break;

          case CXType_Enum:
            group.emplace_back("EnumDecl", start_line, start_col, spell.c_str());
            break;

          case CXType_FunctionNoProto:
          case CXType_FunctionProto:
            //group.emplace_back("Function", start_line, start_col, spell.c_str());
            break;
        }
    });

    switch(cursor_kind)
    {
/********* Declarations **********/
      case CXCursor_UnexposedDecl: /* Unknown declaration */
        //group.emplace_back("UnexposedDecl", start_line, start_col, spell.c_str());
        break;
      case CXCursor_StructDecl: 	
        group.emplace_back("StructDecl", start_line, start_col, spell.c_str());
        break;
      case CXCursor_UnionDecl: 	
        group.emplace_back("UnionDecl", start_line, start_col, spell.c_str());
        break;
      case CXCursor_ClassDecl: 	
        group.emplace_back("ClassDecl", start_line, start_col, spell.c_str());
        break;
      case CXCursor_EnumDecl: 	
        group.emplace_back("EnumDecl", start_line, start_col, spell.c_str());
        break;
      case CXCursor_FieldDecl: 	
        //cursor::visit(cursor, {}, &group);
        clang_visitChildren(cursor, &cursor::visit, &group);
        //group.emplace_back("FieldDecl", start_line, start_col, spell.c_str());
        break;
      case CXCursor_EnumConstantDecl: 	
        group.emplace_back("EnumConstantDecl", start_line, start_col, spell.c_str());
        break;
      case CXCursor_FunctionDecl: 	
        group.emplace_back("FunctionDecl", start_line, start_col, spell.c_str());
        break;
      case CXCursor_VarDecl: 	
        group.emplace_back("VarDecl", start_line, start_col, spell.c_str());
        break;
      case CXCursor_ParmDecl: 	
        group.emplace_back("ParmDecl", start_line, start_col, spell.c_str());
        break;
      case CXCursor_ObjCInterfaceDecl: 	
        //group.emplace_back("ObjCInterfaceDecl", start_line, start_col, spell.c_str());
        break;
      case CXCursor_ObjCCategoryDecl: 	
        //group.emplace_back("ObjCCategoryDecl", start_line, start_col, spell.c_str());
        break;
      case CXCursor_ObjCProtocolDecl: 	
        //group.emplace_back("ObjCProtocolDecl", start_line, start_col, spell.c_str());
        break;
      case CXCursor_ObjCPropertyDecl: 	
        //group.emplace_back("ObjCPropertyDecl", start_line, start_col, spell.c_str());
        break;
      case CXCursor_ObjCIvarDecl:
        //group.emplace_back("ObjCIvarDecl", start_line, start_col, spell.c_str());
        break;
      case CXCursor_ObjCInstanceMethodDecl: 	
        //group.emplace_back("ObjCInstanceMethodDecl", start_line, start_col, spell.c_str());
        break;
      case CXCursor_ObjCClassMethodDecl: 	
        //group.emplace_back("ObjCClassMethodDecl", start_line, start_col, spell.c_str());
        break;
      case CXCursor_ObjCImplementationDecl: 	
        //group.emplace_back("ObjCImplementationDecl", start_line, start_col, spell.c_str());
        break;
      case CXCursor_ObjCCategoryImplDecl: 	
        //group.emplace_back("ObjCCategoryImplDecl", start_line, start_col, spell.c_str());
        break;
      case CXCursor_TypedefDecl:
        group.emplace_back("TypedefDecl", start_line, start_col, spell.c_str());
        break;
      case CXCursor_CXXMethod: 	
        group.emplace_back("CXXMethod", start_line, start_col, spell.c_str());
        break;
      case CXCursor_Namespace: 	
        group.emplace_back("Namespace", start_line, start_col, spell.c_str());
        break;
      case CXCursor_LinkageSpec: 	
        group.emplace_back("LinkageSpec", start_line, start_col, spell.c_str());
        break;
      case CXCursor_Constructor: 	
        group.emplace_back("Constructor", start_line, start_col, spell.c_str());
        break;
      case CXCursor_Destructor: 	
        group.emplace_back("Destructor", start_line, start_col, spell.c_str());
        break;
      case CXCursor_ConversionFunction: 	
        group.emplace_back("ConversionFunction", start_line, start_col, spell.c_str());
        break;
      case CXCursor_TemplateTypeParameter: 	
        group.emplace_back("TemplateTypeParameter", start_line, start_col, spell.c_str());
        break;
      case CXCursor_NonTypeTemplateParameter: 	
        group.emplace_back("NonTypeTemplateParameter", start_line, start_col, spell.c_str());
        break;
      case CXCursor_TemplateTemplateParameter: 	
        group.emplace_back("TemplateTemplateParameter", start_line, start_col, spell.c_str());
        break;
      case CXCursor_FunctionTemplate: 	
        group.emplace_back("FunctionTemplate", start_line, start_col, spell.c_str());
        break;
      case CXCursor_ClassTemplate: 	
        group.emplace_back("ClassTemplate", start_line, start_col, spell.c_str());
        break;
      case CXCursor_ClassTemplatePartialSpecialization: 	
        group.emplace_back("ClassTemplatePartialSpecialization", start_line, start_col, spell.c_str());
        break;
      case CXCursor_NamespaceAlias: 	
        group.emplace_back("NamespaceAlias", start_line, start_col, spell.c_str());
        break;
      case CXCursor_UsingDirective: 	
        group.emplace_back("UsingDirective", start_line, start_col, spell.c_str());
        break;
      case CXCursor_UsingDeclaration: 	
        group.emplace_back("UsingDeclaration", start_line, start_col, spell.c_str());
        break;
      case CXCursor_TypeAliasDecl: 	
        group.emplace_back("TypeAliasDecl", start_line, start_col, spell.c_str());
        break;
      case CXCursor_ObjCSynthesizeDecl: 	
        //group.emplace_back("ObjCSynthesizeDecl", start_line, start_col, spell.c_str());
        break;
      case CXCursor_ObjCDynamicDecl: 	
        //group.emplace_back("ObjCDynamicDecl", start_line, start_col, spell.c_str());
        break;
      case CXCursor_CXXAccessSpecifier: 	
        group.emplace_back("CXXAccessSpecifier", start_line, start_col, spell.c_str());
        break;

/********* References **********/
      case CXCursor_ObjCSuperClassRef:
        //group.emplace_back("ObjCSuperClassRef", start_line, start_col, spell.c_str());
        break;
      case CXCursor_ObjCProtocolRef:
        //group.emplace_back("ObjCProtocolRef", start_line, start_col, spell.c_str());
        break;
      case CXCursor_ObjCClassRef:
        //group.emplace_back("ObjCClassRef", start_line, start_col, spell.c_str());
        break;
      case CXCursor_TypeRef:
        group.emplace_back("TypeRef", start_line, start_col, spell.c_str());
        break;
      case CXCursor_CXXBaseSpecifier: 	
        group.emplace_back("CXXBaseSpecifier", start_line, start_col, spell.c_str());
        break;
      case CXCursor_TemplateRef:
        //group.emplace_back("TemplateRef", start_line, start_col, spell.c_str());
        break;
      case CXCursor_NamespaceRef: 	
        group.emplace_back("NamespaceRef", start_line, start_col, spell.c_str());
        break;
      case CXCursor_MemberRef: 	
        group.emplace_back("MemberRef", start_line, start_col, spell.c_str());
        break;
      case CXCursor_LabelRef: 	
        group.emplace_back("LabelRef", start_line, start_col, spell.c_str());
        break;
      case CXCursor_OverloadedDeclRef: 	
        group.emplace_back("OverloadedDeclRef", start_line, start_col, spell.c_str());
        break;
      case CXCursor_VariableRef: 	
        group.emplace_back("VariableRef", start_line, start_col, spell.c_str());
        break;

/********* Errors **********/
      case CXCursor_InvalidFile:
        //group.emplace_back("InvalidFile", start_line, start_col, spell.c_str());
        break;
      case CXCursor_NoDeclFound:
        //group.emplace_back("NoDeclFound", start_line, start_col, spell.c_str());
        break;
      case CXCursor_NotImplemented:
        //group.emplace_back("NotImplemented", start_line, start_col, spell.c_str());
        break;
      case CXCursor_InvalidCode:
        //group.emplace_back("InvalidCode", start_line, start_col, spell.c_str());
        break;

/********* Expressions **********/
      case CXCursor_UnexposedExpr:
        break;
      case CXCursor_DeclRefExpr: 	
        /* TODO: function to do this switch for other type references. */
        func(cursor_type);
        break;
      case CXCursor_MemberRefExpr: 	
        group.emplace_back("MemberRefExpr", start_line, start_col, spell.c_str());
        break;
      case CXCursor_CallExpr: 	
        //group.emplace_back("CallExpr", start_line, start_col, spell.c_str());
        break;
      case CXCursor_ObjCMessageExpr: 	
        //group.emplace_back("ObjCMessageExpr", start_line, start_col, spell.c_str());
        break;
      case CXCursor_BlockExpr: 	
        //group.emplace_back("BlockExpr", start_line, start_col, spell.c_str());
        break;
      case CXCursor_MacroDefinition:
        //group.emplace_back("MacroDefinition", start_line, start_col, spell.c_str());
        break;
      case CXCursor_MacroInstantiation:
        //group.emplace_back("MacroInstantiation", start_line, start_col, spell.c_str());
        break;
      case CXCursor_PreprocessingDirective: /* XXX: do not want */
        //group.emplace_back("MacroDefinition", start_line, start_col, spell.c_str());
        break;
      case CXCursor_InclusionDirective: /* XXX: do not want */
        //group.emplace_back("MacroDefinition", start_line, start_col, spell.c_str());
        break;
      case CXCursor_ParenExpr:
      case CXCursor_LambdaExpr:
      case CXCursor_CXXForRangeStmt:
      case CXCursor_DeclStmt:
      default:
        break;
      }
    }

    class highlight_group
    {
      public:
        using vec_t = std::vector<highlight>;
        using iterator = vec_t::iterator;
        using const_iterator = vec_t::const_iterator;
        using size_type = std::size_t;

        highlight_group() = default;
        highlight_group(clang::translation_unit const &trans_unit,
                        clang::token_pack &tokens)
        {
#if DUMP_SHIT

          //clang_visitChildren(clang_getTranslationUnitCursor(trans_unit.impl), &cursor::visit, this);
          //return;
#endif
          auto &tu(trans_unit.impl);
          std::vector<CXCursor> cursors(tokens.size());
          clang_annotateTokens(tu, tokens.begin(), tokens.size(), cursors.data());

          auto cursor(cursors.cbegin());
          for(auto token(tokens.cbegin()); token != tokens.cend(); ++token, ++cursor)
          {
            CXTokenKind const kind{ clang_getTokenKind(*token) };
            clang::string const spell{ clang_getTokenSpelling(tu, *token) };
            auto const loc(clang_getTokenLocation(tu, *token));
            auto const cursor_kind(cursor->kind);
            auto const cursor_type(clang_getCursorType(*cursor).kind);
            CXFile file{};
            unsigned line{}, column{}, offset{};
            clang_getFileLocation(loc, &file, &line, &column, &offset);
            auto const cur(clang_getCursor(tu, loc));

            switch(kind)
            {
              case CXToken_Punctuation:
                emplace_back("Punctuation", line, column, spell.c_str());
                break;
              case CXToken_Keyword:
                emplace_back("Keyword", line, column, spell.c_str());
                break;
              case CXToken_Identifier:
                std::cout << spell.c_str() << ", ";
                std::cout << clang::string
                  {clang_getCursorSpelling(*cursor)}.c_str()
                          << ", ";
                std::cout << clang::string
                  {clang_getCursorDisplayName(*cursor)}.c_str()
                          << ", ";
                std::cout << clang::string
                  {clang_getCursorKindSpelling(clang_getCursorKind(*cursor))}.c_str()
                          << ", ";
                std::cout << clang::string
                  {clang_getTypeKindSpelling(clang_getCursorType(*cursor).kind)}.c_str()
                          << std::endl;

                stuff(*this, *cursor, cursor_kind, cursor_type, line, column, spell);
                break;
              case CXToken_Literal:
                stuff(*this, *cursor, cursor_kind, cursor_type, line, column, spell);
                break;
              case CXToken_Comment:
                emplace_back("Comment", line, column, spell.c_str());
                break;
              default:
                emplace_back("Error", line, column, spell.c_str());
            }
          }
        }

        bool empty() const
        { return group_.empty(); }
        size_type size() const
        { return group_.size(); }

        iterator begin()
        { return group_.begin(); }
        const_iterator begin() const
        { return group_.begin(); }
        const_iterator cbegin() const
        { return group_.cbegin(); }
        iterator end()
        { return group_.end(); }
        const_iterator end() const
        { return group_.end(); }
        const_iterator cend() const
        { return group_.cend(); }

        template <typename... Args>
        void emplace_back(Args &&... args)
        {
          std::cout << "adding: ";
          int const _[]{ (std::cout << args << " ", 0)... };
          static_cast<void>(_); std::cout << std::endl;
          group_.emplace_back(std::forward<Args>(args)...);
        }

      private:
        std::vector<highlight> group_;
    };
  }

  /* TODO: bar<T>() spelling is wrong. */
  namespace cursor
  {
    CXChildVisitResult visit(CXCursor const cursor, CXCursor const parent,
                             CXClientData const data)
    {
      auto &group(*static_cast<vim::highlight_group*>(data));
      auto const cursor_kind(cursor.kind);
      auto const cursor_type(clang_getCursorType(cursor).kind);
      clang::string const spell{ clang_getCursorSpelling(cursor) };
      auto const loc(clang_getCursorLocation(cursor));

      auto const range(clang_getCursorExtent(cursor));
      auto const start(clang_getRangeStart(range));
      auto const end(clang_getRangeEnd(range));

      static CXCursor const null_cursor(clang_getNullCursor());
      static CXSourceLocation const null_location(clang_getNullLocation());
      //if(clang_equalLocations(start, null_location) ||
      //   clang_equalLocations(end, null_location))
      //{ return CXChildVisit_Recurse; }

      clang::string file{};
      CXFile cxfile;
      unsigned start_line{}, start_col{}, start_offset{};
      unsigned end_line{}, end_col{}, end_offset{};
      //clang_getPresumedLocation(start, &file.get(), &start_line, &start_col);
      //clang_getPresumedLocation(end, &file.get(), &end_line, &end_col);
      //clang_getExpansionLocation(start, &cxfile, &start_line, &start_col, &start_offset);
      //clang_getExpansionLocation(end, &cxfile, &end_line, &end_col, &end_offset);
      clang_getSpellingLocation(start, &cxfile, &start_line, &start_col, &start_offset);
      clang_getSpellingLocation(end, &cxfile, &end_line, &end_col, &end_offset);

#if DUMP_SHIT
      std::cout << spell.c_str() << ", ";
      std::cout << start_line << ":" << start_col << " -> "
                << end_line << ":" << end_col << ", ";
      std::cout << clang::string
        {clang_getCursorKindSpelling(clang_getCursorKind(cursor))}.c_str()
                << ", ";
      std::cout << clang::string
        {clang_getTypeKindSpelling(clang_getCursorType(cursor).kind)}.c_str()
                << ", ";
      std::cout << clang::string
        {clang_getCursorDisplayName(cursor)}.c_str()
                << std::endl;
      return CXChildVisit_Recurse;
#endif

      //std::cout 
      //<< cursor_kind << " "
      //<< clang::string(clang_getTypeSpelling(
      //                 clang_getCursorType(cursor))).c_str()
      //<< " - "
      //<< clang::string(clang_getTypeKindSpelling(cursor_type)).c_str()
      //<< " " << cursor_type << " "
      //<< std::endl;


      return CXChildVisit_Recurse;
    }
  }
}
