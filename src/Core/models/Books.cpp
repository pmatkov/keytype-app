
// *************************************************************************************************************** //
//                                                                                                               
//                                               XML Data Binding                                                
//                                                                                                               
//         Generated on: 24.11.2023. 0:44:25                                                                     
//       Generated from: C:\Users\surf3r\OneDrive\Documents\Embarcadero\Studio\Projects\KeyType\Data\books.xml   
//   Settings stored in: C:\Users\surf3r\OneDrive\Documents\Embarcadero\Studio\Projects\KeyType\Data\books.xdb   
//                                                                                                               
// *************************************************************************************************************** //

#include <System.hpp>
#pragma hdrstop

#include "books.h"


// Global Functions 

_di_IXMLlibraryType __fastcall Getlibrary(Xml::Xmlintf::_di_IXMLDocument Doc)
{
  return (_di_IXMLlibraryType) Doc->GetDocBinding("library", __classid(TXMLlibraryType), TargetNamespace);
};

_di_IXMLlibraryType __fastcall Getlibrary(Xml::Xmldoc::TXMLDocument *Doc)
{
  Xml::Xmlintf::_di_IXMLDocument DocIntf;
  Doc->GetInterface(DocIntf);
  return Getlibrary(DocIntf);
};

_di_IXMLlibraryType __fastcall Loadlibrary(const System::UnicodeString& FileName)
{
  return (_di_IXMLlibraryType) Xml::Xmldoc::LoadXMLDocument(FileName)->GetDocBinding("library", __classid(TXMLlibraryType), TargetNamespace);
};

_di_IXMLlibraryType __fastcall  Newlibrary()
{
  return (_di_IXMLlibraryType) Xml::Xmldoc::NewXMLDocument()->GetDocBinding("library", __classid(TXMLlibraryType), TargetNamespace);
};

// TXMLlibraryType 

void __fastcall TXMLlibraryType::AfterConstruction(void)
{
  RegisterChildNode(System::UnicodeString("category"), __classid(TXMLcategoryType));
  ItemTag = "category";
  ItemInterface = __uuidof(IXMLcategoryType);
  Xml::Xmldoc::TXMLNodeCollection::AfterConstruction();
};

_di_IXMLcategoryType __fastcall TXMLlibraryType::Get_category(const int Index)
{
  return (_di_IXMLcategoryType) List->Nodes[Index];
};

_di_IXMLcategoryType __fastcall TXMLlibraryType::Add()
{
  return (_di_IXMLcategoryType) AddItem(-1);
};

_di_IXMLcategoryType __fastcall TXMLlibraryType::Insert(const int Index)
{
  return (_di_IXMLcategoryType) AddItem(Index);
};

// TXMLcategoryType 

void __fastcall TXMLcategoryType::AfterConstruction(void)
{
  RegisterChildNode(System::UnicodeString("genre"), __classid(TXMLgenreType));
  ItemTag = "genre";
  ItemInterface = __uuidof(IXMLgenreType);
  Xml::Xmldoc::TXMLNodeCollection::AfterConstruction();
};

System::UnicodeString __fastcall TXMLcategoryType::Get_name()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("name")]->Text;
};

void __fastcall TXMLcategoryType::Set_name(const System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("name"), Value);
};

_di_IXMLgenreType __fastcall TXMLcategoryType::Get_genre(const int Index)
{
  return (_di_IXMLgenreType) List->Nodes[Index];
};

_di_IXMLgenreType __fastcall TXMLcategoryType::Add()
{
  return (_di_IXMLgenreType) AddItem(-1);
};

_di_IXMLgenreType __fastcall TXMLcategoryType::Insert(const int Index)
{
  return (_di_IXMLgenreType) AddItem(Index);
};

// TXMLgenreType 

void __fastcall TXMLgenreType::AfterConstruction(void)
{
  RegisterChildNode(System::UnicodeString("book"), __classid(TXMLbookType));
  ItemTag = "book";
  ItemInterface = __uuidof(IXMLbookType);
  Xml::Xmldoc::TXMLNodeCollection::AfterConstruction();
};

System::UnicodeString __fastcall TXMLgenreType::Get_name()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("name")]->Text;
};

void __fastcall TXMLgenreType::Set_name(const System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("name"), Value);
};

_di_IXMLbookType __fastcall TXMLgenreType::Get_book(const int Index)
{
  return (_di_IXMLbookType) List->Nodes[Index];
};

_di_IXMLbookType __fastcall TXMLgenreType::Add()
{
  return (_di_IXMLbookType) AddItem(-1);
};

_di_IXMLbookType __fastcall TXMLgenreType::Insert(const int Index)
{
  return (_di_IXMLbookType) AddItem(Index);
};

// TXMLbookType 

System::UnicodeString __fastcall TXMLbookType::Get_author()
{
  return GetChildNodes()->Nodes[System::UnicodeString("author")]->Text;
};

void __fastcall TXMLbookType::Set_author(const System::UnicodeString Value)
{
  GetChildNodes()->Nodes[System::UnicodeString("author")]->NodeValue = Value;
};

System::UnicodeString __fastcall TXMLbookType::Get_title()
{
  return GetChildNodes()->Nodes[System::UnicodeString("title")]->Text;
};

void __fastcall TXMLbookType::Set_title(const System::UnicodeString Value)
{
  GetChildNodes()->Nodes[System::UnicodeString("title")]->NodeValue = Value;
};

int __fastcall TXMLbookType::Get_year()
{
  return XmlStrToInt(GetChildNodes()->Nodes[System::UnicodeString("year")]->Text);
};

void __fastcall TXMLbookType::Set_year(const int Value)
{
  GetChildNodes()->Nodes[System::UnicodeString("year")]->NodeValue = Value;
};

System::UnicodeString __fastcall TXMLbookType::Get_paragraph()
{
  return GetChildNodes()->Nodes[System::UnicodeString("paragraph")]->Text;
};

void __fastcall TXMLbookType::Set_paragraph(const System::UnicodeString Value)
{
  GetChildNodes()->Nodes[System::UnicodeString("paragraph")]->NodeValue = Value;
};
