object FServer: TFServer
  Left = 0
  Top = 0
  Caption = 'Server'
  ClientHeight = 202
  ClientWidth = 308
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object LConnectionStatusDisplay: TLabel
    Left = 139
    Top = 24
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
  object BtTCPServer1: TButton
    Left = 18
    Top = 20
    Width = 100
    Height = 25
    Caption = 'Start TCP Server1'
    TabOrder = 0
    OnClick = BtTCPServer1Click
  end
end
