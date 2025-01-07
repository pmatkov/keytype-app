object FrLogin: TFrLogin
  Left = 0
  Top = 0
  Width = 250
  Height = 364
  TabOrder = 0
  object LPassword: TLabel
    Left = 66
    Top = 84
    Width = 53
    Height = 15
    Caption = 'Password:'
  end
  object LUsername: TLabel
    Left = 66
    Top = 24
    Width = 56
    Height = 15
    Caption = 'Username:'
  end
  object LNotRegistered: TLabel
    Left = 66
    Top = 249
    Width = 80
    Height = 15
    Caption = 'Not registered?'
  end
  object LResponse: TLabel
    Left = 66
    Top = 144
    Width = 118
    Height = 15
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object BtRegister: TButton
    Left = 66
    Top = 270
    Width = 118
    Height = 25
    Caption = 'Register'
    TabOrder = 4
    OnClick = BtRegisterClick
  end
  object BtGuest: TButton
    Left = 66
    Top = 201
    Width = 118
    Height = 25
    Caption = 'Sign in as guest'
    TabOrder = 3
    OnClick = BtGuestClick
  end
  object BtSignIn: TButton
    Left = 66
    Top = 165
    Width = 118
    Height = 25
    Caption = 'Sign in'
    Enabled = False
    TabOrder = 2
    OnClick = BtSignInClick
  end
  object EPassword: TEdit
    Left = 66
    Top = 105
    Width = 118
    Height = 23
    PasswordChar = '*'
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
  object CBRestAuth: TCheckBox
    Left = 66
    Top = 315
    Width = 118
    Height = 15
    Caption = 'Reuse credentials'
    Checked = True
    Enabled = False
    State = cbChecked
    TabOrder = 5
    WordWrap = True
  end
end
