object FPractice: TFPractice
  Left = 0
  Top = 0
  Caption = 'Practice Options'
  ClientHeight = 345
  ClientWidth = 525
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poMainFormCenter
  TextHeight = 15
  object LTextSourceInfo: TLabel
    Left = 12
    Top = 8
    Width = 104
    Height = 15
    Caption = 'Select a text source:'
  end
  object PCSourceText: TPageControl
    Left = 8
    Top = 40
    Width = 509
    Height = 253
    ActivePage = TSGeneratedText
    TabOrder = 0
    object TSGeneratedText: TTabSheet
      Caption = 'Generated Text'
      object GBCharacters: TGroupBox
        Left = 3
        Top = 51
        Width = 244
        Height = 162
        TabOrder = 0
        object Bevel1: TBevel
          Left = 11
          Top = 65
          Width = 218
          Height = 2
          Shape = bsBottomLine
        end
        object LettersToolbar: TToolBar
          Left = 3
          Top = 7
          Width = 238
          Height = 46
          Align = alNone
          Caption = 'LettersToolbar'
          TabOrder = 0
        end
        object CBSelectAll: TCheckBox
          Left = 11
          Top = 82
          Width = 77
          Height = 17
          Caption = 'Select all'
          TabOrder = 1
          OnClick = CBSelectAllClick
        end
        object CBNumbers: TCheckBox
          Left = 11
          Top = 105
          Width = 97
          Height = 17
          Caption = 'Numbers'
          TabOrder = 2
        end
        object CBPunctuation: TCheckBox
          Left = 132
          Top = 104
          Width = 97
          Height = 17
          Caption = 'Punctuation'
          TabOrder = 3
        end
        object CBCapitalLetters: TCheckBox
          Left = 132
          Top = 81
          Width = 97
          Height = 17
          Caption = 'Capital letters'
          TabOrder = 4
        end
      end
      object GBWords: TGroupBox
        Left = 253
        Top = 51
        Width = 244
        Height = 162
        TabOrder = 1
      end
      object RGGeneratedText: TRadioGroup
        Left = 3
        Top = 0
        Width = 495
        Height = 45
        Columns = 2
        Items.Strings = (
          'Characters'
          'Words')
        TabOrder = 2
        OnClick = RGGeneratedTextClick
      end
    end
    object TSCustomText: TTabSheet
      Caption = 'Custom Text'
      ImageIndex = 1
    end
    object TSExternalSources: TTabSheet
      Caption = 'External Sources'
      ImageIndex = 2
    end
  end
  object CButton: TButton
    Left = 434
    Top = 312
    Width = 75
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 1
    OnClick = CButtonClick
  end
  object AButton: TButton
    Left = 345
    Top = 312
    Width = 75
    Height = 25
    Caption = 'Accept'
    ModalResult = 1
    TabOrder = 2
  end
end
