object WebModule1: TWebModule1
  Actions = <
    item
      Default = True
      Name = 'DefaultHandler'
      PathInfo = '/'
      OnAction = WebModule1DefaultHandlerAction
    end
    item
      MethodType = mtGet
      Name = 'keymapGET'
      PathInfo = '/keymap'
      OnAction = WebModule1keymapGETAction
    end
    item
      MethodType = mtGet
      Name = 'customtextGET'
      PathInfo = '/customtext'
      OnAction = WebModule1customtextGETAction
    end
    item
      MethodType = mtPost
      Name = 'customtextPOST'
      PathInfo = '/customtext'
      OnAction = WebModule1customtextPOSTAction
    end
    item
      MethodType = mtPut
      Name = 'customtextPUT'
      PathInfo = '/customtext'
      OnAction = WebModule1customtextPUTAction
    end>
  BeforeDispatch = WebModuleBeforeDispatch
  Height = 230
  Width = 415
  object MySQLDBConnection: TFDConnection
    Params.Strings = (
      'Database=keytype'
      'User_Name=root'
      'Password=12345'
      'Server=127.0.0.1'
      'DriverID=MySQL')
    Left = 159
    Top = 81
  end
  object TKeyMapping: TFDTable
    IndexFieldNames = 'id'
    Connection = MySQLDBConnection
    ResourceOptions.AssignedValues = [rvEscapeExpand]
    TableName = 'keymapping'
    Left = 264
    Top = 63
    object TKeyMappingid: TFDAutoIncField
      FieldName = 'id'
      Origin = 'id'
      ProviderFlags = [pfInWhere, pfInKey]
      ReadOnly = True
    end
    object TKeyMappingidRow: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'idRow'
      Origin = 'idRow'
    end
    object TKeyMappingidCol: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'idCol'
      Origin = 'idCol'
    end
    object TKeyMappingkeyValue: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'keyValue'
      Origin = 'keyValue'
      FixedChar = True
    end
  end
  object DKeyMapping: TDataSource
    DataSet = TKeyMapping
    Left = 264
    Top = 126
  end
end
