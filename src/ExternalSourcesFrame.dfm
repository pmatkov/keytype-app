object FrExternalSources: TFrExternalSources
  Left = 0
  Top = 0
  Width = 504
  Height = 400
  TabOrder = 0
  object LAuthor: TLabel
    Left = 148
    Top = 246
    Width = 40
    Height = 15
    Caption = 'Author:'
  end
  object LTitle: TLabel
    Left = 268
    Top = 246
    Width = 25
    Height = 15
    Caption = 'Title:'
  end
  object LYear: TLabel
    Left = 394
    Top = 246
    Width = 25
    Height = 15
    Caption = 'Year:'
  end
  object LParagraph: TLabel
    Left = 148
    Top = 299
    Width = 57
    Height = 15
    Caption = 'Paragraph:'
  end
  object TVLiteratureCategories: TTreeView
    Left = 6
    Top = 6
    Width = 136
    Height = 337
    HideSelection = False
    Indent = 19
    ReadOnly = True
    TabOrder = 0
    OnChange = TVLiteratureCategoriesChange
    Items.NodeData = {
      0301000000280000000000000000000000FFFFFFFFFFFFFFFF00000000000000
      0002000000010542006F006F006B0073002C0000000000000000000000FFFFFF
      FFFFFFFFFF0000000000000000030000000107460069006300740069006F006E
      00280000000000000000000000FFFFFFFFFFFFFFFF0000000000000000000000
      0001054400720061006D0061002C0000000000000000000000FFFFFFFFFFFFFF
      FF000000000000000000000000010743006C00610073007300690063002C0000
      000000000000000000FFFFFFFFFFFFFFFF000000000000000000000000010746
      0061006E007400610073007900340000000000000000000000FFFFFFFFFFFFFF
      FF000000000000000002000000010B4E006F006E002D00460069006300740069
      006F006E002C0000000000000000000000FFFFFFFFFFFFFFFF00000000000000
      0000000000010753006300690065006E00630065003200000000000000000000
      00FFFFFFFFFFFFFFFF000000000000000000000000010A5000680069006C006F
      0073006F00700068007900}
  end
  object LVLiteratureDetails: TListView
    Left = 148
    Top = 6
    Width = 348
    Height = 115
    Columns = <
      item
        Caption = 'Author'
        Width = 110
      end
      item
        Caption = 'Title'
        Width = 180
      end
      item
        Caption = 'Year'
        Width = 55
      end>
    MultiSelect = True
    ReadOnly = True
    RowSelect = True
    TabOrder = 1
    ViewStyle = vsReport
    OnMouseDown = LVLiteratureDetailsMouseDown
    OnSelectItem = LVLiteratureDetailsSelectItem
  end
  object MParagraph: TMemo
    Left = 148
    Top = 132
    Width = 348
    Height = 94
    Lines.Strings = (
      '')
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 2
  end
  object EAuthor: TEdit
    Left = 148
    Top = 267
    Width = 105
    Height = 23
    TabOrder = 3
  end
  object ETitle: TEdit
    Left = 268
    Top = 267
    Width = 105
    Height = 23
    TabOrder = 4
  end
  object EYear: TEdit
    Left = 391
    Top = 267
    Width = 105
    Height = 23
    TabOrder = 5
  end
  object EParagraph: TEdit
    Left = 148
    Top = 320
    Width = 348
    Height = 23
    TabOrder = 6
  end
  object BtDelete: TButton
    Left = 361
    Top = 356
    Width = 58
    Height = 23
    Caption = 'Delete'
    Enabled = False
    TabOrder = 7
    OnClick = BtDeleteClick
  end
  object BtAddSave: TButton
    Left = 438
    Top = 356
    Width = 58
    Height = 23
    Caption = 'Add'
    TabOrder = 8
    OnClick = BtAddSaveClick
  end
  object XMLTransform: TXMLTransform
    Left = 36
    Top = 222
  end
  object XMLDocument: TXMLDocument
    NodeIndentStr = #9
    Options = [doNodeAutoCreate, doNodeAutoIndent, doAttrNull, doAutoPrefix, doNamespaceDecl]
    Left = 39
    Top = 286
  end
end
