object FServer: TFServer
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Server'
  ClientHeight = 141
  ClientWidth = 304
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object LTCPServerStatus: TLabel
    Left = 139
    Top = 39
    Width = 150
    Height = 15
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clTeal
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object LUDPServerStatus: TLabel
    Left = 139
    Top = 87
    Width = 150
    Height = 15
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clTeal
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object BtTCPServer: TButton
    Left = 18
    Top = 35
    Width = 100
    Height = 25
    Caption = 'Start TCP server'
    TabOrder = 0
    OnClick = BtTCPServerClick
  end
  object BtUDPServer: TButton
    Left = 18
    Top = 83
    Width = 100
    Height = 25
    Caption = 'Start UDP server'
    TabOrder = 1
    OnClick = BtUDPServerClick
  end
end
