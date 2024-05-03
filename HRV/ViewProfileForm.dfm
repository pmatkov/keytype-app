object FrViewProfile: TFrViewProfile
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = 'View profile'
  ClientHeight = 339
  ClientWidth = 373
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object LUsername: TLabel
    Left = 147
    Top = 51
    Width = 56
    Height = 15
    Caption = 'Username:'
  end
  object LPassword: TLabel
    Left = 147
    Top = 84
    Width = 53
    Height = 15
    Caption = 'Password:'
  end
  object LName: TLabel
    Left = 147
    Top = 123
    Width = 35
    Height = 15
    Caption = 'Name:'
  end
  object LSurname: TLabel
    Left = 147
    Top = 159
    Width = 50
    Height = 15
    Caption = 'Surname:'
  end
  object LEmail: TLabel
    Left = 147
    Top = 198
    Width = 37
    Height = 15
    Caption = 'E-mail:'
  end
  object LAge: TLabel
    Left = 147
    Top = 237
    Width = 24
    Height = 15
    Caption = 'Age:'
  end
  object ImProfile: TImage
    Left = 27
    Top = 48
    Width = 80
    Height = 80
  end
  object PProfile: TPanel
    Left = 213
    Top = 42
    Width = 139
    Height = 229
    TabOrder = 9
  end
  object EUsername: TEdit
    Left = 222
    Top = 51
    Width = 121
    Height = 23
    TabOrder = 0
  end
  object EPassword: TEdit
    Left = 222
    Top = 84
    Width = 121
    Height = 23
    TabOrder = 1
  end
  object EName: TEdit
    Left = 222
    Top = 123
    Width = 121
    Height = 23
    TabOrder = 2
  end
  object ESurname: TEdit
    Left = 222
    Top = 159
    Width = 121
    Height = 23
    TabOrder = 3
  end
  object EEmail: TEdit
    Left = 222
    Top = 198
    Width = 121
    Height = 23
    TabOrder = 4
  end
  object EAge: TEdit
    Left = 222
    Top = 237
    Width = 121
    Height = 23
    TabOrder = 5
  end
  object BtEditSave: TButton
    Left = 277
    Top = 282
    Width = 75
    Height = 25
    Caption = 'Edit profile'
    TabOrder = 6
  end
  object BtDelete: TButton
    Left = 180
    Top = 282
    Width = 85
    Height = 25
    Caption = 'Delete profile'
    TabOrder = 7
  end
  object BtClose: TButton
    Left = 27
    Top = 155
    Width = 85
    Height = 25
    Caption = 'Change image'
    ModalResult = 1
    TabOrder = 8
  end
end
