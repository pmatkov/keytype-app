object FrRegister: TFrRegister
  Left = 0
  Top = 0
  Width = 250
  Height = 364
  TabOrder = 0
  object LUsername: TLabel
    Left = 66
    Top = 24
    Width = 56
    Height = 15
    Caption = 'Korisni'#269'ko ime'
  end
  object LPassword: TLabel
    Left = 66
    Top = 84
    Width = 53
    Height = 15
    Caption = 'Lozinka'
  end
  object LRepeatPassword: TLabel
    Left = 66
    Top = 144
    Width = 92
    Height = 15
    Caption = 'Ponovi lozinku'
  end
  object LAlreadyRegistered: TLabel
    Left = 66
    Top = 258
    Width = 100
    Height = 15
    Caption = 'Ve'#263' registriran?'
  end
  object LResponse: TLabel
    Left = 66
    Top = 198
    Width = 118
    Height = 15
    AutoSize = False
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
    Left = 66
    Top = 105
    Width = 118
    Height = 23
    TabOrder = 1
    OnChange = EPasswordChange
  end
  object EUsername: TEdit
    Left = 66
    Top = 45
    Width = 118
    Height = 23
    TabOrder = 0
    OnChange = EUsernameChange
  end
  object ERepeatPassword: TEdit
    Left = 66
    Top = 165
    Width = 118
    Height = 23
    PasswordChar = '*'
    TabOrder = 2
    OnChange = ERepeatPasswordChange
  end
  object BtRegister: TButton
    Left = 66
    Top = 219
    Width = 118
    Height = 25
    Caption = 'Registriraj se'
    Enabled = False
    TabOrder = 3
    OnClick = BtRegisterClick
  end
  object BtSignIn: TButton
    Left = 66
    Top = 279
    Width = 118
    Height = 25
    Caption = 'Prijavi se'
    TabOrder = 4
    OnClick = BtSignInClick
  end
  object CBRestAuth: TCheckBox
    Left = 66
    Top = 315
    Width = 118
    Height = 17
    Caption = 'Resue credentials'
    Checked = True
    Enabled = False
    State = cbChecked
    TabOrder = 5
  end
end
