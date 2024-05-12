object DataModule2: TDataModule2
  Height = 480
  Width = 640
  object IdTCPServer: TIdTCPServer
    Bindings = <
      item
        IP = '0.0.0.0'
        Port = 6001
      end>
    DefaultPort = 6001
    OnConnect = IdTCPServerConnect
    OnDisconnect = IdTCPServerDisconnect
    OnExecute = IdTCPServerExecute
    Left = 315
    Top = 270
  end
end
