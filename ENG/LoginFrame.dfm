object FrLogin: TFrLogin
  Left = 0
  Top = 0
  Width = 262
  Height = 343
  TabOrder = 0
  object LPassword: TLabel
    Left = 72
    Top = 96
    Width = 53
    Height = 15
    Caption = 'Password:'
  end
  object LUsername: TLabel
    Left = 72
    Top = 36
    Width = 56
    Height = 15
    Caption = 'Username:'
  end
  object LNotRegistered: TLabel
    Left = 72
    Top = 261
    Width = 80
    Height = 15
    Caption = 'Not registered?'
  end
  object LResponse: TLabel
    Left = 72
    Top = 156
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
    Left = 72
    Top = 282
    Width = 118
    Height = 25
    Caption = 'Register'
    TabOrder = 4
    OnClick = BtRegisterClick
  end
  object BtGuest: TButton
    Left = 72
    Top = 213
    Width = 118
    Height = 25
    Caption = 'Sign in as guest'
    TabOrder = 3
    OnClick = BtGuestClick
  end
  object BtSignIn: TButton
    Left = 72
    Top = 177
    Width = 118
    Height = 25
    Caption = 'Sign in'
    Enabled = False
    TabOrder = 2
    OnClick = BtSignInClick
  end
  object EPassword: TEdit
    Left = 72
    Top = 117
    Width = 118
    Height = 23
    PasswordChar = '*'
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
end
