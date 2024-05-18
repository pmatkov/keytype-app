object FLogs: TFLogs
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Logs'
  ClientHeight = 346
  ClientWidth = 528
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  OnActivate = FormActivate
  TextHeight = 15
  object LVLogDates: TListView
    Left = 15
    Top = 17
    Width = 499
    Height = 107
    Columns = <
      item
        Caption = 'File name'
        Width = 270
      end
      item
        Caption = 'Last modified'
        Width = 120
      end
      item
        Caption = 'File size'
        Width = 100
      end>
    MultiSelect = True
    ReadOnly = True
    RowSelect = True
    TabOrder = 0
    ViewStyle = vsReport
    OnMouseDown = LVLogDatesMouseDown
    OnSelectItem = LVLogDatesSelectItem
  end
  object MLogs: TMemo
    Left = 15
    Top = 141
    Width = 499
    Height = 191
    Lines.Strings = (
      '')
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 1
  end
end
