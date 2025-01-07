object FPracticeSource: TFPracticeSource
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Select a text source'
  ClientHeight = 493
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
    Left = 445
    Top = 460
    Width = 75
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 1
  end
  object BtAccept: TButton
    Left = 347
    Top = 460
    Width = 75
    Height = 25
    Caption = 'Accept'
    ModalResult = 1
    TabOrder = 0
  end
  object PCSourceText: TPageControl
    Left = 8
    Top = 13
    Width = 512
    Height = 430
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
