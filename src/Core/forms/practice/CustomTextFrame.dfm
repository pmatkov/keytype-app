object FrCustomText: TFrCustomText
  Left = 0
  Top = 0
  Width = 504
  Height = 400
  TabOrder = 0
  object LInfo: TLabel
    Left = 372
    Top = 294
    Width = 112
    Height = 15
    AutoSize = False
  end
  object MText: TMemo
    Left = 15
    Top = 219
    Width = 343
    Height = 160
    TabOrder = 0
  end
  object BtAddSave: TButton
    Left = 378
    Top = 219
    Width = 90
    Height = 25
    Caption = 'Add'
    TabOrder = 1
    OnClick = BtAddSaveClick
  end
  object BtDelete: TButton
    Left = 378
    Top = 257
    Width = 90
    Height = 25
    Caption = 'Delete'
    Enabled = False
    TabOrder = 2
    OnClick = BtDeleteClick
  end
  object LVCustomText: TListView
    Left = 15
    Top = 9
    Width = 469
    Height = 187
    Columns = <
      item
        Caption = 'id'
        Width = 30
      end
      item
        Caption = 'Text'
        Width = 320
      end
      item
        Caption = 'Date added'
        Width = 110
      end>
    MultiSelect = True
    ReadOnly = True
    RowSelect = True
    TabOrder = 3
    ViewStyle = vsReport
    OnMouseDown = LVCustomTextMouseDown
    OnSelectItem = LVCustomTextSelectItem
  end
  object msgDisplayTimer: TTimer
    Enabled = False
    Interval = 3000
    OnTimer = msgDisplayTimerTimer
    Left = 413
    Top = 315
  end
end
