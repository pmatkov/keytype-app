object FLessonResults: TFLessonResults
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Lesson results'
  ClientHeight = 420
  ClientWidth = 580
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object DBGridLessonResults: TDBGrid
    Left = 13
    Top = 158
    Width = 561
    Height = 206
    DataSource = DataModule1.DLessonResults
    Options = [dgTitles, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgMultiSelect, dgTitleClick, dgTitleHotTrack]
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -12
    TitleFont.Name = 'Segoe UI'
    TitleFont.Style = []
    Columns = <
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'id'
        Width = 20
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'idUser'
        Width = 40
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'lessonName'
        Title.Caption = 'Lesson name'
        Width = 100
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'lessonGoal'
        Title.Caption = 'Goal'
        Width = 50
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'lessonGoalValue'
        Title.Caption = 'Value'
        Width = 40
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'result'
        Title.Caption = 'Result'
        Width = 50
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'speed'
        Title.Caption = 'Speed'
        Width = 55
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'accuracy'
        Title.Caption = 'Accuracy'
        Width = 55
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'durationHMS'
        Title.Caption = 'Duration'
        Width = 60
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'date'
        Title.Caption = 'Date'
        Width = 60
        Visible = True
      end>
  end
  object DBUsers: TDBGrid
    Left = 125
    Top = 31
    Width = 449
    Height = 100
    DataSource = DataModule1.DUsers
    Options = [dgTitles, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgMultiSelect, dgTitleClick, dgTitleHotTrack]
    TabOrder = 1
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -12
    TitleFont.Name = 'Segoe UI'
    TitleFont.Style = []
    Columns = <
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'id'
        Width = 20
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'username'
        Title.Caption = 'Username'
        Width = 80
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'name'
        Title.Caption = 'Name'
        Width = 80
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'surname'
        Title.Caption = 'Surname'
        Width = 80
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'email'
        Title.Caption = 'E-mail'
        Width = 120
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'age'
        Title.Caption = 'Age'
        Width = 40
        Visible = True
      end>
  end
  object DBImage: TDBImage
    Left = 13
    Top = 31
    Width = 100
    Height = 100
    DataField = 'profileImage'
    DataSource = DataModule1.DUsers
    TabOrder = 2
  end
  object BtViewReport: TButton
    Left = 499
    Top = 379
    Width = 75
    Height = 25
    Caption = 'View report'
    TabOrder = 3
    OnClick = BtViewReportClick
  end
  object BtExportRtf: TButton
    Left = 279
    Top = 379
    Width = 85
    Height = 25
    Caption = 'Export as RTF'
    TabOrder = 4
    OnClick = BtExportRtfClick
  end
  object BtExportPdf: TButton
    Left = 378
    Top = 379
    Width = 85
    Height = 25
    Caption = 'Export as PDF'
    TabOrder = 5
    OnClick = BtExportPdfClick
  end
  object frxReport: TfrxReport
    Version = '2022.2.7'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator, pbExportQuick, pbCopy, pbSelection]
    PreviewOptions.Zoom = 1.000000000000000000
    PrintOptions.Printer = 'Default'
    PrintOptions.PrintOnSheet = 0
    ReportOptions.CreateDate = 45415.780049502300000000
    ReportOptions.LastChange = 45415.780049502300000000
    ScriptLanguage = 'PascalScript'
    ScriptText.Strings = (
      'begin'
      ''
      'end.')
    Left = 15
    Top = 366
    Datasets = <
      item
        DataSet = frxUser
        DataSetName = 'frxUser'
      end
      item
        DataSet = frxLessonResult
        DataSetName = 'frxLessonResult'
      end>
    Variables = <>
    Style = <>
    object Data: TfrxDataPage
      Height = 1000.000000000000000000
      Width = 1000.000000000000000000
    end
    object Page1: TfrxReportPage
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = []
      PaperWidth = 215.900000000000000000
      PaperHeight = 279.400000000000000000
      PaperSize = 1
      LeftMargin = 10.000000000000000000
      RightMargin = 10.000000000000000000
      TopMargin = 10.000000000000000000
      BottomMargin = 10.000000000000000000
      Frame.Typ = []
      MirrorMode = []
      object ReportTitle1: TfrxReportTitle
        FillType = ftBrush
        FillGap.Top = 0
        FillGap.Left = 0
        FillGap.Bottom = 0
        FillGap.Right = 0
        Frame.Typ = []
        Height = 45.354340470000000000
        Top = 18.897650000000000000
        Width = 740.409927000000000000
        object Memo2: TfrxMemoView
          AllowVectorExport = True
          Top = 3.779530000000000000
          Width = 737.008350000000000000
          Height = 30.236220470000000000
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Color = clWhite
          Frame.Typ = []
          Fill.BackColor = clSilver
          Fill.ForeColor = clWhite
          HAlign = haCenter
          Memo.UTF8W = (
            'Lesson results')
          ParentFont = False
          VAlign = vaCenter
        end
      end
      object PageHeader1: TfrxPageHeader
        FillType = ftBrush
        FillGap.Top = 0
        FillGap.Left = 0
        FillGap.Bottom = 0
        FillGap.Right = 0
        Frame.Typ = []
        Height = 26.456710000000000000
        Top = 86.929190000000000000
        Width = 740.409927000000000000
        object SysMemo1: TfrxSysMemoView
          AllowVectorExport = True
          Left = 570.709030000000000000
          Width = 71.811070000000000000
          Height = 18.897650000000000000
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = []
          Memo.UTF8W = (
            '[DATE]')
          ParentFont = False
          VAlign = vaCenter
        end
        object SysMemo2: TfrxSysMemoView
          AllowVectorExport = True
          Left = 650.079160000000000000
          Width = 68.031500940000000000
          Height = 18.897650000000000000
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Color = clWhite
          Frame.Typ = []
          Fill.ForeColor = clWhite
          Memo.UTF8W = (
            '[TIME]')
          ParentFont = False
          VAlign = vaCenter
        end
      end
      object PageFooter1: TfrxPageFooter
        FillType = ftBrush
        FillGap.Top = 0
        FillGap.Left = 0
        FillGap.Bottom = 0
        FillGap.Right = 0
        Frame.Typ = []
        Height = 22.677180000000000000
        Top = 517.795610000000000000
        Width = 740.409927000000000000
        object Memo1: TfrxMemoView
          AllowVectorExport = True
          Left = 634.961040000000000000
          Width = 94.488250000000000000
          Height = 18.897650000000000000
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = []
          HAlign = haRight
          Memo.UTF8W = (
            '[PAGE#]')
          ParentFont = False
        end
      end
      object MasterData1: TfrxMasterData
        FillType = ftBrush
        FillGap.Top = 0
        FillGap.Left = 0
        FillGap.Bottom = 0
        FillGap.Right = 0
        Frame.Typ = []
        Height = 136.063080000000000000
        Top = 173.858380000000000000
        Width = 740.409927000000000000
        DataSet = frxUser
        DataSetName = 'frxUser'
        RowCount = 0
        object Memo4: TfrxMemoView
          AllowVectorExport = True
          Left = 139.842610000000000000
          Top = 15.118120000000000000
          Width = 68.031496060000000000
          Height = 18.897650000000000000
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Color = clWhite
          Frame.Typ = []
          Fill.ForeColor = clWhite
          Memo.UTF8W = (
            'Name:')
          ParentFont = False
          VAlign = vaCenter
        end
        object Memo5: TfrxMemoView
          AllowVectorExport = True
          Left = 139.842610000000000000
          Top = 37.795300000000000000
          Width = 68.031496060000000000
          Height = 18.897650000000000000
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Color = clWhite
          Frame.Typ = []
          Fill.ForeColor = clWhite
          Memo.UTF8W = (
            'Surname:')
          ParentFont = False
          VAlign = vaCenter
        end
        object frxUserusername: TfrxMemoView
          IndexTag = 1
          AllowVectorExport = True
          Left = 22.677180000000000000
          Top = 60.472480000000000000
          Width = 90.708720000000000000
          Height = 34.015770000000000000
          DataSet = frxUser
          DataSetName = 'frxUser'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsItalic]
          Frame.Color = clWhite
          Frame.Typ = []
          Fill.ForeColor = clWhite
          Memo.UTF8W = (
            '[frxUser."username"]')
          ParentFont = False
          VAlign = vaCenter
        end
        object Memo6: TfrxMemoView
          IndexTag = 1
          AllowVectorExport = True
          Left = 222.992270000000000000
          Top = 15.118120000000000000
          Width = 143.622140000000000000
          Height = 18.897650000000000000
          DataField = 'name'
          DataSet = frxUser
          DataSetName = 'frxUser'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clGray
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Color = clWhite
          Frame.Typ = []
          Fill.ForeColor = clWhite
          Memo.UTF8W = (
            '[frxUser."name"]')
          ParentFont = False
          VAlign = vaCenter
        end
        object Memo7: TfrxMemoView
          IndexTag = 1
          AllowVectorExport = True
          Left = 222.992270000000000000
          Top = 37.795300000000000000
          Width = 143.622047240000000000
          Height = 18.897650000000000000
          DataField = 'surname'
          DataSet = frxUser
          DataSetName = 'frxUser'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clGray
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Color = clWhite
          Frame.Typ = []
          Fill.ForeColor = clWhite
          Memo.UTF8W = (
            '[frxUser."surname"]')
          ParentFont = False
          VAlign = vaCenter
        end
        object Picture1: TfrxPictureView
          AllowVectorExport = True
          Left = 22.677180000000000000
          Top = 18.897650000000000000
          Width = 37.795275590551200000
          Height = 37.795275590551200000
          DataField = 'profileImage'
          DataSet = frxUser
          DataSetName = 'frxUser'
          Frame.Typ = []
          HightQuality = False
          Transparent = False
          TransparentColor = clWhite
        end
        object Memo8: TfrxMemoView
          AllowVectorExport = True
          Left = 139.842610000000000000
          Top = 60.472480000000000000
          Width = 68.031496060000000000
          Height = 18.897650000000000000
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Color = clWhite
          Frame.Typ = []
          Fill.ForeColor = clWhite
          Memo.UTF8W = (
            'E-mail:')
          ParentFont = False
          VAlign = vaCenter
        end
        object Memo9: TfrxMemoView
          AllowVectorExport = True
          Left = 139.842610000000000000
          Top = 83.149660000000000000
          Width = 68.031496060000000000
          Height = 18.897650000000000000
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Color = clWhite
          Frame.Typ = []
          Fill.ForeColor = clWhite
          Memo.UTF8W = (
            'Age:')
          ParentFont = False
          VAlign = vaCenter
        end
        object Memo10: TfrxMemoView
          IndexTag = 1
          AllowVectorExport = True
          Left = 222.992270000000000000
          Top = 60.472480000000000000
          Width = 143.622140000000000000
          Height = 18.897650000000000000
          DataField = 'email'
          DataSet = frxUser
          DataSetName = 'frxUser'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clGray
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Color = clWhite
          Frame.Typ = []
          Fill.ForeColor = clWhite
          Memo.UTF8W = (
            '[frxUser."email"]')
          ParentFont = False
          VAlign = vaCenter
        end
        object Memo11: TfrxMemoView
          IndexTag = 1
          AllowVectorExport = True
          Left = 222.992270000000000000
          Top = 83.149660000000000000
          Width = 143.622047240000000000
          Height = 18.897650000000000000
          DataField = 'age'
          DataSet = frxUser
          DataSetName = 'frxUser'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clGray
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Color = clWhite
          Frame.Typ = []
          Fill.ForeColor = clWhite
          Memo.UTF8W = (
            '[frxUser."age"]')
          ParentFont = False
          VAlign = vaCenter
        end
        object Line1: TfrxLineView
          AllowVectorExport = True
          Left = 11.338590000000000000
          Top = 117.165430000000000000
          Width = 706.772110000000000000
          Color = clBlack
          Frame.Typ = []
          Diagonal = True
        end
        object Line2: TfrxLineView
          AllowVectorExport = True
          Left = 11.338590000000000000
          Top = 7.559060000000000000
          Width = 706.772110000000000000
          Color = clBlack
          Frame.Typ = []
          Diagonal = True
        end
      end
      object DetailData1: TfrxDetailData
        FillType = ftBrush
        FillGap.Top = 0
        FillGap.Left = 0
        FillGap.Bottom = 0
        FillGap.Right = 0
        Frame.Typ = []
        Height = 124.724490000000000000
        Top = 332.598640000000000000
        Width = 740.409927000000000000
        DataSet = frxLessonResult
        DataSetName = 'frxLessonResult'
        RowCount = 0
        object Memo12: TfrxMemoView
          AllowVectorExport = True
          Left = 22.677180000000000000
          Top = 11.338590000000000000
          Width = 94.488250000000000000
          Height = 18.897650000000000000
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Color = clWhite
          Frame.Typ = []
          Fill.ForeColor = clWhite
          Memo.UTF8W = (
            'Lesson name:')
          ParentFont = False
          VAlign = vaCenter
        end
        object frxLessonResultlessonName: TfrxMemoView
          IndexTag = 1
          AllowVectorExport = True
          Left = 124.724490000000000000
          Top = 11.338590000000000000
          Width = 211.653680000000000000
          Height = 18.897650000000000000
          DataField = 'lessonName'
          DataSet = frxLessonResult
          DataSetName = 'frxLessonResult'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Color = clWhite
          Frame.Typ = []
          Fill.ForeColor = clWhite
          Memo.UTF8W = (
            '[frxLessonResult."lessonName"]')
          ParentFont = False
          VAlign = vaCenter
        end
        object Memo15: TfrxMemoView
          IndexTag = 1
          AllowVectorExport = True
          Left = 457.323130000000000000
          Top = 11.338590000000000000
          Width = 192.756030000000000000
          Height = 18.897650000000000000
          DataField = 'date'
          DataSet = frxLessonResult
          DataSetName = 'frxLessonResult'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Color = clWhite
          Frame.Typ = []
          Fill.ForeColor = clWhite
          Memo.UTF8W = (
            '[frxLessonResult."date"]')
          ParentFont = False
          VAlign = vaCenter
        end
        object Memo16: TfrxMemoView
          AllowVectorExport = True
          Left = 355.275820000000000000
          Top = 11.338590000000000000
          Width = 94.488188980000000000
          Height = 18.897650000000000000
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Color = clWhite
          Frame.Typ = []
          Fill.ForeColor = clWhite
          Memo.UTF8W = (
            'Date:')
          ParentFont = False
          VAlign = vaCenter
        end
        object Memo17: TfrxMemoView
          AllowVectorExport = True
          Left = 37.795300000000000000
          Top = 41.574830000000000000
          Width = 94.488250000000000000
          Height = 18.897650000000000000
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Color = clWhite
          Frame.Typ = []
          Fill.ForeColor = clWhite
          Memo.UTF8W = (
            'Goal:')
          ParentFont = False
          VAlign = vaCenter
        end
        object Memo18: TfrxMemoView
          IndexTag = 1
          AllowVectorExport = True
          Left = 139.842610000000000000
          Top = 41.574830000000000000
          Width = 192.756030000000000000
          Height = 18.897650000000000000
          DataField = 'lessonGoal'
          DataSet = frxLessonResult
          DataSetName = 'frxLessonResult'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clGray
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Color = clWhite
          Frame.Typ = []
          Fill.ForeColor = clWhite
          Memo.UTF8W = (
            '[frxLessonResult."lessonGoal"]')
          ParentFont = False
          VAlign = vaCenter
        end
        object Memo19: TfrxMemoView
          AllowVectorExport = True
          Left = 37.795300000000000000
          Top = 64.252010000000000000
          Width = 94.488250000000000000
          Height = 18.897650000000000000
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Color = clWhite
          Frame.Typ = []
          Fill.ForeColor = clWhite
          Memo.UTF8W = (
            'Speed:')
          ParentFont = False
          VAlign = vaCenter
        end
        object Memo20: TfrxMemoView
          IndexTag = 1
          AllowVectorExport = True
          Left = 139.842610000000000000
          Top = 64.252010000000000000
          Width = 192.756030000000000000
          Height = 18.897650000000000000
          DataField = 'speed'
          DataSet = frxLessonResult
          DataSetName = 'frxLessonResult'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clGray
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Color = clWhite
          Frame.Typ = []
          Fill.ForeColor = clWhite
          Memo.UTF8W = (
            '[frxLessonResult."speed"]')
          ParentFont = False
          VAlign = vaCenter
        end
        object Memo21: TfrxMemoView
          AllowVectorExport = True
          Left = 355.275820000000000000
          Top = 64.252010000000000000
          Width = 94.488250000000000000
          Height = 18.897650000000000000
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Color = clWhite
          Frame.Typ = []
          Fill.ForeColor = clWhite
          Memo.UTF8W = (
            'Accuracy:')
          ParentFont = False
          VAlign = vaCenter
        end
        object Memo22: TfrxMemoView
          IndexTag = 1
          AllowVectorExport = True
          Left = 457.323130000000000000
          Top = 64.252010000000000000
          Width = 192.756030000000000000
          Height = 18.897650000000000000
          DataField = 'accuracy'
          DataSet = frxLessonResult
          DataSetName = 'frxLessonResult'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clGray
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Color = clWhite
          Frame.Typ = []
          Fill.ForeColor = clWhite
          Memo.UTF8W = (
            '[frxLessonResult."accuracy"]')
          ParentFont = False
          VAlign = vaCenter
        end
        object Memo24: TfrxMemoView
          IndexTag = 1
          AllowVectorExport = True
          Left = 457.323130000000000000
          Top = 41.574830000000000000
          Width = 230.551330000000000000
          Height = 18.897650000000000000
          DataField = 'lessonGoalValue'
          DataSet = frxLessonResult
          DataSetName = 'frxLessonResult'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clGray
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Color = clWhite
          Frame.Typ = []
          Fill.ForeColor = clWhite
          Memo.UTF8W = (
            '[frxLessonResult."lessonGoalValue"]')
          ParentFont = False
          VAlign = vaCenter
        end
        object Memo13: TfrxMemoView
          AllowVectorExport = True
          Left = 37.795300000000000000
          Top = 86.929190000000000000
          Width = 94.488250000000000000
          Height = 18.897650000000000000
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Color = clWhite
          Frame.Typ = []
          Fill.ForeColor = clWhite
          Memo.UTF8W = (
            'Result:')
          ParentFont = False
          VAlign = vaCenter
        end
        object Memo14: TfrxMemoView
          IndexTag = 1
          AllowVectorExport = True
          Left = 139.842610000000000000
          Top = 86.929190000000000000
          Width = 192.756030000000000000
          Height = 18.897650000000000000
          DataField = 'result'
          DataSet = frxLessonResult
          DataSetName = 'frxLessonResult'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clGray
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Color = clWhite
          Frame.Typ = []
          Fill.ForeColor = clWhite
          Memo.UTF8W = (
            '[frxLessonResult."result"]')
          ParentFont = False
          VAlign = vaCenter
        end
        object Memo23: TfrxMemoView
          AllowVectorExport = True
          Left = 355.275820000000000000
          Top = 41.574830000000000000
          Width = 94.488250000000000000
          Height = 18.897650000000000000
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Color = clWhite
          Frame.Typ = []
          Fill.ForeColor = clWhite
          Memo.UTF8W = (
            'Goal value:')
          ParentFont = False
          VAlign = vaCenter
        end
        object Memo25: TfrxMemoView
          AllowVectorExport = True
          Left = 355.275820000000000000
          Top = 86.929190000000000000
          Width = 94.488250000000000000
          Height = 18.897650000000000000
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Color = clWhite
          Frame.Typ = []
          Fill.ForeColor = clWhite
          Memo.UTF8W = (
            'Duration:')
          ParentFont = False
          VAlign = vaCenter
        end
        object Memo26: TfrxMemoView
          IndexTag = 1
          AllowVectorExport = True
          Left = 457.323130000000000000
          Top = 86.929190000000000000
          Width = 207.874150000000000000
          Height = 18.897650000000000000
          DataField = 'durationHMS'
          DataSet = frxLessonResult
          DataSetName = 'frxLessonResult'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clGray
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Color = clWhite
          Frame.Typ = []
          Fill.ForeColor = clWhite
          Memo.UTF8W = (
            '[frxLessonResult."durationHMS"]')
          ParentFont = False
          VAlign = vaCenter
        end
      end
    end
  end
  object frxUser: TfrxDBDataset
    UserName = 'frxUser'
    CloseDataSource = False
    DataSet = DataModule1.TUsers
    BCDToCurrency = False
    DataSetOptions = []
    Left = 93
    Top = 369
  end
  object frxLessonResult: TfrxDBDataset
    UserName = 'frxLessonResult'
    CloseDataSource = False
    DataSet = DataModule1.TLessonResults
    BCDToCurrency = False
    DataSetOptions = []
    Left = 177
    Top = 369
  end
  object frxPDFExport: TfrxPDFExport
    UseFileCache = True
    ShowProgress = True
    OverwritePrompt = False
    DataOnly = False
    EmbedFontsIfProtected = False
    InteractiveFormsFontSubset = 'A-Z,a-z,0-9,#43-#47 '
    OpenAfterExport = False
    PrintOptimized = False
    Outline = False
    Background = False
    HTMLTags = True
    Quality = 95
    Author = 'FastReport'
    Subject = 'FastReport PDF export'
    Creator = 'FastReport'
    ProtectionFlags = [ePrint, eModify, eCopy, eAnnot]
    HideToolbar = False
    HideMenubar = False
    HideWindowUI = False
    FitWindow = False
    CenterWindow = False
    PrintScaling = False
    PdfA = False
    PDFStandard = psNone
    PDFVersion = pv17
    Left = 441
    Top = 240
  end
  object frxRTFExport: TfrxRTFExport
    UseFileCache = True
    ShowProgress = True
    OverwritePrompt = False
    DataOnly = False
    PictureType = gpPNG
    OpenAfterExport = False
    Wysiwyg = True
    Creator = 'FastReport'
    SuppressPageHeadersFooters = False
    HeaderFooterMode = hfText
    AutoSize = False
    Left = 441
    Top = 306
  end
end
