object FPracticeOptions: TFPracticeOptions
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = 'Select a text source'
  ClientHeight = 444
  ClientWidth = 530
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poMainFormCenter
  TextHeight = 15
  object BtCancel: TButton
    Left = 441
    Top = 411
    Width = 75
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 0
  end
  object BtAccept: TButton
    Left = 344
    Top = 411
    Width = 75
    Height = 25
    Caption = 'Accept'
    ModalResult = 1
    TabOrder = 1
  end
  object PCSourceText: TPageControl
    Left = 8
    Top = 8
    Width = 512
    Height = 390
    ActivePage = TSGeneratedText
    TabOrder = 2
    object TSGeneratedText: TTabSheet
      Caption = 'Generated Text'
    end
    object TSExternalSources: TTabSheet
      Caption = 'External Sources'
      ImageIndex = 2
    end
    object TSCustomText: TTabSheet
      Caption = 'Custom Text'
      ImageIndex = 1
    end
  end
end
