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

            std::cout << "kind: " << kind << std::endl;
            switch(kind)
            {
              case CXToken_Punctuation:
                group_.emplace_back("Punctuation", line, column, spell.c_str());
                break;
              case CXToken_Keyword:
                group_.emplace_back("Keyword", line, column, spell.c_str());
                break;
              case CXToken_Identifier:
                cursor::visit(*cursor, {}, this);
                clang_visitChildren(*cursor, &cursor::visit, this);
                //clang_visitChildren(clang_getCursorLexicalParent(*cursor), &cursor::visit, this);
                break;
              case CXToken_Literal:
                cursor::visit(*cursor, {}, this);
                clang_visitChildren(*cursor, &cursor::visit, this);
                //clang_visitChildren(clang_getCursorLexicalParent(*cursor), &cursor::visit, this);
                break;
              case CXToken_Comment:
                group_.emplace_back("Comment", line, column, spell.c_str());
                break;
              default:
                group_.emplace_back("Error", line, column, spell.c_str());
            }
            std::cout << std::endl;
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
        { group_.emplace_back(std::forward<Args>(args)...); }

      private:
        std::vector<highlight> group_;
    };
  }

  namespace cursor
  {
    template <typename T, typename T2>
    void show(T t, T2 t2)
    {
      switch(t)
      {
        case CXCursor_StructDecl: 	
          std::cout << "StructDecl" << std::endl;
          break;
        case CXCursor_UnionDecl: 	
          std::cout << "UnionDecl" << std::endl;
          break;
        case CXCursor_ClassDecl: 	
          std::cout << "ClassDecl" << std::endl;
          break;
        case CXCursor_EnumDecl: 	
          std::cout << "EnumDecl" << std::endl;
          break;
        case CXCursor_FieldDecl: 	
          std::cout << "FieldDecl" << std::endl;
          break;
        case CXCursor_EnumConstantDecl: 	
          std::cout << "EnumConstantDecl" << std::endl;
          break;
        case CXCursor_FunctionDecl: 	
          std::cout << "FunctionDecl" << std::endl;
          break;
        case CXCursor_VarDecl: 	
          std::cout << "VarDecl" << std::endl;
          break;
        case CXCursor_ParmDecl: 	
          std::cout << "ParmDecl" << std::endl;
          break;
        case CXCursor_ObjCInterfaceDecl: 	
          std::cout << "ObjCInterfaceDecl" << std::endl;
          break;
        case CXCursor_ObjCCategoryDecl: 	
          std::cout << "ObjCCategoryDecl" << std::endl;
          break;
        case CXCursor_ObjCProtocolDecl: 	
          std::cout << "ObjCProtocolDecl" << std::endl;
          break;
        case CXCursor_ObjCPropertyDecl: 	
          std::cout << "ObjCPropertyDecl" << std::endl;
          break;
        case CXCursor_ObjCIvarDecl:
          std::cout << "ObjCIvarDecl" << std::endl;
          break;
        case CXCursor_ObjCInstanceMethodDecl: 	
          std::cout << "ObjCInstanceMethodDecl" << std::endl;
          break;
        case CXCursor_ObjCClassMethodDecl: 	
          std::cout << "ObjCClassMethodDecl" << std::endl;
          break;
        case CXCursor_ObjCImplementationDecl: 	
          std::cout << "ObjCImplementationDecl" << std::endl;
          break;
        case CXCursor_ObjCCategoryImplDecl: 	
          std::cout << "ObjCCategoryImplDecl" << std::endl;
          break;
        case CXCursor_TypedefDecl: 	
          std::cout << "TypedefDecl" << std::endl;
          break;
        case CXCursor_CXXMethod: 	
          std::cout << "CXXMethod" << std::endl;
          break;
        case CXCursor_Namespace: 	
          std::cout << "Namespace" << std::endl;
          break;
        case CXCursor_LinkageSpec: 	
          std::cout << "LinkageSpec" << std::endl;
          break;
        case CXCursor_Constructor: 	
          std::cout << "Constructor" << std::endl;
          break;
        case CXCursor_Destructor: 	
          std::cout << "Destructor" << std::endl;
          break;
        case CXCursor_ConversionFunction: 	
          std::cout << "ConversionFunction" << std::endl;
          break;
        case CXCursor_TemplateTypeParameter: 	
          std::cout << "TemplateTypeParameter" << std::endl;
          break;
        case CXCursor_NonTypeTemplateParameter: 	
          std::cout << "NonTypeTemplateParameter" << std::endl;
          break;
        case CXCursor_TemplateTemplateParameter: 	
          std::cout << "TemplateTemplateParameter" << std::endl;
          break;
        case CXCursor_FunctionTemplate: 	
          std::cout << "FunctionTemplate" << std::endl;
          break;
        case CXCursor_ClassTemplate: 	
          std::cout << "ClassTemplate" << std::endl;
          break;
        case CXCursor_ClassTemplatePartialSpecialization: 	
          std::cout << "ClassTemplatePartialSpecialization" << std::endl;
          break;
        case CXCursor_NamespaceAlias: 	
          std::cout << "NamespaceAlias" << std::endl;
          break;
        case CXCursor_UsingDirective: 	
          std::cout << "UsingDirective" << std::endl;
          break;
        case CXCursor_UsingDeclaration: 	
          std::cout << "UsingDeclaration" << std::endl;
          break;
        case CXCursor_TypeAliasDecl: 	
          std::cout << "TypeAliasDecl" << std::endl;
          break;
        case CXCursor_ObjCSynthesizeDecl: 	
          std::cout << "ObjCSynthesizeDecl" << std::endl;
          break;
        case CXCursor_ObjCDynamicDecl: 	
          std::cout << "ObjCDynamicDecl" << std::endl;
          break;
        case CXCursor_CXXAccessSpecifier: 	
          std::cout << "CXXAccessSpecifier" << std::endl;
          break;
        case CXCursor_ObjCSuperClassRef:
          std::cout << "ObjCSuperClassRef" << std::endl;
          break;
        case CXCursor_ObjCProtocolRef:
          std::cout << "ObjCProtocolRef" << std::endl;
          break;
        case CXCursor_ObjCClassRef:
          std::cout << "ObjCClassRef" << std::endl;
          break;
        case CXCursor_TypeRef:
          std::cout << "TypeRef" << std::endl;
          break;
        case CXCursor_CXXBaseSpecifier: 	
          std::cout << "CXXBaseSpecifier" << std::endl;
          break;
        case CXCursor_NamespaceRef: 	
          std::cout << "NamespaceRef" << std::endl;
          break;
        case CXCursor_MemberRef: 	
          std::cout << "MemberRef" << std::endl;
          break;
        case CXCursor_LabelRef: 	
          std::cout << "LabelRef" << std::endl;
          break;
        case CXCursor_OverloadedDeclRef: 	
          std::cout << "OverloadedDeclRef" << std::endl;
          break;
        case CXCursor_VariableRef: 	
          std::cout << "VariableRef" << std::endl;
          break;
        case CXCursor_NoDeclFound:
          std::cout << "NoDeclFound" << std::endl;
          break;
        case CXCursor_NotImplemented:
          std::cout << "NotImplemented" << std::endl;
          break;
        case CXCursor_InvalidCode:
          std::cout << "InvalidCode" << std::endl;
          break;
        case CXCursor_DeclRefExpr: 	
          switch(t2)
          {
            case CXType_Enum:
              std::cout << "EnumConstantDecl" << std::endl;
              break;
            case CXType_Typedef:
              std::cout << "Type" << std::endl;
              break;
            case CXType_FunctionProto:
            case CXType_FunctionNoProto:
              std::cout << "Function" << std::endl;
              break;
            case CXType_MemberPointer:
              std::cout << "MemberRef" << std::endl;
              break;
            default:
              std::cout << "Variable" << std::endl;
              break;
          }
          break;
        case CXCursor_MemberRefExpr: 	
          std::cout << "MemberRefExpr" << std::endl;
          break;
        case CXCursor_CallExpr: 	
          std::cout << "CallExpr" << std::endl;
          break;
        case CXCursor_ObjCMessageExpr: 	
          std::cout << "ObjCMessageExpr" << std::endl;
          break;
        case CXCursor_BlockExpr: 	
          std::cout << "BlockExpr" << std::endl;
          break;
        case CXCursor_MacroDefinition:
          std::cout << "MacroDefinition" << std::endl;
          break;
        case CXCursor_MacroInstantiation:
          std::cout << "MacroInstantiation" << std::endl;
          break;
        case CXCursor_PreprocessingDirective:
          std::cout << "MacroDefinition" << std::endl;
          break;
        case CXCursor_InclusionDirective:
          std::cout << "MacroDefinition" << std::endl;
          break;
        case CXCursor_TemplateRef:
          std::cout << "Type" << std::endl;
          break;
        case CXCursor_UnexposedDecl: /* Some decl, not sure what kind. */
          std::cout << "UnexposedDecl" << std::endl;
          break;
        case CXCursor_ParenExpr:
          std::cout << "ParenExpr" << std::endl;
        case CXCursor_LambdaExpr:
          std::cout << "LambdaExpr" << std::endl;
        case CXCursor_CXXForRangeStmt:
          std::cout << "CXXForRangeStmt" << std::endl;
        case CXCursor_DeclStmt:
          std::cout << "DeclStmt" << std::endl;
        default:
          std::cout << "Unknown: " << t << std::endl;
      }
    }

    CXChildVisitResult visit(CXCursor const cursor, CXCursor const parent,
                             CXClientData const data)
    {
      auto &group(*static_cast<vim::highlight_group*>(data));
      auto const cursor_kind(cursor.kind);
      auto const cursor_type(clang_getCursorType(cursor).kind);
      clang::string const spell{ clang_getCursorSpelling(cursor) };
      //std::cout 
      //<< cursor_kind << " "
      //<< clang::string(clang_getTypeSpelling(
      //                 clang_getCursorType(cursor))).c_str()
      //<< " - "
      //<< clang::string(clang_getTypeKindSpelling(cursor_type)).c_str()
      //<< " " << cursor_type << " "
      //<< std::endl;

      auto const range(clang_getCursorExtent(cursor));
      auto const location(clang_getCursorLocation(cursor));

      static CXCursor const null_cursor(clang_getNullCursor());
      static CXSourceLocation const null_location(clang_getNullLocation());
      if(clang_equalLocations(location, null_location))
      { return CXChildVisit_Continue; }

      clang::string file{};
      unsigned start_line{}, start_col{}, start_offset{};
      unsigned end_line{}, end_col{}, end_offset{};
      clang_getPresumedLocation(location, &file.get(), &start_line, &start_col);
      std::cout << start_line << ", " << start_col << ", "
                << start_offset << ", " << spell.c_str() << std::endl;
      show(cursor_kind, cursor_type);

      switch(cursor_kind)
      {
        case CXCursor_StructDecl: 	
          //group.emplace_back("StructDecl", start_line, start_col, spell.c_str());
          break;
        case CXCursor_UnionDecl: 	
          //group.emplace_back("UnionDecl", start_line, start_col, spell.c_str());
          break;
        case CXCursor_ClassDecl: 	
          //group.emplace_back("ClassDecl", start_line, start_col, spell.c_str());
          break;
        case CXCursor_EnumDecl: 	
          //group.emplace_back("EnumDecl", start_line, start_col, spell.c_str());
          break;
        case CXCursor_FieldDecl: 	
          //group.emplace_back("FieldDecl", start_line, start_col, spell.c_str());
          break;
        case CXCursor_EnumConstantDecl: 	
          //group.emplace_back("EnumConstantDecl", start_line, start_col, spell.c_str());
          break;
        case CXCursor_FunctionDecl: 	
          //group.emplace_back("FunctionDecl", start_line, start_col, spell.c_str());
          break;
        case CXCursor_VarDecl: 	
          //group.emplace_back("VarDecl", start_line, start_col, spell.c_str());
          break;
        case CXCursor_ParmDecl: 	
          //group.emplace_back("ParmDecl", start_line, start_col, spell.c_str());
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
          //group.emplace_back("TypedefDecl", start_line, start_col, spell.c_str());
          break;
        case CXCursor_CXXMethod: 	
          //group.emplace_back("CXXMethod", start_line, start_col, spell.c_str());
          break;
        case CXCursor_Namespace: 	
          //group.emplace_back("Namespace", start_line, start_col, spell.c_str());
          break;
        case CXCursor_LinkageSpec: 	
          //group.emplace_back("LinkageSpec", start_line, start_col, spell.c_str());
          break;
        case CXCursor_Constructor: 	
          //group.emplace_back("Constructor", start_line, start_col, spell.c_str());
          break;
        case CXCursor_Destructor: 	
          //group.emplace_back("Destructor", start_line, start_col, spell.c_str());
          break;
        case CXCursor_ConversionFunction: 	
          //group.emplace_back("ConversionFunction", start_line, start_col, spell.c_str());
          break;
        case CXCursor_TemplateTypeParameter: 	
          //group.emplace_back("TemplateTypeParameter", start_line, start_col, spell.c_str());
          break;
        case CXCursor_NonTypeTemplateParameter: 	
          //group.emplace_back("NonTypeTemplateParameter", start_line, start_col, spell.c_str());
          break;
        case CXCursor_TemplateTemplateParameter: 	
          //group.emplace_back("TemplateTemplateParameter", start_line, start_col, spell.c_str());
          break;
        case CXCursor_FunctionTemplate: 	
          //group.emplace_back("FunctionTemplate", start_line, start_col, spell.c_str());
          break;
        case CXCursor_ClassTemplate: 	
          //group.emplace_back("ClassTemplate", start_line, start_col, spell.c_str());
          break;
        case CXCursor_ClassTemplatePartialSpecialization: 	
          //group.emplace_back("ClassTemplatePartialSpecialization", start_line, start_col, spell.c_str());
          break;
        case CXCursor_NamespaceAlias: 	
          //group.emplace_back("NamespaceAlias", start_line, start_col, spell.c_str());
          break;
        case CXCursor_UsingDirective: 	
          //group.emplace_back("UsingDirective", start_line, start_col, spell.c_str());
          break;
        case CXCursor_UsingDeclaration: 	
          //group.emplace_back("UsingDeclaration", start_line, start_col, spell.c_str());
          break;
        case CXCursor_TypeAliasDecl: 	
          //group.emplace_back("TypeAliasDecl", start_line, start_col, spell.c_str());
          break;
        case CXCursor_ObjCSynthesizeDecl: 	
          //group.emplace_back("ObjCSynthesizeDecl", start_line, start_col, spell.c_str());
          break;
        case CXCursor_ObjCDynamicDecl: 	
          //group.emplace_back("ObjCDynamicDecl", start_line, start_col, spell.c_str());
          break;
        case CXCursor_CXXAccessSpecifier: 	
          //group.emplace_back("CXXAccessSpecifier", start_line, start_col, spell.c_str());
          break;
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
          //group.emplace_back("TypeRef", start_line, start_col, spell.c_str());
          break;
        case CXCursor_CXXBaseSpecifier: 	
          //group.emplace_back("CXXBaseSpecifier", start_line, start_col, spell.c_str());
          break;
        case CXCursor_NamespaceRef: 	
          //group.emplace_back("NamespaceRef", start_line, start_col, spell.c_str());
          break;
        case CXCursor_MemberRef: 	
          //group.emplace_back("MemberRef", start_line, start_col, spell.c_str());
          break;
        case CXCursor_LabelRef: 	
          //group.emplace_back("LabelRef", start_line, start_col, spell.c_str());
          break;
        case CXCursor_OverloadedDeclRef: 	
          //group.emplace_back("OverloadedDeclRef", start_line, start_col, spell.c_str());
          break;
        case CXCursor_VariableRef: 	
          //group.emplace_back("VariableRef", start_line, start_col, spell.c_str());
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
        case CXCursor_DeclRefExpr: 	
          /*
          switch(cursor_type)
          {
            case CXType_Enum:
              group.emplace_back("EnumConstantDecl", start_line, start_col, spell.c_str());
              break;
            case CXType_Typedef:
              group.emplace_back("Type", start_line, start_col, spell.c_str());
              break;
            case CXType_FunctionProto:
            case CXType_FunctionNoProto:
              group.emplace_back("Function", start_line, start_col, spell.c_str());
              break;
            case CXType_MemberPointer:
              group.emplace_back("MemberRef", start_line, start_col, spell.c_str());
              break;
            default:
              group.emplace_back("Variable", start_line, start_col, spell.c_str());
              break;
          }*/
          break;
        case CXCursor_MemberRefExpr: 	
          //group.emplace_back("MemberRefExpr", start_line, start_col, spell.c_str());
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
          group.emplace_back("MacroDefinition", start_line, start_col, spell.c_str());
          break;
        case CXCursor_MacroInstantiation:
          group.emplace_back("MacroInstantiation", start_line, start_col, spell.c_str());
          break;
        case CXCursor_PreprocessingDirective:
          //group.emplace_back("MacroDefinition", start_line, start_col, spell.c_str());
          break;
        case CXCursor_InclusionDirective: /* XXX: do not want */
          //group.emplace_back("MacroDefinition", start_line, start_col, spell.c_str());
          break;
        case CXCursor_TemplateRef:
          //group.emplace_back("Type", start_line, start_col, spell.c_str());
          break;
        case CXCursor_UnexposedDecl: /* Some decl, not sure what kind. */
        case CXCursor_ParenExpr:
        case CXCursor_LambdaExpr:
        case CXCursor_CXXForRangeStmt:
        case CXCursor_DeclStmt:
        default:
          return CXChildVisit_Recurse;
      }

      return CXChildVisit_Recurse;
    }
  }
}
