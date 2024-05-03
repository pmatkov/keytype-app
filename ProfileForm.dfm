object FrProfile: TFrProfile
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = 'Profile'
  ClientHeight = 309
  ClientWidth = 381
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  OnActivate = FormActivate
  TextHeight = 15
  object LUsername: TLabel
    Left = 147
    Top = 42
    Width = 56
    Height = 15
    Caption = 'Username:'
  end
  object LPassword: TLabel
    Left = 147
    Top = 75
    Width = 53
    Height = 15
    Caption = 'Password:'
  end
  object LName: TLabel
    Left = 147
    Top = 111
    Width = 35
    Height = 15
    Caption = 'Name:'
  end
  object LSurname: TLabel
    Left = 147
    Top = 147
    Width = 50
    Height = 15
    Caption = 'Surname:'
  end
  object LEmail: TLabel
    Left = 147
    Top = 180
    Width = 37
    Height = 15
    Caption = 'E-mail:'
  end
  object LAge: TLabel
    Left = 147
    Top = 216
    Width = 24
    Height = 15
    Caption = 'Age:'
  end
  object LInfo: TLabel
    Left = 25
    Top = 274
    Width = 100
    Height = 15
    AutoSize = False
  end
  object BtEditSave: TButton
    Left = 285
    Top = 270
    Width = 85
    Height = 25
    Caption = 'Edit profile'
    TabOrder = 0
    OnClick = BtEditSaveClick
  end
  object BtChangeImage: TButton
    Left = 25
    Top = 152
    Width = 85
    Height = 25
    Caption = 'Change image'
    TabOrder = 1
    OnClick = BtChangeImageClick
  end
  object GBProfile: TGroupBox
    Left = 231
    Top = 27
    Width = 139
    Height = 220
    TabOrder = 3
    object EName: TDBEdit
      Left = 9
      Top = 81
      Width = 121
      Height = 23
      DataField = 'name'
      DataSource = DataModule1.DUsers
      TabOrder = 2
    end
    object ESurname: TDBEdit
      Left = 9
      Top = 117
      Width = 121
      Height = 23
      DataField = 'surname'
      DataSource = DataModule1.DUsers
      TabOrder = 3
    end
    object EEmail: TDBEdit
      Left = 9
      Top = 150
      Width = 121
      Height = 23
      DataField = 'email'
      DataSource = DataModule1.DUsers
      TabOrder = 4
    end
    object EAge: TDBEdit
      Left = 9
      Top = 183
      Width = 121
      Height = 23
      BiDiMode = bdLeftToRight
      DataField = 'age'
      DataSource = DataModule1.DUsers
      ParentBiDiMode = False
      TabOrder = 5
    end
    object EPassword: TDBEdit
      Left = 9
      Top = 45
      Width = 121
      Height = 23
      DataField = 'password'
      DataSource = DataModule1.DUsers
      PasswordChar = '*'
      TabOrder = 1
    end
    object EUsername: TDBEdit
      Left = 9
      Top = 12
      Width = 121
      Height = 23
      DataField = 'username'
      DataSource = DataModule1.DUsers
      TabOrder = 0
    end
  end
  object BtDeleteImage: TButton
    Left = 25
    Top = 191
    Width = 85
    Height = 25
    Caption = 'Delete image'
    TabOrder = 2
    OnClick = BtDeleteImageClick
  end
  object DBImage: TDBImage
    Left = 17
    Top = 39
    Width = 100
    Height = 100
    DataField = 'profileImage'
    DataSource = DataModule1.DUsers
    TabOrder = 4
  end
  object DFileOpen: TOpenPictureDialog
    Left = 177
    Top = 252
  end
  object msgDisplayTimer: TTimer
    Enabled = False
    Interval = 3000
    OnTimer = msgDisplayTimerTimer
    Left = 180
    Top = 4
  end
end
