object FrExternalSources: TFrExternalSources
  Left = 0
  Top = 0
  Width = 517
  Height = 370
  TabOrder = 0
  object LAuthor: TLabel
    Left = 163
    Top = 207
    Width = 40
    Height = 15
    Caption = 'Author:'
  end
  object LTitle: TLabel
    Left = 283
    Top = 207
    Width = 25
    Height = 15
    Caption = 'Title:'
  end
  object LYear: TLabel
    Left = 403
    Top = 207
    Width = 25
    Height = 15
    Caption = 'Year:'
  end
  object LParagraph: TLabel
    Left = 163
    Top = 260
    Width = 57
    Height = 15
    Caption = 'Paragraph:'
  end
  object TVLiteratureCategories: TTreeView
    Left = 3
    Top = 3
    Width = 148
    Height = 337
    Indent = 19
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
    Left = 163
    Top = 3
    Width = 351
    Height = 94
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
    TabOrder = 1
    ViewStyle = vsReport
  end
  object MParagraph: TMemo
    Left = 163
    Top = 109
    Width = 351
    Height = 84
    Lines.Strings = (
      '')
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 2
  end
  object EAuthor: TEdit
    Left = 163
    Top = 228
    Width = 108
    Height = 23
    TabOrder = 3
  end
  object ETitle: TEdit
    Left = 283
    Top = 228
    Width = 111
    Height = 23
    TabOrder = 4
  end
  object EYear: TEdit
    Left = 406
    Top = 228
    Width = 108
    Height = 23
    TabOrder = 5
  end
  object EParagraph: TEdit
    Left = 163
    Top = 281
    Width = 351
    Height = 23
    TabOrder = 6
  end
  object BtDelete2: TButton
    Left = 387
    Top = 317
    Width = 58
    Height = 23
    Caption = 'Delete'
    TabOrder = 7
  end
  object BtAddSave2: TButton
    Left = 456
    Top = 317
    Width = 58
    Height = 23
    Caption = 'Edit'
    TabOrder = 8
  end
  object XMLTransform1: TXMLTransform
    Left = 282
    Top = 138
  end
  object XMLDocument1: TXMLDocument
    Active = True
    FileName = 
      'C:\Users\surf3r\OneDrive\Documents\Embarcadero\Studio\Projects\K' +
      'eyType\Data\books.xml'
    Options = [doNodeAutoCreate, doNodeAutoIndent, doAttrNull, doAutoPrefix, doNamespaceDecl]
    Left = 348
    Top = 136
  end
end
