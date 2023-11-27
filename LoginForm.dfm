object FLogin: TFLogin
  Left = 0
  Top = 0
  Caption = 'Login'
  ClientHeight = 291
  ClientWidth = 259
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object LUsername: TLabel
    Left = 72
    Top = 63
    Width = 56
    Height = 15
    Caption = 'Username:'
  end
  object LPassword: TLabel
    Left = 75
    Top = 135
    Width = 53
    Height = 15
    Caption = 'Password:'
  end
  object EUsername: TEdit
    Left = 72
    Top = 84
    Width = 121
    Height = 23
    TabOrder = 0
  end
  object EPassword: TEdit
    Left = 72
    Top = 156
    Width = 121
    Height = 23
    TabOrder = 1
  end
  object BtLogin: TButton
    Left = 72
    Top = 195
    Width = 121
    Height = 25
    Caption = 'Log in'
    TabOrder = 2
  end
  object BtGuest: TButton
    Left = 72
    Top = 237
    Width = 121
    Height = 25
    Caption = 'Continue as guest'
    TabOrder = 3
    OnClick = BtGuestClick
  end
end
