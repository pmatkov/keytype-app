object DataModule1: TDataModule1
  Height = 480
  Width = 640
  object MySQLDBConnection: TFDConnection
    Params.Strings = (
      'Database=keytype'
      'User_Name=root'
      'Password=12345'
      'Server=127.0.0.1'
      'DriverID=MySQL')
    Left = 270
    Top = 171
  end
end
