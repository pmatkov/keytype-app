
// *************************************************************************************************************** //
//                                                                                                               
//                                               XML Data Binding                                                
//                                                                                                               
//         Generated on: 24.11.2023. 0:44:25                                                                     
//       Generated from: C:\Users\surf3r\OneDrive\Documents\Embarcadero\Studio\Projects\KeyType\Data\books.xml   
//   Settings stored in: C:\Users\surf3r\OneDrive\Documents\Embarcadero\Studio\Projects\KeyType\Data\books.xdb   
//                                                                                                               
// *************************************************************************************************************** //

#ifndef   booksH
#define   booksH

#include <System.hpp>
#include <System.Variants.hpp>
#include <System.SysUtils.hpp>
#include <Xml.Xmldom.hpp>
#include <Xml.XMLIntf.hpp>
#include <Xml.XMLDoc.hpp>
#include <XMLNodeImp.h>
#include <Xml.xmlutil.hpp>


// Forward Decls 

__interface IXMLlibraryType;
typedef System::DelphiInterface<IXMLlibraryType> _di_IXMLlibraryType;
__interface IXMLcategoryType;
typedef System::DelphiInterface<IXMLcategoryType> _di_IXMLcategoryType;
__interface IXMLgenreType;
typedef System::DelphiInterface<IXMLgenreType> _di_IXMLgenreType;
__interface IXMLbookType;
typedef System::DelphiInterface<IXMLbookType> _di_IXMLbookType;

// IXMLlibraryType 

__interface INTERFACE_UUID("{E15F25EC-00AE-43B8-A51E-C4C0AE2ADA2E}") IXMLlibraryType : public Xml::Xmlintf::IXMLNodeCollection
{
public:
public:
  // Property Accessors 
  virtual _di_IXMLcategoryType __fastcall Get_category(const int Index) = 0;
  // Methods & Properties 
  virtual _di_IXMLcategoryType __fastcall Add() = 0;
  virtual _di_IXMLcategoryType __fastcall Insert(const int Index) = 0;
  __property _di_IXMLcategoryType category[const int Index] = { read=Get_category };/* default */
};

// IXMLcategoryType 

__interface INTERFACE_UUID("{894E4B88-4EE6-4A77-AC9D-111E91238E2C}") IXMLcategoryType : public Xml::Xmlintf::IXMLNodeCollection
{
public:
public:
  // Property Accessors 
  virtual System::UnicodeString __fastcall Get_name() = 0;
  virtual _di_IXMLgenreType __fastcall Get_genre(const int Index) = 0;
  virtual void __fastcall Set_name(const System::UnicodeString Value) = 0;
  // Methods & Properties 
  virtual _di_IXMLgenreType __fastcall Add() = 0;
  virtual _di_IXMLgenreType __fastcall Insert(const int Index) = 0;
  __property System::UnicodeString name = { read=Get_name, write=Set_name };
  __property _di_IXMLgenreType genre[const int Index] = { read=Get_genre };/* default */
};

// IXMLgenreType 

__interface INTERFACE_UUID("{05C4BA62-B65F-4349-82DC-CBAFCE1DEE9F}") IXMLgenreType : public Xml::Xmlintf::IXMLNodeCollection
{
public:
public:
  // Property Accessors 
  virtual System::UnicodeString __fastcall Get_name() = 0;
  virtual _di_IXMLbookType __fastcall Get_book(const int Index) = 0;
  virtual void __fastcall Set_name(const System::UnicodeString Value) = 0;
  // Methods & Properties 
  virtual _di_IXMLbookType __fastcall Add() = 0;
  virtual _di_IXMLbookType __fastcall Insert(const int Index) = 0;
  __property System::UnicodeString name = { read=Get_name, write=Set_name };
  __property _di_IXMLbookType book[const int Index] = { read=Get_book };/* default */
};

// IXMLbookType 

__interface INTERFACE_UUID("{9791FBC1-F9A4-4CC7-B6F2-2FEBECB27185}") IXMLbookType : public Xml::Xmlintf::IXMLNode
{
public:
  // Property Accessors 
  virtual System::UnicodeString __fastcall Get_author() = 0;
  virtual System::UnicodeString __fastcall Get_title() = 0;
  virtual int __fastcall Get_year() = 0;
  virtual System::UnicodeString __fastcall Get_paragraph() = 0;
  virtual void __fastcall Set_author(const System::UnicodeString Value) = 0;
  virtual void __fastcall Set_title(const System::UnicodeString Value) = 0;
  virtual void __fastcall Set_year(const int Value) = 0;
  virtual void __fastcall Set_paragraph(const System::UnicodeString Value) = 0;
  // Methods & Properties 
  __property System::UnicodeString author = { read=Get_author, write=Set_author };
  __property System::UnicodeString title = { read=Get_title, write=Set_title };
  __property int year = { read=Get_year, write=Set_year };
  __property System::UnicodeString paragraph = { read=Get_paragraph, write=Set_paragraph };
};

// Forward Decls 

class TXMLlibraryType;
class TXMLcategoryType;
class TXMLgenreType;
class TXMLbookType;

// TXMLlibraryType 

class TXMLlibraryType : public Xml::Xmldoc::TXMLNodeCollection, public IXMLlibraryType
{
  __IXMLNODECOLLECTION_IMPL__
protected:
  // IXMLlibraryType 
  virtual _di_IXMLcategoryType __fastcall Get_category(const int Index);
  virtual _di_IXMLcategoryType __fastcall Add();
  virtual _di_IXMLcategoryType __fastcall Insert(const int Index);
public:
  virtual void __fastcall AfterConstruction(void);
};

// TXMLcategoryType 

class TXMLcategoryType : public Xml::Xmldoc::TXMLNodeCollection, public IXMLcategoryType
{
  __IXMLNODECOLLECTION_IMPL__
protected:
  // IXMLcategoryType 
  virtual System::UnicodeString __fastcall Get_name();
  virtual _di_IXMLgenreType __fastcall Get_genre(const int Index);
  virtual void __fastcall Set_name(const System::UnicodeString Value);
  virtual _di_IXMLgenreType __fastcall Add();
  virtual _di_IXMLgenreType __fastcall Insert(const int Index);
public:
  virtual void __fastcall AfterConstruction(void);
};

// TXMLgenreType 

class TXMLgenreType : public Xml::Xmldoc::TXMLNodeCollection, public IXMLgenreType
{
  __IXMLNODECOLLECTION_IMPL__
protected:
  // IXMLgenreType 
  virtual System::UnicodeString __fastcall Get_name();
  virtual _di_IXMLbookType __fastcall Get_book(const int Index);
  virtual void __fastcall Set_name(const System::UnicodeString Value);
  virtual _di_IXMLbookType __fastcall Add();
  virtual _di_IXMLbookType __fastcall Insert(const int Index);
public:
  virtual void __fastcall AfterConstruction(void);
};

// TXMLbookType 

class TXMLbookType : public Xml::Xmldoc::TXMLNode, public IXMLbookType
{
  __IXMLNODE_IMPL__
protected:
  // IXMLbookType 
  virtual System::UnicodeString __fastcall Get_author();
  virtual System::UnicodeString __fastcall Get_title();
  virtual int __fastcall Get_year();
  virtual System::UnicodeString __fastcall Get_paragraph();
  virtual void __fastcall Set_author(const System::UnicodeString Value);
  virtual void __fastcall Set_title(const System::UnicodeString Value);
  virtual void __fastcall Set_year(const int Value);
  virtual void __fastcall Set_paragraph(const System::UnicodeString Value);
};

// Global Functions 

_di_IXMLlibraryType __fastcall Getlibrary(Xml::Xmlintf::_di_IXMLDocument Doc);
_di_IXMLlibraryType __fastcall Getlibrary(Xml::Xmldoc::TXMLDocument *Doc);
_di_IXMLlibraryType __fastcall Loadlibrary(const System::UnicodeString& FileName);
_di_IXMLlibraryType __fastcall  Newlibrary();

#define TargetNamespace ""

#endif