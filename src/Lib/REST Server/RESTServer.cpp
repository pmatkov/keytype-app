
//---------------------------------------------------------------------------
#include <WinApi.ActiveX.hpp>
#include <System.Win.ComObj.hpp>
#include <Web.WebBroker.hpp>
#include <Web.Win.ISAPIApp.hpp>
#include <Web.Win.ISAPIThreadPool.hpp>
#include <Winapi.Isapi2.hpp>
#pragma hdrstop

USEFORM("WebModule.cpp", WebModule1); /* TWebModule: File Type */
//---------------------------------------------------------------------------
#define Application Webbroker::Application

#pragma link "Web.Win.isapiapp"
#pragma link "Web.Win.isapithreadpool"
#pragma link "Web.webbroker"
#pragma package(smart_init)

extern PACKAGE TComponentClass WebModuleClass;
//---------------------------------------------------------------------------
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void*)
{
  try
  {
    if (reason == DLL_PROCESS_ATTACH) {
      CoInitFlags = COINIT_MULTITHREADED;
      Application->Initialize();
     Application->WebModuleClass = WebModuleClass;
      Application->Run();
    }
  }
  catch (Exception &exception)
  {
  }
  return 1;
}
//---------------------------------------------------------------------------
extern "C"
{
  BOOL __declspec(dllexport) WINAPI GetExtensionVersion(Isapi2::THSE_VERSION_INFO &Ver)
  {
    return Isapithreadpool::GetExtensionVersion(Ver);
  }
  //---------------------------------------------------------------------------
  unsigned __declspec(dllexport) WINAPI HttpExtensionProc(Isapi2::TEXTENSION_CONTROL_BLOCK &ECB)
  {
    return Isapithreadpool::HttpExtensionProc(ECB);
  }
  //---------------------------------------------------------------------------
  BOOL __declspec(dllexport) WINAPI TerminateExtension(int dwFlags)
  {
    return Isapithreadpool::TerminateExtension(dwFlags);
  }
}
//---------------------------------------------------------------------------
#undef Application
//---------------------------------------------------------------------------


