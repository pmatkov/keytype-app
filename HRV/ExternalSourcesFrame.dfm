object FrExternalSources: TFrExternalSources
  Left = 0
  Top = 0
  Width = 504
  Height = 360
  TabOrder = 0
  object LAuthor: TLabel
    Left = 148
    Top = 207
    Width = 40
    Height = 15
    Caption = 'Autor:'
  end
  object LTitle: TLabel
    Left = 271
    Top = 207
    Width = 25
    Height = 15
    Caption = 'Naslov:'
  end
  object LYear: TLabel
    Left = 394
    Top = 207
    Width = 25
    Height = 15
    Caption = 'Godina:'
  end
  object LParagraph: TLabel
    Left = 148
    Top = 260
    Width = 57
    Height = 15
    Caption = 'Paragraf:'
  end
  object TVLiteratureCategories: TTreeView
    Left = 3
    Top = 3
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
    Left = 145
    Top = 8
    Width = 351
    Height = 94
    Columns = <
      item
        Caption = 'Autor'
        Width = 110
      end
      item
        Caption = 'Naslov'
        Width = 180
      end
      item
        Caption = 'Godina'
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
    Left = 145
    Top = 106
    Width = 351
    Height = 84
    Lines.Strings = (
      '')
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 2
  end
  object EAuthor: TEdit
    Left = 145
    Top = 232
    Width = 108
    Height = 23
    TabOrder = 3
  end
  object ETitle: TEdit
    Left = 265
    Top = 228
    Width = 111
    Height = 23
    TabOrder = 4
  end
  object EYear: TEdit
    Left = 388
    Top = 228
    Width = 108
    Height = 23
    TabOrder = 5
  end
  object EParagraph: TEdit
    Left = 145
    Top = 281
    Width = 351
    Height = 23
    TabOrder = 6
  end
  object BtDelete2: TButton
    Left = 364
    Top = 317
    Width = 58
    Height = 23
    Caption = 'Obri'#353'i'
    Enabled = False
    TabOrder = 7
    OnClick = BtDelete2Click
  end
  object BtAddSave2: TButton
    Left = 438
    Top = 317
    Width = 58
    Height = 23
    Caption = 'Dodaj'
    TabOrder = 8
    OnClick = BtAddSave2Click
  end
  object XMLTransform: TXMLTransform
    Left = 282
    Top = 138
  end
  object XMLDocument: TXMLDocument
    NodeIndentStr = #9
    Options = [doNodeAutoCreate, doNodeAutoIndent, doAttrNull, doAutoPrefix, doNamespaceDecl]
    Left = 378
    Top = 142
  end
end
