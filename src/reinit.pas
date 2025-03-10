
//---------------------------------------------------------------------------

// This software is Copyright (c) 2011 Embarcadero Technologies, Inc. 
// You may only use this software if you are an authorized licensee
// of Delphi, C++Builder or RAD Studio (Embarcadero Products).
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------
unit reinit;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms;

procedure ReinitializeForms;
function LoadNewResourceModule(Locale: LCID): Longint;

implementation

type
  TAsInheritedReader = class(TReader)
  public
    procedure ReadPrefix(var Flags: TFilerFlags; var AChildPos: Integer); override;
  end;

procedure TAsInheritedReader.ReadPrefix(var Flags: TFilerFlags; var AChildPos: Integer);
begin
  inherited ReadPrefix(Flags, AChildPos);
  Include(Flags, ffInherited);
end;

function SetResourceHInstance(NewInstance: Longint): Longint;
var
  CurModule: PLibModule;
begin
  CurModule := LibModuleList;
  Result := 0;
  while CurModule <> nil do
  begin
    if CurModule.Instance = HInstance then
    begin
      if CurModule.ResInstance <> CurModule.Instance then
        FreeLibrary(CurModule.ResInstance);
      CurModule.ResInstance := NewInstance;
      Result := NewInstance;
      Exit;
    end;
    CurModule := CurModule.Next;
  end;
end;

function LoadNewResourceModule(Locale: LCID): Longint;
var
  FileName: array [0..260] of char;
  NewName: string;
  LocaleName: array[0..4] of Char;
  NewInst: Longint;
begin
  GetModuleFileName(HInstance, FileName, SizeOf(FileName));

    // create libname from base name

  GetLocaleInfo(Locale, LOCALE_SABBREVLANGNAME, LocaleName, SizeOf(LocaleName));
  NewInst := 0;
  Result := 0;
  begin
    if LocaleName[0] <> #0 then
    begin
      NewName := StringReplace(FileName, '.exe', '.' + String(LocaleName), [rfIgnoreCase]) ;

      // Then look for a potential language/country translation

      NewInst := LoadLibraryEx(PChar(NewName), 0, LOAD_LIBRARY_AS_DATAFILE);
      if NewInst = 0 then
      begin
        // Finally look for a language only translation

        LocaleName[2] := #0;
        NewName := StringReplace(FileName, '.exe', '.' + String(LocaleName), [rfIgnoreCase]) ;
        NewInst := LoadLibraryEx(PChar(NewName), 0, LOAD_LIBRARY_AS_DATAFILE);
      end;
    end;
  end;
  if NewInst <> 0 then
    Result := SetResourceHInstance(NewInst)
end;

function InternalReloadComponentRes(const ResName: string; HInst: THandle; var Instance: TComponent): Boolean;
var
  HRsrc: THandle;
  ResStream: TResourceStream;
  AsInheritedReader: TAsInheritedReader;
begin                   { avoid possible EResNotFound exception }
  if HInst = 0 then HInst := HInstance;
  HRsrc := FindResource(HInst, PChar(ResName), RT_RCDATA);
  Result := HRsrc <> 0;
  if not Result then Exit;
  ResStream := TResourceStream.Create(HInst, ResName, RT_RCDATA);
  try
    AsInheritedReader := TAsInheritedReader.Create(ResStream, 4096);
    try
      Instance := AsInheritedReader.ReadRootComponent(Instance);
    finally
      AsInheritedReader.Free;
    end;
  finally
    ResStream.Free;
  end;
  Result := True;
end;

function ReloadInheritedComponent(Instance: TComponent; RootAncestor: TClass): Boolean;

  function InitComponent(ClassType: TClass): Boolean;
  begin
    Result := False;
    if (ClassType = TComponent) or (ClassType = RootAncestor) then Exit;
    Result := InitComponent(ClassType.ClassParent);
    Result := InternalReloadComponentRes(ClassType.ClassName, FindResourceHInstance(
      FindClassHInstance(ClassType)), Instance) or Result;
  end;

begin
  Result := InitComponent(Instance.ClassType);
end;

procedure ReinitializeForms;
var
  Count: Integer;
  I: Integer;
  Form: TForm;
begin
  Count := Screen.FormCount;
  for I := 0 to Count - 1 do
  begin
    Form := Screen.Forms[I];
    ReloadInheritedComponent(Form, TForm);
  end;
end;

end.