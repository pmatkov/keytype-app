object FrRegister: TFrRegister
  Left = 0
  Top = 0
  Width = 262
  Height = 343
  TabOrder = 0
  object LUsername: TLabel
    Left = 72
    Top = 36
    Width = 56
    Height = 15
    Caption = 'Korisni'#269'ko ime'
  end
  object LPassword: TLabel
    Left = 72
    Top = 96
    Width = 53
    Height = 15
    Caption = 'Lozinka'
  end
  object LRepeatPassword: TLabel
    Left = 72
    Top = 156
    Width = 92
    Height = 15
    Caption = 'Ponovi lozinku'
  end
  object LAlreadyRegistered: TLabel
    Left = 72
    Top = 270
    Width = 100
    Height = 15
    Caption = 'Ve'#263' registriran?'
  end
  object LResponse: TLabel
    Left = 72
    Top = 210
    Width = 3
    Height = 15
    Color = clBtnFace
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentColor = False
    ParentFont = False
  end
  object EPassword: TEdit
    Left = 72
    Top = 117
    Width = 118
    Height = 23
    TabOrder = 1
    OnChange = EPasswordChange
  end
  object EUsername: TEdit
    Left = 72
    Top = 57
    Width = 118
    Height = 23
    TabOrder = 0
    OnChange = EUsernameChange
  end
  object ERepeatPassword: TEdit
    Left = 72
    Top = 177
    Width = 118
    Height = 23
    PasswordChar = '*'
    TabOrder = 2
    OnChange = ERepeatPasswordChange
  end
  object BtRegister: TButton
    Left = 72
    Top = 231
    Width = 118
    Height = 25
    Caption = 'Registriraj se'
    Enabled = False
    TabOrder = 3
    OnClick = BtRegisterClick
  end
  object BtSignIn: TButton
    Left = 72
    Top = 291
    Width = 118
    Height = 25
    Caption = 'Prijavi se'
    TabOrder = 4
    OnClick = BtSignInClick
  end
end
